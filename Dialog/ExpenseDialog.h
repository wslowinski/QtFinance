#ifndef EXPENSEDIALOG_H
#define EXPENSEDIALOG_H

#include "Class/Expense.h"
#include "Class/Currencies.h"

#include <QDialog>
#include <vector>
#include <utility>

namespace Ui {
class ExpenseDialog;
}

class CategoryModel;

class ExpenseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExpenseDialog(Expense& expense, QWidget *parent = nullptr);
    ~ExpenseDialog();

private slots:
    void accept();
    void reject();
    void setting();
    void download();
    void filter(int index);
    void addCategory();

private:
    Ui::ExpenseDialog *ui;
    Expense& m_expense; 
    std::vector<std::pair<QString, QString>> categoriesArray;
    QStringList m_list;
    Currencies::Rates m_rates;
    CategoryModel* category_model_;

    void init();
};

#endif
