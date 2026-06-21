#ifndef MEMBER_WIDGET_H
#define MEMBER_WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QSqlQueryModel>

class member_widget : public QWidget
{
    Q_OBJECT
public:
    explicit member_widget(QWidget *parent = nullptr);
    ~member_widget();

    void set_member_page(QWidget *page_member);
    void refresh();

private slots:
    void on_search_member();
    void on_add_member_clicked();
    void on_edit_member_clicked();
    void on_delete_member_clicked();
    void on_refresh_clicked();

private:
    void setup_models();
    void setup_connections();
    void load_member_data();
    void setupStatsModel();        // 初始化统计模型
    void loadMemberStats();        // 加载会员统计数据

    QWidget *m_member_page = nullptr;
    QStandardItemModel *m_member_model = nullptr;
    QSqlQueryModel *m_statsModel;  // 会员消费统计模型
};

#endif // MEMBER_WIDGET_H
