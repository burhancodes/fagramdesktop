/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

#pragma once

#include "apiwrap.h"
#include "api/api_text_entities.h"

#include "lang_auto.h"
#include "fa/data/entities.h"
#include "core/mime_type.h"
#include "data/data_channel.h"
#include "data/data_forum.h"
#include "data/data_forum_topic.h"
#include "data/data_histories.h"
#include "data/data_peer_id.h"
#include "data/data_photo.h"
#include "data/data_user.h"
#include "data/data_peer.h"
#include "inline_bots/inline_bot_result.h"

#include "core/application.h"
#include "data/data_document.h"
#include "data/data_session.h"
#include "history/history.h"
#include "history/history_item.h"
#include "history/history_item_components.h"
#include "history/history_unread_things.h"
#include "main/main_account.h"
#include "main/main_session.h"
#include "ui/text/format_values.h"

#include <string>     
#include <utility>    
#include <functional>  
#include <unordered_set>
#include <QtCore/QJsonArray>
#include <QtCore/QUrl>
#include <QtCore/QDir>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

extern std::unordered_set<ID> fagram_channels;
extern std::unordered_set<ID> fagram_devs;

void initialize_fagram_data();

void markAsOnline(not_null<Main::Session*> session);

ID getBareID(not_null<PeerData*> peer);
bool isFAgramRelated(ID peerId);

QString getLocationDC(int dc_id);
QString getPeerDC(not_null<PeerData*> peer);
QString getOnlyDC(not_null<PeerData*> peer);
QString getIpDC(int dc_id, bool test);

void cleanDebugLogs();

void readHistory(not_null<HistoryItem*> message);