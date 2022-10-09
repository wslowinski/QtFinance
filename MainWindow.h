#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ExpenseWidget;
class IncomeWidget;
class MainWidget;
class PieChartWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void close();
    void on_btnDB_clicked();

private:
    Ui::MainWindow *ui;

    ExpenseWidget* m_expenseWidget;
    IncomeWidget* m_incomeWidget;
    MainWidget* m_mainWidget;
    PieChartWidget* m_pieChartWidget;
};
#endif
