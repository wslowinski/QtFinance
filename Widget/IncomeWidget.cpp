#include "IncomeWidget.h"
#include "ui_IncomeWidget.h"
#include "Dialog/IncomeDialog.h"
#include "Model/IncomeModel.h"
#include "Code/Messages.h"
#include "Code/Style.h"

#include <QMessageBox>

IncomeWidget::IncomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IncomeWidget),
    m_incomeModel(new IncomeModel(this))
{
    ui->setupUi(this);
    connect(ui->btnAdd, &QPushButton::clicked, this, &IncomeWidget::add);
    connect(ui->btnDelete, &QPushButton::clicked, this, &IncomeWidget::remove);
    setModel(m_incomeModel);
    Style::setTableViewStyle(ui->tabIncomes);
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
    unsigned int currentRow = ui->tabIncomes->currentIndex().row();
    !m_incomeModel->removeRows(currentRow, 1) ?
        showMessage(MSG_CANNOT_DELETE_ROW) : showMessage(MSG_DELETE_ROW);
}
