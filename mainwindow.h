#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStackedWidget>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class SalesWidget;
class inventory_widget;
class member_widget;
class report_widget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setCurrentUser(int userId, const QString &userName, const QString &role);
    int getCurrentUserId() const { return m_currentUserId; }

private slots:
    void onSalesClicked();
    void onInventoryClicked();
    void onMemberClicked();
    void onReportClicked();
    void onLogoutClicked();

private:
    Ui::MainWindow *ui;
    QStackedWidget *m_stackedWidget;

    SalesWidget *m_salesWidget;
    inventory_widget *m_inventoryWidget;
    member_widget *m_memberWidget;
    report_widget *m_reportWidget;

    int m_currentUserId;
    QString m_currentUserName;
    QString m_currentUserRole;

    void setupUI();
    void setupConnections();
    void updateUserInfo();
};

#endif // MAINWINDOW_H
