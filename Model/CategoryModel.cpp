#include "CategoryModel.h"

#include "Database/DatabaseManager.h"

CategoryModel::CategoryModel(QObject* parent) :
    QAbstractTableModel(parent),
    database_(DatabaseManager::getInstance()),
    categories_{database_.categoryDao_.getAll()}
{

}

QModelIndex CategoryModel::add(const Category &category)
{
    int rowIndex = rowCount();
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    Category new_category{category};
    database_.categoryDao_.add(new_category);
    categories_.push_back(new_category);
    endInsertRows();
    return index(rowIndex, 0);
}

int CategoryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return categories_.size();
}

int CategoryModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant CategoryModel::data(const QModelIndex &index, int role) const
{
    if(!isValidIndex(index))
    {
        return QVariant();
    }
    const Category& category = categories_.at(index.row());
    switch(role)
    {
    case Roles::ID_ROLE:
        return QVariant::fromValue(category);
    case Qt::DisplayRole:
    {
        switch(index.column())
        {
        case ColumnName::ID:
            return category.getId();
        case ColumnName::NAME:
            return category.getName();
        }
    }
    }
    return QVariant();
}

QVariant CategoryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch(section)
        {
        case ColumnName::ID:
            return QString("ID");
        case ColumnName::NAME:
            return QString("NAME");
        }
    }
    return QVariant();
}

bool CategoryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!isValidIndex(index) || role != Roles::ID_ROLE)
    {
        return false;
    }
    auto category = qvariant_cast<Category>(value);
    categories_.at(index.row()) = category;
    emit dataChanged(index, index);
    return true;
}

bool CategoryModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row < 0 || row >= rowCount() || count < 0 || (row + count) > rowCount())
    {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    int leftCount = count;
    while(leftCount--)
    {
        auto& category = categories_.at(row + leftCount);
        database_.categoryDao_.remove(category.getId());
    }
    categories_.erase(categories_.begin() + row, categories_.begin() + row + count);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> CategoryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Roles::ID_ROLE] = "ID";
    roles[Roles::NAME_ROLE] = "Name";
    return roles;
}

bool CategoryModel::isValidIndex(const QModelIndex &index) const
{
    return index.isValid() && index.row() < rowCount();
}
