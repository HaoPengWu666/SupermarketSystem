#include "inventory_widget.h"
#include "databasemanager.h"
#include "logindialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QTableView>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QJsonArray>
#include <QFormLayout>
#include <QJsonObject>

inventory_widget::inventory_widget(QWidget *parent) :
    QWidget(parent),  // 初始化成员
    m_inventory_page(nullptr)
{
    m_inventory_model=new QStandardItemModel(this);
    m_warning_model=new QSqlQueryModel(this);
}

inventory_widget::~inventory_widget()
{
    // 清理资源
    if (m_inventory_model) m_inventory_model->deleteLater();
    if (m_warning_model) m_warning_model->deleteLater();
}

void inventory_widget::set_inventory_page(QWidget *page_inventory)
{
    if (!page_inventory) {
        qWarning() << "inventory_widget: Invalid page_inventory pointer";
        return;
    }

    m_inventory_page = page_inventory;
    setup_models();
    setup_connections();
    setup_filters();

    // 设置表格模型
    auto *tblInventory = m_inventory_page->findChild<QTableView*>("tblInventory_in");
    auto *tblWarning = m_inventory_page->findChild<QTableView*>("tblWarning_in");

    if (tblInventory) tblInventory->setModel(m_inventory_model);
    if (tblWarning) tblWarning->setModel(m_warning_model);

    // 初始加载数据
    refresh();
}

void inventory_widget::refresh()
{
    // 清空搜索框
    auto *txtSearch = m_inventory_page->findChild<QLineEdit*>("txtSearch_in");
    if (txtSearch) txtSearch->clear();

    // 重置筛选器
    auto *cmbStockStatus = m_inventory_page->findChild<QComboBox*>("cmbStockStatus_in");
    auto *cmbSupplier = m_inventory_page->findChild<QComboBox*>("cmbSupplier_in");
    if (cmbStockStatus) cmbStockStatus->setCurrentIndex(0);
    if (cmbSupplier) cmbSupplier->setCurrentIndex(0);

    // 重新加载数据
    load_inventory_data();
    load_warning_data();
}

void inventory_widget::setup_models()
{
    // 主库存表格模型
    m_inventory_model->setHorizontalHeaderLabels(
        {"商品条码", "商品名称", "规格", "零售价", "库存量", "供应商"});

    // 预警表格模型 (使用SQL查询模型)
    m_warning_model->setQuery("SELECT * FROM 库存预警视图");
}

void inventory_widget::setup_connections()
{
    // 搜索按钮
    auto *btnSearch = m_inventory_page->findChild<QPushButton*>("btnSearch_in");
    if (btnSearch) {
        connect(btnSearch, &QPushButton::clicked, this, &inventory_widget::on_search_inventory);
    }

    // 搜索框回车键
    auto *txtSearch = m_inventory_page->findChild<QLineEdit*>("txtSearch_in");
    if (txtSearch) {
        connect(txtSearch, &QLineEdit::returnPressed, this, &inventory_widget::on_search_inventory);
    }

    // 库存状态筛选
    auto *cmbStockStatus = m_inventory_page->findChild<QComboBox*>("cmbStockStatus_in");
    if (cmbStockStatus) {
        connect(cmbStockStatus, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &inventory_widget::on_stock_status_filter_changed);
    }

    // 供应商筛选
    auto *cmbSupplier = m_inventory_page->findChild<QComboBox*>("cmbSupplier_in");
    if (cmbSupplier) {
        connect(cmbSupplier, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &inventory_widget::on_supplier_filter_changed);
    }

    // 操作按钮
    auto *btnStockIn = m_inventory_page->findChild<QPushButton*>("btnStockIn_in");
    auto *btnEdit = m_inventory_page->findChild<QPushButton*>("btnEditProduct_in");
    auto *btnDelete = m_inventory_page->findChild<QPushButton*>("btnDeleteProduct_in");
    auto *btnAdd = m_inventory_page->findChild<QPushButton*>("btnAddProduct_in");
    auto *btnRefresh = m_inventory_page->findChild<QPushButton*>("btnRefresh_in");

    if (btnStockIn) connect(btnStockIn, &QPushButton::clicked, this, &inventory_widget::on_stock_in_clicked);
    if (btnEdit) connect(btnEdit, &QPushButton::clicked, this, &inventory_widget::on_edit_product_clicked);
    if (btnDelete) connect(btnDelete, &QPushButton::clicked, this, &inventory_widget::on_delete_product_clicked);
    if (btnAdd) connect(btnAdd, &QPushButton::clicked, this, &inventory_widget::on_add_product_clicked);
    if (btnRefresh) connect(btnRefresh, &QPushButton::clicked, this, &inventory_widget::on_refresh_clicked);
}

