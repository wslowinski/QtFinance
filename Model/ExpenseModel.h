#ifndef EXPENSEMODEL_H
#define EXPENSEMODEL_H

#include <vector>

#include <QAbstractTableModel>
#include <QHash>

#include "Class/Expense.h"

class DatabaseManager;

class ExpenseModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Roles {
        ID_ROLE = Qt::UserRole + 1, EXPENSE_ROLE, CURRENCY_CODE_ROLE,
        CATEGORY_ROLE, TITLE_ROLE, DATE_ROLE, EXCHANGE_RATE_ROLE, COMMENT_ROLE
    };

    enum ColumnName {
        ID = 0, EXPENSE, CURRENCY_CODE, CATEGORY, TITLE, DATE, EXCHANGE_RATE,
        COMMENT
    };

    explicit ExpenseModel(QObject* parent = nullptr, const QString& sql = "");

    QModelIndex add(const Expense& expense);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    QHash<int, QByteArray> roleNames() const override;

    double calculateSum();

private:
    bool isValidIndex(const QModelIndex& index) const;

    DatabaseManager& database_;
    std::vector<Expense> expenses_;
};

#endif
