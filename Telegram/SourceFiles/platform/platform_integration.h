/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

namespace Platform {

class Integration {
public:
	virtual void init() {
	}

	virtual ~Integration();

	[[nodiscard]] static std::unique_ptr<Integration> Create();
	[[nodiscard]] static Integration &Instance();
};

} // namespace Platform
