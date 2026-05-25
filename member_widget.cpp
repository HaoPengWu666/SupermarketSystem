#include "member_widget.h"
#include "databasemanager.h"
#include "qdatetime.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QTableView>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>

member_widget::member_widget(QWidget *parent) : QWidget(parent)
{
    m_member_model = new QStandardItemModel(this);
    m_statsModel = new QSqlQueryModel(this);  // 新增统计模型
}

member_widget::~member_widget()
{
    if (m_member_model) m_member_model->deleteLater();
}

void member_widget::set_member_page(QWidget *page_member)
{
    if (!page_member) {
        qWarning() << "member_widget: Invalid page_member pointer";
        return;
    }

    m_member_page = page_member;
    setup_models();
    setup_connections();

    // 设置表格模型
    auto *tblMember = m_member_page->findChild<QTableView*>("tblMember_m");
    if (tblMember) tblMember->setModel(m_member_model);

    // 设置统计表格模型
    auto *tblStats = m_member_page->findChild<QTableView*>("tblMemberStats_m");
    if (tblStats) {
        tblStats->setModel(m_statsModel);
    }

    loadMemberStats();
    // 初始加载数据
    refresh();
}

void member_widget::refresh()
{
    // 清空搜索框
    auto *txtSearch = m_member_page->findChild<QLineEdit*>("txtSearch_m");
    if (txtSearch) txtSearch->clear();

    // 重置筛选器
    auto *cmbMemberLevel = m_member_page->findChild<QComboBox*>("cmbMemberLevel_m");
    if (cmbMemberLevel) cmbMemberLevel->setCurrentIndex(0);

    // 重新加载数据
    load_member_data();
    loadMemberStats();
}

void member_widget::setup_models()
{
    // 会员表格模型
    m_member_model->setHorizontalHeaderLabels(
        {"会员ID", "姓名", "电话", "积分", "折扣率", "注册日期"});
}

void member_widget::setupStatsModel()
{
    m_statsModel->setQuery("SELECT * FROM 会员消费视图 LIMIT 0"); // 空查询初始化结构
    m_statsModel->setHeaderData(0, Qt::Horizontal, tr("会员ID"));
    m_statsModel->setHeaderData(1, Qt::Horizontal, tr("姓名"));
    m_statsModel->setHeaderData(2, Qt::Horizontal, tr("电话"));
    m_statsModel->setHeaderData(3, Qt::Horizontal, tr("积分"));
    m_statsModel->setHeaderData(4, Qt::Horizontal, tr("消费总额"));
    m_statsModel->setHeaderData(5, Qt::Horizontal, tr("消费次数"));
    m_statsModel->setHeaderData(6, Qt::Horizontal, tr("最近消费"));
}

void member_widget::setup_connections()
{
    // 搜索按钮
    auto *btnSearch = m_member_page->findChild<QPushButton*>("btnSearch_m");
    if (btnSearch) {
        connect(btnSearch, &QPushButton::clicked, this, &member_widget::on_search_member);
    }

    // 搜索框回车键
    auto *txtSearch = m_member_page->findChild<QLineEdit*>("txtSearch_m");
    if (txtSearch) {
        connect(txtSearch, &QLineEdit::returnPressed, this, &member_widget::on_search_member);
    }

    // 会员等级筛选
    auto *cmbMemberLevel = m_member_page->findChild<QComboBox*>("cmbMemberLevel_m");
    if (cmbMemberLevel) {
        cmbMemberLevel->clear();
        cmbMemberLevel->addItem("所有会员", 0);
        cmbMemberLevel->addItem("钻石会员", 1);
        cmbMemberLevel->addItem("黄金会员", 2);
        cmbMemberLevel->addItem("白银会员", 3);
        cmbMemberLevel->addItem("普通会员", 4);
        cmbMemberLevel->addItem("新会员", 5);

        connect(cmbMemberLevel, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &member_widget::load_member_data);
    }

    // 操作按钮
    auto *btnAddMember = m_member_page->findChild<QPushButton*>("btnAddMember_m");
    auto *btnEditMember = m_member_page->findChild<QPushButton*>("btnEditMember_m");
    auto *btnRefresh = m_member_page->findChild<QPushButton*>("btnRefresh_m");

    if (btnAddMember) connect(btnAddMember, &QPushButton::clicked, this, &member_widget::on_add_member_clicked);
    if (btnEditMember) connect(btnEditMember, &QPushButton::clicked, this, &member_widget::on_edit_member_clicked);
    if (btnRefresh) connect(btnRefresh, &QPushButton::clicked, this, &member_widget::on_refresh_clicked);
}

