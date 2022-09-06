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
        ID_ROLE = Qt::UserRole + 1, INCOME_ROLE, CURRENCY_CODE_ROLE,
        TITLE_ROLE, DATE_ROLE, EXCHANGE_RATE_ROLE, COMMENT_ROLE
    };

    enum ColumnName {
        ID = 0, INCOME, CURRENCY_CODE, TITLE, DATE, EXCHANGE_RATE,
        COMMENT
    };

    explicit IncomeModel(QObject* parent = nullptr, const QString& sql = "");
    QModelIndex add(const Income& income);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    QHash<int, QByteArray> roleNames() const override;

private:
    bool isValidIndex(const QModelIndex& index) const;

    DatabaseManager& m_database;
    std::vector<Income> m_incomes;
};

#endif
