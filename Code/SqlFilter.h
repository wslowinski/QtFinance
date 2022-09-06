#ifndef SQLFILTER_H
#define SQLFILTER_H

#include <QString>
#include <QDate>

QString filterRecordsByPeriod(const QString& table, int type,
    QDate dtFrom = QDate::currentDate(), QDate dtTo = QDate::currentDate());

#endif
