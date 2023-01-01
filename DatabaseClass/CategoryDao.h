#ifndef CATEGORYDAO_H
#define CATEGORYDAO_H

#include <vector>

#include "Class/Category.h"

class QSqlDatabase;

class CategoryDao final
{
public:
    explicit CategoryDao(QSqlDatabase& database);

    void add(Category& category) const;
    void update(const Category& category) const;
    void remove(const int id) const;
    std::vector<Category> getAll() const;

private:
    QSqlDatabase& database_;
};

#endif // CATEGORYDAO_H
