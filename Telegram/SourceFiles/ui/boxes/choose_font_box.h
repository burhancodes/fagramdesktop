/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

namespace Ui {

class GenericBox;

void ChooseFontBox(
	not_null<GenericBox*> box,
	Fn<QImage()> generatePreviewBg,
	const QString &family,
	Fn<void(QString)> save);

} // namespace Ui
