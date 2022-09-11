#ifndef EXPENSEANALYSIS_H
#define EXPENSEANALYSIS_H

#include <QSqlDatabase>
#include <QDate>

class ExpenseAnalysis
{
public:
    explicit ExpenseAnalysis(QSqlDatabase& database);
    double getCategoryExpenseSum(const QString& category, int type,
                                 const QDate& from = QDate::currentDate(),
                                 const QDate& to = QDate::currentDate());
private:
    QSqlDatabase& m_database;
};

#endif
