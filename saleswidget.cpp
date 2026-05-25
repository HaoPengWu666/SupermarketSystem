#include "saleswidget.h"
#include "ui_mainwindow.h"  // 关键：包含 MainWindow 的 UI 头文件
#include "mainwindow.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

SalesWidget::SalesWidget(QWidget *parent) :
    QWidget(parent),
    m_salesPage(nullptr)
{

    // 初始化模型
    m_productModel = new QStandardItemModel(this);
    m_cartModel = new QStandardItemModel(this);

}

SalesWidget::~SalesWidget()
{

}

void SalesWidget::setSalesPage(QWidget *page_sales) {
    if (!page_sales) {
        qWarning() << "SalesWidget: Invalid page_sales pointer";
        return;
    }

    m_salesPage = page_sales;

    setupModels();
    setupConnections();

    // 初始化模型（假设 page_sales 里有 tblProducts 和 tblCart）
    auto *tblProducts = m_salesPage->findChild<QTableView*>("tblProducts");
    auto *tblCart = m_salesPage->findChild<QTableView*>("tblCart");

    if (tblProducts && tblCart) {
        tblProducts->setModel(m_productModel);
        tblCart->setModel(m_cartModel);
    }

    // 设置表头
    m_productModel->setHorizontalHeaderLabels({"条码", "名称", "规格", "单价", "库存"});
    m_cartModel->setHorizontalHeaderLabels({"条码", "名称", "单价", "数量", "小计"});

}


void SalesWidget::refresh()
{
    // 使用 findChild 获取 txtSearch
    auto *txtSearch = m_salesPage->findChild<QLineEdit*>("txtSearch");
    if (txtSearch) {
        txtSearch->clear();
    }

    // 商品列表加载所有商品
    loadAllProducts();

     // 清空购物车
    m_cartModel->clear();
    setupModels();
    // 同样处理 lblTotal
    auto *lblTotal = m_salesPage->findChild<QLabel*>("lblTotal");
    if (lblTotal) {
        lblTotal->setText("0.00");
    }

    // 处理 chkMember
    auto *chkMember = m_salesPage->findChild<QCheckBox*>("chkMember");
    if (chkMember) {
        chkMember->setChecked(false);
    }

    // 处理 txtMemberId 和 txtMemberName
    auto *txtMemberId = m_salesPage->findChild<QLineEdit*>("txtMemberId");
    auto *txtMemberName = m_salesPage->findChild<QLineEdit*>("txtMemberName");
    if (txtMemberId) txtMemberId->clear();
    if (txtMemberName) txtMemberName->clear();
}

void SalesWidget::setupModels()
{
    // 商品列表模型
    m_productModel->setHorizontalHeaderLabels({"条码", "名称", "规格", "单价", "库存"});
    auto *tblProducts = m_salesPage->findChild<QTableView*>("tblProducts");
    if (tblProducts) {
        tblProducts->setModel(m_productModel);
    }

    // 购物车模型
    m_cartModel->setHorizontalHeaderLabels({"条码", "名称", "单价", "数量", "小计"});
    auto *tblCart = m_salesPage->findChild<QTableView*>("tblCart");
    if (tblCart) {
        tblCart->setModel(m_cartModel);
    }

    // 初始化时加载所有商品
    loadAllProducts();
}

void SalesWidget::loadAllProducts()
{
    QSqlQuery query;
    query.prepare("SELECT 商品条码, 商品名称, 规格, 零售价, 库存数量 FROM 商品表");

    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "加载商品失败: " + query.lastError().text());
        return;
    }

    m_productModel->removeRows(0, m_productModel->rowCount());

    while (query.next()) {
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(query.value(0).toString());
        rowItems << new QStandardItem(query.value(1).toString());
        rowItems << new QStandardItem(query.value(2).toString());
        rowItems << new QStandardItem(QString::number(query.value(3).toDouble(), 'f', 2));
        rowItems << new QStandardItem(query.value(4).toString());
        m_productModel->appendRow(rowItems);
    }
}

