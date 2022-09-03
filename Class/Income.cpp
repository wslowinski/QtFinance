#include "Income.h"

Income::Income():
    m_id(0),
    m_income(0.0),
    m_currencyCode("PLN"),
    m_title(""),
    m_date(QDate::currentDate()),
    m_exchangeRate(1.0),
    m_comment("")
{
}

Income::Income(int id, double income, const QString& currencyCode,
    const QString& title, const QDate& date,
    double exchangeRate, const QString& comment):
    m_id(id),
    m_income(income),
    m_currencyCode(currencyCode),
    m_title(title),
    m_date(date),
    m_exchangeRate(exchangeRate),
    m_comment(comment)
{
}

Income::Income(double income, const QString& currencyCode,
    const QString& title, const QDate& date,
    double exchangeRate, const QString& comment):
    Income(0, income, currencyCode, title, date, exchangeRate, comment)
{
}

void Income::setID(int id)
{
    m_id = id;
}

void Income::setIncome(double income)
{
    m_income = income;
}

void Income::setCurrencyCode(const QString& currencyCode)
{
    m_currencyCode = currencyCode;
}

void Income::setTitle(const QString& title)
{
    m_title = title;
}

void Income::setDate(const QDate& date)
{
    m_date = date;
}

void Income::setExchangeRate(double exchangeRate)
{
    m_exchangeRate = exchangeRate;
}

void Income::setComment(const QString& comment)
{
    m_comment = comment;
}

int Income::getID() const
{
    return m_id;
}

double Income::getIncome() const
{
    return m_income;
}

QString Income::getCurrencyCode() const
{
    return m_currencyCode;
}


QString Income::getTitle() const
{
    return m_title;
}

QDate Income::getDate() const
{
    return m_date;
}

double Income::getExchangeRate() const
{
    return m_exchangeRate;
}

QString Income::getComment() const
{
    return m_comment;
}
