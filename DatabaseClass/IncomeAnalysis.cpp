#include "IncomeAnalysis.h"
#include "Code/SqlFilter.h"
#include "Database/DatabaseManager.h"

#include <QSqlQuery>

IncomeAnalysis::IncomeAnalysis(QSqlDatabase& database):
    m_database(database)
{
}

double IncomeAnalysis::getIncomesSum(int type, const QDate& from, const QDate& to)
{
    const QString& sql = filterRecordsByPeriod("incomes", type, from, to);
    QSqlQuery query(sql, m_database);
    query.exec();
    DatabaseManager::debugQuery(query);
    double sum = 0;
    while (query.next())
    {
        sum = sum + query.value("income").toDouble();
    }
    return sum;
}
