#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include "Widget/ExpenseWidget.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_expenseWidget(new ExpenseWidget(this))
{
    ui->setupUi(this);
    ui->tabWidget->addTab(m_expenseWidget, "Expenses");
}

MainWindow::~MainWindow()
{
    delete ui;
}