void inventory_widget::setup_filters()
{
    // 初始化库存状态筛选器
    auto *cmbStockStatus = m_inventory_page->findChild<QComboBox*>("cmbStockStatus_in");
    if (cmbStockStatus) {
        cmbStockStatus->clear();
        cmbStockStatus->addItem("所有库存状态", 0);
        cmbStockStatus->addItem("红色预警(库存≤10)", 1);
        cmbStockStatus->addItem("黄色预警(库存≤20)", 2);
        cmbStockStatus->addItem("库存充足(库存>20)", 3);
    }

    // 初始化供应商筛选器
    auto *cmbSupplier = m_inventory_page->findChild<QComboBox*>("cmbSupplier_in");
    if (cmbSupplier) {
        cmbSupplier->clear();
        cmbSupplier->addItem("所有供应商", 0);

        QSqlQuery query("SELECT 供应商ID, 名称 FROM 供应商表 ORDER BY 名称");
        while (query.next()) {
            cmbSupplier->addItem(query.value(1).toString(), query.value(0).toInt());
        }
    }
}


void inventory_widget::load_inventory_data()
{
    QString sql = "SELECT p.商品条码, p.商品名称, p.规格, p.零售价, p.库存数量, "
                  "IFNULL(s.名称, '无') AS 供应商名称 "
                  "FROM 商品表 p LEFT JOIN 供应商表 s ON p.供应商ID = s.供应商ID WHERE 1=1";

    // 获取筛选条件
    auto *cmbStockStatus = m_inventory_page->findChild<QComboBox*>("cmbStockStatus_in");
    auto *cmbSupplier = m_inventory_page->findChild<QComboBox*>("cmbSupplier_in");

    // 库存状态筛选
    if (cmbStockStatus && cmbStockStatus->currentIndex() > 0) {
        switch (cmbStockStatus->currentIndex()) {
        case 1: sql += " AND p.库存数量 <= 10"; break;  // 红色预警
        case 2: sql += " AND p.库存数量 <= 20"; break; // 黄色预警
        }
    }

    // 供应商筛选
    if (cmbSupplier && cmbSupplier->currentIndex() > 0) {
        int supplierId = cmbSupplier->currentData().toInt();
        sql += QString(" AND p.供应商ID = %1").arg(supplierId);
    }

    sql += " ORDER BY p.库存数量 ASC";

    QSqlQuery query;
    if (!query.exec(sql)) {
        QMessageBox::critical(this, "错误", "加载库存数据失败: " + query.lastError().text());
        return;
    }

    m_inventory_model->removeRows(0, m_inventory_model->rowCount());

    while (query.next()) {
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(query.value(0).toString());
        rowItems << new QStandardItem(query.value(1).toString());
        rowItems << new QStandardItem(query.value(2).toString());
        rowItems << new QStandardItem(QString::number(query.value(3).toDouble(), 'f', 2));
        rowItems << new QStandardItem(query.value(4).toString());
        rowItems << new QStandardItem(query.value(5).toString());
        m_inventory_model->appendRow(rowItems);
    }
}


