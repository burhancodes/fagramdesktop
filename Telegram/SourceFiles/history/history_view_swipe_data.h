/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

namespace HistoryView {

struct ChatPaintGestureHorizontalData {
	float64 ratio = 0.;
	float64 reachRatio = 0.;
	int64 msgBareId = 0;
	int translation = 0;
	int cursorTop = 0;
};

} // namespace HistoryView
