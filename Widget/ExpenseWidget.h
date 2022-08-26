#ifndef EXPENSEWIDGET_H
#define EXPENSEWIDGET_H

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
    void setDesign();

private slots:
    void add();
    void edit();
    void remove();

private:
    Ui::ExpenseWidget *ui;

    ExpenseModel* m_expenseModel;
};

#endif