void inventory_widget::load_warning_data()
{
    if (!m_warning_model) return;

    QString sql = "SELECT * FROM 库存预警视图 WHERE 1=1";

    // 获取库存状态筛选条件
    auto *cmbStockStatus = m_inventory_page->findChild<QComboBox*>("cmbStockStatus_in");
    if (cmbStockStatus && cmbStockStatus->currentIndex() > 0) {
        switch (cmbStockStatus->currentIndex()) {
        case 1: sql += " AND 预警级别 = '红色预警'"; break;
        case 2: sql += " AND 预警级别 = '黄色预警'"; break;
        case 3: sql += " AND 预警级别 NOT IN ('红色预警', '黄色预警')"; break;
        }
    }

    sql += " ORDER BY 库存数量 ASC";

    m_warning_model->setQuery(sql);
    if (m_warning_model->lastError().isValid()) {
        QMessageBox::critical(this, "错误", "加载预警数据失败: " + m_warning_model->lastError().text());
    }
}

void inventory_widget::on_search_inventory()
{
    auto *txtSearch = m_inventory_page->findChild<QLineEdit*>("txtSearch_in");
    QString keyword = txtSearch ? txtSearch->text().trimmed() : "";

    if (keyword.isEmpty()) {
        load_inventory_data();
        return;
    }

    QString sql = "SELECT p.商品条码, p.商品名称, p.规格, p.零售价, p.库存数量, "
                  "IFNULL(s.名称, '无') AS 供应商名称 "
                  "FROM 商品表 p LEFT JOIN 供应商表 s ON p.供应商ID = s.供应商ID "
                  "WHERE p.商品名称 LIKE :keyword OR p.商品条码 LIKE :keyword";

    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":keyword", "%" + keyword + "%");

    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "搜索失败: " + query.lastError().text());
        return;
    }

    m_inventory_model->removeRows(0, m_inventory_model->rowCount());

    bool hasResults = false;
    while (query.next()) {
        hasResults = true;
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(query.value(0).toString());
        rowItems << new QStandardItem(query.value(1).toString());
        rowItems << new QStandardItem(query.value(2).toString());
        rowItems << new QStandardItem(QString::number(query.value(3).toDouble(), 'f', 2));
        rowItems << new QStandardItem(query.value(4).toString());
        rowItems << new QStandardItem(query.value(5).toString());
        m_inventory_model->appendRow(rowItems);
    }

    if (!hasResults) {
        QMessageBox::information(this, "提示", "未找到匹配的商品");
    }
}

void inventory_widget::on_stock_status_filter_changed(int index)
{
    Q_UNUSED(index);
    load_inventory_data();
    load_warning_data();
}

void inventory_widget::on_supplier_filter_changed(int index)
{
    Q_UNUSED(index);
    load_inventory_data();
}

