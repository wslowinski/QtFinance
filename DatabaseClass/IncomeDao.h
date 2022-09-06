#ifndef INCOMEDAO_H
#define INCOMEDAO_H

#include "Class/Income.h"

#include <QSqlDatabase>
#include <vector>

class IncomeDao
{
public:
    explicit IncomeDao(QSqlDatabase& database);

    void add(Income& expense) const;
    void update(Income& expense) const;
    void remove(int id) const;
    std::vector<Income> getAll() const;
    std::vector<Income> getAll(const QString& sql) const;

private:
    QSqlDatabase& m_database;
};

#endif
