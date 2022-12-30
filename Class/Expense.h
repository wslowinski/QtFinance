#ifndef EXPENSE_H
#define EXPENSE_H

#include <QDate>

#include "Class/Category.h"

class Expense
{
public:
    Expense();
    Expense(double expense, const QString& currencyCode,
            const Category& category, const QString& title, const QDate& date,
            double exchangeRate, const QString& comment);
    Expense(int id, double expense, const QString& currencyCode,
            const Category& category, const QString& title, const QDate& date,
            double exchangeRate, const QString& comment);
    ~Expense() = default;

    void setId(int id);

    int getID() const;
    double getExpense() const;
    const QString& getCurrencyCode() const;
    const QString& getTitle() const;
    const QDate& getDate() const;
    double getExchangeRate() const;
    const QString& getComment() const;
    const Category& getCategory() const;

private:
    int id_;
    double expense_;
    QString currencyCode_;
    QString title_;
    QDate date_;
    double exchangeRate_;
    QString comment_;
    Category category_;
};

#endif
