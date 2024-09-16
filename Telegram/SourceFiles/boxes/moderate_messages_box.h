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
} // namespace Ui

void CreateModerateMessagesBox(
	not_null<Ui::GenericBox*> box,
	const HistoryItemsList &items,
	Fn<void()> confirmed);

[[nodiscard]] bool CanCreateModerateMessagesBox(const HistoryItemsList &);

void DeleteChatBox(not_null<Ui::GenericBox*> box, not_null<PeerData*> peer);
