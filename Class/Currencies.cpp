#include "Currencies.h"

#include <QEventLoop>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

Currencies::Currencies(const QDate& date):
    m_date(date)
{
}

QString Currencies::downloadCurrencies()
{
    QString urlAsString = QString{"http://api.nbp.pl/api/exchangerates/tables/A/"
            + m_date.toString("yyyy-MM-dd") +"/?format=json"};
    QNetworkAccessManager manager;
    QNetworkReply* response = manager.get(QNetworkRequest(QUrl(urlAsString)));
    QEventLoop event;
    QAbstractSocket::connect(response, SIGNAL(finished()), &event, SLOT(quit()));
    event.exec();
    QString content = response->readAll();
    return content;
}
