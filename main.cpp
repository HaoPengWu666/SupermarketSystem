#include "mainwindow.h"
#include "databasemanager.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 初始化数据库
    if (!DatabaseManager::instance().connect(
            "localhost",    // 主机
            "超市销售管理系统",  // 数据库名
            "root",        // 用户名
            "root",      // 密码
            3306           // 端口
            )) {
        QMessageBox::critical(nullptr, "错误",
                              "数据库连接失败: " + DatabaseManager::instance().lastError());
        return -1;
    }

    // 显示登录对话框
    LoginDialog login;
    if(login.exec() != QDialog::Accepted) {
        return 0; // 登录失败退出程序
    }

    // 登录成功后显示主窗口
    MainWindow w;
    w.setCurrentUser(login.getUserId(), login.getUsername(), login.getUserRole()); // 传递完整用户信息
    w.show();

    return a.exec();
}
