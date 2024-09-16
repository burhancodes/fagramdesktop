/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

namespace Ui {
class RpWindow;
} // namespace Ui

namespace Iv {

class Delegate {
public:
	virtual void ivSetLastSourceWindow(not_null<QWidget*> window) = 0;
	[[nodiscard]] virtual QRect ivGeometry() const = 0;
	virtual void ivSaveGeometry(not_null<Ui::RpWindow*> window) = 0;
};

} // namespace Iv
