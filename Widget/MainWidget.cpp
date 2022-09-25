#include "MainWidget.h"
#include "ui_MainWidget.h"
#include <Class/Currencies.h>

#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

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

    connect(ui->btnDownloadExchangeRates, &QPushButton::clicked, this, &MainWidget::download);

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::setting()
{
    bool isChecked = ui->cbArchivedExchangeRates->isChecked();
    ui->dtExchangeRateDate->setEnabled(isChecked);
    if (!isChecked) ui->dtExchangeRateDate->setDate(QDate::currentDate());
}

void MainWidget::download()
{
    Currencies currencies(ui->dtExchangeRateDate->date());
    Currencies::Rates rates = currencies.parseJSON();
    for (unsigned int i = 0; i < rates.size(); i++)
    {
        ui->edtText->append(QString{rates.at(i).first + ":           " + QString::number(rates.at(i).second)});
    }
}