void inventory_widget::on_stock_in_clicked()
{
    // 创建进货对话框
    QDialog dialog(this);
    dialog.setWindowTitle("商品进货");
    dialog.setMinimumSize(800, 600); // 设置合适的大小

    // 设置对话框布局
    QFormLayout layout(&dialog);

    // 供应商选择
    QComboBox cmbSupplier;
    // cmbSupplier.addItem("所有供应商", 0); // 默认选项
    QSqlQuery supplierQuery("SELECT 供应商ID, 名称 FROM 供应商表 ORDER BY 名称");
    while (supplierQuery.next()) {
        cmbSupplier.addItem(supplierQuery.value(1).toString(), supplierQuery.value(0).toInt());
    }
    layout.addRow("供应商:", &cmbSupplier);

    // 商品表格
    QTableView tblProducts;
    tblProducts.setSelectionBehavior(QAbstractItemView::SelectRows);
    tblProducts.setSelectionMode(QAbstractItemView::SingleSelection);

    QStandardItemModel *productModel = new QStandardItemModel(&dialog); // 使用指针，避免局部变量销毁
    productModel->setHorizontalHeaderLabels({"选择", "商品条码", "商品名称", "规格", "当前库存", "进货数量", "进价"});
    tblProducts.setModel(productModel);

    // 加载所有商品数据（初始状态）
    auto loadProducts = [&](int supplierId = 0) {
        productModel->removeRows(0, productModel->rowCount()); // 清空现有数据

        QString sql = "SELECT 商品条码, 商品名称, 规格, 库存数量 FROM 商品表";
        if (supplierId > 0) {
            sql += " WHERE 供应商ID = :supplierId";
        }
        sql += " ORDER BY 商品名称";

        QSqlQuery query;
        query.prepare(sql);
        if (supplierId > 0) {
            query.bindValue(":supplierId", supplierId);
        }

        if (!query.exec()) {
            QMessageBox::critical(&dialog, "错误", "加载商品失败: " + query.lastError().text());
            return;
        }

        while (query.next()) {
            QList<QStandardItem*> rowItems;

            // 选择复选框
            QStandardItem* checkItem = new QStandardItem();
            checkItem->setCheckable(true);
            checkItem->setCheckState(Qt::Unchecked);
            rowItems << checkItem;

            rowItems << new QStandardItem(query.value(0).toString());
            rowItems << new QStandardItem(query.value(1).toString());
            rowItems << new QStandardItem(query.value(2).toString());
            rowItems << new QStandardItem(query.value(3).toString());
            rowItems << new QStandardItem("0"); // 进货数量初始为0
            rowItems << new QStandardItem("0.00"); // 进价初始为0

            productModel->appendRow(rowItems);
        }
    };

    // 初始加载所有商品
    loadProducts();

    // 供应商选择变化时，过滤商品
    connect(&cmbSupplier, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index) {
        int supplierId = cmbSupplier.itemData(index).toInt();
        loadProducts(supplierId); // 重新加载对应供应商的商品
    });

    // 添加到布局
    layout.addRow(&tblProducts);

    // 按钮
    QDialogButtonBox buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout.addRow(&buttons);

    // 连接信号槽
    connect(&buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // 显示对话框
    if (dialog.exec() == QDialog::Accepted) {
        // 准备进货数据
        QJsonArray itemsArray;
        int supplierId = cmbSupplier.currentData().toInt();

        for (int row = 0; row < productModel->rowCount(); ++row) {
            if (productModel->item(row, 0)->checkState() == Qt::Checked) {
                QString barcode = productModel->item(row, 1)->text();
                QString name = productModel->item(row, 2)->text();
                QString size = productModel->item(row, 3)->text();
                int quantity = productModel->item(row, 5)->text().toInt();
                double price = productModel->item(row, 6)->text().toDouble();

                if (quantity > 0 && price > 0) {
                    QJsonObject itemObj;
                    itemObj["条码"] = barcode;
                    itemObj["名称"] = name;
                    itemObj["规格"] = size;
                    itemObj["进价"] = price;
                    itemObj["零售价"] = price*1.2;
                    itemObj["数量"] = quantity;

                    itemsArray.append(itemObj);
                }
            }
        }

        if (itemsArray.isEmpty()) {
            QMessageBox::warning(this, "警告", "请至少选择一种商品并设置有效的进货数量和进价");
            return;
        }

        // 调用存储过程处理进货
        QJsonDocument doc(itemsArray);
        QString jsonStr = doc.toJson(QJsonDocument::Compact);

        qDebug() << "准备传入的JSON数据:" << jsonStr;

        QSqlDatabase db = DatabaseManager::instance().database();
        if (!db.transaction()) {
            QMessageBox::critical(this, "错误", "无法开始进货事务: " + db.lastError().text());
            return;
        }

        QSqlQuery query(db);
        query.prepare("CALL 处理进货(?, ?, ?)");
        int userId = DatabaseManager::instance().currentUserId();
        if(userId <= 0) {
            db.rollback();
            QMessageBox::critical(this, "错误", "无效的用户ID，请重新登录");
            return;
        }
        query.bindValue(0, userId);
        if(supplierId <= 0) {
            db.rollback();
            QMessageBox::critical(this, "错误", "请选择有效的供应商");
            return;
        }
        query.bindValue(1, supplierId);
        query.bindValue(2, jsonStr);

        if (!query.exec()) {
            const QString errorText = query.lastError().text();
            query.finish();
            db.rollback();
            QMessageBox::critical(this, "错误", "进货失败: " + errorText);
            return;
        }

        int stockInId = -1;
        double total = 0.0;
        bool resultFound = false;

        do {
            const QSqlRecord record = query.record();
            const int stockInIdColumn = record.indexOf("进货单号");
            const int totalColumn = record.indexOf("总金额");

            while (query.next()) {
                if (!resultFound && stockInIdColumn >= 0 && totalColumn >= 0) {
                    stockInId = query.value(stockInIdColumn).toInt();
                    total = query.value(totalColumn).toDouble();
                    resultFound = true;
                }
            }
        } while (query.nextResult());

        const QString resultError = query.lastError().text();
        query.finish();

        if (!resultFound || stockInId <= 0) {
            db.rollback();
            QMessageBox::critical(this, "错误",
                                  QString("进货过程未返回有效进货单号") +
                                      (resultError.isEmpty() ? QString() : QString(": ") + resultError));
            return;
        }

        if (!db.commit()) {
            const QString errorText = db.lastError().text();
            db.rollback();
            QMessageBox::critical(this, "错误", "进货事务提交失败: " + errorText);
            return;
        }

        QMessageBox::information(this, "成功",
                                 QString("进货操作已完成\n进货单号: %1\n总金额: %2")
                                     .arg(stockInId).arg(total));
        refresh();
    }
}