void SalesWidget::setupConnections()
{
    auto *btnSearch = m_salesPage->findChild<QPushButton*>("btnSearch");
    auto *btnAdd = m_salesPage->findChild<QPushButton*>("btnAdd");
    auto *btnRemove = m_salesPage->findChild<QPushButton*>("btnRemove");
    auto *btnCheckout = m_salesPage->findChild<QPushButton*>("btnCheckout");
    auto *chkMember = m_salesPage->findChild<QCheckBox*>("chkMember");

    if (btnSearch) {
        connect(btnSearch, &QPushButton::clicked, this, &SalesWidget::onSearchProduct);
    }
    if (btnAdd) {
        connect(btnAdd, &QPushButton::clicked, this, &SalesWidget::onAddToCart);
    }
    if (btnRemove) {
        connect(btnRemove, &QPushButton::clicked, this, &SalesWidget::onRemoveFromCart);
    }
    if (btnCheckout) {
        connect(btnCheckout, &QPushButton::clicked, this, &SalesWidget::onCheckout);
    }
    if (chkMember) {
        connect(chkMember, &QCheckBox::toggled, this, &SalesWidget::onMemberChecked);
    }


    auto *txtSearch = m_salesPage->findChild<QLineEdit*>("txtSearch");
    if (txtSearch) {
        // 回车键触发搜索
        connect(txtSearch, &QLineEdit::returnPressed, this, &SalesWidget::onSearchProduct);

        // 文本变化时检查是否为空
        connect(txtSearch, &QLineEdit::textChanged, [this](const QString &text){
            if (text.isEmpty()) {
                loadAllProducts(); // 搜索框为空时自动加载全部商品
            }
        });
    }
}

void SalesWidget::onSearchProduct()
{
    auto *txtSearch = m_salesPage->findChild<QLineEdit*>("txtSearch");
    QString keyword = txtSearch ? txtSearch->text().trimmed() : "";
    if (keyword.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入搜索关键词");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT 商品条码, 商品名称, 规格, 零售价, 库存数量 FROM 商品表 "
                  "WHERE 商品名称 LIKE :keyword OR 商品条码 LIKE :keyword");
    query.bindValue(":keyword", "%" + keyword + "%");

    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "查询失败: " + query.lastError().text());
        return;
    }

    // 创建临时模型存储搜索结果
    QStandardItemModel tempModel;
    tempModel.setHorizontalHeaderLabels({"条码", "名称", "规格", "单价", "库存"});

    bool hasResults = false;
    while (query.next()) {
        hasResults = true;
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(query.value(0).toString());
        rowItems << new QStandardItem(query.value(1).toString());
        rowItems << new QStandardItem(query.value(2).toString());
        rowItems << new QStandardItem(QString::number(query.value(3).toDouble(), 'f', 2));
        rowItems << new QStandardItem(query.value(4).toString());
        tempModel.appendRow(rowItems);
    }

    // 只有找到结果时才更新模型
    if (hasResults) {
        m_productModel->clear();
        m_productModel->setHorizontalHeaderLabels({"条码", "名称", "规格", "单价", "库存"});

        // 将搜索结果复制到主模型
        for (int i = 0; i < tempModel.rowCount(); ++i) {
            QList<QStandardItem*> rowItems;
            for (int j = 0; j < tempModel.columnCount(); ++j) {
                rowItems << tempModel.item(i, j)->clone();
            }
            m_productModel->appendRow(rowItems);
        }
    } else {
        QMessageBox::information(this, "提示", "未找到匹配的商品");
    }
}

