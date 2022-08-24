#include "Income.h"

Income::Income():
    m_id(0),
    m_date(QDate::currentDate()),
    m_title(""),
    m_income(0.0)
{
}

Income::Income(const QDate& date, const QString& title, double income):
    m_id(0),
    m_date(date),
    m_title(title),
    m_income(income)
{
}

Income::Income(int id, const QDate& date, const QString& title,
               double income):
    m_id(id),
    m_date(date),
    m_title(title),
    m_income(income)
{
}

void Income::setID(int id)
{
    m_id = id;
}

int Income::getID() const
{
    return m_id;
}

QDate Income::getDate() const
{
    return m_date;
}

QString Income::getTitle() const
{
    return m_title;
}

double Income::getIncome() const
{
    return m_income;
}
