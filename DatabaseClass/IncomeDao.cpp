#include "IncomeDao.h"
#include "Database/DatabaseManager.h"

IncomeDao::IncomeDao(QSqlDatabase& database):
    m_database(database)
{
}

void IncomeDao::add(Income& income) const
{
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO incomes(income, currencyCode, \
                   title, date, exchangeRate, comment) \
                   VALUES (:expense, :currencyCode, \
                   :title, :date, :exchangeRate, :comment)");
    query.bindValue(":expense", income.getIncome());
    query.bindValue(":currencyCode", income.getCurrencyCode());
    query.bindValue(":title", income.getTitle());
    query.bindValue(":date", income.getDate());
    query.bindValue(":exchangeRate", income.getExchangeRate());
    query.bindValue(":comment", income.getComment());
    query.exec();
    DatabaseManager::debugQuery(query);
    income.setID(query.lastInsertId().toInt());
}

void IncomeDao::update(Income& income) const
{
    QSqlQuery query(m_database);
    query.prepare("UPDATE incomes SET \
                     income = (:income), \
                     currencyCode = (:currencyCode), \
                     title = (:title) \
                     date = (:date), \
                     exchangeRate = (:exchangeRate), \
                     comment = (:comment),\
                     WHERE id = (:id)");
    query.bindValue(":income", income.getIncome());
    query.bindValue(":currencyCode", income.getCurrencyCode());
    query.bindValue(":title", income.getTitle());
    query.bindValue(":date", income.getDate());
    query.bindValue(":exchangeRate", income.getExchangeRate());
    query.bindValue(":comment", income.getComment());
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
    query.prepare("UPDATE SQLITE_SEQUENCE SET SEQ=1 WHERE NAME='incomes'");
    query.exec();
    DatabaseManager::debugQuery(query);
}

std::vector<Income> IncomeDao::getAll(const QString& sql) const
{
    QSqlQuery query(sql, m_database);
    query.exec();
    DatabaseManager::debugQuery(query);

    std::vector<Income> array;
    while(query.next())
    {
        array.emplace_back(query.value("id").toInt(),
                          query.value("income").toDouble(),
                          query.value("currencyCode").toString(),
                          query.value("title").toString(),
                          query.value("date").toDate(),
                          query.value("exchangeRate").toDouble(),
                          query.value("comment").toString());
    }
    return array;
}

std::vector<Income> IncomeDao::getAll() const
{
    const QString& sql = "SELECT id, income, currencyCode, title, \
                     date, exchangeRate, comment FROM incomes";
    return getAll(sql);
}
