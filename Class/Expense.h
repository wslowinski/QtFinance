#ifndef EXPENSE_H
#define EXPENSE_H

#include <QDate>

class Expense
{
public:
    Expense();
    Expense(int id, const QDate& date, const QString& category, double expense,
        const QString& shopName);
    ~Expense() = default;
    void setID(int id);
    void setDate(const QDate& date);
    void setCategory(const QString& category);
    void setExpense(double expense);
    void setShopName(const QString& shopName);

    int getID() const;
    QDate getDate() const;
    QString getCategory() const;
    double getExpense() const;
    QString getShopName() const;

private:
    int m_id;
    QDate m_date;
    QString m_category;
    double m_expense;
    QString m_shopName;
};

#endif
