#include "IncomeModel.h"

IncomeModel::IncomeModel(QObject* parent, const QString& sql):
    QAbstractTableModel(parent),
    m_database(DatabaseManager::getInstance()),
    m_incomes(m_database.m_incomeDao.getAll(sql))
{
}


QModelIndex IncomeModel::add(const Income& income)
{
    int rowIndex = rowCount();
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    Income newIncome{income};
    m_database.m_incomeDao.add(newIncome);
    m_incomes.push_back(income);
    endInsertRows();
    return index(rowIndex, 0);
}

int IncomeModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_incomes.size();
}

int IncomeModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 7;
}

QVariant IncomeModel::data(const QModelIndex& index, int role) const
{
    if(!isValidIndex(index))
    {
        return QVariant();
    }
    const Income& income = m_incomes.at(index.row());
    switch(role)
    {
        case Roles::ID_ROLE:
        return QVariant::fromValue(income);
        case Qt::DisplayRole:
        {
            switch(index.column())
            {
                case ColumnName::ID:
                return income.getID();
                case ColumnName::INCOME:
                return income.getIncome();
                case ColumnName::CURRENCY_CODE:
                return income.getCurrencyCode();
                case ColumnName::TITLE:
                return income.getTitle();
                case ColumnName::DATE:
                return income.getDate();
                case ColumnName::EXCHANGE_RATE:
                return income.getExchangeRate();
                case ColumnName::COMMENT:
                return income.getComment();
            }
        }
    }
    return QVariant();
}

QVariant IncomeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch(section)
        {
            case ColumnName::ID:
            return QString("ID");
            case ColumnName::INCOME:
            return QString("Income [gross]");
            case ColumnName::CURRENCY_CODE:
            return QString("Currency Code");
            case ColumnName::TITLE:
            return QString("Title");
            case ColumnName::DATE:
            return QString("Date");
            case ColumnName::EXCHANGE_RATE:
            return QString("Exchange Rate");
            case ColumnName::COMMENT:
            return QString("Comment");
        }
    }
    return QVariant();
}


bool IncomeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(!isValidIndex(index) || role != Roles::ID_ROLE)
    {
        return false;
    }
    auto income = qvariant_cast<Income>(value);
    m_incomes.at(index.row()) = income;
    emit dataChanged(index, index);
    return true;
}

bool IncomeModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if(row < 0 || row >= rowCount() || count < 0 || (row + count) > rowCount())
    {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    int leftCount = count;
    while(leftCount--)
    {
        const Income& income = m_incomes.at(row + leftCount);
        m_database.m_incomeDao.remove(income.getID());
    }
    m_incomes.erase(m_incomes.begin() + row, m_incomes.begin() + row + count);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> IncomeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Roles::ID_ROLE] = "ID";
    roles[Roles::INCOME_ROLE] = "Income";
    roles[Roles::CURRENCY_CODE_ROLE] = "CurrencyCode";
    roles[Roles::TITLE_ROLE] = "Title";
    roles[Roles::DATE_ROLE] = "Date";
    roles[Roles::EXCHANGE_RATE_ROLE] = "ExchangeRole";
    roles[Roles::COMMENT_ROLE] = "Comment";
    return roles;
}

bool IncomeModel::isValidIndex(const QModelIndex& index) const
{
    return index.isValid() && index.row() < rowCount();
}



