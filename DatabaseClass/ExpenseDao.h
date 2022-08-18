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

    void add(Expense& expense);
    void update(Expense& expense);
    void remove(int id);
    std::vector<Expense> getAll();

private:
    QSqlDatabase& m_database;
};

#endif