void member_widget::load_member_data()
{
    QString sql = "SELECT 会员ID, 姓名, 电话, 积分, 折扣率, 注册日期 FROM 会员表 WHERE 1=1";

    // 获取筛选条件
    auto *cmbMemberLevel = m_member_page->findChild<QComboBox*>("cmbMemberLevel_m");
    auto *txtSearch = m_member_page->findChild<QLineEdit*>("txtSearch_m");

    // 会员等级筛选 - 修改为使用积分范围筛选
    if (cmbMemberLevel && cmbMemberLevel->currentIndex() > 0) {
        switch (cmbMemberLevel->currentData().toInt()) {
        case 1: // 钻石会员
            sql += " AND 积分 >= 1000";
            break;
        case 2: // 黄金会员
            sql += " AND 积分 >= 500 AND 积分 < 1000";
            break;
        case 3: // 白银会员
            sql += " AND 积分 >= 200 AND 积分 < 500";
            break;
        case 4: // 普通会员
            sql += " AND 积分 >= 100 AND 积分 < 200";
            break;
        case 5: // 新会员
            sql += " AND 积分 < 100";
            break;
        }
    }

    // 搜索条件
    if (txtSearch && !txtSearch->text().isEmpty()) {
        QString keyword = txtSearch->text().trimmed();
        sql += " AND (姓名 LIKE '%" + keyword + "%' OR 电话 LIKE '%" + keyword + "%')";
    }

    sql += " ORDER BY 积分 DESC";

    QSqlQuery query;
    if (!query.exec(sql)) {
        QMessageBox::critical(nullptr, "错误", "加载会员数据失败: " + query.lastError().text());
        return;
    }

    m_member_model->removeRows(0, m_member_model->rowCount());

    while (query.next()) {
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(query.value(0).toString());
        rowItems << new QStandardItem(query.value(1).toString());
        rowItems << new QStandardItem(query.value(2).toString());
        rowItems << new QStandardItem(query.value(3).toString());

        // 格式化折扣率显示，例如0.75显示为"75折"
        double discountRate = query.value(4).toDouble();
        QString discountText = QString::number(static_cast<int>(discountRate * 100)) + "折";
        rowItems << new QStandardItem(discountText);

        rowItems << new QStandardItem(query.value(5).toDate().toString("yyyy-MM-dd"));
        m_member_model->appendRow(rowItems);
    }
}

void member_widget::loadMemberStats()
{
    QString sql = "SELECT * FROM 会员消费视图";

    // 可以添加筛选条件，比如只显示有消费记录的会员
    // sql += " WHERE 消费次数 > 0";

    sql += " ORDER BY 消费总额 DESC LIMIT 20"; // 限制显示20条记录

    m_statsModel->setQuery(sql);
    if (m_statsModel->lastError().isValid()) {
        QMessageBox::critical(nullptr, "错误", "加载会员消费统计失败: " +
                                                   m_statsModel->lastError().text());
    }
}

void member_widget::on_search_member()
{
    load_member_data();
}

