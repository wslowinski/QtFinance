#include "Currencies.h"

#include <QEventLoop>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

Currencies::Currencies(const QDate& date, bool isArchival):
    m_date(date),
    m_isArchival(isArchival)
{
}

QString Currencies::downloadCurrencies()
{
    QString urlAsString = m_isArchival ? QString{"http://api.nbp.pl/api/exchangerates/tables/A/"
            + m_date.toString("yyyy-MM-dd") +"/?format=json"} :
            QString{"http://api.nbp.pl/api/exchangerates/tables/A/?format=json"};                             ;
    QNetworkAccessManager manager;
    QNetworkReply* response = manager.get(QNetworkRequest(QUrl(urlAsString)));
    QEventLoop event;
    QAbstractSocket::connect(response, SIGNAL(finished()), &event, SLOT(quit()));
    event.exec();
    QString content = response->readAll();
    return content;
}

Currencies::Rates Currencies::parseJSON()
{
    QString json = downloadCurrencies();
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    QJsonArray docArray = doc.array();
    QJsonObject jsonObject = docArray[0].toObject();
    QJsonArray jsonArray = jsonObject["rates"].toArray();
    Rates exchangeRates;
    foreach (const QJsonValue& value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        if (obj["code"].toString() == "EUR" || obj["code"].toString() == "USD")
        {
            exchangeRates.insert(exchangeRates.begin(), std::make_pair(obj["code"].toString(),
                                    obj["mid"].toDouble()));
        }
        else exchangeRates.push_back(std::make_pair(obj["code"].toString(),
                                obj["mid"].toDouble()));
    }
    exchangeRates.insert(exchangeRates.begin(), std::make_pair("PLN", 1.0));
    return exchangeRates;
}
