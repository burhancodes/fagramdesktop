/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

#include "telegram_helpers.h"

std::unordered_set<ID> fagram_channels = {
    static_cast<ID>(2490382357), // @fagramnews
    static_cast<ID>(2495029489), // @fagramgroup
    static_cast<ID>(2390525721), // @fagramwindows
    static_cast<ID>(2348386822), // @fagramlinux
};
std::unordered_set<ID> fagram_devs = {
    static_cast<ID>(6204024154), // @vecax
};


ID getBareID(not_null<PeerData *> peer) {
	return peerIsUser(peer->id)
		   ? peerToUser(peer->id).bare
		   : peerIsChat(peer->id)
			 ? peerToChat(peer->id).bare
			 : peerIsChannel(peer->id)
			   ? peerToChannel(peer->id).bare
			   : peer->id.value;
}

bool isFAgramRelated(ID peerId)
{
	return fagram_devs.contains(peerId) || fagram_channels.contains(peerId);
}

// thanks ayugram