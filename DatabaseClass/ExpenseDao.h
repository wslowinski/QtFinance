#ifndef EXPENSEDAO_H
#define EXPENSEDAO_H

#include "Class/Expense.h"

#include <QSqlDatabase>
#include <memory>
#include <vector>

class ExpenseDao
{
public:
    explicit ExpenseDao(QSqlDatabase& database);

    void add(Expense& expense) const;
    void update(Expense& expense) const;
    void remove(int id) const;
    std::vector<Expense> getAll() const;

private:
    QSqlDatabase& m_database;
};

#endif
