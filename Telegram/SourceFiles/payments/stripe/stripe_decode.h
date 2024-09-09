/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

#include <QtCore/QJsonObject>
#include <vector>

namespace Stripe {

[[nodiscard]] bool ContainsFields(
	const QJsonObject &object,
	std::vector<QStringView> keys);

} // namespace Stripe
