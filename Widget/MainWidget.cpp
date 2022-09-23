#include "MainWidget.h"
#include "ui_MainWidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    QStringList list = QStringList() << "PL" << "EUR" << "USD";
    ui->cbbSymbol->addItems(list);
    ui->dtExchangeRateDate->setDate(QDate::currentDate());
    ui->dtExchangeRateDate->setEnabled(false);
    connect(ui->cbArchivedExchangeRates, &QCheckBox::clicked, this, &MainWidget::setting);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::setting()
{
    ui->dtExchangeRateDate->setEnabled(ui->cbArchivedExchangeRates->isChecked());
}
