#ifndef INVENTORY_WIDGET_H
#define INVENTORY_WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QSqlQueryModel>

class inventory_widget : public QWidget
{
    Q_OBJECT

public:
    explicit inventory_widget(QWidget *parent = nullptr);
    ~inventory_widget();

    void set_inventory_page(QWidget *page_inventory);  // 设置要操作的页面
    void refresh();  // 刷新界面数据

public slots:
    void on_stock_status_filter_changed(int index);  // 库存状态筛选变化
    void on_supplier_filter_changed(int index);     // 供应商筛选变化

private slots:
    void on_search_inventory();       // 搜索商品
    void on_stock_in_clicked();        // 进货按钮点击
    void on_edit_product_clicked();    // 编辑商品点击
    void on_add_product_clicked();     // 添加商品点击
    void on_refresh_clicked();        // 刷新按钮点击

private:
    QWidget *m_inventory_page;       // 指向MainWindow的库存页面
    QStandardItemModel *m_inventory_model;  // 主库存表格模型
    QSqlQueryModel *m_warning_model;  // 预警表格模型

    void load_inventory_data();       // 加载库存数据
    void load_warning_data();         // 加载预警数据
    void setup_models();             // 初始化模型
    void setup_connections();        // 连接信号槽
    void setup_filters();            // 初始化筛选器数据
    void show_product_dialog(bool isEditMode, const QString& barcode = "");
    bool validate_product_data(const QString& name, const QString& price, const QString& cost);
};

#endif // INVENTORY_WIDGET_H
