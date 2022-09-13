#include "ExpenseWidget.h"
#include "ui_ExpenseWidget.h"
#include "Dialog/ExpenseDialog.h"
#include "Model/ExpenseModel.h"
#include "Code/Messages.h"
#include "Code/Style.h"
#include "Code/PeriodTypes.h"
#include "Code/SqlFilter.h"

#include <QMessageBox>

ExpenseWidget::ExpenseWidget(QWidget* parent):
    QWidget(parent),
    ui(new Ui::ExpenseWidget),
    m_expenseModel(
        new ExpenseModel(this, filterRecordsByPeriod("expenses", getPeriodType(PeriodType::ALL)))),
    m_database(DatabaseManager::instance()),
    m_expenseAnalysis(m_database.m_expenseAnalysis)
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
    ui->lblTotal->setText(QVariant(calculateSum()).toString() + " zł");
}

void ExpenseWidget::edit()
{

}

void ExpenseWidget::remove()
{
    unsigned int currentRow = ui->tabExpenses->currentIndex().row();
    !m_expenseModel->removeRows(currentRow, 1) ?
        showMessage(MSG_CANNOT_DELETE_ROW) : showMessage(MSG_DELETE_ROW);
    ui->lblTotal->setText(QVariant(calculateSum()).toString() + " zł");
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
                                     << "Current month"
                                     << "Current year"
                                     << "Previous month"
                                     << "Previous year"
                                     << "Non-standard period";
    ui->cbbPeriod->addItems(list);
    connect(ui->cbbPeriod, &QComboBox::currentIndexChanged, this, &ExpenseWidget::setting);
    ui->dtTo->setDate(QDate::currentDate());

    setModel(m_expenseModel);
    Style::setTableViewStyle(ui->tabExpenses);

    categoriesName = {"Beauty", "Bills", "Drugstore", "Fashion", "Free Time",
                      "Groceries", "Health", "Home appliances", "Restaurants",
                      "Transport", "No Category"};
    categoriesLabels = {ui->lblBeauty, ui->lblBills, ui->lblDrugstore,
                        ui->lblFashion, ui->lblFreeTime, ui->lblGroceries,
                        ui->lblHealth, ui->lblHomeAppliances, ui->lblRestaurants,
                        ui->lblTransport, ui->lblNoCategory};
    categoriesPercentages = {ui->lblBeautyPercentage, ui->lblBillsPercentage, ui->lblDrugstorePercentage,
                             ui->lblFashionPercentage, ui->lblFreeTimePercentage, ui->lblGroceriesPercentage,
                             ui->lblHealthPercentage, ui->lblHomeAppliancesPercentage, ui->lblRestaurantsPercentage,
                             ui->lblTransportPercentage, ui->lblNoCategoryPercentage};
    ui->lblTotal->setText(QVariant(calculateSum()).toString() + " zł");
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
    m_expenseModel = (index != PeriodType::NON_STANDARD) ?
                new ExpenseModel(this, filterRecordsByPeriod("expenses", index)):
                new ExpenseModel(this, filterRecordsByPeriod("expenses", index,
                    ui->dtFrom->date(), ui->dtTo->date()));
    setModel(m_expenseModel);
}

double ExpenseWidget::calculateSum()
{
    double expensesSum = 0.;
    std::vector<double> expenses;
    for (unsigned int i = 0; i < categoriesName.size(); i++)
    {
        double sum = m_expenseAnalysis.getCategoryExpenseSum(categoriesName.at(i), PeriodType::CURRENT_MONTH);
        expenses.push_back(sum);
        categoriesLabels.at(i)->setText(QVariant(sum).toString() + " zł");
        expensesSum += sum;
    }
    for (unsigned int i = 0; i < expenses.size(); i++)
    {
        double percentage = expenses.at(i) / expensesSum * 100.;
        categoriesPercentages.at(i)->setText(QString::number(percentage, 'g', 2) + " %");
    }
    return expensesSum;
}

int ExpenseWidget::getCurrentID()
{
    int rowCount = ui->tabExpenses->model()->rowCount();
    return ui->tabExpenses->model()->index(rowCount - 1, 0).data().toInt();
}

