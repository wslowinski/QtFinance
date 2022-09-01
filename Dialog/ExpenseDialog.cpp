#include "ExpenseDialog.h"
#include "ui_ExpenseDialog.h"

ExpenseDialog::ExpenseDialog(Expense& expense, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpenseDialog),
    m_expense(expense)
{
    ui->setupUi(this);

    connect(ui->btnBox, &QDialogButtonBox::accepted, this, &ExpenseDialog::accept);
    connect(ui->btnBox, &QDialogButtonBox::rejected, this, &ExpenseDialog::reject);

    ui->dsbExpense->setValue(m_expense.getExpense());
    QStringList currencyCodesList = QStringList() << "PLN"
                                                  << "EUR"
                                                  << "USD";
    ui->cbbCurrencyCode->addItems(currencyCodesList);
    QStringList categoriesList = QStringList() << "Beauty"
                                     << "Bills"
                                     << "Drugstore"
                                     << "Fashion"
                                     << "Free Time"
                                     << "Groceries"
                                     << "Health"
                                     << "Home appliances"
                                     << "Restaurants"
                                     << "Transport"
                                     << "No Category";
    ui->cbCategory->addItems(categoriesList);
    ui->edtTitle->setText(m_expense.getTitle());
    ui->dtDate->setDate(m_expense.getDate());
    ui->dsbExchangeRate->setValue(m_expense.getExchangeRate());
    ui->edtComment->setPlainText(m_expense.getComment());
}

ExpenseDialog::~ExpenseDialog()
{
    delete ui;
}

void ExpenseDialog::accept()
{
    m_expense = Expense(ui->dsbExpense->value(), ui->cbbCurrencyCode->currentText(),
                        ui->cbCategory->currentText(), ui->edtTitle->text(),
                        ui->dtDate->date(), ui->dsbExchangeRate->value(),
                        ui->edtComment->toPlainText());
    QDialog::accept();
}

void ExpenseDialog::reject()
{
    QDialog::reject();
}
