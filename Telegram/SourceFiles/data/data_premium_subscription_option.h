/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

namespace Data {

struct PremiumSubscriptionOption {
	QString duration;
	QString discount;
	QString costPerMonth;
	QString costTotal;
	QString total;
	QString botUrl;
};
using PremiumSubscriptionOptions = std::vector<PremiumSubscriptionOption>;

} // namespace Data
