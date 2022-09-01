#include "ExpenseDao.h"
#include "Database/DatabaseManager.h"

ExpenseDao::ExpenseDao(QSqlDatabase& database):
    m_database(database)
{
}

void ExpenseDao::add(Expense& expense) const
{
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO expenses(expense, currencyCode, category, \
                    title, date, exchangeRate, comment) \
                   VALUES (:expense, :currencyCode, :category, \
                    :title, :date, :exchangeRate, :comment)");
    query.bindValue(":expense", expense.getExpense());
    query.bindValue(":currencyCode", expense.getCurrencyCode());
    query.bindValue(":category", expense.getCategory());
    query.bindValue(":title", expense.getTitle());
    query.bindValue(":date", expense.getDate());
    query.bindValue(":exchangeRate", expense.getExchangeRate());
    query.bindValue(":comment", expense.getComment());
    query.exec();
    DatabaseManager::debugQuery(query);
    expense.setID(query.lastInsertId().toInt());
}

void ExpenseDao::update(Expense& expense) const
{
    QSqlQuery query(m_database);
    query.prepare("UPDATE expenses SET \
                     expense = (:expense), \
                     currencyCode = (:currencyCode), \
                     category = (:category), \
                     title = (:title) \
                     date = (:date), \
                     exchangeRate = (:exchangeRate), \
                     comment = (:comment),\
                     WHERE id = (:id)");
    query.bindValue(":expense", expense.getExpense());
    query.bindValue(":currencyCode", expense.getCurrencyCode());
    query.bindValue(":category", expense.getCategory());
    query.bindValue(":title", expense.getTitle());
    query.bindValue(":date", expense.getDate());
    query.bindValue(":exchangeRate", expense.getExchangeRate());
    query.bindValue(":comment", expense.getComment());
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
    QSqlQuery query("SELECT id, expense, currencyCode, category, title, \
                     date, exchangeRate, comment FROM expenses", m_database);
    query.exec();
    DatabaseManager::debugQuery(query);

    std::vector<Expense> list;
    while(query.next())
    {
        list.emplace_back(query.value("id").toInt(),
                          query.value("expense").toDouble(),
                          query.value("currencyCode").toString(),
                          query.value("category").toString(),
                          query.value("title").toString(),
                          query.value("date").toDate(),
                          query.value("exchangeRate").toDouble(),
                          query.value("comment").toString());
    }
    return list;
}
