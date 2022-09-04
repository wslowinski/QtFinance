#ifndef SQLFILTER_H
#define SQLFILTER_H

#include "Code/PeriodTypes.h"

#include <QString>

QString filterRecordsByPeriod(const QString& table, const PeriodType& type);

#endif
