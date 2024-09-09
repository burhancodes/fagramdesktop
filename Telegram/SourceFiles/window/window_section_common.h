/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

namespace Window {

enum class SectionActionResult {
	Handle, // Handle an action and stay in the current section.
	Fallback, // Ignore an action and fallback to the HistoryWidget.
	Ignore, // Ignore an action and stay in the current section.
};

} // namespace Window
