#include "CategoryDao.h"

#include <QSqlDatabase>
#include <QSqlQuery>

#include "Database/DatabaseManager.h"

CategoryDao::CategoryDao(QSqlDatabase& database) :
    database_{database}
{

}

void CategoryDao::add(Category &category) const
{
    QSqlQuery query(database_);
    query.prepare("INSERT INTO categories(name) VALUES (:name)");

    query.bindValue(":name", category.getName());

    query.exec();

    DatabaseManager::debugQuery(query);
    category.setId(query.lastInsertId().toInt());
}

void CategoryDao::update(const Category &category) const
{
    QSqlQuery query(database_);
    query.prepare("UPDATE expenses SET name = (:name) WHERE id = (:id)");

    query.bindValue(":id", category.getId());
    query.bindValue(":name", category.getName());

    query.exec();
    DatabaseManager::debugQuery(query);
}

void CategoryDao::remove(const int id) const
{
    QSqlQuery query(database_);
    query.prepare("DELETE FROM categories WHERE id = (:id)");

    query.bindValue(":id", id);

    query.exec();
    DatabaseManager::debugQuery(query);
}

std::vector<Category> CategoryDao::getAll() const
{
    QSqlQuery query("SELECT * FROM categories", database_);
    query.exec();
    DatabaseManager::debugQuery(query);

    std::vector<Category> categories;

    while(query.next())
    {
        categories.emplace_back(query.value("id").toInt(), query.value("name").toString());
    }

    return categories;
}
