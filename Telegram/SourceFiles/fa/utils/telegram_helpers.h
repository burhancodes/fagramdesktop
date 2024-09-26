/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

#pragma once

#include "fa/data/entities.h"
#include "data/data_peer.h"
#include "core/application.h"
#include "main/main_account.h"
#include "main/main_domain.h"
#include "main/main_session.h"
#include "dialogs/dialogs_main_list.h"

#include <string>     
#include <utility>    
#include <functional>  
#include <unordered_set>
#include <QtCore/QJsonArray>
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

extern std::unordered_set<ID> fagram_channels;
extern std::unordered_set<ID> fagram_devs;

void initialize_fagram_data();

ID getBareID(not_null<PeerData*> peer);
bool isFAgramRelated(ID peerId);