void inventory_widget::on_edit_product_clicked()
{
    // 获取当前选中的商品
    auto *tblInventory = m_inventory_page->findChild<QTableView*>("tblInventory_in");
    if (!tblInventory) return;

    QModelIndexList selected = tblInventory->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择要编辑的商品");
        return;
    }

    QString barcode = m_inventory_model->item(selected.first().row(), 0)->text();
    show_product_dialog(true, barcode);
}

void inventory_widget::on_delete_product_clicked()
{
    auto *tblInventory = m_inventory_page->findChild<QTableView*>("tblInventory_in");
    if (!tblInventory || !tblInventory->selectionModel()) return;

    const QModelIndexList selected = tblInventory->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择要删除的商品");
        return;
    }

    const int row = selected.first().row();
    const QString barcode = m_inventory_model->item(row, 0)->text();
    const QString productName = m_inventory_model->item(row, 1)->text();
    const auto answer = QMessageBox::question(
        this,
        "确认删除商品",
        QString("确定要删除商品“%1”（条码：%2）吗？\n此操作不可撤销。")
            .arg(productName, barcode),
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No);
    if (answer != QMessageBox::Yes) return;

    QSqlQuery query;
    query.prepare("CALL 删除商品(?)");
    query.addBindValue(barcode);
    if (!query.exec()) {
        QMessageBox::critical(this, "删除失败", query.lastError().text());
        return;
    }
    do {
        while (query.next()) {}
    } while (query.nextResult());

    QMessageBox::information(this, "删除成功", "商品已删除");
    refresh();
}

void inventory_widget::on_add_product_clicked()
{
    show_product_dialog(false);
}

