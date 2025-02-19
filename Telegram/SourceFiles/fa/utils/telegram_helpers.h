/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

#pragma once

#include "apiwrap.h"
#include "lang_auto.h"
#include "mainwidget.h"
#include "mainwindow.h"
#include "fa/ui/menu_item_subtext.h"
#include "history/history_item_components.h"

#include "core/mime_type.h"
#include "styles/style_menu_icons.h"
#include "ui/widgets/popup_menu.h"
#include "ui/widgets/menu/menu_add_action_callback_factory.h"
#include "window/window_peer_menu.h"

#include "base/unixtime.h"
#include "data/data_channel.h"
#include "data/data_user.h"
#include "data/data_chat.h"
#include "data/data_histories.h"
#include "data/data_forum_topic.h"
#include "data/data_session.h"
#include "history/history.h"
#include "history/view/history_view_context_menu.h"
#include "history/view/history_view_element.h"
#include "window/window_session_controller.h"

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

void readMentions(base::weak_ptr<Data::Thread> weakThread);
void readReactions(base::weak_ptr<Data::Thread> weakThread);
void readHistory(not_null<HistoryItem*> message);

ID getBareID(not_null<PeerData*> peer);
bool isFAgramRelated(ID peerId);

QString getLocationDC(int dc_id);
QString getPeerDC(not_null<PeerData*> peer);
QString getOnlyDC(not_null<PeerData*> peer);
QString getIpDC(int dc_id, bool test);

void cleanDebugLogs();

bool is_me(ID userId);

void MessageDetails(not_null<Ui::PopupMenu*> menu, HistoryItem *item);

ID getUserIdFromPackId(uint64 id);