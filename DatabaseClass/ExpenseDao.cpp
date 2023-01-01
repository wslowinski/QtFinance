#include "ExpenseDao.h"

#include "Database/DatabaseManager.h"

ExpenseDao::ExpenseDao(QSqlDatabase& database):
    database_(database)
{
}

void ExpenseDao::add(Expense& expense) const
{
    QSqlQuery query(database_);
    query.prepare("INSERT INTO expenses(expense, currencyCode, category_id, \
                   title, date, exchangeRate, comment) \
                   VALUES (:expense, :currencyCode, :category_id, \
                   :title, :date, :exchangeRate, :comment)");
    query.bindValue(":expense", expense.getExpense());
    query.bindValue(":currencyCode", expense.getCurrencyCode());
    query.bindValue(":category", expense.getCategory().getId());
    query.bindValue(":title", expense.getTitle());
    query.bindValue(":date", expense.getDate());
    query.bindValue(":exchangeRate", expense.getExchangeRate());
    query.bindValue(":comment", expense.getComment());
    query.exec();
    DatabaseManager::debugQuery(query);
    expense.setId(query.lastInsertId().toInt());
}

void ExpenseDao::update(const Expense& expense) const
{
    QSqlQuery query(database_);
    query.prepare("UPDATE expenses SET \
                     expense = (:expense), \
                     currencyCode = (:currencyCode), \
                     category_id = (:category_id), \
                     title = (:title) \
                     date = (:date), \
                     exchangeRate = (:exchangeRate), \
                     comment = (:comment),\
                     WHERE id = (:id)");
    query.bindValue(":expense", expense.getExpense());
    query.bindValue(":currencyCode", expense.getCurrencyCode());
    query.bindValue(":category", expense.getCategory().getId());
    query.bindValue(":title", expense.getTitle());
    query.bindValue(":date", expense.getDate());
    query.bindValue(":exchangeRate", expense.getExchangeRate());
    query.bindValue(":comment", expense.getComment());
    query.exec();
    DatabaseManager::debugQuery(query);
}

void ExpenseDao::remove(int id) const
{
    QSqlQuery query(database_);
    query.prepare("DELETE FROM expenses WHERE id = (:id)");
    query.bindValue(":id", id);
    query.exec();
    DatabaseManager::debugQuery(query);
    query.prepare("UPDATE SQLITE_SEQUENCE SET SEQ=1 WHERE NAME='expenses'");
    query.exec();
    DatabaseManager::debugQuery(query);
}

std::vector<Expense> ExpenseDao::getAll(const std::optional<QString>& sql) const
{
    auto queryString = [&] {
        if(sql.has_value()) return sql.value();
        else return QString("SELECT * FROM expenses");
    };

    QSqlQuery query(queryString(), database_);
    query.exec();
    DatabaseManager::debugQuery(query);

    std::vector<Expense> array;
    while(query.next())
    {
        array.emplace_back(query.value("id").toInt(),
                          query.value("expense").toDouble(),
                          query.value("currencyCode").toString(),
                          query.value("category").toString(),
                          query.value("title").toString(),
                          query.value("date").toDate(),
                          query.value("exchangeRate").toDouble(),
                          query.value("comment").toString());
    }
    return array;
}
