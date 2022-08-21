#ifndef EXPENSEDIALOG_H
#define EXPENSEDIALOG_H

#include "Class/Expense.h"

#include <QDialog>

namespace Ui {
class ExpenseDialog;
}

class ExpenseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExpenseDialog(Expense& expense, QWidget *parent = nullptr);
    ~ExpenseDialog();

private slots:
    void accept();
    void reject();

private:
    Ui::ExpenseDialog *ui;
    Expense& m_expense;
};

#endif
