/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#include "stripe/stripe_decode.h"

namespace Stripe {

[[nodiscard]] bool ContainsFields(
		const QJsonObject &object,
		std::vector<QStringView> keys) {
	for (const auto &key : keys) {
		if (object.value(key).isUndefined()) {
			return false;
		}
	}
	return true;
}

} // namespace Stripe
