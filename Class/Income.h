#ifndef INCOME_H
#define INCOME_H

#include <QDate>

class Income
{
public:
    Income();
    Income(double expense, const QString& currencyCode, const QString& title,
           const QDate& date, double exchangeRate, const QString& comment);
    Income(int id, double expense, const QString& currencyCode, const QString& title,
           const QDate& date, double exchangeRate, const QString& comment);
    ~Income() = default;

    void setID(int id);
    void setIncome(double income);
    void setCurrencyCode(const QString& currencyCode);
    void setTitle(const QString& title);
    void setDate(const QDate& date);
    void setExchangeRate(double exchangeRate);
    void setComment(const QString& comment);

    int getID() const;
    double getIncome() const;
    QString getCurrencyCode() const;
    QString getTitle() const;
    QDate getDate() const;
    double getExchangeRate() const;
    QString getComment() const;

private:
    int m_id;
    double m_income;
    QString m_currencyCode;
    QString m_title;
    QDate m_date;
    double m_exchangeRate;
    QString m_comment;
};

#endif
