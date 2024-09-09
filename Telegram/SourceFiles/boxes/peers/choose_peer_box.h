/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

struct RequestPeerQuery;

namespace Ui {
class BoxContent;
} // namespace Ui

namespace Window {
class SessionNavigation;
} // namespace Window

void ShowChoosePeerBox(
	not_null<Window::SessionNavigation*> navigation,
	not_null<UserData*> bot,
	RequestPeerQuery query,
	Fn<void(std::vector<not_null<PeerData*>>)> chosen);
