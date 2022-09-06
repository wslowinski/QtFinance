#include "PeriodTypes.h"

int getPeriodType(const PeriodType& type)
{
    switch (type) {
    case PeriodType::ALL:
        return 0;
    case PeriodType::CURRENT_DAY:
        return 1;
    case PeriodType::CURRENT_MONTH:
        return 2;
    case PeriodType::CURRENT_YEAR:
        return 3;
    case PeriodType::PREVIOUS_MONTH:
        return 4;
    case PeriodType::PREVIOUS_YEAR:
        return 5;
    case PeriodType::NON_STANDARD:
        return 6;
    }
    return 0;
}
