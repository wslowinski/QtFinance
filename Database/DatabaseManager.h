#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "DatabaseClass/ExpenseDao.h"

class DatabaseManager
{
public:
    explicit DatabaseManager(const QString& path = "/home/vladyslav/Database/budget.db");
    static void debugQuery(const QSqlQuery& query);
    ~DatabaseManager();
    static DatabaseManager& instance();

private:
    void updateDatabase();

    QSqlDatabase m_database;
    const ExpenseDao m_expenseDao;
};

#endif
