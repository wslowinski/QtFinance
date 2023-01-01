#include "Expense.h"

Expense::Expense():
    id_(-1),
    expense_(0.0),
    currencyCode_("PLN"),
    category_(),
    title_(""),
    date_(QDate::currentDate()),
    exchangeRate_(1.0),
    comment_("")
{
}

Expense::Expense(int id, double expense, const QString& currencyCode,
                 const Category& category, const QString& title, const QDate& date,
                 double exchangeRate, const QString& comment):
    id_(id),
    expense_(expense),
    currencyCode_(currencyCode),
    category_(category),
    title_(title),
    date_(date),
    exchangeRate_(exchangeRate),
    comment_(comment)
{
}

Expense::Expense(double expense, const QString& currencyCode,
                 const Category& category, const QString& title, const QDate& date,
                 double exchangeRate, const QString& comment):
    Expense(-1, expense, currencyCode, category, title, date, exchangeRate, comment)
{
}

void Expense::setId(int id)
{
    id_ = id;
}

int Expense::getID() const
{
    return id_;
}

double Expense::getExpense() const
{
    return expense_;
}

const QString& Expense::getCurrencyCode() const
{
    return currencyCode_;
}

const Category& Expense::getCategory() const
{
    return category_;
}

const QString& Expense::getTitle() const
{
    return title_;
}

const QDate& Expense::getDate() const
{
    return date_;
}

double Expense::getExchangeRate() const
{
    return exchangeRate_;
}

const QString& Expense::getComment() const
{
    return comment_;
}
