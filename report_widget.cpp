// report_widget.cpp
#include "report_widget.h"
#include "databasemanager.h"
#include <QMessageBox>
#include <QTableView>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFileDialog>
#include <QTextStream>
#include <QStringConverter>  // 用于 Qt 5.15 及以后版本

report_widget::report_widget(QWidget *parent) : QWidget(parent)
{
    m_report_model = new QSqlQueryModel(this);
}

report_widget::~report_widget()
{
    if (m_report_model) m_report_model->deleteLater();
}

void report_widget::set_report_page(QWidget *page_report)
{
    if (!page_report) {
        qWarning() << "report_widget: Invalid page_report pointer";
        return;
    }

    m_report_page = page_report;
    setup_models();
    setup_connections();

    // 设置表格模型
    auto *tblReport = m_report_page->findChild<QTableView*>("tblReport");
    if (tblReport) {
        tblReport->setModel(m_report_model);
        tblReport->setSelectionMode(QAbstractItemView::SingleSelection);
        tblReport->setSelectionBehavior(QAbstractItemView::SelectRows);
    }

    // 初始化日期范围
    auto *dateStart = m_report_page->findChild<QDateEdit*>("dateStart_report");
    auto *dateEnd = m_report_page->findChild<QDateEdit*>("dateEnd_report");
    if (dateStart && dateEnd) {
        dateStart->setDate(QDate::currentDate().addDays(-7)); // 默认显示最近7天
        dateEnd->setDate(QDate::currentDate());
    }

    // 初始加载数据
    refresh();
}

void report_widget::setup_models()
{
    // 报表模型结构将在加载数据时动态设置
}

void report_widget::setup_connections()
{
    // 生成报表按钮
    auto *btnGenerate = m_report_page->findChild<QPushButton*>("btnGenerate_report");
    if (btnGenerate) {
        connect(btnGenerate, &QPushButton::clicked, this, &report_widget::on_generate_report);
    }

    // 导出按钮
    auto *btnExport = m_report_page->findChild<QPushButton*>("btnExport_report");
    if (btnExport) {
        connect(btnExport, &QPushButton::clicked, this, &report_widget::on_export_report);
    }

    // 刷新按钮
    auto *btnRefresh = m_report_page->findChild<QPushButton*>("btnRefresh_report");
    if (btnRefresh) {
        connect(btnRefresh, &QPushButton::clicked, this, &report_widget::on_refresh_clicked);
    }
}

