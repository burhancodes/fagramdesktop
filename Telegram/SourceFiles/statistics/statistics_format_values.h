/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

namespace Statistic {

[[nodiscard]] QString LangDayMonthYear(crl::time seconds);
[[nodiscard]] QString LangDayMonth(crl::time seconds);
[[nodiscard]] QString LangDetailedDayMonth(crl::time seconds);

} // namespace Statistic
