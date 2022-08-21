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

    ui->dtDate->setDate(QDate::currentDate());
    QStringList list = QStringList() << "Beauty"
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
    ui->cbCategory->addItems(list);
    ui->edtShopName->setText(m_expense.getShopName());
    ui->dsbExpense->setValue(m_expense.getExpense());
}

ExpenseDialog::~ExpenseDialog()
{
    delete ui;
}

void ExpenseDialog::accept()
{
    m_expense = Expense(ui->dtDate->date(), ui->cbCategory->currentText(),
                        ui->dsbExpense->value(), ui->edtShopName->text());
    QDialog::accept();
}

void ExpenseDialog::reject()
{
    QDialog::reject();
}
