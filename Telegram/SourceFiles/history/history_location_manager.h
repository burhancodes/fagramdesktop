/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

#include "data/data_location.h"

class LocationClickHandler : public ClickHandler {
public:
	LocationClickHandler(const Data::LocationPoint &point)
	: _point(point) {
		setup();
	}

	static QString Url(const Data::LocationPoint &coords);

	void onClick(ClickContext context) const override;

	QString tooltip() const override {
		return QString();
	}

	QString url() const override {
		return _text;
	}

	QString dragText() const override {
		return _text;
	}

	QString copyToClipboardText() const override;
	QString copyToClipboardContextItemText() const override;

private:

	void setup();
	Data::LocationPoint _point;
	QString _text;

};
