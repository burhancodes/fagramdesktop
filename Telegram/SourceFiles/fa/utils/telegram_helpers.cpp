/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

#include "telegram_helpers.h"

#include "core/application.h"

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtNetwork/QNetworkRequest>
#include <QtCore/QEventLoop>
#include <QtCore/QElapsedTimer>
#include <QtCore/QDebug>

std::unordered_set<ID> fagram_channels;
std::unordered_set<ID> fagram_devs;

std::unordered_map<ID, bool> state;

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

void markAsOnline(not_null<Main::Session*> session) {
	state[session->userId().bare] = true;
}

// stole from Ayugram
void readMentions(base::weak_ptr<Data::Thread> weakThread) {
	const auto thread = weakThread.get();
	if (!thread) {
		return;
	}
	const auto peer = thread->peer();
	const auto topic = thread->asTopic();
	const auto rootId = topic ? topic->rootId() : 0;
	using Flag = MTPmessages_ReadMentions::Flag;
	peer->session().api().request(MTPmessages_ReadMentions(
		MTP_flags(rootId ? Flag::f_top_msg_id : Flag()),
		peer->input,
		MTP_int(rootId)
	)).done([=](const MTPmessages_AffectedHistory &result)
	{
		const auto offset = peer->session().api().applyAffectedHistory(
			peer,
			result);
		if (offset > 0) {
			readMentions(weakThread);
		} else {
			peer->owner().history(peer)->clearUnreadMentionsFor(rootId);
		}
	}).send();
}

// stole from Ayugram
void readReactions(base::weak_ptr<Data::Thread> weakThread) {
	const auto thread = weakThread.get();
	if (!thread) {
		return;
	}
	const auto topic = thread->asTopic();
	const auto peer = thread->peer();
	const auto rootId = topic ? topic->rootId() : 0;
	using Flag = MTPmessages_ReadReactions::Flag;
	peer->session().api().request(MTPmessages_ReadReactions(
		MTP_flags(rootId ? Flag::f_top_msg_id : Flag(0)),
		peer->input,
		MTP_int(rootId)
	)).done([=](const MTPmessages_AffectedHistory &result)
	{
		const auto offset = peer->session().api().applyAffectedHistory(
			peer,
			result);
		if (offset > 0) {
			readReactions(weakThread);
		} else {
			peer->owner().history(peer)->clearUnreadReactionsFor(rootId);
		}
	}).send();
}

// stole from Ayugram
void readHistory(not_null<HistoryItem*> message) {
	const auto history = message->history();
	const auto tillId = message->id;

	history->session().data().histories()
		.sendRequest(history,
					 Data::Histories::RequestType::ReadInbox,
					 [=](Fn<void()> finish)
					 {
						 if (const auto channel = history->peer->asChannel()) {
							 return history->session().api().request(MTPchannels_ReadHistory(
								 channel->inputChannel,
								 MTP_int(tillId)
							 )).done([=] { markAsOnline(&history->session()); }).send();
						 }

						 return history->session().api().request(MTPmessages_ReadHistory(
							 history->peer->input,
							 MTP_int(tillId)
						 )).done([=](const MTPmessages_AffectedMessages &result)
						 {
							 history->session().api().applyAffectedMessages(history->peer, result);
							 markAsOnline(&history->session());
						 }).fail([=]
						 {
						 }).send();
					 });

	if (history->unreadMentions().has()) {
		readMentions(history->asThread());
	}

	if (history->unreadReactions().has()) {
		readReactions(history->asThread());
	}
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

QString getLocationDC(int dc_id) {
    QString dc_location;

    switch (dc_id) {
        case 1:
            dc_location = "Miami FL, USA";
            break;
        case 2:
            dc_location = "Amsterdam, NL";
            break;
        case 3:
            dc_location = "Miami FL, USA";
            break;
        case 4:
            dc_location = "Amsterdam, NL";
            break;
        case 5:
            dc_location = "Singapore, SG";
            break;
        default:
            dc_location = "UNKNOWN";
            break;
    }

    return dc_location;
}

QString getPeerDC(not_null<PeerData*> peer) {
    int dc = 0;

    if (const auto statsDcId = peer->owner().statsDcId(peer)) {
        dc = statsDcId;
    }
    else if (peer->hasUserpic()) {
        dc = v::match(
            peer->userpicLocation().file().data,
            [&](const StorageFileLocation &data) {
                return data.dcId();
            },
            [&](const WebFileLocation &) {
                return 4;
            },
            [&](const GeoPointLocation &) {
                return 0;
            },
            [&](const AudioAlbumThumbLocation &) {
                return 0;
            },
            [&](const PlainUrlLocation &) {
                return 4;
            },
            [&](const InMemoryLocation &) {
                return 0;
            }
        );
    }
    else {
        return QString("DC_UNKNOWN");
    }

    QString dc_location = getLocationDC(dc);

    if (dc < 1) {
        return QString("DC_UNKNOWN");
    }

    return QString("DC%1, %2").arg(dc).arg(dc_location);
}

QString getOnlyDC(not_null<PeerData*> peer) {
    int dc = 0;

    if (const auto statsDcId = peer->owner().statsDcId(peer)) {
        dc = statsDcId;
    }
    else if (peer->hasUserpic()) {
        dc = v::match(
            peer->userpicLocation().file().data,
            [&](const StorageFileLocation &data) {
                return data.dcId();
            },
            [&](const WebFileLocation &) {
                return 4;
            },
            [&](const GeoPointLocation &) {
                return 0;
            },
            [&](const AudioAlbumThumbLocation &) {
                return 0;
            },
            [&](const PlainUrlLocation &) {
                return 4;
            },
            [&](const InMemoryLocation &) {
                return 0;
            }
        );
    }
    else {
        return QString("DC_UNKNOWN");
    }

    if (dc < 1) {
        return QString("DC_UNKNOWN");
    }

    return QString("Datacenter %1").arg(dc);
}

QString getIpDC(int dc_id, bool test) {
    QString ip;

    if (!test) {
        switch (dc_id) {
            case 1:
                ip = "149.154.175.53";
                break;
            case 2:
                ip = "149.154.167.51";
                break;
            case 3:
                ip = "149.154.175.100";
                break;
            case 4:
                ip = "149.154.167.91";
                break;
            case 5:
                ip = "91.108.56.130";
                break;
            default:
                return QString("UNKNOWN");
        }
    }

    else {
        switch (dc_id) {
            case 1:
                ip = "149.154.175.10";
                break;
            case 2:
                ip = "149.154.167.40";
                break;
            case 3:
                ip = "149.154.175.117";
                break;
            default:
                return QString("UNKNOWN");
        }
    }

    return ip;
}

void cleanDebugLogs() {
    QString workingDir = cWorkingDir();
    QDir debugLogsDir(cWorkingDir() + "/DebugLogs");

    if (!debugLogsDir.exists()) {
        return;
    }

    QStringList files = debugLogsDir.entryList(QDir::Files);
    
    for (const QString &file : files) {
        debugLogsDir.remove(file);
    }

    return;
}