void inventory_widget::show_product_dialog(bool isEditMode, const QString& barcode)
{
    QDialog dialog(this);
    dialog.setWindowTitle(isEditMode ? "编辑商品" : "新增商品");
    dialog.setFixedSize(500, 400);

    QFormLayout layout(&dialog);

    // 商品条码（新增时可编辑，编辑时不可编辑）
    QLineEdit txtBarcode;
    txtBarcode.setEnabled(!isEditMode);
    if (isEditMode) txtBarcode.setText(barcode);
    layout.addRow("商品条码:", &txtBarcode);

    // 商品名称
    QLineEdit txtName;
    layout.addRow("商品名称:", &txtName);

    // 规格
    QLineEdit txtSpec;
    layout.addRow("规格:", &txtSpec);

    // 零售价
    QLineEdit txtPrice;
    txtPrice.setValidator(new QDoubleValidator(0.01, 9999.99, 2, &txtPrice));    //用于限制用户输入的内容必须符合特定的数值格式，2：小数位数，表示最多允许2位小数
    layout.addRow("零售价:", &txtPrice);

    // 成本价
    QLineEdit txtCost;
    txtCost.setValidator(new QDoubleValidator(0.01, 9999.99, 2, &txtCost));
    layout.addRow("成本价:", &txtCost);

    // 供应商
    QComboBox cmbSupplier;
    cmbSupplier.addItem("无供应商", 0);
    QSqlQuery query("SELECT 供应商ID, 名称 FROM 供应商表 ORDER BY 名称");
    while (query.next()) {
        cmbSupplier.addItem(query.value(1).toString(), query.value(0).toInt());
    }
    layout.addRow("供应商:", &cmbSupplier);

    // 如果是编辑模式，加载现有数据
    if (isEditMode) {
        QSqlQuery query;
        query.prepare("SELECT 商品名称, 规格, 零售价, 成本价, 供应商ID FROM 商品表 WHERE 商品条码 = ?");
        query.addBindValue(barcode);
        if (query.exec() && query.next()) {
            txtName.setText(query.value(0).toString());
            txtSpec.setText(query.value(1).toString());
            txtPrice.setText(QString::number(query.value(2).toDouble(), 'f', 2));
            txtCost.setText(QString::number(query.value(3).toDouble(), 'f', 2));

            int supplierIdx = cmbSupplier.findData(query.value(4).toInt());
            if (supplierIdx >= 0) cmbSupplier.setCurrentIndex(supplierIdx);
        }
    }

    QDialogButtonBox buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout.addRow(&buttons);

    connect(&buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        // 验证数据
        if (!validate_product_data(txtName.text(), txtPrice.text(), txtCost.text())) {
            return;
        }

        // 准备SQL
        QSqlQuery query;
        if (isEditMode) {
            query.prepare("UPDATE 商品表 SET 商品名称=?, 规格=?, 零售价=?, 成本价=?, 供应商ID=? WHERE 商品条码=?");
            query.addBindValue(txtName.text());
            query.addBindValue(txtSpec.text());
            query.addBindValue(txtPrice.text().toDouble());
            query.addBindValue(txtCost.text().toDouble());
            query.addBindValue(cmbSupplier.currentData().toInt() > 0 ? cmbSupplier.currentData() : QVariant());
            query.addBindValue(barcode);
        } else {
            query.prepare("INSERT INTO 商品表 (商品条码, 商品名称, 规格, 零售价, 成本价, 供应商ID) "
                          "VALUES (?, ?, ?, ?, ?, ?)");
            query.addBindValue(txtBarcode.text());
            query.addBindValue(txtName.text());
            query.addBindValue(txtSpec.text());
            query.addBindValue(txtPrice.text().toDouble());
            query.addBindValue(txtCost.text().toDouble());
            query.addBindValue(cmbSupplier.currentData().toInt() > 0 ? cmbSupplier.currentData() : QVariant());
        }

        if (query.exec()) {
            QMessageBox::information(this, "成功", isEditMode ? "商品信息已更新" : "商品已添加");
            refresh(); // 刷新列表
        } else {
            QMessageBox::critical(this, "错误", "操作失败: " + query.lastError().text());
        }
    }
}

bool inventory_widget::validate_product_data(const QString& name, const QString& price, const QString& cost)
{
    if (name.isEmpty()) {
        QMessageBox::warning(this, "警告", "商品名称不能为空");
        return false;
    }

    if (price.toDouble() <= 0) {
        QMessageBox::warning(this, "警告", "零售价必须大于0");
        return false;
    }

    if (cost.toDouble() <= 0) {
        QMessageBox::warning(this, "警告", "成本价必须大于0");
        return false;
    }

    if (price.toDouble() < cost.toDouble()) {
        QMessageBox::warning(this, "警告", "零售价不能低于成本价");
        return false;
    }

    return true;
}

void inventory_widget::on_refresh_clicked()
{
    refresh();
}
