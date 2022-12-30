#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "DatabaseClass/ExpenseDao.h"
#include "DatabaseClass/IncomeDao.h"
#include "DatabaseClass/ExpenseAnalysis.h"
#include "DatabaseClass/IncomeAnalysis.h"
#include "DatabaseClass/CategoryDao.h"

class DatabaseManager
{
public:
    explicit DatabaseManager(const QString& path = QString(getenv("HOME")) + "/Database/budget.db");
    static void debugQuery(const QSqlQuery& query);
    ~DatabaseManager();
    static DatabaseManager& getInstance();

    const ExpenseDao expenseDao_;
    const IncomeDao m_incomeDao;
    const CategoryDao categoryDao_;
    ExpenseAnalysis m_expenseAnalysis;
    IncomeAnalysis m_incomeAnalysis;

private:
    void updateDatabase();

    QSqlDatabase database_;
};

#endif
