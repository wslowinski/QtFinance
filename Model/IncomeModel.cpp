#include "IncomeModel.h"

IncomeModel::IncomeModel(QObject* parent):
    QAbstractTableModel(parent),
    m_database(DatabaseManager::instance()),
    m_incomes(m_database.m_incomeDao.getAll())
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
    return 4;
}

QVariant IncomeModel::data(const QModelIndex& index, int role) const
{
    if(!isValidIndex(index))
    {
        return QVariant();
    }
    const Income& income = m_incomes.at(index.row());
    switch(role) {
        case Roles::ID_ROLE:
            return QVariant::fromValue(income);
        case Qt::DisplayRole: {
            switch(index.column()) {
                case ColumnName::ID:
                    return income.getID();
                case ColumnName::DATE:
                    return income.getDate();
                case ColumnName::TITLE:
                    return income.getTitle();
                case ColumnName::INCOME:
                    return income.getIncome();
            }
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
    roles[Roles::DATE_ROLE] = "Date";
    roles[Roles::TITLE_ROLE] = "Title";
    roles[Roles::INCOME_ROLE] = "Income";
    return roles;
}

bool IncomeModel::isValidIndex(const QModelIndex& index) const
{
    return index.isValid() && index.row() < rowCount();
}



