// headers/database/database_manager.h
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    // 单例访问点
    static DatabaseManager& instance();

    // 禁止拷贝和赋值
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    // 连接数据库
    bool connect(const QString& host,
                 const QString& dbName,
                 const QString& user,
                 const QString& password,
                 int port = 3306);

    // 获取数据库对象
    QSqlDatabase database() const;

    // 获取最后错误信息
    QString lastError() const;

    // 用户会话管理
    void setCurrentUserId(int userId);
    int currentUserId() const;

private:
    // 私有构造函数
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    QSqlDatabase m_db;
    int m_currentUserId = -1; // 当前登录用户ID，-1表示未登录
};

#endif // DATABASEMANAGER_H
