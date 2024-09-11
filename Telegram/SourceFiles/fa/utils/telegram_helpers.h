/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

#pragma once

#include "core/application.h"
#include "main/main_account.h"
#include "main/main_domain.h"
#include "main/main_session.h"
#include "dialogs/dialogs_main_list.h"

#include <string>       // For std::string
#include <utility>      // For std::pair
#include <functional>   // For std::function

using ID = int;

Main::Session *getSession(ID userId);
bool accountExists(ID userId);
void dispatchToMainThread(std::function<void()> callback);
not_null<History *> getHistoryFromDialogId(ID dialogId, Main::Session *session);
ID getDialogIdFromPeer(not_null<PeerData *> peer);
std::pair<std::string, std::string> serializeTextWithEntities(not_null<HistoryItem *> item);

ID getBareID(not_null<PeerData *> peer);

bool isFAgramRelated(ID peerId);

// thanks ayugram