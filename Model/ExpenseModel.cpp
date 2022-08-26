#include "ExpenseModel.h"

ExpenseModel::ExpenseModel(QObject* parent):
    QAbstractTableModel(parent),
    m_database(DatabaseManager::instance()),
    m_expenses(m_database.m_expenseDao.getAll())
{
}

QModelIndex ExpenseModel::add(const Expense& expense)
{
    int rowIndex = rowCount();
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    Expense newExpense{expense};
    m_database.m_expenseDao.add(newExpense);
    m_expenses.push_back(expense);
    endInsertRows();
    return index(rowIndex, 0);
}

int ExpenseModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_expenses.size();
}

int ExpenseModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant ExpenseModel::data(const QModelIndex& index, int role) const
{
    if(!isValidIndex(index))
    {
        return QVariant();
    }
    const Expense& expense = m_expenses.at(index.row());
    switch(role)
    {
        case Roles::ID_ROLE:
        return QVariant::fromValue(expense);
        case Qt::DisplayRole:
        {
            switch(index.column())
            {
                case ColumnName::ID:
                return expense.getID();
                case ColumnName::DATE:
                return expense.getDate();
                case ColumnName::CATEGORY:
                return expense.getCategory();
                case ColumnName::EXPENSE:
                return expense.getExpense();
                case ColumnName::SHOP_NAME:
                return expense.getShopName();
            }
        }
    }
    return QVariant();
}

QVariant ExpenseModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch(section)
        {
            case ColumnName::ID:
            return QString("Expense ID");
            case ColumnName::DATE:
            return QString("Date");
            case ColumnName::CATEGORY:
            return QString("Category");
            case ColumnName::EXPENSE:
            return QString("Expense [zł]");
            case ColumnName::SHOP_NAME:
            return QString("Shop name / title");
        }
    }
    return QVariant();
}

bool ExpenseModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(!isValidIndex(index) || role != Roles::ID_ROLE)
    {
        return false;
    }
    auto expense = qvariant_cast<Expense>(value);
    m_expenses.at(index.row()) = expense;
    emit dataChanged(index, index);
    return true;
}

bool ExpenseModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if(row < 0 || row >= rowCount() || count < 0 || (row + count) > rowCount())
    {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    int leftCount = count;
    while(leftCount--)
    {
        const Expense& expense = m_expenses.at(row + leftCount);
        m_database.m_expenseDao.remove(expense.getID());
    }
    m_expenses.erase(m_expenses.begin() + row, m_expenses.begin() + row + count);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> ExpenseModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Roles::ID_ROLE] = "ID";
    roles[Roles::DATE_ROLE] = "Date";
    roles[Roles::CATEGORY_ROLE] = "Category";
    roles[Roles::EXPENSE_ROLE] = "Expense";
    roles[Roles::SHOP_NAME_ROLE] = "Shop name";
    return roles;
}

bool ExpenseModel::isValidIndex(const QModelIndex& index) const
{
    return index.isValid() && index.row() < rowCount();
}
