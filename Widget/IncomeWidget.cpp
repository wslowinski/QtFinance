#include "IncomeWidget.h"
#include "ui_IncomeWidget.h"
#include "Dialog/IncomeDialog.h"
#include "Model/IncomeModel.h"

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
    setDesign();
}

IncomeWidget::~IncomeWidget()
{
    delete ui;
}

void IncomeWidget::setModel(IncomeModel* model)
{
    ui->tabIncomes->setModel(model);
}

void IncomeWidget::setDesign()
{

    ui->tabIncomes->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tabIncomes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabIncomes->setTextElideMode(Qt::ElideRight);
    ui->tabIncomes->horizontalHeader()->setVisible(true);
    ui->tabIncomes->resizeColumnsToContents();
    ui->tabIncomes->setCurrentIndex(ui->tabIncomes->model()->index(0,0));
    ui->tabIncomes->show();
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
                QMessageBox::warning(this, tr("Delete current row"),
                    tr("Current row could not be deleted!"), QMessageBox::Ok) :
                QMessageBox::information(this, tr("Delete current row"),
                    tr("Current row has been deleted!"), QMessageBox::Ok);
}
