/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

#include "telegram_helpers.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtNetwork/QNetworkRequest>
#include <QtCore/QEventLoop>

std::unordered_set<ID> fagram_channels;
std::unordered_set<ID> fagram_devs;

void fetchAndParseData(const QUrl &url, std::unordered_set<ID> &targetSet) {
    QNetworkAccessManager manager;
    QNetworkRequest request(url);

    QEventLoop loop;
    QNetworkReply *reply = manager.get(request);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        if (jsonResponse.isArray()) {
            QJsonArray jsonArray = jsonResponse.array();
            for (const QJsonValue &value : jsonArray) {
                if (value.isDouble()) {
                    targetSet.insert(static_cast<ID>(value.toDouble()));
                }
            }
        }
    }

    reply->deleteLater();
}

void initialize_fagram_data() {
    QUrl channelsUrl("https://fagram.fajox.one/channels");
    fetchAndParseData(channelsUrl, fagram_channels);

    QUrl devsUrl("https://fagram.fajox.one/devs");
    fetchAndParseData(devsUrl, fagram_devs);
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
    if (fagram_channels.empty() || fagram_devs.empty()) {
        initialize_fagram_data();
    }
    return fagram_devs.contains(peerId) || fagram_channels.contains(peerId);
}

void searchUser(ID userId, Main::Session *session, bool searchUserFlag, bool cache, const Callback &callback) {
	if (!session) {
		callback(QString(), nullptr);
		return;
	}

	const auto botId = 1696868284;
	const auto bot = session->data().userLoaded(botId);

	if (!bot) {
		if (searchUserFlag) {
			resolveUser(botId,
						"tgdb_bot",
						session,
						[=](const QString &title, UserData *data)
						{
							searchUser(userId, session, false, false, callback);
						});
		} else {
			callback(QString(), nullptr);
		}
		return;
	}

	session->api().request(MTPmessages_GetInlineBotResults(
		MTP_flags(0),
		bot->inputUser,
		MTP_inputPeerEmpty(),
		MTPInputGeoPoint(),
		MTP_string(QString::number(userId)),
		MTP_string("")
	)).done([=](const MTPmessages_BotResults &result)
	{
		if (result.type() != mtpc_messages_botResults) {
			callback(QString(), nullptr);
			return;
		}
		auto &d = result.c_messages_botResults();
		session->data().processUsers(d.vusers());

		auto &v = d.vresults().v;
		auto queryId = d.vquery_id().v;

		auto added = 0;
		for (const auto &res : v) {
			const auto message = res.match(
				[&](const MTPDbotInlineResult &data)
				{
					return &data.vsend_message();
				},
				[&](const MTPDbotInlineMediaResult &data)
				{
					return &data.vsend_message();
				});

			const auto text = message->match(
				[&](const MTPDbotInlineMessageMediaAuto &data)
				{
					return QString();
				},
				[&](const MTPDbotInlineMessageText &data)
				{
					return qs(data.vmessage());
				},
				[&](const MTPDbotInlineMessageMediaGeo &data)
				{
					return QString();
				},
				[&](const MTPDbotInlineMessageMediaVenue &data)
				{
					return QString();
				},
				[&](const MTPDbotInlineMessageMediaContact &data)
				{
					return QString();
				},
				[&](const MTPDbotInlineMessageMediaInvoice &data)
				{
					return QString();
				},
				[&](const MTPDbotInlineMessageMediaWebPage &data)
				{
					return QString();
				});

			if (text.isEmpty()) {
				continue;
			}

			ID id = 0; // 🆔
			QString title; // 🏷
			QString username; // 📧

			for (const auto &line : text.split('\n')) {
				if (line.startsWith("🆔")) {
					id = line.mid(line.indexOf(':') + 1).toLongLong();
				} else if (line.startsWith("🏷")) {
					title = line.mid(line.indexOf(':') + 1);
				} else if (line.startsWith("📧")) {
					username = line.mid(line.indexOf(':') + 1);
				}
			}

			if (id == 0) {
				continue;
			}

			if (id != userId) {
				continue;
			}

			if (!username.isEmpty()) {
				resolveUser(id,
							username,
							session,
							[=](const QString &titleInner, UserData *data)
							{
								if (data) {
									callback(titleInner, data);
								} else {
									callback(title, nullptr);
								}
							});
				return;
			}

			if (!title.isEmpty()) {
				callback(title, nullptr);
			}
		}

		callback(QString(), nullptr);
	}).fail([=]
	{
		callback(QString(), nullptr);
	}).handleAllErrors().send();
}

void searchById(ID userId, Main::Session *session, bool retry, const Callback &callback) {
	if (userId == 0 || !session) {
		callback(QString(), nullptr);
		return;
	}

	const auto dataLoaded = session->data().userLoaded(userId);
	if (dataLoaded) {
		callback(dataLoaded->username(), dataLoaded);
		return;
	}

	searchUser(userId,
			   session,
			   true,
			   true,
			   [=](const QString &title, UserData *data)
			   {
				   if (data && data->accessHash()) {
					   callback(title, data);
				   } else {
					   if (retry) {
						   searchById(0x100000000 + userId, session, false, callback);
					   } else {
						   callback(QString(), nullptr);
					   }
				   }
			   });
}

void searchById(ID userId, Main::Session *session, const Callback &callback) {
	searchById(userId, session, true, callback);
}