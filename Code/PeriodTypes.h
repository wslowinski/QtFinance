#ifndef PERIODTYPES_H
#define PERIODTYPES_H

enum PeriodType {
    ALL = 0, CURRENT_DAY, CURRENT_MONTH, CURRENT_YEAR,
    PREVIOUS_MONTH, PREVIOUS_YEAR, NON_STANDARD
};

int getPeriodType(const PeriodType& type);

#endif
