#ifndef EXPENSEDAO_H
#define EXPENSEDAO_H

#include <vector>
#include <optional>

#include <QSqlDatabase>

#include "Class/Expense.h"

class ExpenseDao final
{
public:
    explicit ExpenseDao(QSqlDatabase& database);

    void add(Expense& expense) const;
    void update(const Expense& expense) const;
    void remove(int id) const;
    std::vector<Expense> getAll(const std::optional<QString>& sql) const;

private:
    QSqlDatabase& database_;
};

#endif
