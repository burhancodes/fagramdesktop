/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

#pragma one

#include "core/application.h"
#include "main/main_account.h"
#include "main/main_domain.h"
#include "main/main_session.h"
#include "dialogs/dialogs_main_list.h"

ID getBareID(not_null<PeerData *> peer);

bool isFAgramRelated(ID peerId);

// thanks ayugram