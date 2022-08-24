#ifndef INCOME_H
#define INCOME_H

#include <QDate>

class Income
{
public:
    Income();
    Income(const QDate& date, const QString& title, double income);
    Income(int id, const QDate& date, const QString& title, double income);
    ~Income() = default;
    void setID(int id);

    int getID() const;
    QDate getDate() const;
    QString getTitle() const;
    double getIncome() const;

private:
    int m_id;
    QDate m_date;
    QString m_title;
    double m_income;
};

#endif
