#include "ExpenseModel.h"

#include "Database/DatabaseManager.h"

ExpenseModel::ExpenseModel(QObject* parent, const QString& sql):
    QAbstractTableModel(parent),
    database_(DatabaseManager::getInstance()),
    expenses_(database_.expenseDao_.getAll(sql))
{
}

QModelIndex ExpenseModel::add(const Expense& expense)
{
    int rowIndex = rowCount();
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    Expense newExpense{expense};
    database_.expenseDao_.add(newExpense);
    expenses_.push_back(expense);
    endInsertRows();
    return index(rowIndex, 0);
}

int ExpenseModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return expenses_.size();
}

int ExpenseModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 8;
}

QVariant ExpenseModel::data(const QModelIndex& index, int role) const
{
    if(!isValidIndex(index))
    {
        return QVariant();
    }
    const Expense& expense = expenses_.at(index.row());
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
                case ColumnName::EXPENSE:
                return expense.getExpense();
                case ColumnName::CURRENCY_CODE:
                return expense.getCurrencyCode();
                case ColumnName::CATEGORY:
                return expense.getCategory().getName();
                case ColumnName::TITLE:
                return expense.getTitle();
                case ColumnName::DATE:
                return expense.getDate();
                case ColumnName::EXCHANGE_RATE:
                return expense.getExchangeRate();
                case ColumnName::COMMENT:
                return expense.getComment();
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
            return QString("ID");
            case ColumnName::EXPENSE:
            return QString("EXPENSE [GROSS]");
            case ColumnName::CURRENCY_CODE:
            return QString("CURRENCY CODE");
            case ColumnName::CATEGORY:
            return QString("CATEGORY");
            case ColumnName::TITLE:
            return QString("TITLE/SHOP NAME");
            case ColumnName::DATE:
            return QString("DATE");
            case ColumnName::EXCHANGE_RATE:
            return QString("EXCHANGE RATE");
            case ColumnName::COMMENT:
            return QString("COMMENT");
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
    expenses_.at(index.row()) = expense;
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
        const Expense& expense = expenses_.at(row + leftCount);
        database_.expenseDao_.remove(expense.getID());
    }
    expenses_.erase(expenses_.begin() + row, expenses_.begin() + row + count);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> ExpenseModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Roles::ID_ROLE] = "ID";
    roles[Roles::EXPENSE_ROLE] = "Expense";
    roles[Roles::CURRENCY_CODE_ROLE] = "CurrencyCode";
    roles[Roles::CATEGORY_ROLE] = "Category";
    roles[Roles::TITLE_ROLE] = "Title";
    roles[Roles::DATE_ROLE] = "Date";
    roles[Roles::EXCHANGE_RATE_ROLE] = "ExchangeRole";
    roles[Roles::COMMENT_ROLE] = "Comment";
    return roles;
}

double ExpenseModel::calculateSum()
{
    double sum{};

    for(const auto& elem : expenses_) {
        sum += elem.getExpense();
    }

    return sum;
}

bool ExpenseModel::isValidIndex(const QModelIndex& index) const
{
    return index.isValid() && index.row() < rowCount();
}
