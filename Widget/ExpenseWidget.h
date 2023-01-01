#ifndef EXPENSEWIDGET_H
#define EXPENSEWIDGET_H

#include <QWidget>
#include <QLabel>

#include "Database/DatabaseManager.h"

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

    int getCurrentID();

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
    std::vector<QString> m_categoriesName;
    std::vector<QLabel*> m_categoriesLabels;
    std::vector<QLabel*> m_categoriesPercentages;
    std::vector<double> m_percentages;
    double m_expensesSum;

    void init();
    void paintEvent(QPaintEvent *event);
    double getPie(double percentage);
};

#endif
