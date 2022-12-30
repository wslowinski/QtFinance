#ifndef CATEGORYMODEL_H
#define CATEGORYMODEL_H

#include <vector>

#include <QAbstractTableModel>
#include <QHash>

#include "Class/Category.h"

class DatabaseManager;

class CategoryModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Roles {
        ID_ROLE = Qt::UserRole + 1, NAME_ROLE
    };

    enum ColumnName {
        ID = 0, NAME
    };

    explicit CategoryModel(QObject* parent = nullptr);

    QModelIndex add(const Category& category);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    QHash<int, QByteArray> roleNames() const override;

private:
    bool isValidIndex(const QModelIndex& index) const;

    DatabaseManager& database_;
    std::vector<Category> categories_;
};

#endif // CATEGORYMODEL_H
