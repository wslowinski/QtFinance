#include "Expense.h"

Expense::Expense():
    m_id(0),
    m_expense(0.0),
    m_currencyCode("PLN"),
    m_category(""),
    m_title(""),
    m_date(QDate::currentDate()),
    m_exchangeRate(1.0),
    m_comment("")
{
}

Expense::Expense(int id, double expense, const QString& currencyCode,
    const QString& category, const QString& title, const QDate& date,
    double exchangeRate, const QString& comment):
    m_id(id),
    m_expense(expense),
    m_currencyCode(currencyCode),
    m_category(category),
    m_title(title),
    m_date(date),
    m_exchangeRate(exchangeRate),
    m_comment(comment)
{
}

Expense::Expense(double expense, const QString& currencyCode,
    const QString& category, const QString& title, const QDate& date,
    double exchangeRate, const QString& comment):
    Expense(0, expense, currencyCode, category, title, date, exchangeRate, comment)
{
}

void Expense::setID(int id)
{
    m_id = id;
}

void Expense::setExpense(double expense)
{
    m_expense = expense;
}

void Expense::setCurrencyCode(const QString& currencyCode)
{
    m_currencyCode = currencyCode;
}

void Expense::setCategory(const QString& category)
{
    m_category = category;
}

void Expense::setTitle(const QString& title)
{
    m_title = title;
}

void Expense::setDate(const QDate& date)
{
    m_date = date;
}

void Expense::setExchangeRate(double exchangeRate)
{
    m_exchangeRate = exchangeRate;
}

void Expense::setComment(const QString& comment)
{
    m_comment = comment;
}

int Expense::getID() const
{
    return m_id;
}

double Expense::getExpense() const
{
    return m_expense;
}

QString Expense::getCurrencyCode() const
{
    return m_currencyCode;
}

QString Expense::getCategory() const
{
    return m_category;
}

QString Expense::getTitle() const
{
    return m_title;
}

QDate Expense::getDate() const
{
    return m_date;
}

double Expense::getExchangeRate() const
{
    return m_exchangeRate;
}

QString Expense::getComment() const
{
    return m_comment;
}
