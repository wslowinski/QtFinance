#include "SqlFilter.h"
#include "Code/PeriodTypes.h"

QString filterRecordsByPeriod(const QString& table, int type, QDate dtFrom, QDate dtTo)
{
    int monthNumber = QDate::currentDate().month();
    int currentYear = QDate::currentDate().year();
    if (PeriodType::ALL == type)
    {
        return QString{"SELECT * FROM " + table + " WHERE id IS NOT NULL"};
    }
    else if (PeriodType::CURRENT_DAY == type)
    {
        return QString{"SELECT * FROM "} + table + QString{" WHERE date = '"} +
            QString{QDate::currentDate().toString("yyyy-MM-dd")} + QString{"'"};
    }
    else if (PeriodType::CURRENT_MONTH == type)
    {
        int daysInCurrentMonth = QDate::currentDate().daysInMonth();
        return QString{"SELECT * FROM "} + table + QString{" WHERE date >= '"} +
            QString{QDate(currentYear, monthNumber, 1).toString("yyyy-MM-dd")} + QString{"' AND date <= '"} +
            QString{QDate(currentYear, monthNumber, daysInCurrentMonth).toString("yyyy-MM-dd") + "'"};
    }
    else if (PeriodType::CURRENT_YEAR == type)
    {
        return QString{"SELECT * FROM "} + table + QString{" WHERE date >= '"} +
            QString{QDate(currentYear, 1, 1).toString("yyyy-MM-dd")} + QString{"' AND date <= '"} +
            QString{QDate(currentYear, 12, 31).toString("yyyy-MM-dd") + "'"};
    }
    else if (PeriodType::PREVIOUS_MONTH == type)
    {
        int previousMonth = (monthNumber != 1) ? (monthNumber - 1) : 12;
        int year = (previousMonth != 12) ? currentYear : (currentYear - 1);
        return QString{"SELECT * FROM "} + table + QString{" WHERE date >= '"} +
            QString{QDate(year, previousMonth, 1).toString("yyyy-MM-dd")} + QString{"' AND date <= '"} +
            QString{QDate(year, previousMonth,
            QDate(year, previousMonth, 1).daysInMonth()).toString("yyyy-MM-dd") + "'"};
    }
    else if (PeriodType::PREVIOUS_YEAR == type)
    {
        int previousYear = QDate::currentDate().year() - 1;
        return QString{"SELECT * FROM "} + table + QString{" WHERE date >= '"} +
            QString{QDate(previousYear, 1, 1).toString("yyyy-MM-dd")} + QString{"' AND date <= '"} +
            QString{QDate(previousYear, 12, 31).toString("yyyy-MM-dd") + "'"};
    }
    else if (PeriodType::NON_STANDARD == type)
    {
    return QString{"SELECT * FROM " + table + " WHERE date >= '" +
        dtFrom.toString("yyyy-MM-dd") + "' AND date <= '" +
        dtTo.toString("yyyy-MM-dd") + "'"};
    }
    return QString{"SELECT * FROM " + table};
}


