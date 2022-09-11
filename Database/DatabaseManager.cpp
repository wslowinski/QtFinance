#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(const QString& path):
    m_expenseDao(m_database),
    m_incomeDao(m_database),
    m_expenseAnalysis(m_database),
    m_database(QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", "SQLITE")))
{
    m_database.setDatabaseName(path);
    bool openStatus = m_database.open();
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

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::~DatabaseManager()
{
    if(m_database.isOpen())
    {
       m_database.close();
    }

}

void DatabaseManager::updateDatabase()
{
    if(!m_database.tables().contains("expenses"))
    {
        QSqlQuery query(m_database);
        query.exec("CREATE TABLE expenses (\
                        id INTEGER PRIMARY KEY AUTOINCREMENT, \
                        expense FLOAT, \
                        currencyCode VARCHAR(5), \
                        category VARCHAR(50), \
                        title VARCHAR(50), \
                        date DATE,\
                        exchangeRate FLOAT, \
                        comment VARCHAR(200))");
        DatabaseManager::debugQuery(query);
    }
    if(!m_database.tables().contains("incomes"))
    {
        QSqlQuery query(m_database);
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
