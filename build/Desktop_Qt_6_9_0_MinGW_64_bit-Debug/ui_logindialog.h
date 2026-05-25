/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *txtUsername;
    QLineEdit *txtPassword;
    QPushButton *btnLogin;
    QLabel *label_3;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(615, 550);
        LoginDialog->setMinimumSize(QSize(300, 200));
        LoginDialog->setStyleSheet(QString::fromUtf8("/* \347\231\273\345\275\225\347\252\227\345\217\243\346\225\264\344\275\223\346\240\267\345\274\217 */\n"
"QDialog#LoginDialog {\n"
"    background-color: #f5f7fa;\n"
"    border: 1px solid #d1d9e6;\n"
"    border-radius: 8px;\n"
"}\n"
"\n"
"/* \347\231\273\345\275\225\345\256\271\345\231\250\346\240\267\345\274\217 */\n"
"#loginContainer {\n"
"    background-color: white;\n"
"    border-radius: 6px;\n"
"    padding: 30px;\n"
"    border: 1px solid #e0e5ec;\n"
"    box-shadow: 0 2px 10px rgba(0,0,0,0.05);\n"
"}\n"
"\n"
"/* \346\240\207\351\242\230\346\240\267\345\274\217 */\n"
"QLabel#loginTitle {\n"
"    color: #2c3e50;\n"
"    font-size: 22px;\n"
"    font-weight: bold;\n"
"    padding-bottom: 20px;\n"
"    qproperty-alignment: AlignCenter;\n"
"}\n"
"\n"
"/* \350\276\223\345\205\245\346\241\206\346\240\207\347\255\276\346\240\267\345\274\217 */\n"
"QLabel[text^=\"\347\224\250\346\210\267\345\220\215\"], \n"
"QLabel[text^=\"\345\257\206\347\240\201\"] {\n"
"    color: #7f8c8d;\n"
"    font-size: 13px;\n"
"   "
                        " padding-bottom: 5px;\n"
"}\n"
"\n"
"/* \350\276\223\345\205\245\346\241\206\346\240\267\345\274\217 */\n"
"QLineEdit {\n"
"    border: 1px solid #d1d9e6;\n"
"    border-radius: 4px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"    min-height: 36px;\n"
"    background-color: #f9fbfd;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 1px solid #3498db;\n"
"    background-color: white;\n"
"}\n"
"\n"
"/* \347\231\273\345\275\225\346\214\211\351\222\256\346\240\267\345\274\217 */\n"
"QPushButton#btnLogin {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 12px;\n"
"    border-radius: 4px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    min-width: 120px;\n"
"}\n"
"\n"
"QPushButton#btnLogin:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"\n"
"QPushButton#btnLogin:pressed {\n"
"    background-color: #1a5276;\n"
"}\n"
"\n"
"/* \350\256\260\344\275\217\345\257\206\347\240\201\345\244\215\351\200\211\346\241\206 */\n"
"QCheckBox#chkRemember {\n"
"    s"
                        "pacing: 6px;\n"
"    font-size: 12px;\n"
"    color: #7f8c8d;\n"
"}\n"
"\n"
"QCheckBox#chkRemember::indicator {\n"
"    width: 16px;\n"
"    height: 16px;\n"
"}\n"
"\n"
"/* \351\224\231\350\257\257\346\217\220\347\244\272\346\240\207\347\255\276 */\n"
"QLabel#lblError {\n"
"    color: #e74c3c;\n"
"    font-size: 12px;\n"
"    qproperty-alignment: AlignCenter;\n"
"    padding-top: 10px;\n"
"}\n"
"\n"
"/* \345\272\225\351\203\250\347\211\210\346\235\203\344\277\241\346\201\257 */\n"
"QLabel#copyright {\n"
"    color: #95a5a6;\n"
"    font-size: 11px;\n"
"    qproperty-alignment: AlignCenter;\n"
"    padding-top: 20px;\n"
"}\n"
"\n"
"/* \347\231\273\345\275\225\347\252\227\345\217\243\346\225\264\344\275\223\346\240\267\345\274\217 */\n"
"QDialog#LoginDialog {\n"
"    background-image: url(C:/Users/\345\220\264\345\220\233\350\261\252/Desktop/\345\233\276\347\211\207/\350\266\205\345\270\202\351\224\200\345\224\256\347\256\241\347\220\206\347\263\273\347\273\237.png); /* \346\233\277\346\215\242\344\270\272\344\275"
                        "\240\347\232\204\345\256\236\351\231\205\345\233\276\347\211\207\350\267\257\345\276\204 */\n"
"	\n"
"    background-size: cover; /* \345\233\276\347\211\207\345\260\206\350\246\206\347\233\226\346\225\264\344\270\252\345\257\271\350\257\235\346\241\206 */\n"
"    background-position: center;\n"
"    border: 1px solid #d1d9e6;\n"
"    border-radius: 8px;\n"
"}\n"
"/* \347\231\273\345\275\225\345\256\271\345\231\250\346\240\267\345\274\217 - \346\267\273\345\212\240\345\215\212\351\200\217\346\230\216\350\203\214\346\231\257 */\n"
"#loginContainer {\n"
"    background-color: rgba(255, 255, 255, 0.9); /* 90%\344\270\215\351\200\217\346\230\216\347\232\204\347\231\275\350\211\262 */\n"
"    border-radius: 6px;\n"
"    padding: 30px;\n"
"    border: 1px solid #e0e5ec;\n"
"    box-shadow: 0 2px 10px rgba(0,0,0,0.1);\n"
"}\n"
"\n"
"\n"
"/* \345\205\266\344\273\226\346\240\267\345\274\217\344\277\235\346\214\201\344\270\215\345\217\230... */"));
        label = new QLabel(LoginDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(160, 170, 71, 51));
        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 250, 71, 41));
        txtUsername = new QLineEdit(LoginDialog);
        txtUsername->setObjectName("txtUsername");
        txtUsername->setGeometry(QRect(250, 170, 211, 58));
        txtPassword = new QLineEdit(LoginDialog);
        txtPassword->setObjectName("txtPassword");
        txtPassword->setGeometry(QRect(250, 250, 211, 58));
        txtPassword->setEchoMode(QLineEdit::EchoMode::Password);
        btnLogin = new QPushButton(LoginDialog);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setGeometry(QRect(190, 340, 261, 51));
        label_3 = new QLabel(LoginDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(210, 100, 181, 51));

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "\347\263\273\347\273\237\347\231\273\345\275\225", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:700;\">\347\224\250\346\210\267\345\220\215:</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:700;\">\345\257\206\347\240\201:</span></p></body></html>", nullptr));
        btnLogin->setText(QCoreApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        label_3->setText(QCoreApplication::translate("LoginDialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt; font-weight:700;\">\350\266\205\345\270\202\351\224\200\345\224\256\347\256\241\347\220\206\347\263\273\347\273\237</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
