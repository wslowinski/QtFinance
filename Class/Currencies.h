#ifndef CURRENCIES_H
#define CURRENCIES_H

#include <QString>
#include <QDate>
#include <utility>
#include <vector>

class Currencies
{
public:
    using Rates = std::vector<std::pair<QString, double>>;

public:
    explicit Currencies(const QDate& date = QDate::currentDate());
    ~Currencies() = default;

    QString downloadCurrencies();
    Rates parseJSON();

private:
    QDate m_date;
};

#endif
