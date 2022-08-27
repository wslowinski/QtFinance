#include "ExpenseWidget.h"
#include "ui_ExpenseWidget.h"
#include "Dialog/ExpenseDialog.h"
#include "Model/ExpenseModel.h"

ExpenseWidget::ExpenseWidget(QWidget* parent):
    QWidget(parent),
    ui(new Ui::ExpenseWidget),
    m_expenseModel(new ExpenseModel(this))
{
    ui->setupUi(this);
    connect(ui->btnAdd, &QPushButton::clicked, this, &ExpenseWidget::add);
    setModel(m_expenseModel);
    setDesign();
}

ExpenseWidget::~ExpenseWidget()
{
    delete ui;
}

void ExpenseWidget::setModel(ExpenseModel* model)
{
    ui->tabExpenses->setModel(model);
}

void ExpenseWidget::setDesign()
{
//    ui->tabExpenses->setStyleSheet("QTableView{"
//                                   "background-color: #FFCCE5;"
//                                   "alternate-background-color: #FF99CC;"
//                                   "selection-background-color: #FF3399;"
//                                   "}");
//    ui->tabExpenses->setAlternatingRowColors(true);
    ui->tabExpenses->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tabExpenses->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabExpenses->setTextElideMode(Qt::ElideRight);
    ui->tabExpenses->horizontalHeader()->setVisible(true);
    ui->tabExpenses->resizeColumnsToContents();
    ui->tabExpenses->show();
}

void ExpenseWidget::add()
{
    Expense expense;
    ExpenseDialog dialog(expense);
    auto dialogCode = dialog.exec();
    if(dialogCode == QDialog::Accepted)
    {
        QModelIndex createdIndex = m_expenseModel->add(expense);
        ui->tabExpenses->setCurrentIndex(createdIndex);
    }
}

void ExpenseWidget::edit()
{
    Expense expense;
    ExpenseDialog dialog(expense);
    auto dialogCode = dialog.exec();
    if(dialogCode == QDialog::Accepted)
    {
        QModelIndex createdIndex = m_expenseModel->add(expense);
        ui->tabExpenses->setCurrentIndex(createdIndex);
    }
}

void ExpenseWidget::remove()
{

}
