#include "IncomeDao.h"
#include "Database/DatabaseManager.h"

IncomeDao::IncomeDao(QSqlDatabase& database):
    m_database(database)
{
}

void IncomeDao::add(Income& income) const
{
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO incomes(date, title, income) \
        VALUES (:date, :title, :income)");
    query.bindValue(":date", income.getDate());
    query.bindValue(":title", income.getTitle());
    query.bindValue(":income", income.getIncome());
    query.exec();
    DatabaseManager::debugQuery(query);
    income.setID(query.lastInsertId().toInt());
}

void IncomeDao::update(Income& income) const
{
    QSqlQuery query(m_database);
    query.prepare("UPDATE incomes SET \
                     date = (:date), \
                     title = (:title), \
                     income = (:income) \
                     WHERE od = (:id)");
    query.bindValue(":id", income.getID());
    query.bindValue(":date", income.getDate());
    query.bindValue(":title", income.getTitle());
    query.bindValue(":income", income.getIncome());
    query.exec();
    DatabaseManager::debugQuery(query);
}

void IncomeDao::remove(int id) const
{
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM incomes WHERE id = (:id)");
    query.bindValue(":id", id);
    query.exec();
    DatabaseManager::debugQuery(query);
}

std::vector<Income> IncomeDao::getAll() const
{
    QSqlQuery query("SELECT id, date, title, income FROM incomes",
                    m_database);
    query.exec();
    DatabaseManager::debugQuery(query);

    std::vector<Income> list;
    while(query.next())
    {
        list.emplace_back(query.value("id").toInt(),
                          query.value("date").toDate(),
                          query.value("title").toString(),
                          query.value("income").toDouble());
    }
    return list;
}