void member_widget::on_add_member_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("新增会员");
    dialog.setFixedSize(400, 300);

    QFormLayout layout(&dialog);

    // 姓名
    QLineEdit txtName;
    layout.addRow("姓名:", &txtName);

    // 电话
    QLineEdit txtPhone;
    layout.addRow("电话:", &txtPhone);

    QDialogButtonBox buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout.addRow(&buttons);

    connect(&buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        // 验证数据
        if (txtName.text().isEmpty()) {
            QMessageBox::warning(this, "警告", "姓名不能为空");
            return;
        }

        if (txtPhone.text().isEmpty()) {
            QMessageBox::warning(this, "警告", "电话不能为空");
            return;
        }

        // 插入新会员
        QSqlQuery query;
        query.prepare("INSERT INTO 会员表 (姓名, 电话, 注册日期) VALUES (?, ?, CURDATE())");
        query.addBindValue(txtName.text());
        query.addBindValue(txtPhone.text());

        if (query.exec()) {
            // 获取新插入的会员ID
            int newMemberId = query.lastInsertId().toInt();

            // 调用存储过程更新折扣率（虽然新会员默认1.0，但为了确保一致性）
            QSqlQuery callProc;
            callProc.prepare("CALL 更新会员折扣(?)");
            callProc.addBindValue(newMemberId);
            if (!callProc.exec()) {
                QMessageBox::warning(this, "警告", "更新折扣率失败: " + callProc.lastError().text());
            }

            QMessageBox::information(this, "成功", "会员添加成功");
            refresh();
        } else {
            QMessageBox::critical(this, "错误", "添加会员失败: " + query.lastError().text());
        }
    }
}



void member_widget::on_edit_member_clicked()
{
    // 获取当前选中的会员
    auto *tblMember = m_member_page->findChild<QTableView*>("tblMember_m");
    if (!tblMember) return;

    QModelIndexList selected = tblMember->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择要编辑的会员");
        return;
    }

    QString memberId = m_member_model->item(selected.first().row(), 0)->text();

    QDialog dialog(this);
    dialog.setWindowTitle("编辑会员");
    dialog.setFixedSize(400, 300);

    QFormLayout layout(&dialog);

    // 会员ID (不可编辑)
    QLineEdit txtId;
    txtId.setEnabled(false);
    layout.addRow("会员ID:", &txtId);

    // 姓名
    QLineEdit txtName;
    layout.addRow("姓名:", &txtName);

    // 电话
    QLineEdit txtPhone;
    layout.addRow("电话:", &txtPhone);

    // 积分
    QLineEdit txtPoints;
    txtPoints.setValidator(new QIntValidator(0, 999999, &txtPoints));
    layout.addRow("积分:", &txtPoints);

    // 加载会员数据
    QSqlQuery query;
    query.prepare("SELECT 姓名, 电话, 积分 FROM 会员表 WHERE 会员ID = ?");
    query.addBindValue(memberId);
    if (query.exec() && query.next()) {
        txtId.setText(memberId);
        txtName.setText(query.value(0).toString());
        txtPhone.setText(query.value(1).toString());
        txtPoints.setText(query.value(2).toString());
    }

    QDialogButtonBox buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout.addRow(&buttons);

    connect(&buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        // 验证数据
        if (txtName.text().isEmpty()) {
            QMessageBox::warning(this, "警告", "姓名不能为空");
            return;
        }

        if (txtPhone.text().isEmpty()) {
            QMessageBox::warning(this, "警告", "电话不能为空");
            return;
        }

        // 更新会员信息
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE 会员表 SET 姓名=?, 电话=?, 积分=? WHERE 会员ID=?");
        updateQuery.addBindValue(txtName.text());
        updateQuery.addBindValue(txtPhone.text());
        updateQuery.addBindValue(txtPoints.text().toInt());
        updateQuery.addBindValue(memberId);

        if (updateQuery.exec()) {
            // 调用存储过程更新折扣率
            QSqlQuery callProc;
            callProc.prepare("CALL 更新会员折扣(?)");
            callProc.addBindValue(memberId);
            if (!callProc.exec()) {
                QMessageBox::warning(this, "警告", "更新折扣率失败: " + callProc.lastError().text());
            }

            QMessageBox::information(this, "成功", "会员信息已更新");
            refresh();
        } else {
            QMessageBox::critical(this, "错误", "更新会员信息失败: " + updateQuery.lastError().text());
        }
    }
}

void member_widget::on_refresh_clicked()
{
    refresh();
}
