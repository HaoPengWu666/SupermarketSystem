#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "ui_logindialog.h"
#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    // 获取用户信息的方法
    int getUserId() const { return m_userId; }  // 普通成员函数
    QString getUsername() const { return m_username; }
    QString getUserRole() const { return m_role; }

private slots:
    void onLoginClicked();
    void setupDatabaseConnectionForRole(const QString& role, const QString& password);

private:
    Ui::LoginDialog *ui;
    int m_userId = -1;       // 新增：保存用户ID
    QString m_username;      // 新增：保存用户名
    QString m_role;          // 新增：保存用户角色
};

#endif // LOGINDIALOG_H
