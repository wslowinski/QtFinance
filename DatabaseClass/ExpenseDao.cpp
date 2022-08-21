#include "ExpenseDao.h"
#include "Database/DatabaseManager.h"

ExpenseDao::ExpenseDao(QSqlDatabase& database):
    m_database(database)
{
}

void ExpenseDao::add(Expense& expense) const
{
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO expenses(date, category, expense, shopname) \
        VALUES (:date, :category, :expense, :shopname)");
    query.bindValue(":date", expense.getDate());
    query.bindValue(":category", expense.getCategory());
    query.bindValue(":expense", expense.getExpense());
    query.bindValue(":shopname", expense.getShopName());
    query.exec();
    DatabaseManager::debugQuery(query);
    expense.setID(query.lastInsertId().toInt());
}

void ExpenseDao::update(Expense& expense) const
{
    QSqlQuery query(m_database);
    query.prepare("UPDATE expenses SET \
                     date = (:date), \
                     category = (:category), \
                     expense = (:expense), \
                     shopname = (:shopname) \
                     WHERE od = (:id)");
    query.bindValue(":id", expense.getID());
    query.bindValue(":date", expense.getDate());
    query.bindValue(":category", expense.getCategory());
    query.bindValue(":expense", expense.getExpense());
    query.bindValue(":shopname", expense.getShopName());
    query.exec();
    DatabaseManager::debugQuery(query);
}

void ExpenseDao::remove(int id) const
{
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM expenses WHERE id = (:id)");
    query.bindValue(":id", id);
    query.exec();
    DatabaseManager::debugQuery(query);
}

std::vector<Expense> ExpenseDao::getAll() const
{
    QSqlQuery query("SELECT * FROM expenses", m_database);
    query.exec();
    DatabaseManager::debugQuery(query);

    std::vector<Expense> list;
    while(query.next())
    {
        list.emplace_back(query.value("id").toInt(),
                          query.value("date").toDate(),
                          query.value("category").toString(),
                          query.value("expense").toDouble(),
                          query.value("shopname").toString());
    }
    return list;
}