void SalesWidget::onAddToCart()
{
    QModelIndexList selection;
    auto *tblProducts = m_salesPage->findChild<QTableView*>("tblProducts");
    if (tblProducts && tblProducts->selectionModel()) {
        selection = tblProducts->selectionModel()->selectedRows();
    }
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择商品");
        return;
    }

    int row = selection.first().row();
    QString barcode = m_productModel->item(row, 0)->text();
    QString name = m_productModel->item(row, 1)->text();
    double price = m_productModel->item(row, 3)->text().toDouble();
    int stock = m_productModel->item(row, 4)->text().toInt();

    // 检查是否已在购物车
    for (int i = 0; i < m_cartModel->rowCount(); ++i) {
        if (m_cartModel->item(i, 0)->text() == barcode) {
            int currentQty = m_cartModel->item(i, 3)->text().toInt();
            if (currentQty >= stock) {
                QMessageBox::warning(this, "提示", "库存不足");
                return;
            }
            m_cartModel->item(i, 3)->setText(QString::number(currentQty + 1));
            m_cartModel->item(i, 4)->setText(
                QString::number((currentQty + 1) * price, 'f', 2));
            auto *lblTotal = m_salesPage->findChild<QLabel*>("lblTotal");
            if (lblTotal) {
                lblTotal->setText(QString::number(calculateTotal(), 'f', 2));
            }
            return;
        }
    }

    // 新商品加入购物车
    QList<QStandardItem*> rowItems;
    rowItems << new QStandardItem(barcode);
    rowItems << new QStandardItem(name);
    rowItems << new QStandardItem(QString::number(price, 'f', 2));
    rowItems << new QStandardItem("1");
    rowItems << new QStandardItem(QString::number(price, 'f', 2));
    m_cartModel->appendRow(rowItems);

    auto *lblTotal = m_salesPage->findChild<QLabel*>("lblTotal");
    if (lblTotal) {
        lblTotal->setText(QString::number(calculateTotal(), 'f', 2));
    }
}

void SalesWidget::onRemoveFromCart()
{
    QModelIndexList selection;
    auto *tblCart = m_salesPage->findChild<QTableView*>("tblCart");
    if (tblCart && tblCart->selectionModel()) {
        selection = tblCart->selectionModel()->selectedRows();
    }
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择商品");
        return;
    }

    int row = selection.first().row();
    int currentQty = m_cartModel->item(row, 3)->text().toInt();

    if (currentQty > 1) {
        double price = m_cartModel->item(row, 2)->text().toDouble();
        m_cartModel->item(row, 3)->setText(QString::number(currentQty - 1));
        m_cartModel->item(row, 4)->setText(
            QString::number((currentQty - 1) * price, 'f', 2));
    } else {
        m_cartModel->removeRow(row);
    }

    auto *lblTotal = m_salesPage->findChild<QLabel*>("lblTotal");
    if (lblTotal) {
        lblTotal->setText(QString::number(calculateTotal(), 'f', 2));
    }
}

