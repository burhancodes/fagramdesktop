/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

#include "telegram_helpers.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QEventLoop>
#include <iostream>

std::unordered_set<ID> fagram_channels;
std::unordered_set<ID> fagram_devs;

std::unordered_set<ID> parse_json_array(const QJsonArray& jsonArray) {
    std::unordered_set<ID> result;
    for (const auto& item : jsonArray) {
        if (item.isDouble()) {
            result.insert(static_cast<ID>(item.toInt()));
        }
    }
    return result;
}

std::unordered_set<ID> fetch_ids_from_url(const QString& url) {
    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    QEventLoop loop;
    QNetworkReply *reply = manager.get(request);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();  

    std::unordered_set<ID> result;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        if (jsonResponse.isArray()) {
            result = parse_json_array(jsonResponse.array());
        }
    } else {
        std::cerr << "Error fetching data from " << url.toStdString() << ": " 
                  << reply->errorString().toStdString() << std::endl;
    }

    reply->deleteLater();
    return result;
}

void initialize_fagram_data() {
    fagram_channels = fetch_ids_from_url("http://fagram.fajox.one/channels");
    fagram_devs = fetch_ids_from_url("http://fagram.fajox.one/devs");
}

ID getBareID(not_null<PeerData*> peer) {
    return peerIsUser(peer->id)
               ? peerToUser(peer->id).bare
               : peerIsChat(peer->id)
                     ? peerToChat(peer->id).bare
                     : peerIsChannel(peer->id)
                           ? peerToChannel(peer->id).bare
                           : peer->id.value;
}

bool isFAgramRelated(ID peerId) {
    initialize_fagram_data();
    return fagram_devs.contains(peerId) || fagram_channels.contains(peerId);
}

// thanks ayugram