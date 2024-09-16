/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

class HistoryItem;

namespace Window {
class SessionController;
} // namespace Window

namespace ChatHelpers {

void ShowTTLMediaLayerWidget(
	not_null<Window::SessionController*> controller,
	not_null<HistoryItem*> item);

} // namespace ChatHelpers
