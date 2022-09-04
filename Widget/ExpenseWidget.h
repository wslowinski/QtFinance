#ifndef EXPENSEWIDGET_H
#define EXPENSEWIDGET_H

#include "Code/PeriodTypes.h"

#include <QWidget>

namespace Ui {
class ExpenseWidget;
}

class ExpenseModel;

class ExpenseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExpenseWidget(QWidget* parent = nullptr);
    ~ExpenseWidget();

    void setModel(ExpenseModel* model);

private slots:
    void add();
    void edit();
    void remove();
    void setting();
    void filter(int index);

private:
    Ui::ExpenseWidget *ui;
    ExpenseModel* m_expenseModel;

    QString getSQLFilter(int index);
    void init();
};

#endif
