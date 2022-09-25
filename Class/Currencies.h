#ifndef CURRENCIES_H
#define CURRENCIES_H

#include <QString>
#include <QDate>

class Currencies
{
public:
    explicit Currencies(const QDate& date = QDate::currentDate());
    ~Currencies() = default;

    QString downloadCurrencies();

private:
    QDate m_date;
};

#endif
