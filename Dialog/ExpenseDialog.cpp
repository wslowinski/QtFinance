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
    init();
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

void ExpenseDialog::init()
{
    ui->dsbExpense->setValue(m_expense.getExpense());
    QStringList currencyCodesList = QStringList() << "PLN" << "EUR" << "USD";
    ui->cbbCurrencyCode->addItems(currencyCodesList);
    const QString& path = "/home/vladyslav/Desktop/QtFinance/QtFinance/Images/";

    categoriesArray.push_back(std::make_pair(path + "beauty.png", "Beauty"));
    categoriesArray.push_back(std::make_pair(path + "bills.png", "Bills"));
    categoriesArray.push_back(std::make_pair(path + "drugstore.png", "Drugstore"));
    categoriesArray.push_back(std::make_pair(path + "fashion.png", "Fashion"));
    categoriesArray.push_back(std::make_pair(path + "free_time.png", "Free Time"));
    categoriesArray.push_back(std::make_pair(path + "groceries.png", "Groceries"));
    categoriesArray.push_back(std::make_pair(path + "health.png", "Health"));
    categoriesArray.push_back(std::make_pair(path + "home_appliances.png", "Home appliances"));
    categoriesArray.push_back(std::make_pair(path + "restaurants.png", "Restaurants"));
    categoriesArray.push_back(std::make_pair(path + "transport.png", "Transport"));
    categoriesArray.push_back(std::make_pair(path + "no_category.png", "No Category"));
    for (unsigned int i = 0; i < categoriesArray.size(); i++)
    {
        ui->cbCategory->addItem(QIcon(categoriesArray[i].first), categoriesArray[i].second);
    }
    ui->edtTitle->setText(m_expense.getTitle());
    ui->dtDate->setDate(m_expense.getDate());
    ui->dsbExchangeRate->setValue(m_expense.getExchangeRate());
    ui->edtComment->setPlainText(m_expense.getComment());
}
