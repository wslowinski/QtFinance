#ifndef INCOMEMODEL_H
#define INCOMEMODEL_H

#include "Class/Income.h"
#include "Database/DatabaseManager.h"

#include <vector>
#include <QAbstractTableModel>
#include <QHash>

class IncomeModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Roles {
        ID_ROLE = Qt::UserRole + 1, DATE_ROLE, TITLE_ROLE,
        INCOME_ROLE
    };

    enum ColumnName {
        ID = 0, DATE, TITLE, INCOME
    };

    explicit IncomeModel(QObject* parent = nullptr);
    QModelIndex add(const Income& income);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;
    QHash<int, QByteArray> roleNames() const override;

private:
    bool isValidIndex(const QModelIndex& index) const;

    DatabaseManager& m_database;
    std::vector<Income> m_incomes;
};

#endif
