#include "ExpenseWidget.h"
#include "ui_ExpenseWidget.h"
#include "Dialog/ExpenseDialog.h"
#include "Model/ExpenseModel.h"
#include "Code/Messages.h"
#include "Code/Style.h"
#include "Code/PeriodTypes.h"
#include "Code/SqlFilter.h"

#include <QMessageBox>
#include <QPainter>

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
    ui->lblTotal->setText(QString::number(calculateSum()) + " zł");
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

    m_categoriesName = {"Beauty", "Bills", "Drugstore", "Fashion", "Free Time",
                      "Groceries", "Health", "Home appliances", "Restaurants",
                      "Transport", "No Category"};
    m_categoriesLabels = {ui->lblBeauty, ui->lblBills, ui->lblDrugstore,
                        ui->lblFashion, ui->lblFreeTime, ui->lblGroceries,
                        ui->lblHealth, ui->lblHomeAppliances, ui->lblRestaurants,
                        ui->lblTransport, ui->lblNoCategory};
    m_categoriesPercentages = {ui->lblBeautyPercentage, ui->lblBillsPercentage, ui->lblDrugstorePercentage,
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
    ui->lblTotal->setText(QVariant(calculateSum()).toString() + " zł");
    setModel(m_expenseModel);
}

double ExpenseWidget::calculateSum()
{
    double expensesSum = 0.;
    std::vector<double> expenses;
    m_percentages = {};
    for (unsigned int i = 0; i < m_categoriesName.size(); i++)
    {
        double sum = m_expenseAnalysis.getCategoryExpenseSum(m_categoriesName.at(i), ui->cbbPeriod->currentIndex());
        expenses.push_back(sum);
        m_categoriesLabels.at(i)->setText(QString::number(sum, 'f', 2) + " zł");
        expensesSum += sum;
    }
    for (unsigned int i = 0; i < expenses.size(); i++)
    {
        double percentage = (expensesSum != 0.) ? expenses.at(i) / expensesSum * 100. : 0.;
        m_percentages.push_back(percentage);
        m_categoriesPercentages.at(i)->setText(QString::number(percentage, 'f', 2) + " %");
    }
    this->update();
    m_expensesSum = expensesSum;
    return expensesSum;
}

int ExpenseWidget::getCurrentID()
{
    int rowCount = ui->tabExpenses->model()->rowCount();
    return ui->tabExpenses->model()->index(rowCount - 1, 0).data().toInt();
}

void ExpenseWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if (m_expensesSum == 0.) return;
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Ubuntu", 11));
    QRectF size = QRectF(1070, 250, 300, 300);
    std::vector<Qt::GlobalColor> colors = {Qt::black, Qt::blue, Qt::cyan, Qt::green, Qt::magenta, Qt::red,
                                          Qt::yellow, Qt::white, Qt::darkYellow, Qt::lightGray, Qt::darkCyan};
    const int rate = 27; int y = 260; double sum = 0;
    for (unsigned int i = 0; i < m_percentages.size(); ++i)
    {
        painter.setBrush(colors.at(i));
        painter.drawPie(size, sum, getPie(m_percentages.at(i)));
        sum += getPie(m_percentages.at(i));
        painter.drawEllipse(1390+20, y - 10, 10, 10);
        painter.drawText(1430+20, y, m_categoriesName.at(i));
        painter.drawText(1600+20, y, QString::number(m_percentages.at(i), 'g', 2) + " %");
        y += rate;
    }
    painter.setBrush(Qt::white);
    painter.drawEllipse(1140, 320, 160, 160);
    painter.setFont(QFont("Ubuntu", 22, QFont::Bold));
    painter.drawText(1180, 410, "100 %");
}

double ExpenseWidget::getPie(double percentage)
{
    return 16 * percentage * 360 / 100;
}
