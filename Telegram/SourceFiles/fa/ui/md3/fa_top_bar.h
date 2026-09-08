/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fagramdesktop/fadesktop/blob/dev/LEGAL
*/
#pragma once

#include "ui/rp_widget.h"

#include <vector>

class QPainter;

namespace FA::Ui {

int LayoutTopBarPillButtons(
	int newWidth,
	int topBarHeight,
	const std::vector<base::unique_qptr<::Ui::RpWidget>> &buttons);

int LayoutTopBarBackButton(
	int newWidth,
	int topBarHeight,
	::Ui::RpWidget *backButton);

int TopBarBackPillSkip();

void PaintTopBarPill(
	QPainter &p,
	int widgetWidth,
	int topBarHeight,
	const std::vector<base::unique_qptr<::Ui::RpWidget>> &buttons,
	const ::Ui::RpWidget *backButton,
	bool searchModeEnabled,
	bool selectionMode);

} // namespace FA::Ui
