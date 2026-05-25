#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "saleswidget.h"
#include "inventory_widget.h"
#include "member_widget.h"
#include "report_widget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("超市销售管理系统");

    // 初始化stackedWidget指针（使用UI设计器生成的）
    m_stackedWidget = ui->stackedWidget; // 关键修改！

    // 创建各个功能部件
    m_salesWidget = qobject_cast<SalesWidget*>(ui->stackedWidget->widget(0));
    m_inventoryWidget = qobject_cast<inventory_widget*>(ui->stackedWidget->widget(3));
    m_memberWidget = qobject_cast<member_widget*>(ui->stackedWidget->widget(1));
    m_reportWidget = qobject_cast<report_widget*>(ui->stackedWidget->widget(2));

    // 延迟设置 salesPage（确保UI完全加载）
    QTimer::singleShot(0, this, [this]() {
        if (m_salesWidget) {
            m_salesWidget->setSalesPage(ui->page_sales);
        }
    });

    // 延迟设置 inventoryPage（确保UI完全加载）
    QTimer::singleShot(0, this, [this]() {
        if (m_inventoryWidget) {
            m_inventoryWidget->set_inventory_page(ui->page_inventory);
        }
    });

    // 延迟设置 memberPage（确保UI完全加载）
    QTimer::singleShot(0, this, [this]() {
        if (m_memberWidget) {
            m_memberWidget->set_member_page(ui->page_member);
        }
    });

    // 延迟设置 memberPage（确保UI完全加载）
    QTimer::singleShot(0, this, [this]() {
        if (m_reportWidget) {
            m_reportWidget->set_report_page(ui->page_report);
        }
    });

    // 设置初始页面
    ui->stackedWidget->setCurrentWidget(m_salesWidget);

    // 在MainWindow构造函数中添加
    setWindowState(Qt::WindowMaximized);  // 或者 setWindowState(Qt::WindowFullScreen);
    // setupUI();
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentUser(int userId, const QString &userName, const QString &role)
{
    // 添加验证
    Q_ASSERT(userId > 0); // 确保ID是有效的数据库ID

    m_currentUserId = userId;
    m_currentUserName = userName;
    m_currentUserRole = role;

    qDebug() << "设置当前用户: ID=" << userId << "姓名=" << userName << "角色=" << role;

    updateUserInfo();

    // 根据角色启用/禁用功能
    ui->btnInventory->setEnabled(role == "库存管理员" || role == "经理");
    ui->btnReport->setEnabled(role == "经理");
    ui->btnSales->setEnabled(role == "收银员" || role == "经理"); // 添加收银员支持
}

void MainWindow::setupUI()
{
    // 设置工具栏按钮样式等
    //ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    // 添加动作
    ui->btnSales->setIcon(QIcon(":/icons/sales.png"));
    ui->btnInventory->setIcon(QIcon(":/icons/inventory.png"));
    ui->btnMember->setIcon(QIcon(":/icons/member.png"));
    ui->btnReport->setIcon(QIcon(":/icons/report.png"));
    ui->btnLogout->setIcon(QIcon(":/icons/logout.png"));
}

void MainWindow::setupConnections()
{
    connect(ui->btnSales, &QToolButton::clicked, this, &MainWindow::onSalesClicked);
    connect(ui->btnInventory, &QToolButton::clicked, this, &MainWindow::onInventoryClicked);
    connect(ui->btnMember, &QToolButton::clicked, this, &MainWindow::onMemberClicked);
    connect(ui->btnReport, &QToolButton::clicked, this, &MainWindow::onReportClicked);
    connect(ui->btnLogout, &QToolButton::clicked, this, &MainWindow::onLogoutClicked);
}

void MainWindow::updateUserInfo()
{
    ui->statusbar->showMessage(QString("当前用户: %1 (%2)").arg(m_currentUserName).arg(m_currentUserRole));
}

void MainWindow::onSalesClicked()
{
    m_stackedWidget->setCurrentWidget(m_salesWidget);
    m_salesWidget->refresh();
}

void MainWindow::onInventoryClicked()
{
    m_stackedWidget->setCurrentWidget(m_inventoryWidget);
    m_inventoryWidget->refresh();
}

void MainWindow::onMemberClicked()
{
    m_stackedWidget->setCurrentWidget(m_memberWidget);
    m_memberWidget->refresh();
}

void MainWindow::onReportClicked()
{
    m_stackedWidget->setCurrentWidget(m_reportWidget);
    m_reportWidget->refresh();
}

void MainWindow::onLogoutClicked()
{
    close();
}


