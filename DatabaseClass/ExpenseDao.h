#ifndef EXPENSEDAO_H
#define EXPENSEDAO_H

#include "Class/Expense.h"

#include <QSqlDatabase>
#include <vector>

class ExpenseDao
{
public:
    explicit ExpenseDao(QSqlDatabase& database);

    void add(Expense& expense) const;
    void update(Expense& expense) const;
    void remove(int id) const;
    std::vector<Expense> getAll() const;
    std::vector<Expense> getAll(const QString& sql) const;

private:
    QSqlDatabase& m_database;
};

#endif
