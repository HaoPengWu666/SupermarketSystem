// sources/database/database_manager.cpp
#include "databasemanager.h"
#include <QDebug>
#include <QMessageBox>

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
}

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::connect(const QString& host,
                              const QString& dbName,
                              const QString& user,
                              const QString& password,
                              int port)
{
    m_db.setHostName(host);
    m_db.setDatabaseName(dbName);
    m_db.setUserName(user);
    m_db.setPassword(password);
    m_db.setPort(port);

    if (!m_db.open()) {
        QMessageBox::critical(nullptr, "数据库错误",
                              QString("连接失败:\n主机: %1\n数据库: %2\n错误: %3")
                                  .arg(host)
                                  .arg(dbName)
                                  .arg(m_db.lastError().text()));
        return false;
    }

    QMessageBox::information(nullptr, "成功", "数据库连接已建立");
    return true;
}

QSqlDatabase DatabaseManager::database() const
{
    return m_db;
}

QString DatabaseManager::lastError() const
{
    return m_db.lastError().text();
}

void DatabaseManager::setCurrentUserId(int userId)
{
    m_currentUserId = userId;
}

int DatabaseManager::currentUserId() const
{
    return m_currentUserId;    //我没有设置登出时置毁回-1，所以想换个用户，要直接退出系统重进
}

DatabaseManager::~DatabaseManager()
{
    if (m_db.isOpen()) {
        m_db.close();
        qDebug() << "Database connection closed";
    }
}
