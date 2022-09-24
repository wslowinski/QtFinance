#include "ExpenseAnalysis.h"
#include "Code/SqlFilter.h"
#include "Database/DatabaseManager.h"

#include <QSqlQuery>

ExpenseAnalysis::ExpenseAnalysis(QSqlDatabase& database):
    m_database(database)
{
}


double ExpenseAnalysis::getCategoryExpenseSum(const QString& category, int type,
                             const QDate& from, const QDate& to)
{
    const QString& sql = filterRecordsByPeriod("expenses", type, from, to) +
            QString{" AND category = '" + category + "'"};
    QSqlQuery query(sql, m_database);
    query.exec();
    DatabaseManager::debugQuery(query);
    double sum = 0;
    while (query.next())
    {
        sum = sum + query.value("expense").toDouble();
    }
    return sum;
}

