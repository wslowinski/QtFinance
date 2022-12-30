#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(const QString& path):
    expenseDao_(database_),
    m_incomeDao(database_),
    m_expenseAnalysis(database_),
    m_incomeAnalysis(database_),
    categoryDao_(database_),
    database_(QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", "SQLITE")))
{
    database_.setDatabaseName(path);
    bool openStatus = database_.open();
    qDebug() << "Database connection: " << (openStatus ? "OK" : "ERROR");
    updateDatabase();
}

void DatabaseManager::debugQuery(const QSqlQuery& query)
{
    if(query.lastError().type() == QSqlError::ErrorType::NoError)
    {
        qDebug() << "Query OK: " << query.lastQuery();
    }
    else
    {
        qWarning() << "Query KO: " << query.lastError().type();
        qWarning() << "Query text: " << query.lastQuery();
    }
}

DatabaseManager& DatabaseManager::getInstance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::~DatabaseManager()
{
    if(database_.isOpen())
    {
       database_.close();
    }

}

void DatabaseManager::updateDatabase()
{
    if(!database_.tables().contains("categories"))
    {
       QSqlQuery query(database_);
       query.exec("CREATE TABLE categories(id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(50))");
       DatabaseManager::debugQuery(query);
    }

    if(!database_.tables().contains("expenses"))
    {
        QSqlQuery query(database_);
        query.exec("CREATE TABLE expenses (\
                        id INTEGER PRIMARY KEY AUTOINCREMENT, \
                        expense FLOAT, \
                        currencyCode VARCHAR(5), \
                        category_id VARCHAR(50), \
                        title VARCHAR(50), \
                        date DATE,\
                        exchangeRate FLOAT, \
                        comment VARCHAR(200),"
                   "FOREIGN KEY(category_id) REFERENCES categories(id))");
        DatabaseManager::debugQuery(query);
    }
    if(!database_.tables().contains("incomes"))
    {
        QSqlQuery query(database_);
        query.exec("CREATE TABLE incomes (\
                        id INTEGER PRIMARY KEY AUTOINCREMENT, \
                        income FLOAT, \
                        currencyCode VARCHAR(5), \
                        title VARCHAR(50), \
                        date DATE,\
                        exchangeRate FLOAT, \
                        comment VARCHAR(200))");
        DatabaseManager::debugQuery(query);
    }

}
