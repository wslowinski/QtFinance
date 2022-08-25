#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include "Widget/ExpenseWidget.h"
#include "Widget/IncomeWidget.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_expenseWidget(new ExpenseWidget(this)),
    m_incomeWidget(new IncomeWidget(this))
{
    ui->setupUi(this);
    connect(ui->tbtnExit, &QToolButton::clicked, this, &QMainWindow::close);
    ui->tabWidget->addTab(m_expenseWidget, "Expenses");
    ui->tabWidget->addTab(m_incomeWidget, "Incomes");
}

MainWindow::~MainWindow()
{
    close();
    delete ui;
}

void MainWindow::close()
{
    QMainWindow::close();
}

