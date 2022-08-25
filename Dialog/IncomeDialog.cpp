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

    ui->dtDate->setDate(m_income.getDate());
    ui->edtTitle->setText(m_income.getTitle());
    ui->dsbIncome->setValue(m_income.getIncome());
}

IncomeDialog::~IncomeDialog()
{
    delete ui;
}

void IncomeDialog::accept()
{
    m_income = Income(ui->dtDate->date(), ui->edtTitle->text(),
                      ui->dsbIncome->value());
    QDialog::accept();
}

void IncomeDialog::reject()
{
    QDialog::reject();
}
