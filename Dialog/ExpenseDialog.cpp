#include "ExpenseDialog.h"
#include "Class/Currencies.h"
#include "ui_ExpenseDialog.h"
#include "Widget/ExpenseWidget.h"
#include "Dialog/CategoryDialog.h"
#include "Model/CategoryModel.h"

ExpenseDialog::ExpenseDialog(Expense& expense, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpenseDialog),
    m_expense(expense),
    category_model_(new CategoryModel(this))
{
    ui->setupUi(this);
    connect(ui->btnBox, &QDialogButtonBox::accepted, this, &ExpenseDialog::accept);
    connect(ui->btnBox, &QDialogButtonBox::rejected, this, &ExpenseDialog::reject);
    connect(ui->btnAddCategory, &QPushButton::clicked, this, &ExpenseDialog::addCategory);
    init();

    ui->cbCategory->setModel(category_model_);
    ui->cbCategory->setModelColumn(1);
}

ExpenseDialog::~ExpenseDialog()
{
    delete ui;
}

void ExpenseDialog::accept()
{
    ExpenseWidget exp;
    int previousID = exp.getCurrentID();
    m_expense = Expense((previousID != 0) ? previousID + 1 : 1,
                        ui->dsbExpense->value(), ui->cbbSymbol->currentText(),
                        ui->cbCategory->currentText(), ui->edtTitle->text(),
                        ui->dtDate->date(), ui->dspRate->value(),
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
    const QString& path = "/home/vladyslav/Desktop/QtFinance/QtFinance/Images/";

    ui->edtTitle->setText(m_expense.getTitle());
    ui->dtDate->setDate(m_expense.getDate());

    ui->edtComment->setPlainText(m_expense.getComment());
    const QPixmap& pmIncome(path + "expenses.png");
    ui->imgExpense->setPixmap(pmIncome.scaled(70, 60, Qt::KeepAspectRatio));

    ui->dtExchangeRateDate->setDate(QDate::currentDate());
    ui->dtExchangeRateDate->setEnabled(false);
    connect(ui->cbArchivedExchangeRates, &QCheckBox::clicked, this, &ExpenseDialog::setting);
    connect(ui->btnDownloadExchangeRates, &QPushButton::clicked, this, &ExpenseDialog::download);
    Currencies currencies;
    m_rates = currencies.parseJSON();
    for (unsigned int i = 0; i < m_rates.size(); i++)
    {
        m_list << m_rates.at(i).first;
    }
    ui->cbbSymbol->addItems(m_list);
    ui->dspRate->setValue(m_expense.getExchangeRate());
    connect(ui->cbbSymbol, SIGNAL(currentIndexChanged(int)),
                this, SLOT(filter(int)));
}

void ExpenseDialog::setting()
{
    bool isChecked = ui->cbArchivedExchangeRates->isChecked();
    ui->dtExchangeRateDate->setEnabled(isChecked);
    if (!isChecked) ui->dtExchangeRateDate->setDate(QDate::currentDate());
}

void ExpenseDialog::download()
{
    Currencies currencies(ui->dtExchangeRateDate->date(), true);
    m_rates = currencies.parseJSON();
}

void ExpenseDialog::filter(int index)
{
    ui->dspRate->setValue(m_rates.at(index).second);
}

void ExpenseDialog::addCategory()
{
    Category category;
    CategoryDialog dialog(category);
    auto dialogCode = dialog.exec();
    if(dialogCode == QDialog::Accepted)
    {
        QModelIndex createdIndex = category_model_->add(category);
        ui->cbCategory->setCurrentIndex(createdIndex.row());
    }
}
