#include "MainWidget.h"
#include "ui_MainWidget.h"

#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->dtExchangeRateDate->setDate(QDate::currentDate());
    ui->dtExchangeRateDate->setEnabled(false);
    connect(ui->cbArchivedExchangeRates, &QCheckBox::clicked, this, &MainWidget::setting);
    connect(ui->btnDownloadExchangeRates, &QPushButton::clicked, this, &MainWidget::download);
    Currencies currencies;
    m_rates = currencies.parseJSON();
    for (unsigned int i = 0; i < m_rates.size(); i++)
    {
        m_list << m_rates.at(i).first;
    }
    ui->cbbSymbol->addItems(m_list);
    ui->dspRate->setValue(1.0);
    connect(ui->cbbSymbol, SIGNAL(currentIndexChanged(int)),
                this, SLOT(filter(int)));
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
    Currencies currencies(ui->dtExchangeRateDate->date(), true);
    m_rates = currencies.parseJSON();
    for (unsigned int i = 0; i < m_rates.size(); i++)
    {
        ui->edtText->append(QString{m_rates.at(i).first + ": " + QString::number(m_rates.at(i).second)});
    }
}

void MainWidget::filter(int index)
{
    ui->dspRate->setValue(m_rates.at(index).second);
}
