#ifndef EXPENSEWIDGET_H
#define EXPENSEWIDGET_H

#include <QWidget>
#include <QLabel>

#include <Database/DatabaseManager.h>

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
    DatabaseManager& m_database;
    ExpenseAnalysis& m_expenseAnalysis;
    std::vector<QString> categoriesName;
    std::vector<QLabel*> categoriesLabels;
    std::vector<QLabel*> categoriesPercentages;

    void init();
    double calculateSum();
};

#endif
