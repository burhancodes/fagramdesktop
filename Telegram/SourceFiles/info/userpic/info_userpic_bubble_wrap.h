/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

#include "ui/rp_widget.h"

namespace Ui {

class VerticalLayout;

[[nodiscard]] QRect BubbleWrapInnerRect(const QRect &r);

not_null<Ui::RpWidget*> AddBubbleWrap(
	not_null<Ui::VerticalLayout*> container,
	const QSize &size);

} // namespace Ui
