#include "PeriodTypes.h"

int getPeriodType(const PeriodType& type)
{
    switch (type) {
    case PeriodType::ALL:
        return 0;
    case PeriodType::CURRENT_DAY:
        return 1;
    case PeriodType::CURRENT_WEEK:
        return 2;
    case PeriodType::CURRENT_MONTH:
        return 3;
    case PeriodType::CURRENT_YEAR:
        return 4;
    case PeriodType::PREVIOUS_DAY:
        return 5;
    case PeriodType::PREVIOUS_WEEK:
        return 6;
    case PeriodType::PREVIOUS_MONTH:
        return 7;
    case PeriodType::PREVIOUS_YEAR:
        return 8;
    case PeriodType::NON_STANDARD:
        return 9;
    default:
        return 0;
    }
}
