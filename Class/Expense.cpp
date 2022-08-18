#include "Expense.h"

Expense::Expense(int id, const QDate& date, const QString& category, double expense,
    const QString& shopName):
    m_id(id),
    m_date(date),
    m_category(category),
    m_expense(expense),
    m_shopName(shopName)
{
}

void Expense::setID(int id)
{
    m_id = id;
}

void Expense::setDate(const QDate& date)
{
    m_date = date;
}

void Expense::setCategory(const QString& category)
{
    m_category = category;
}

void Expense::setExpense(double expense)
{
    m_expense = expense;
}

void Expense::setShopName(const QString& shopName)
{
    m_shopName = shopName;
}

int Expense::getID() const
{
    return m_id;
}

QDate Expense::getDate() const
{
    return m_date;
}

QString Expense::getCategory() const
{
    return m_category;
}

double Expense::getExpense() const
{
    return m_expense;
}

QString Expense::getShopName() const
{
    return m_shopName;
}
