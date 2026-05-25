#include "logindialog.h"
#include "ui_logindialog.h"
#include "databasemanager.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QCryptographicHash>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowTitle("用户登录");

    // 连接信号槽
    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(ui->txtPassword, &QLineEdit::returnPressed, this, &LoginDialog::onLoginClicked);

    // 设置密码输入框为密码模式
    ui->txtPassword->setEchoMode(QLineEdit::Password);
}

void LoginDialog::onLoginClicked()
{
    QString username = ui->txtUsername->text().trimmed();
    QString password = ui->txtPassword->text();

    // 验证输入
    if(username.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名不能为空");
        return;
    }
    if(password.isEmpty()) {
        QMessageBox::warning(this, "警告", "密码不能为空");
        return;
    }

    // 真实数据库验证 - 根据你的员工表结构
    QSqlQuery query(DatabaseManager::instance().database());
    query.prepare("SELECT 员工ID, 姓名, 角色, 密码 FROM 员工表 WHERE 用户名 = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "查询失败: " + query.lastError().text());
        return;
    }

    if (query.next()) {
        // 验证密码（使用MD5加密比对，与你的SQL插入语句一致）
        QString inputMd5 = QCryptographicHash::hash(password.toUtf8(),
                                                    QCryptographicHash::Md5).toHex();
        QString storedPassword = query.value(3).toString();

        if (inputMd5 == storedPassword) {
            m_userId = query.value(0).toInt();      // 员工ID
            m_username = query.value(1).toString(); // 姓名
            m_role = query.value(2).toString();     // 角色

            // 根据角色设置数据库连接权限
            setupDatabaseConnectionForRole(m_role, password);

            accept(); // 登录成功
        } else {
            QMessageBox::critical(this, "错误", "密码错误");
            ui->txtPassword->clear();
            ui->txtPassword->setFocus();
        }
    } else {
        QMessageBox::critical(this, "错误", "用户名不存在");
        ui->txtUsername->clear();
        ui->txtPassword->clear();
        ui->txtUsername->setFocus();
    }
}

void LoginDialog::setupDatabaseConnectionForRole(const QString& role, const QString& password)
{
    QString dbUser, dbPassword;

    if (role == "经理") {
        dbUser = "经理";  // 使用中文用户名
        dbPassword = "manager123";
    } else if (role == "库存管理员") {
        dbUser = "库存员";  // 注意与你创建的用户名一致
        dbPassword = "stock123";
    } else if (role == "收银员") {
        dbUser = "收银员";
        dbPassword = "cashier123";
    }

    // 重新连接数据库
    if (!DatabaseManager::instance().connect(
            "localhost",
            "超市销售管理系统",  // 中文数据库名
            dbUser,
            dbPassword,
            3306)) {
        QMessageBox::critical(this, "错误", "数据库权限连接失败");
    }
    // 登录验证成功后
    int userId = m_userId; // 从数据库获取的实际用户ID
    DatabaseManager::instance().setCurrentUserId(userId);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
