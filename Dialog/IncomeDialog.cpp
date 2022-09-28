#include "IncomeDialog.h"
#include "ui_IncomeDialog.h"
#include "Widget/IncomeWidget.h"

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
    IncomeWidget inc;
    int previousID = inc.getCurrentID();
    m_income = Income((previousID != 0) ? previousID + 1 : 1,
                      ui->dsbIncome->value(), ui->cbbSymbol->currentText(),
                      ui->edtTitle->text(), ui->dtDate->date(),
                      ui->dspRate->value(),
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

    const QString& path = "/home/vladyslav/Desktop/QtFinance/QtFinance/Images/";
    const QPixmap& pmIncome(path + "incomes.png");
    ui->imgIncome->setPixmap(pmIncome.scaled(70, 60, Qt::KeepAspectRatio));

    ui->dtExchangeRateDate->setDate(QDate::currentDate());
    ui->dtExchangeRateDate->setEnabled(false);
    connect(ui->cbArchivedExchangeRates, &QCheckBox::clicked, this, &IncomeDialog::setting);
    connect(ui->btnDownloadExchangeRates, &QPushButton::clicked, this, &IncomeDialog::download);
    Currencies currencies;
    m_rates = currencies.parseJSON();
    for (unsigned int i = 0; i < m_rates.size(); i++)
    {
        m_list << m_rates.at(i).first;
    }
    ui->cbbSymbol->addItems(m_list);
    ui->dspRate->setValue(m_income.getExchangeRate());
    connect(ui->cbbSymbol, SIGNAL(currentIndexChanged(int)),
                this, SLOT(filter(int)));
}

void IncomeDialog::setting()
{
    bool isChecked = ui->cbArchivedExchangeRates->isChecked();
    ui->dtExchangeRateDate->setEnabled(isChecked);
    if (!isChecked) ui->dtExchangeRateDate->setDate(QDate::currentDate());
}

void IncomeDialog::download()
{
    Currencies currencies(ui->dtExchangeRateDate->date(), true);
    m_rates = currencies.parseJSON();
}

void IncomeDialog::filter(int index)
{
    ui->dspRate->setValue(m_rates.at(index).second);
}
