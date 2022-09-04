#include "SqlFilter.h"

#include <QDate>

QString filterRecordsByPeriod(const QString& table, const PeriodType& type)
{
    switch (type) {
    case PeriodType::ALL:
        return QString{"SELECT * FROM "} + table;
    case PeriodType::CURRENT_DAY:
        return QString{"SELECT * FROM "} + table + QString{" WHERE date = '"} +
            QString{QDate::currentDate().toString("yyyy-MM-dd")} + QString{"'"};
    default:
        return QString{"SELECT * FROM expenses"};
    }

}
