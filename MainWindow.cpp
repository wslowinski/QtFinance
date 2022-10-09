#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "Widget/ExpenseWidget.h"
#include "Widget/IncomeWidget.h"
#include "Widget/MainWidget.h"
#include "Widget/PieChartWidget.h"
#include "Dialog/DatabaseDialog.h"

#include <QScreen>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_expenseWidget(new ExpenseWidget(this)),
    m_incomeWidget(new IncomeWidget(this)),
    m_mainWidget(new MainWidget(this)),
    m_pieChartWidget(new PieChartWidget(this))
{
    ui->setupUi(this);
    QMainWindow::setWindowState(Qt::WindowMaximized);
    connect(ui->btnExit, &QToolButton::clicked, this, &QMainWindow::close);
    ui->btnDB->setIcon(QIcon("/home/vladyslav/Desktop/QtFinance/QtFinance/Images/db.png"));
    ui->btnDB->setIconSize(QSize(70, 70));
    ui->btnExit->setIcon(QIcon("/home/vladyslav/Desktop/QtFinance/QtFinance/Images/shutdown.png"));
    ui->btnExit->setIconSize(QSize(70, 70));
    ui->tabWidget->addTab(m_mainWidget,
                          QIcon("/home/vladyslav/Desktop/QtFinance/QtFinance/Images/main.png"), "Main");
    ui->tabWidget->addTab(m_expenseWidget,
                          QIcon("/home/vladyslav/Desktop/QtFinance/QtFinance/Images/expenses.png"), "Expenses");
    ui->tabWidget->addTab(m_incomeWidget,
                          QIcon("/home/vladyslav/Desktop/QtFinance/QtFinance/Images/incomes.png"), "Incomes");
    ui->tabWidget->addTab(m_pieChartWidget,
                          QIcon("/home/vladyslav/Desktop/QtFinance/QtFinance/Images/chart.png"), "Analysis");
    ui->tabWidget->setIconSize(QSize(40, 40));
}

MainWindow::~MainWindow()
{
    delete m_expenseWidget;
    delete m_incomeWidget;
    delete m_mainWidget;
    delete m_pieChartWidget;
    delete ui;
    close();
}

void MainWindow::close()
{
    QMainWindow::close();
}

void MainWindow::on_btnDB_clicked()
{
    DatabaseDialog dbDialog("/home/vladyslav/Database/budget.db");
    dbDialog.exec();
}

