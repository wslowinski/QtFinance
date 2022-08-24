#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "DatabaseClass/ExpenseDao.h"
#include "DatabaseClass/IncomeDao.h"

class DatabaseManager
{
public:
    explicit DatabaseManager(const QString& path = "/home/vladyslav/Database/budget.db");
    static void debugQuery(const QSqlQuery& query);
    ~DatabaseManager();
    static DatabaseManager& instance();

    const ExpenseDao m_expenseDao;
    const IncomeDao m_incomeDao;

private:
    void updateDatabase();

    QSqlDatabase m_database;
};

#endif