void report_widget::load_report_data()
{
    auto *cmbReportType = m_report_page->findChild<QComboBox*>("cmbReportType");
    auto *dateStart = m_report_page->findChild<QDateEdit*>("dateStart_report");
    auto *dateEnd = m_report_page->findChild<QDateEdit*>("dateEnd_report");

    if (!cmbReportType || !dateStart || !dateEnd) return;

    QString reportType = cmbReportType->currentData().toString();
    QDate startDate = dateStart->date();
    QDate endDate = dateEnd->date();

    if (startDate > endDate) {
        QMessageBox::warning(this, "警告", "开始日期不能晚于结束日期");
        return;
    }

    QString sql;
    if (reportType == "daily_sales") {
        // 直接使用日销售汇总视图
        sql = QString(
                  "SELECT * FROM 日销售汇总视图 "
                  "WHERE 销售日期 BETWEEN '%1' AND '%2' "
                  "ORDER BY 销售日期 DESC")
                  .arg(startDate.toString("yyyy-MM-dd"))
                  .arg(endDate.toString("yyyy-MM-dd"));
    }
    else if (reportType == "product_sales") {
        // 直接使用商品销售排行视图
        sql = QString(
                  "SELECT 商品名称, 规格, 销售总量 AS 销售数量, 销售总额 AS 销售金额, 毛利润 "
                  "FROM 商品销售排行视图 "
                  "WHERE 商品条码 IN ("
                  "   SELECT DISTINCT d.商品条码 "
                  "   FROM 销售明细表 d "
                  "   JOIN 销售单表 s ON d.销售单号 = s.销售单号 "
                  "   WHERE DATE(s.销售日期) BETWEEN '%1' AND '%2'"
                  ") "
                  "ORDER BY 销售总额 DESC")
                  .arg(startDate.toString("yyyy-MM-dd"))
                  .arg(endDate.toString("yyyy-MM-dd"));
    }
    else if (reportType == "member_consumption") {
        // 直接使用会员消费排行视图
        sql = QString(
                  "SELECT * FROM 会员消费排行视图 "
                  "WHERE 最近消费日期 BETWEEN '%1' AND '%2' OR 最近消费日期 IS NULL "
                  "ORDER BY 消费总额 DESC")
                  .arg(startDate.toString("yyyy-MM-dd"))
                  .arg(endDate.toString("yyyy-MM-dd"));
    }

    m_report_model->setQuery(sql);
    if (m_report_model->lastError().isValid()) {
        QMessageBox::critical(this, "错误", "加载报表数据失败: " + m_report_model->lastError().text());
        return;
    }

    // 根据报表类型设置表头
    if (reportType == "daily_sales") {
        m_report_model->setHeaderData(0, Qt::Horizontal, tr("销售日期"));
        m_report_model->setHeaderData(1, Qt::Horizontal, tr("订单总数"));
        m_report_model->setHeaderData(2, Qt::Horizontal, tr("销售总额"));
        m_report_model->setHeaderData(3, Qt::Horizontal, tr("会员销售额"));
        m_report_model->setHeaderData(4, Qt::Horizontal, tr("非会员销售额"));
        m_report_model->setHeaderData(5, Qt::Horizontal, tr("参与员工数"));
    }
    else if (reportType == "product_sales") {
        m_report_model->setHeaderData(0, Qt::Horizontal, tr("商品名称"));
        m_report_model->setHeaderData(1, Qt::Horizontal, tr("规格"));
        m_report_model->setHeaderData(2, Qt::Horizontal, tr("销售数量"));
        m_report_model->setHeaderData(3, Qt::Horizontal, tr("销售金额"));
        m_report_model->setHeaderData(4, Qt::Horizontal, tr("毛利润"));
    }
    else if (reportType == "member_consumption") {
        m_report_model->setHeaderData(0, Qt::Horizontal, tr("会员ID"));
        m_report_model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
        m_report_model->setHeaderData(2, Qt::Horizontal, tr("电话"));
        m_report_model->setHeaderData(3, Qt::Horizontal, tr("消费次数"));
        m_report_model->setHeaderData(4, Qt::Horizontal, tr("消费总额"));
        m_report_model->setHeaderData(5, Qt::Horizontal, tr("最近消费日期"));
        m_report_model->setHeaderData(6, Qt::Horizontal, tr("积分"));
        m_report_model->setHeaderData(7, Qt::Horizontal, tr("折扣率"));
    }
}
void report_widget::on_generate_report()
{
    load_report_data();
}

void report_widget::on_export_report()
{
    if (m_report_model->rowCount() == 0) {
        QMessageBox::warning(this, "警告", "没有数据可导出");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "导出报表", "", "CSV文件 (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "无法创建文件: " + file.errorString());
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    // 写入表头
    for (int col = 0; col < m_report_model->columnCount(); ++col) {
        if (col > 0) out << ",";
        out << "\"" << m_report_model->headerData(col, Qt::Horizontal).toString() << "\"";
    }
    out << "\n";

    // 写入数据
    for (int row = 0; row < m_report_model->rowCount(); ++row) {
        for (int col = 0; col < m_report_model->columnCount(); ++col) {
            if (col > 0) out << ",";
            out << "\"" << m_report_model->data(m_report_model->index(row, col)).toString() << "\"";
        }
        out << "\n";
    }

    file.close();
    QMessageBox::information(this, "成功", "报表已导出");
}

void report_widget::on_refresh_clicked()
{
    refresh();
}

void report_widget::refresh()
{
    // 初始化报表类型下拉框
    auto *cmbReportType = m_report_page->findChild<QComboBox*>("cmbReportType");
    if (cmbReportType) {
        cmbReportType->clear();
        cmbReportType->addItem("日销售报表", "daily_sales");
        cmbReportType->addItem("商品销售排行", "product_sales");
        cmbReportType->addItem("会员消费统计", "member_consumption");
    }

    // 加载默认报表
    load_report_data();
}
