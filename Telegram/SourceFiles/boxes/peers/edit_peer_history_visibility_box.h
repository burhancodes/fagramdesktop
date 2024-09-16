/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

namespace Ui {
class GenericBox;
} // namespace Ui

enum class HistoryVisibility {
	Visible,
	Hidden,
};

void EditPeerHistoryVisibilityBox(
	not_null<Ui::GenericBox*> box,
	bool isLegacy,
	Fn<void(HistoryVisibility)> savedCallback,
	HistoryVisibility historyVisibilitySavedValue);
