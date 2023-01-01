#include "IncomeWidget.h"
#include "ui_IncomeWidget.h"
#include "Dialog/IncomeDialog.h"
#include "Model/IncomeModel.h"
#include "Code/Messages.h"
#include "Code/Style.h"
#include "Code/PeriodTypes.h"
#include "Code/SqlFilter.h"

#include <QMessageBox>

IncomeWidget::IncomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IncomeWidget),
    m_incomeModel(new IncomeModel(this, filterRecordsByPeriod("incomes", getPeriodType(PeriodType::ALL)))),
    m_database(DatabaseManager::getInstance()),
    m_incomeAnalysis(m_database.m_incomeAnalysis)
{
    init();
}

IncomeWidget::~IncomeWidget()
{
    delete m_incomeModel;
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
    ui->lblTotal->setText(QVariant(m_incomeAnalysis.getIncomesSum(ui->cbbPeriod->currentIndex())).toString() + " zł");
}

void IncomeWidget::edit()
{

}

void IncomeWidget::remove()
{
    unsigned int currentRow = ui->tabIncomes->currentIndex().row();
    !m_incomeModel->removeRows(currentRow, 1) ?
        showMessage(MSG_CANNOT_DELETE_ROW) : showMessage(MSG_DELETE_ROW);
    ui->lblTotal->setText(QVariant(m_incomeAnalysis.getIncomesSum(ui->cbbPeriod->currentIndex())).toString() + " zł");
}

void IncomeWidget::init()
{
    ui->setupUi(this);
    connect(ui->btnAdd, &QPushButton::clicked, this, &IncomeWidget::add);
    ui->btnAdd->setIcon(QIcon("/home/vladyslav/Desktop/QtFinance/QtFinance/Images/add.png"));
    ui->btnAdd->setIconSize(QSize(25, 25));

    connect(ui->btnDelete, &QPushButton::clicked, this, &IncomeWidget::remove);
    ui->btnDelete->setIcon(QIcon("/home/vladyslav/Desktop/QtFinance/QtFinance/Images/delete.png"));
    ui->btnDelete->setIconSize(QSize(25, 25));

    ui->btnEdit->setIcon(QIcon("/home/vladyslav/Desktop/QtFinance/QtFinance/Images/edit.png"));
    ui->btnEdit->setIconSize(QSize(25, 25));

    QStringList list = QStringList() << "All"
                                     << "Current day"
                                     << "Current month"
                                     << "Current year"
                                     << "Previous month"
                                     << "Previous year"
                                     << "Non-standard period";
    ui->cbbPeriod->addItems(list);
    connect(ui->cbbPeriod, SIGNAL(currentIndexChanged(int)),
                this, SLOT(filter(int)));
    connect(ui->cbbPeriod, &QComboBox::currentIndexChanged, this, &IncomeWidget::setting);
    ui->dtTo->setDate(QDate::currentDate());

    setModel(m_incomeModel);
    Style::setTableViewStyle(ui->tabIncomes);
    ui->lblTotal->setText(QVariant(m_incomeAnalysis.getIncomesSum(ui->cbbPeriod->currentIndex())).toString() + " zł");
}

void IncomeWidget::setting()
{
    bool enabledCondition =
            ui->cbbPeriod->currentIndex() == getPeriodType(PeriodType::NON_STANDARD);
    ui->dtFrom->setEnabled(enabledCondition);
    ui->dtTo->setEnabled(enabledCondition);
}

void IncomeWidget::filter(int index)
{
    m_incomeModel = (index != PeriodType::NON_STANDARD) ?
                new IncomeModel(this, filterRecordsByPeriod("incomes", index)):
                new IncomeModel(this, filterRecordsByPeriod("incomes", index,
                    ui->dtFrom->date(), ui->dtTo->date()));
    ui->lblTotal->setText(QVariant(m_incomeAnalysis.getIncomesSum(ui->cbbPeriod->currentIndex())).toString() + " zł");
    setModel(m_incomeModel);
}

int IncomeWidget::getCurrentID()
{
    int rowCount = ui->tabIncomes->model()->rowCount();
    return ui->tabIncomes->model()->index(rowCount - 1, 0).data().toInt();
}
