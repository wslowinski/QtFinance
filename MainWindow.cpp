#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include "Widget/ExpenseWidget.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_expenseWidget(new ExpenseWidget(this))
{
    ui->setupUi(this);
    connect(ui->tbtnExit, &QToolButton::clicked, this, &QMainWindow::close);
    ui->tabWidget->addTab(m_expenseWidget, "Expenses");
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