void SalesWidget::onCheckout()
{
    if (m_cartModel->rowCount() == 0) {
        QMessageBox::warning(this, "提示", "购物车为空");
        return;
    }

    // 检查会员ID是否有效
    int memberId = -1;
    auto *chkMember = m_salesPage->findChild<QCheckBox*>("chkMember");
    auto *txtMemberId = m_salesPage->findChild<QLineEdit*>("txtMemberId");

    if (chkMember && chkMember->isChecked()) {
        QString memberIdStr = txtMemberId ? txtMemberId->text().trimmed() : "";
        if (memberIdStr.isEmpty()) {
            QMessageBox::warning(this, "提示", "请输入会员ID");
            return;
        }

        QSqlQuery query;
        query.prepare("SELECT 会员ID FROM 会员表 WHERE 会员ID = :id");
        query.bindValue(":id", memberIdStr);

        if (!query.exec() || !query.next()) {
            QMessageBox::warning(this, "错误", "无效的会员ID");
            return;
        }

        memberId = query.value(0).toInt();
    }

    // 首先检查所有商品的库存是否足够
    for (int i = 0; i < m_cartModel->rowCount(); ++i) {
        QString barcode = m_cartModel->item(i, 0)->text();
        int quantity = m_cartModel->item(i, 3)->text().toInt();

        QSqlQuery stockQuery;
        stockQuery.prepare("SELECT 商品名称, 库存数量 FROM 商品表 WHERE 商品条码 = :barcode");
        stockQuery.bindValue(":barcode", barcode);

        if (!stockQuery.exec() || !stockQuery.next()) {
            QMessageBox::warning(this, "错误", QString("无法查询商品库存: %1").arg(barcode));
            return;
        }

        QString productName = stockQuery.value(0).toString();
        int stock = stockQuery.value(1).toInt();

        if (stock < quantity) {
            QMessageBox::warning(this, "库存不足",
                                 QString("商品【%1】库存不足\n当前库存: %2\n需要数量: %3")
                                     .arg(productName).arg(stock).arg(quantity));
            return;
        }
    }

    // 准备商品列表JSON
    QJsonArray itemsArray;
    for (int i = 0; i < m_cartModel->rowCount(); ++i) {
        QJsonObject itemObj;
        itemObj["条码"] = m_cartModel->item(i, 0)->text();
        itemObj["数量"] = m_cartModel->item(i, 3)->text().toInt();
        itemsArray.append(itemObj);
    }

    QJsonDocument doc(itemsArray);
    QString itemsJson = doc.toJson(QJsonDocument::Compact);

    // 获取主窗口中的当前用户ID
    MainWindow *mainWindow = qobject_cast<MainWindow*>(window());
    if (!mainWindow) {
        QMessageBox::critical(this, "错误", "无法获取用户信息");
        return;
    }

    int currentUserId = mainWindow->getCurrentUserId();

    // 获取支付方式
    auto *cbxPayment = m_salesPage->findChild<QComboBox*>("cbxPaymentMethod");
    QString paymentMethod = "现金"; // 默认值
    if (cbxPayment) {
        paymentMethod = cbxPayment->currentText();
    }

    // 开始事务
    QSqlDatabase::database().transaction();

    try {
        // 调用存储过程
        QSqlQuery query;
        query.prepare("CALL 处理销售(?, ?, ?, ?)");
        query.bindValue(0, currentUserId);
        query.bindValue(1, memberId == -1 ? QVariant() : memberId);
        query.bindValue(2, paymentMethod);
        query.bindValue(3, itemsJson);

        if (!query.exec()) {
            // 回滚事务
            QSqlDatabase::database().rollback();

            // 检查是否是库存不足错误
            if (query.lastError().text().contains("商品库存不足")) {
                QMessageBox::warning(this, "库存不足",
                                     "某些商品库存不足，请检查库存后重试");
            } else {
                QMessageBox::critical(this, "错误",
                                      "销售处理失败: " + query.lastError().text());
            }
            return;
        }

        // 尝试移除显式事务，像第一个代码那样让存储过程自己管理事务
        // 或者确保存储过程能适应外部事务

        // 或者改为这样调用：
        QSqlDatabase::database().transaction();
        if (query.exec()) {
            QSqlDatabase::database().commit();
        } else {
            QSqlDatabase::database().rollback();
        }

        // 执行成功后的处理
        query.exec("SELECT 销售单号, 总金额 FROM 销售单表 ORDER BY 销售单号 DESC LIMIT 1");
        if (query.next()) {
            int saleId = query.value(0).toInt();
            double total = query.value(1).toDouble();

            // 更新前端商品模型的库存数量
            for (int i = 0; i < m_cartModel->rowCount(); ++i) {
                QString barcode = m_cartModel->item(i, 0)->text();
                int quantity = m_cartModel->item(i, 3)->text().toInt();

                for (int j = 0; j < m_productModel->rowCount(); ++j) {
                    if (m_productModel->item(j, 0)->text() == barcode) {
                        int currentStock = m_productModel->item(j, 4)->text().toInt();
                        m_productModel->item(j, 4)->setText(QString::number(currentStock - quantity));
                        break;
                    }
                }
            }

            // 清空购物车
            m_cartModel->removeRows(0, m_cartModel->rowCount());

            QMessageBox::information(this, "成功",
                                     QString("销售完成!\n销售单号: %1\n总金额: %2")
                                         .arg(saleId).arg(total));
            refresh();
        }
    } catch (...) {
        // 回滚事务
        QSqlDatabase::database().rollback();
        QMessageBox::critical(this, "错误", "销售处理过程中发生异常");
    }
}

void SalesWidget::onMemberChecked(bool checked)
{
    auto *txtMemberId = m_salesPage->findChild<QLineEdit*>("txtMemberId");
    auto *txtMemberName = m_salesPage->findChild<QLineEdit*>("txtMemberName");

    if (txtMemberId) {
        txtMemberId->setEnabled(checked);
    }

    if (!checked) {
        if (txtMemberId) {
            txtMemberId->clear();
        }
        if (txtMemberName) {
            txtMemberName->clear();
        }
    }
}

double SalesWidget::calculateTotal() const
{
    double total = 0.0;
    for (int i = 0; i < m_cartModel->rowCount(); ++i) {
        total += m_cartModel->item(i, 4)->text().toDouble();
    }
    return total;
}
