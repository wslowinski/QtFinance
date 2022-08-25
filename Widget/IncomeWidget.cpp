#include "IncomeWidget.h"
#include "ui_IncomeWidget.h"
#include "Dialog/IncomeDialog.h"
#include "Model/IncomeModel.h"

IncomeWidget::IncomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IncomeWidget),
    m_incomeModel(new IncomeModel(this))
{
    ui->setupUi(this);
    connect(ui->btnAdd, &QPushButton::clicked, this, &IncomeWidget::add);
    setModel(m_incomeModel);
}

IncomeWidget::~IncomeWidget()
{
    delete ui;
}

void IncomeWidget::setModel(IncomeModel* model)
{
    ui->tabIncomes->setModel(model);
}

void IncomeWidget::add()
{
    Income income;
    IncomeDialog dialog(income);
    auto dialogCode = dialog.exec();
    if(dialogCode == QDialog::Accepted)
    {
        QModelIndex createdIndex = m_incomeModel->add(income);
        ui->tabIncomes->setCurrentIndex(createdIndex);
    }
}

void IncomeWidget::edit()
{

}

void IncomeWidget::remove()
{

}
