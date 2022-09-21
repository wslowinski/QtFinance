#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "Widget/ExpenseWidget.h"
#include "Widget/IncomeWidget.h"
#include "Widget/MainWidget.h"

#include <QScreen>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_expenseWidget(new ExpenseWidget(this)),
    m_incomeWidget(new IncomeWidget(this)),
    m_mainWidget(new MainWidget(this))
{
    ui->setupUi(this);
    QMainWindow::setWindowState(Qt::WindowMaximized);
    connect(ui->tbtnExit, &QToolButton::clicked, this, &QMainWindow::close);
    ui->tabWidget->addTab(m_mainWidget,
                          QIcon("/home/vladyslav/Desktop/QtFinance/QtFinance/Images/main.png"), "Main");
    ui->tabWidget->addTab(m_expenseWidget,
                          QIcon("/home/vladyslav/Desktop/QtFinance/QtFinance/Images/expenses.png"), "Expenses");
    ui->tabWidget->addTab(m_incomeWidget,
                          QIcon("/home/vladyslav/Desktop/QtFinance/QtFinance/Images/incomes.png"), "Incomes");
    ui->tabWidget->setIconSize(QSize(40, 40));
}

MainWindow::~MainWindow()
{
    delete m_expenseWidget;
    delete m_incomeWidget;
    delete ui;
    close();
}

void MainWindow::close()
{
    QMainWindow::close();
}

