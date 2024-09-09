/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

namespace Data {
struct StatisticalChart;
} // namespace Data

namespace Statistic {

[[nodiscard]] QImage ChartCurrencyIcon(
		const Data::StatisticalChart &chartData,
		std::optional<QColor> color);

} // namespace Statistic
