#ifndef INCOMEANALYSIS_H
#define INCOMEANALYSIS_H

#include <QSqlDatabase>
#include <QDate>

class IncomeAnalysis
{
public:
    explicit IncomeAnalysis(QSqlDatabase& database);
    double getIncomesSum(int type, const QDate& from = QDate::currentDate(),
        const QDate& to = QDate::currentDate());

private:
    QSqlDatabase& m_database;
};

#endif
