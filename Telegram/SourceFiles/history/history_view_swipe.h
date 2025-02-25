/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

namespace Ui {
class RpWidget;
class ScrollArea;
} // namespace Ui

namespace HistoryView {

struct ChatPaintGestureHorizontalData;

struct SwipeHandlerFinishData {
	Fn<void(void)> callback;
	int64 msgBareId = 0;
};

void SetupSwipeHandler(
	not_null<Ui::RpWidget*> widget,
	not_null<Ui::ScrollArea*> scroll,
	Fn<void(ChatPaintGestureHorizontalData)> update,
	Fn<SwipeHandlerFinishData(int)> generateFinishByTop,
	rpl::producer<bool> dontStart = nullptr);

} // namespace HistoryView
