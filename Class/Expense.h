#ifndef EXPENSE_H
#define EXPENSE_H

#include <QDate>

class Expense
{
public:
    Expense();
    Expense(double expense, const QString& currencyCode,
            const QString& category, const QString& title, const QDate& date,
            double exchangeRate, const QString& comment);
    Expense(int id, double expense, const QString& currencyCode,
            const QString& category, const QString& title, const QDate& date,
            double exchangeRate, const QString& comment);
    ~Expense() = default;

    void setID(int id);
    void setExpense(double expense);
    void setCurrencyCode(const QString& currencyCode);
    void setCategory(const QString& category);
    void setTitle(const QString& title);
    void setDate(const QDate& date);
    void setExchangeRate(double exchangeRate);
    void setComment(const QString& comment);

    int getID() const;
    double getExpense() const;
    QString getCurrencyCode() const;
    QString getCategory() const;
    QString getTitle() const;
    QDate getDate() const;
    double getExchangeRate() const;
    QString getComment() const;

private:
    int m_id;
    double m_expense;
    QString m_currencyCode;
    QString m_category;
    QString m_title;
    QDate m_date;
    double m_exchangeRate;
    QString m_comment;
};

#endif
