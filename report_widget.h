// report_widget.h
#ifndef REPORT_WIDGET_H
#define REPORT_WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QSqlQueryModel>

class report_widget : public QWidget
{
    Q_OBJECT
public:
    explicit report_widget(QWidget *parent = nullptr);
    ~report_widget();

    void set_report_page(QWidget *page_report);
    void refresh();

private slots:
    void on_generate_report();
    void on_export_report();
    void on_refresh_clicked();

private:
    void setup_models();
    void setup_connections();
    void load_report_data();

    QWidget *m_report_page = nullptr;
    QSqlQueryModel *m_report_model = nullptr;
};

#endif // REPORT_WIDGET_H
