#ifndef SALESWIDGET_H
#define SALESWIDGET_H

#include <QWidget>
#include <QStandardItemModel>

class SalesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SalesWidget(QWidget *parent = nullptr);
    ~SalesWidget();

    void setSalesPage(QWidget *page_sales);  // 关键：设置要操作的页面

    void refresh();  // 刷新界面

public slots:
    void onMemberChecked(bool checked);  // 会员复选框状态变化

private slots:
    void onSearchProduct();    // 搜索商品
    void onAddToCart();        // 添加到购物车
    void onRemoveFromCart();   // 从购物车移除
    void onCheckout();         // 结账

private:
    QWidget *m_salesPage;  // 指向 MainWindow 的 page_sales
    QStandardItemModel *m_productModel;  // 商品列表模型
    QStandardItemModel *m_cartModel;     // 购物车模型

    void loadAllProducts();
    void setupModels();       // 初始化模型
    void setupConnections();  // 连接信号槽
    double calculateTotal() const;  // 计算总金额
};

#endif // SALESWIDGET_H
