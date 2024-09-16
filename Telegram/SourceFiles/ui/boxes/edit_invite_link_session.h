/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

class PeerData;

namespace Ui {

class GenericBox;
class SettingsButton;

struct InviteLinkSubscriptionToggle;

InviteLinkSubscriptionToggle FillCreateInviteLinkSubscriptionToggle(
	not_null<Ui::GenericBox*> box,
	not_null<PeerData*> peer);

} // namespace Ui
