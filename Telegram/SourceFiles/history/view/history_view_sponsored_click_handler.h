/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

class ClickHandler;

namespace HistoryView {

[[nodiscard]] std::shared_ptr<ClickHandler> SponsoredLink(
	const QString &link,
	bool isInternal);

} // namespace HistoryView
