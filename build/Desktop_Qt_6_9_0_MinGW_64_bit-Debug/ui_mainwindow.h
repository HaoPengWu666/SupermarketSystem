/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "inventory_widget.h"
#include "member_widget.h"
#include "report_widget.h"
#include "saleswidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *leftWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QToolButton *btnSales;
    QToolButton *btnInventory;
    QToolButton *btnMember;
    QToolButton *btnReport;
    QSpacerItem *verticalSpacer_2;
    QToolButton *btnLogout;
    QSpacerItem *verticalSpacer_3;
    QStackedWidget *stackedWidget;
    SalesWidget *page_sales;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *txtSearch;
    QPushButton *btnSearch;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_3;
    QTableView *tblProducts;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *chkMember;
    QLabel *label_2;
    QLineEdit *txtMemberId;
    QLabel *label_3;
    QLineEdit *txtMemberName;
    QLabel *label_19;
    QComboBox *cbxPaymentMethod;
    QSpacerItem *verticalSpacer_4;
    QPushButton *btnAdd;
    QPushButton *btnRemove;
    QPushButton *btnCheckout;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_11;
    QLabel *lblTotal;
    QLabel *label_5;
    QTableView *tblCart;
    member_widget *page_member;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *txtSearch_m;
    QPushButton *btnSearch_m;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_9;
    QComboBox *cmbMemberLevel_m;
    QSpacerItem *horizontalSpacer;
    QLabel *label_10;
    QTableView *tblMember_m;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btnAddMember_m;
    QPushButton *btnRefresh_m;
    QPushButton *btnEditMember_m;
    QLabel *label_12;
    QTableView *tblMemberStats_m;
    report_widget *page_report;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_13;
    QDateEdit *dateStart_report;
    QLabel *label_14;
    QDateEdit *dateEnd_report;
    QLabel *label_15;
    QComboBox *cmbReportType;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnGenerate_report;
    QLabel *label_16;
    QTableView *tblReport;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *btnExport_report;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnRefresh_report;
    inventory_widget *page_inventory;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *txtSearch_in;
    QPushButton *btnSearch_in;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_20;
    QComboBox *cmbStockStatus_in;
    QLabel *label_21;
    QComboBox *cmbSupplier_in;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_22;
    QTableView *tblInventory_in;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *btnStockIn_in;
    QPushButton *btnAddProduct_in;
    QPushButton *btnEditProduct_in;
    QPushButton *btnRefresh_in;
    QLabel *label_23;
    QTableView *tblWarning_in;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1024, 768);
        MainWindow->setStyleSheet(QString::fromUtf8("/* \344\270\273\347\252\227\345\217\243\350\203\214\346\231\257 */\n"
"QMainWindow {\n"
"    background-color: #f0f0f0;\n"
"}\n"
"\n"
"/* \345\267\246\344\276\247\345\257\274\350\210\252\345\214\272\345\237\237 */\n"
"#centralwidget {\n"
"    background-color: #2c3e50;\n"
"}\n"
"\n"
"/* \345\267\246\344\276\247\345\257\274\350\210\252\346\214\211\351\222\256 - \347\273\274\345\220\210\346\224\271\350\277\233 */\n"
"QToolButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 12px 12px 12px 20px;\n"
"    font-size: 14px;\n"
"    border-radius: 4px;\n"
"    margin: 5px;\n"
"    text-align: left;\n"
"    min-width: 120px;\n"
"    transition: all 0.1s ease;  /* \346\267\273\345\212\240\345\271\263\346\273\221\350\277\207\346\270\241\346\225\210\346\236\234 */\n"
"}\n"
"\n"
"QToolButton:hover {\n"
"    background-color: #2980b9;\n"
"    padding-left: 22px;  /* \346\202\254\345\201\234\346\227\266\350\275\273\345\276\256\345\217\263\347\247\273 */\n"
"}\n"
"\n"
"QTool"
                        "Button:pressed {\n"
"    background-color: #154360;  /* \346\233\264\346\267\261\347\232\204\350\223\235\350\211\262 */\n"
"    color: #ecf0f1;\n"
"    border-left: 3px solid #f39c12;\n"
"    padding-left: 17px;  /* \344\277\235\346\214\201\346\200\273\351\227\264\350\267\235\344\270\215\345\217\230 */\n"
"    box-shadow: inset 2px 2px 4px rgba(0,0,0,0.2);\n"
"}\n"
"\n"
"/* \345\275\223\345\211\215\351\200\211\344\270\255\346\214\211\351\222\256\347\232\204\347\211\271\346\256\212\346\240\267\345\274\217 */\n"
"QToolButton:checked {\n"
"    background-color: #1a5276;\n"
"    font-weight: bold;\n"
"    border-left: 3px solid #f1c40f;  /* \346\267\273\345\212\240\345\267\246\344\276\247\351\253\230\344\272\256\350\276\271\346\241\206 */\n"
"}\n"
"\n"
"#btnLogout:hover {\n"
"    background-color: #c0392b;\n"
"}\n"
"\n"
"/* \345\206\205\345\256\271\345\214\272\345\237\237\346\240\207\351\242\230 */\n"
"QLabel[text^=\"<html>\"] {\n"
"    color: #2c3e50;\n"
"    font-size: 16px;\n"
"}\n"
"\n"
"/* \350\241\250\346\240"
                        "\274\346\240\267\345\274\217 */\n"
"QTableView {\n"
"    background-color: white;\n"
"    border: 1px solid #ddd;\n"
"    gridline-color: #eee;\n"
"    selection-background-color: #3498db;\n"
"    selection-color: white;\n"
"    font-size: 12px;\n"
"}\n"
"\n"
"QTableView::item {\n"
"    padding: 8px;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    padding: 8px;\n"
"    border: none;\n"
"    font-size: 12px;\n"
"}\n"
"\n"
"/* \350\276\223\345\205\245\346\241\206\346\240\267\345\274\217 */\n"
"QLineEdit, QComboBox, QDateEdit {\n"
"    border: 1px solid #ddd;\n"
"    border-radius: 3px;\n"
"    padding: 8px;\n"
"    font-size: 13px;\n"
"    min-height: 30px;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 25px;\n"
"    border-left-width: 1px;\n"
"    border-left-color: #ddd;\n"
"    border-left-style: solid;\n"
"}\n"
"\n"
"/* \346\214\211\351\222\256\346\240\267\345\274\217 */\n"
""
                        "QPushButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 4px;\n"
"    font-size: 13px;\n"
"    min-width: 100px;\n"
"    min-height: 30px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1a5276;\n"
"}\n"
"\n"
"/* \345\244\215\351\200\211\346\241\206\346\240\267\345\274\217 */\n"
"QCheckBox {\n"
"    spacing: 8px;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 18px;\n"
"    height: 18px;\n"
"}\n"
"\n"
"/* \347\212\266\346\200\201\346\240\217 */\n"
"QStatusBar {\n"
"    background-color: #ecf0f1;\n"
"    color: #7f8c8d;\n"
"    font-size: 12px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/* \345\210\206\347\273\204\346\241\206 */\n"
"QGroupBox {\n"
"    border: 1px solid #ddd;\n"
"    border-radius: 3px;\n"
"    margin-top: 15px;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
""
                        "    subcontrol-origin: margin;\n"
"    left: 15px;\n"
"    padding: 0 5px;\n"
"}\n"
"\n"
"/* \345\240\206\345\217\240\351\241\265\351\235\242\350\203\214\346\231\257 */\n"
"QStackedWidget {\n"
"    background-color: white;\n"
"    border: 1px solid #ddd;\n"
"    border-radius: 5px;\n"
"    margin: 10px;\n"
"}\n"
"\n"
"/* \351\224\200\345\224\256\351\241\265\351\235\242\350\264\255\347\211\251\350\275\246\345\214\272\345\237\237 */\n"
"#tblCart {\n"
"    background-color: #f9f9f9;\n"
"    border-top: 2px solid #3498db;\n"
"}\n"
"\n"
"/* \351\224\200\345\224\256\351\241\265\351\235\242\345\225\206\345\223\201\345\210\227\350\241\250 */\n"
"#tblProducts {\n"
"    background-color: #f9f9f9;\n"
"    border-top: 2px solid #2ecc71;\n"
"}\n"
"\n"
"/* \344\274\232\345\221\230\344\277\241\346\201\257\350\241\250\346\240\274 */\n"
"#tblMember_m {\n"
"    background-color: #f9f9f9;\n"
"    border-top: 2px solid #9b59b6;\n"
"}\n"
"\n"
"/* \344\274\232\345\221\230\346\266\210\350\264\271\347\273\237\350\256\241\350\241\250\346"
                        "\240\274 */\n"
"#tblMemberStats_m {\n"
"    background-color: #f9f9f9;\n"
"    border-top: 2px solid #e67e22;\n"
"}\n"
"\n"
"/* \346\212\245\350\241\250\346\225\260\346\215\256\350\241\250\346\240\274 */\n"
"#tblReport {\n"
"    background-color: #f9f9f9;\n"
"    border-top: 2px solid #1abc9c;\n"
"}\n"
"\n"
"/* \345\272\223\345\255\230\350\241\250\346\240\274 */\n"
"#tblInventory_in {\n"
"    background-color: #f9f9f9;\n"
"    border-top: 2px solid #f1c40f;\n"
"}\n"
"\n"
"/* \345\272\223\345\255\230\351\242\204\350\255\246\350\241\250\346\240\274 */\n"
"#tblWarning_in {\n"
"    background-color: #fff8e1;\n"
"    border-top: 2px solid #e74c3c;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        leftWidget = new QWidget(centralwidget);
        leftWidget->setObjectName("leftWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(leftWidget->sizePolicy().hasHeightForWidth());
        leftWidget->setSizePolicy(sizePolicy);
        leftWidget->setMinimumSize(QSize(150, 0));
        leftWidget->setStyleSheet(QString::fromUtf8("background-color: #2c3e50;"));
        verticalLayout = new QVBoxLayout(leftWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        btnSales = new QToolButton(leftWidget);
        btnSales->setObjectName("btnSales");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnSales->sizePolicy().hasHeightForWidth());
        btnSales->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(btnSales);

        btnInventory = new QToolButton(leftWidget);
        btnInventory->setObjectName("btnInventory");
        sizePolicy1.setHeightForWidth(btnInventory->sizePolicy().hasHeightForWidth());
        btnInventory->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(btnInventory);

        btnMember = new QToolButton(leftWidget);
        btnMember->setObjectName("btnMember");
        sizePolicy1.setHeightForWidth(btnMember->sizePolicy().hasHeightForWidth());
        btnMember->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(btnMember);

        btnReport = new QToolButton(leftWidget);
        btnReport->setObjectName("btnReport");
        sizePolicy1.setHeightForWidth(btnReport->sizePolicy().hasHeightForWidth());
        btnReport->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(btnReport);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        btnLogout = new QToolButton(leftWidget);
        btnLogout->setObjectName("btnLogout");
        sizePolicy1.setHeightForWidth(btnLogout->sizePolicy().hasHeightForWidth());
        btnLogout->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(btnLogout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        horizontalLayout->addWidget(leftWidget);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setStyleSheet(QString::fromUtf8("/* \344\270\273\347\252\227\345\217\243\350\203\214\346\231\257 */\n"
"QMainWindow {\n"
"    background-color: #f0f0f0;\n"
"}\n"
"\n"
"/* \345\267\246\344\276\247\345\257\274\350\210\252\345\214\272\345\237\237 */\n"
"#centralwidget {\n"
"    background-color: #2c3e50;\n"
"}\n"
"\n"
"/* \345\267\246\344\276\247\345\257\274\350\210\252\346\214\211\351\222\256 */\n"
"QToolButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 12px;\n"
"    font-size: 14px;\n"
"    border-radius: 4px;\n"
"    margin: 5px;\n"
"    text-align: left;\n"
"    padding-left: 20px;\n"
"    min-width: 120px;\n"
"}\n"
"\n"
"QToolButton:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"\n"
"QToolButton:pressed {\n"
"    background-color: #1a5276;\n"
"}\n"
"\n"
"/* \351\200\200\345\207\272\346\214\211\351\222\256\347\211\271\346\256\212\346\240\267\345\274\217 */\n"
"#btnLogout {\n"
"    background-color: #e74c3c;\n"
"}\n"
"\n"
"#btnLogout:hover {\n"
"    background-color: #c0392b;\n"
"}\n"
""
                        "\n"
"/* \345\206\205\345\256\271\345\214\272\345\237\237\346\240\207\351\242\230 */\n"
"QLabel[text^=\"<html>\"] {\n"
"    color: #2c3e50;\n"
"    font-size: 16px;\n"
"}\n"
"\n"
"/* \350\241\250\346\240\274\346\240\267\345\274\217 */\n"
"QTableView {\n"
"    background-color: white;\n"
"    border: 1px solid #ddd;\n"
"    gridline-color: #eee;\n"
"    selection-background-color: #3498db;\n"
"    selection-color: white;\n"
"    font-size: 12px;\n"
"}\n"
"\n"
"QTableView::item {\n"
"    padding: 8px;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    padding: 8px;\n"
"    border: none;\n"
"    font-size: 12px;\n"
"}\n"
"\n"
"/* \350\276\223\345\205\245\346\241\206\346\240\267\345\274\217 */\n"
"QLineEdit, QComboBox, QDateEdit {\n"
"    border: 1px solid #ddd;\n"
"    border-radius: 3px;\n"
"    padding: 8px;\n"
"    font-size: 13px;\n"
"    min-height: 30px;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: t"
                        "op right;\n"
"    width: 25px;\n"
"    border-left-width: 1px;\n"
"    border-left-color: #ddd;\n"
"    border-left-style: solid;\n"
"}\n"
"\n"
"/* \346\214\211\351\222\256\346\240\267\345\274\217 */\n"
"QPushButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 4px;\n"
"    font-size: 13px;\n"
"    min-width: 100px;\n"
"    min-height: 30px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1a5276;\n"
"}\n"
"\n"
"/* \345\244\215\351\200\211\346\241\206\346\240\267\345\274\217 */\n"
"QCheckBox {\n"
"    spacing: 8px;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 18px;\n"
"    height: 18px;\n"
"}\n"
"\n"
"/* \347\212\266\346\200\201\346\240\217 */\n"
"QStatusBar {\n"
"    background-color: #ecf0f1;\n"
"    color: #7f8c8d;\n"
"    font-size: 12px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/* \345\210\206\347\273\204\346"
                        "\241\206 */\n"
"QGroupBox {\n"
"    border: 1px solid #ddd;\n"
"    border-radius: 3px;\n"
"    margin-top: 15px;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 15px;\n"
"    padding: 0 5px;\n"
"}\n"
"\n"
"/* \345\240\206\345\217\240\351\241\265\351\235\242\350\203\214\346\231\257 */\n"
"QStackedWidget {\n"
"    background-color: white;\n"
"    border: 1px solid #ddd;\n"
"    border-radius: 5px;\n"
"    margin: 10px;\n"
"}\n"
"\n"
"/* \351\224\200\345\224\256\351\241\265\351\235\242\350\264\255\347\211\251\350\275\246\345\214\272\345\237\237 */\n"
"#tblCart {\n"
"    background-color: #f9f9f9;\n"
"    border-top: 2px solid #3498db;\n"
"}\n"
"\n"
"/* \351\224\200\345\224\256\351\241\265\351\235\242\345\225\206\345\223\201\345\210\227\350\241\250 */\n"
"#tblProducts {\n"
"    background-color: #f9f9f9;\n"
"    border-top: 2px solid #2ecc71;\n"
"}\n"
"\n"
"/* \344\274\232\345\221\230\344\277\241\346\201\257\350\241\250\346\240"
                        "\274 */\n"
"#tblMember_m {\n"
"    background-color: #f9f9f9;\n"
"    border-top: 2px solid #9b59b6;\n"
"}\n"
"\n"
"/* \344\274\232\345\221\230\346\266\210\350\264\271\347\273\237\350\256\241\350\241\250\346\240\274 */\n"
"#tblMemberStats_m {\n"
"    background-color: #f9f9f9;\n"
"    border-top: 2px solid #e67e22;\n"
"}\n"
"\n"
"/* \346\212\245\350\241\250\346\225\260\346\215\256\350\241\250\346\240\274 */\n"
"#tblReport {\n"
"    background-color: #f9f9f9;\n"
"    border-top: 2px solid #1abc9c;\n"
"}\n"
"\n"
"/* \345\272\223\345\255\230\350\241\250\346\240\274 */\n"
"#tblInventory_in {\n"
"    background-color: #f9f9f9;\n"
"    border-top: 2px solid #f1c40f;\n"
"}\n"
"\n"
"/* \345\272\223\345\255\230\351\242\204\350\255\246\350\241\250\346\240\274 */\n"
"#tblWarning_in {\n"
"    background-color: #fff8e1;\n"
"    border-top: 2px solid #e74c3c;\n"
"}"));
        page_sales = new SalesWidget();
        page_sales->setObjectName("page_sales");
        verticalLayout_2 = new QVBoxLayout(page_sales);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(page_sales);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        txtSearch = new QLineEdit(page_sales);
        txtSearch->setObjectName("txtSearch");
        txtSearch->setMinimumSize(QSize(0, 48));

        horizontalLayout_2->addWidget(txtSearch);

        btnSearch = new QPushButton(page_sales);
        btnSearch->setObjectName("btnSearch");
        btnSearch->setMinimumSize(QSize(140, 50));

        horizontalLayout_2->addWidget(btnSearch);


        verticalLayout_2->addLayout(horizontalLayout_2);

        label_4 = new QLabel(page_sales);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        tblProducts = new QTableView(page_sales);
        tblProducts->setObjectName("tblProducts");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(tblProducts->sizePolicy().hasHeightForWidth());
        tblProducts->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(tblProducts);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        chkMember = new QCheckBox(page_sales);
        chkMember->setObjectName("chkMember");

        verticalLayout_3->addWidget(chkMember);

        label_2 = new QLabel(page_sales);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);

        txtMemberId = new QLineEdit(page_sales);
        txtMemberId->setObjectName("txtMemberId");

        verticalLayout_3->addWidget(txtMemberId);

        label_3 = new QLabel(page_sales);
        label_3->setObjectName("label_3");

        verticalLayout_3->addWidget(label_3);

        txtMemberName = new QLineEdit(page_sales);
        txtMemberName->setObjectName("txtMemberName");

        verticalLayout_3->addWidget(txtMemberName);

        label_19 = new QLabel(page_sales);
        label_19->setObjectName("label_19");

        verticalLayout_3->addWidget(label_19);

        cbxPaymentMethod = new QComboBox(page_sales);
        cbxPaymentMethod->addItem(QString());
        cbxPaymentMethod->addItem(QString());
        cbxPaymentMethod->addItem(QString());
        cbxPaymentMethod->addItem(QString());
        cbxPaymentMethod->setObjectName("cbxPaymentMethod");

        verticalLayout_3->addWidget(cbxPaymentMethod);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        btnAdd = new QPushButton(page_sales);
        btnAdd->setObjectName("btnAdd");

        verticalLayout_3->addWidget(btnAdd);

        btnRemove = new QPushButton(page_sales);
        btnRemove->setObjectName("btnRemove");

        verticalLayout_3->addWidget(btnRemove);

        btnCheckout = new QPushButton(page_sales);
        btnCheckout->setObjectName("btnCheckout");

        verticalLayout_3->addWidget(btnCheckout);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_11 = new QLabel(page_sales);
        label_11->setObjectName("label_11");

        horizontalLayout_4->addWidget(label_11);

        lblTotal = new QLabel(page_sales);
        lblTotal->setObjectName("lblTotal");

        horizontalLayout_4->addWidget(lblTotal);


        verticalLayout_3->addLayout(horizontalLayout_4);


        horizontalLayout_3->addLayout(verticalLayout_3);


        verticalLayout_2->addLayout(horizontalLayout_3);

        label_5 = new QLabel(page_sales);
        label_5->setObjectName("label_5");

        verticalLayout_2->addWidget(label_5);

        tblCart = new QTableView(page_sales);
        tblCart->setObjectName("tblCart");
        sizePolicy2.setHeightForWidth(tblCart->sizePolicy().hasHeightForWidth());
        tblCart->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(tblCart);

        stackedWidget->addWidget(page_sales);
        page_member = new member_widget();
        page_member->setObjectName("page_member");
        verticalLayout_4 = new QVBoxLayout(page_member);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_7 = new QLabel(page_member);
        label_7->setObjectName("label_7");

        verticalLayout_4->addWidget(label_7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        txtSearch_m = new QLineEdit(page_member);
        txtSearch_m->setObjectName("txtSearch_m");
        txtSearch_m->setMinimumSize(QSize(0, 48));

        horizontalLayout_5->addWidget(txtSearch_m);

        btnSearch_m = new QPushButton(page_member);
        btnSearch_m->setObjectName("btnSearch_m");
        btnSearch_m->setMinimumSize(QSize(140, 50));

        horizontalLayout_5->addWidget(btnSearch_m);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_9 = new QLabel(page_member);
        label_9->setObjectName("label_9");

        horizontalLayout_6->addWidget(label_9);

        cmbMemberLevel_m = new QComboBox(page_member);
        cmbMemberLevel_m->setObjectName("cmbMemberLevel_m");

        horizontalLayout_6->addWidget(cmbMemberLevel_m);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout_6);

        label_10 = new QLabel(page_member);
        label_10->setObjectName("label_10");

        verticalLayout_4->addWidget(label_10);

        tblMember_m = new QTableView(page_member);
        tblMember_m->setObjectName("tblMember_m");
        sizePolicy2.setHeightForWidth(tblMember_m->sizePolicy().hasHeightForWidth());
        tblMember_m->setSizePolicy(sizePolicy2);

        verticalLayout_4->addWidget(tblMember_m);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        btnAddMember_m = new QPushButton(page_member);
        btnAddMember_m->setObjectName("btnAddMember_m");

        horizontalLayout_7->addWidget(btnAddMember_m);

        btnRefresh_m = new QPushButton(page_member);
        btnRefresh_m->setObjectName("btnRefresh_m");

        horizontalLayout_7->addWidget(btnRefresh_m);

        btnEditMember_m = new QPushButton(page_member);
        btnEditMember_m->setObjectName("btnEditMember_m");

        horizontalLayout_7->addWidget(btnEditMember_m);


        verticalLayout_4->addLayout(horizontalLayout_7);

        label_12 = new QLabel(page_member);
        label_12->setObjectName("label_12");

        verticalLayout_4->addWidget(label_12);

        tblMemberStats_m = new QTableView(page_member);
        tblMemberStats_m->setObjectName("tblMemberStats_m");
        sizePolicy2.setHeightForWidth(tblMemberStats_m->sizePolicy().hasHeightForWidth());
        tblMemberStats_m->setSizePolicy(sizePolicy2);

        verticalLayout_4->addWidget(tblMemberStats_m);

        stackedWidget->addWidget(page_member);
        page_report = new report_widget();
        page_report->setObjectName("page_report");
        verticalLayout_5 = new QVBoxLayout(page_report);
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_8 = new QLabel(page_report);
        label_8->setObjectName("label_8");

        verticalLayout_5->addWidget(label_8);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_13 = new QLabel(page_report);
        label_13->setObjectName("label_13");

        horizontalLayout_8->addWidget(label_13);

        dateStart_report = new QDateEdit(page_report);
        dateStart_report->setObjectName("dateStart_report");

        horizontalLayout_8->addWidget(dateStart_report);

        label_14 = new QLabel(page_report);
        label_14->setObjectName("label_14");

        horizontalLayout_8->addWidget(label_14);

        dateEnd_report = new QDateEdit(page_report);
        dateEnd_report->setObjectName("dateEnd_report");

        horizontalLayout_8->addWidget(dateEnd_report);

        label_15 = new QLabel(page_report);
        label_15->setObjectName("label_15");

        horizontalLayout_8->addWidget(label_15);

        cmbReportType = new QComboBox(page_report);
        cmbReportType->setObjectName("cmbReportType");

        horizontalLayout_8->addWidget(cmbReportType);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        btnGenerate_report = new QPushButton(page_report);
        btnGenerate_report->setObjectName("btnGenerate_report");

        horizontalLayout_8->addWidget(btnGenerate_report);


        verticalLayout_5->addLayout(horizontalLayout_8);

        label_16 = new QLabel(page_report);
        label_16->setObjectName("label_16");

        verticalLayout_5->addWidget(label_16);

        tblReport = new QTableView(page_report);
        tblReport->setObjectName("tblReport");
        sizePolicy2.setHeightForWidth(tblReport->sizePolicy().hasHeightForWidth());
        tblReport->setSizePolicy(sizePolicy2);

        verticalLayout_5->addWidget(tblReport);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        btnExport_report = new QPushButton(page_report);
        btnExport_report->setObjectName("btnExport_report");

        horizontalLayout_9->addWidget(btnExport_report);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        btnRefresh_report = new QPushButton(page_report);
        btnRefresh_report->setObjectName("btnRefresh_report");

        horizontalLayout_9->addWidget(btnRefresh_report);


        verticalLayout_5->addLayout(horizontalLayout_9);

        stackedWidget->addWidget(page_report);
        page_inventory = new inventory_widget();
        page_inventory->setObjectName("page_inventory");
        verticalLayout_6 = new QVBoxLayout(page_inventory);
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_6 = new QLabel(page_inventory);
        label_6->setObjectName("label_6");

        verticalLayout_6->addWidget(label_6);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        txtSearch_in = new QLineEdit(page_inventory);
        txtSearch_in->setObjectName("txtSearch_in");
        txtSearch_in->setMinimumSize(QSize(0, 48));

        horizontalLayout_10->addWidget(txtSearch_in);

        btnSearch_in = new QPushButton(page_inventory);
        btnSearch_in->setObjectName("btnSearch_in");
        btnSearch_in->setMinimumSize(QSize(140, 50));

        horizontalLayout_10->addWidget(btnSearch_in);


        verticalLayout_6->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_20 = new QLabel(page_inventory);
        label_20->setObjectName("label_20");

        horizontalLayout_11->addWidget(label_20);

        cmbStockStatus_in = new QComboBox(page_inventory);
        cmbStockStatus_in->setObjectName("cmbStockStatus_in");

        horizontalLayout_11->addWidget(cmbStockStatus_in);

        label_21 = new QLabel(page_inventory);
        label_21->setObjectName("label_21");

        horizontalLayout_11->addWidget(label_21);

        cmbSupplier_in = new QComboBox(page_inventory);
        cmbSupplier_in->setObjectName("cmbSupplier_in");

        horizontalLayout_11->addWidget(cmbSupplier_in);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_4);


        verticalLayout_6->addLayout(horizontalLayout_11);

        label_22 = new QLabel(page_inventory);
        label_22->setObjectName("label_22");

        verticalLayout_6->addWidget(label_22);

        tblInventory_in = new QTableView(page_inventory);
        tblInventory_in->setObjectName("tblInventory_in");
        sizePolicy2.setHeightForWidth(tblInventory_in->sizePolicy().hasHeightForWidth());
        tblInventory_in->setSizePolicy(sizePolicy2);

        verticalLayout_6->addWidget(tblInventory_in);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        btnStockIn_in = new QPushButton(page_inventory);
        btnStockIn_in->setObjectName("btnStockIn_in");

        horizontalLayout_12->addWidget(btnStockIn_in);

        btnAddProduct_in = new QPushButton(page_inventory);
        btnAddProduct_in->setObjectName("btnAddProduct_in");

        horizontalLayout_12->addWidget(btnAddProduct_in);

        btnEditProduct_in = new QPushButton(page_inventory);
        btnEditProduct_in->setObjectName("btnEditProduct_in");

        horizontalLayout_12->addWidget(btnEditProduct_in);

        btnRefresh_in = new QPushButton(page_inventory);
        btnRefresh_in->setObjectName("btnRefresh_in");

        horizontalLayout_12->addWidget(btnRefresh_in);


        verticalLayout_6->addLayout(horizontalLayout_12);

        label_23 = new QLabel(page_inventory);
        label_23->setObjectName("label_23");

        verticalLayout_6->addWidget(label_23);

        tblWarning_in = new QTableView(page_inventory);
        tblWarning_in->setObjectName("tblWarning_in");
        sizePolicy2.setHeightForWidth(tblWarning_in->sizePolicy().hasHeightForWidth());
        tblWarning_in->setSizePolicy(sizePolicy2);

        verticalLayout_6->addWidget(tblWarning_in);

        stackedWidget->addWidget(page_inventory);

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1024, 18));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\266\205\345\270\202\351\224\200\345\224\256\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        btnSales->setText(QCoreApplication::translate("MainWindow", "\351\224\200\345\224\256", nullptr));
        btnInventory->setText(QCoreApplication::translate("MainWindow", "\345\272\223\345\255\230", nullptr));
        btnMember->setText(QCoreApplication::translate("MainWindow", "\344\274\232\345\221\230", nullptr));
        btnReport->setText(QCoreApplication::translate("MainWindow", "\346\212\245\350\241\250", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:700; font-style:italic; color:#00aaff;\">\350\266\205\345\270\202\351\224\200\345\224\256\347\256\241\347\220\206\347\263\273\347\273\237 - \351\224\200\345\224\256\346\250\241\345\235\227</span></p></body></html>", nullptr));
        btnSearch->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">\345\225\206\345\223\201\345\210\227\350\241\250</span></p></body></html>", nullptr));
        chkMember->setText(QCoreApplication::translate("MainWindow", "\344\274\232\345\221\230", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"right\"><span style=\" font-size:10pt;\">\344\274\232\345\221\230ID: </span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"right\"><span style=\" font-size:10pt;\">\345\247\223\345\220\215:</span></p></body></html>", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\346\224\257\344\273\230\346\226\271\345\274\217:", nullptr));
        cbxPaymentMethod->setItemText(0, QCoreApplication::translate("MainWindow", "\344\274\232\345\221\230\345\215\241", nullptr));
        cbxPaymentMethod->setItemText(1, QCoreApplication::translate("MainWindow", "\346\224\257\344\273\230\345\256\235", nullptr));
        cbxPaymentMethod->setItemText(2, QCoreApplication::translate("MainWindow", "\347\216\260\351\207\221", nullptr));
        cbxPaymentMethod->setItemText(3, QCoreApplication::translate("MainWindow", "\345\276\256\344\277\241", nullptr));

        btnAdd->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\345\210\260\350\264\255\347\211\251\350\275\246", nullptr));
        btnRemove->setText(QCoreApplication::translate("MainWindow", "\344\273\216\350\264\255\347\211\251\350\275\246\347\247\273\351\231\244", nullptr));
        btnCheckout->setText(QCoreApplication::translate("MainWindow", "\347\273\223\350\264\246", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\346\200\273\350\256\241\357\274\232</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">\350\264\255\347\211\251\350\275\246</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:700; font-style:italic; color:#00aaff;\">\350\266\205\345\270\202\351\224\200\345\224\256\347\256\241\347\220\206\347\263\273\347\273\237 - \344\274\232\345\221\230\346\250\241\345\235\227</span></p></body></html>", nullptr));
        btnSearch_m->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700; font-style:italic;\">\344\274\232\345\221\230\347\255\211\347\272\247\347\255\233\351\200\211:</span></p></body></html>", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\344\274\232\345\221\230\344\277\241\346\201\257\350\241\250\346\240\274</span></p></body></html>", nullptr));
        btnAddMember_m->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\344\274\232\345\221\230", nullptr));
        btnRefresh_m->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        btnEditMember_m->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221\344\274\232\345\221\230", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\344\274\232\345\221\230\346\266\210\350\264\271\347\273\237\350\256\241</span></p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:700; font-style:italic; color:#00aaff;\">\350\266\205\345\270\202\351\224\200\345\224\256\347\256\241\347\220\206\347\263\273\347\273\237 - \346\212\245\350\241\250\346\250\241\345\235\227</span></p></body></html>", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\346\227\266\351\227\264\350\214\203\345\233\264:</span></p></body></html>", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-weight:700;\">\350\207\263 </span></p></body></html>", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\346\212\245\350\241\250\347\261\273\345\236\213:</span></p></body></html>", nullptr));
        btnGenerate_report->setText(QCoreApplication::translate("MainWindow", "\347\224\237\346\210\220\346\212\245\350\241\250", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\346\212\245\350\241\250\346\225\260\346\215\256\350\241\250\346\240\274</span></p></body></html>", nullptr));
        btnExport_report->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272Excel", nullptr));
        btnRefresh_report->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:700; font-style:italic; color:#00aaff;\">\350\266\205\345\270\202\351\224\200\345\224\256\347\256\241\347\220\206\347\263\273\347\273\237 - \345\272\223\345\255\230\346\250\241\345\235\227</span></p></body></html>", nullptr));
        btnSearch_in->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">\345\272\223\345\255\230\347\212\266\346\200\201\347\255\233\351\200\211:</span></p></body></html>", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"right\"><span style=\" font-size:10pt; font-weight:700;\">\344\276\233\345\272\224\345\225\206\347\255\233\351\200\211:</span></p></body></html>", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">\345\275\223\345\211\215\345\272\223\345\255\230</span></p></body></html>", nullptr));
        btnStockIn_in->setText(QCoreApplication::translate("MainWindow", "\350\277\233\350\264\247", nullptr));
        btnAddProduct_in->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\345\225\206\345\223\201", nullptr));
        btnEditProduct_in->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221\345\225\206\345\223\201", nullptr));
        btnRefresh_in->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">\345\272\223\345\255\230\351\242\204\350\255\246\344\277\241\346\201\257</span></p></body></html>", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
