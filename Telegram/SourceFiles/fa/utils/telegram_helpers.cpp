/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

#include "telegram_helpers.h"

std::unordered_set<ID> fagram_channels = {
    2490382357, // @fagramnews
    2495029489, // @fagramgroup
    2390525721, // @fagramwindows
    2348386822, // @fagramlinux
	2330622040, // @fagrammacos
	2444094156, // @fagramandroid
	2497995101, // @fagramios
};
std::unordered_set<ID> fagram_devs = {
    6204024154, // @vecax
    2085438865, // @dev_kitten
};


ID getBareID(not_null<PeerData*> peer) {
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