#include "IncomeDialog.h"
#include "ui_IncomeDialog.h"

IncomeDialog::IncomeDialog(Income& income, QWidget *parent):
    QDialog(parent),
    ui(new Ui::IncomeDialog),
    m_income(income)
{
    ui->setupUi(this);

    connect(ui->btnBox, &QDialogButtonBox::accepted, this, &IncomeDialog::accept);
    connect(ui->btnBox, &QDialogButtonBox::rejected, this, &IncomeDialog::reject);
    init();
}

IncomeDialog::~IncomeDialog()
{
    delete ui;
}

void IncomeDialog::accept()
{
    m_income = Income(ui->dsbIncome->value(), ui->cbbCurrencyCode->currentText(),
                      ui->edtTitle->text(), ui->dtDate->date(),
                      ui->dsbExchangeRate->value(),
                      ui->edtComment->toPlainText());
    QDialog::accept();
}

void IncomeDialog::reject()
{
    QDialog::reject();
}

void IncomeDialog::init()
{
    ui->dtDate->setDate(m_income.getDate());
    ui->edtTitle->setText(m_income.getTitle());
    ui->dsbIncome->setValue(m_income.getIncome());
    QStringList currencyCodesList = QStringList() << "PLN" << "EUR" << "USD";
    ui->cbbCurrencyCode->addItems(currencyCodesList);
    const QString& path = "/home/vladyslav/Desktop/QtFinance/QtFinance/Images/";
    const QPixmap& pmIncome(path + "incomes.png");
    ui->imgIncome->setPixmap(pmIncome.scaled(70, 60, Qt::KeepAspectRatio));
}
