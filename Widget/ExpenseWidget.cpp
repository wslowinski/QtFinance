#include "ExpenseWidget.h"
#include "ui_ExpenseWidget.h"
#include "Dialog/ExpenseDialog.h"
#include "Model/ExpenseModel.h"
#include "Code/Messages.h"
#include "Code/Style.h"

#include <QMessageBox>

ExpenseWidget::ExpenseWidget(QWidget* parent):
    QWidget(parent),
    ui(new Ui::ExpenseWidget),
    m_expenseModel(
        new ExpenseModel(this, getSQLFilter(getPeriodType(PeriodType::ALL))))
{
    init();
}

ExpenseWidget::~ExpenseWidget()
{
    delete m_expenseModel;
    delete ui;
}

void ExpenseWidget::setModel(ExpenseModel* model)
{
    ui->tabExpenses->setModel(model);
}

void ExpenseWidget::add()
{
    Expense expense;
    ExpenseDialog dialog(expense);
    auto dialogCode = dialog.exec();
    if(dialogCode == QDialog::Accepted)
    {
        QModelIndex createdIndex = m_expenseModel->add(expense);
        ui->tabExpenses->setCurrentIndex(createdIndex);
    }
}

void ExpenseWidget::edit()
{

}

void ExpenseWidget::remove()
{
    unsigned int currentRow = ui->tabExpenses->currentIndex().row();
    !m_expenseModel->removeRows(currentRow, 1) ?
        showMessage(MSG_CANNOT_DELETE_ROW) : showMessage(MSG_DELETE_ROW);
}

void ExpenseWidget::init()
{
    ui->setupUi(this);
    connect(ui->btnAdd, &QPushButton::clicked, this, &ExpenseWidget::add);
    ui->btnAdd->setIcon(QIcon("/home/vladyslav/Desktop/QtFinance/QtFinance/Images/add.png"));
    ui->btnAdd->setIconSize(QSize(25, 25));

    connect(ui->btnDelete, &QPushButton::clicked, this, &ExpenseWidget::remove);
    ui->btnDelete->setIcon(QIcon("/home/vladyslav/Desktop/QtFinance/QtFinance/Images/delete.png"));
    ui->btnDelete->setIconSize(QSize(25, 25));

    ui->btnEdit->setIcon(QIcon("/home/vladyslav/Desktop/QtFinance/QtFinance/Images/edit.png"));
    ui->btnEdit->setIconSize(QSize(25, 25));

    connect(ui->cbbPeriod, SIGNAL(currentIndexChanged(int)),
                this, SLOT(filter(int)));

    QStringList list = QStringList() << "All"
                                     << "Current day"
                                     << "Current week"
                                     << "Current month"
                                     << "Current year"
                                     << "Previous day"
                                     << "Previous week"
                                     << "Previous month"
                                     << "Previous year"
                                     << "Non-standard period";
    ui->cbbPeriod->addItems(list);
    connect(ui->cbbPeriod, &QComboBox::currentIndexChanged, this, &ExpenseWidget::setting);
    ui->dtTo->setDate(QDate::currentDate());

    setModel(m_expenseModel);
    Style::setTableViewStyle(ui->tabExpenses);
}


void ExpenseWidget::setting()
{
    bool enabledCondition =
            ui->cbbPeriod->currentIndex() == getPeriodType(PeriodType::NON_STANDARD);
    ui->dtFrom->setEnabled(enabledCondition);
    ui->dtTo->setEnabled(enabledCondition);
}

void ExpenseWidget::filter(int index)
{
    m_expenseModel =
            new ExpenseModel(this, getSQLFilter(index));
    setModel(m_expenseModel);
}

QString ExpenseWidget::getSQLFilter(int index)
{
    switch (index) {
    case 0:
        return QString{"SELECT * FROM expenses"};
    case 1:
        return QString{"SELECT * FROM expenses WHERE date = '"} +
            QString{QDate::currentDate().toString("yyyy-MM-dd")} + QString{"'"};
    default:
        return QString{"SELECT * FROM expenses"};
    }
}

