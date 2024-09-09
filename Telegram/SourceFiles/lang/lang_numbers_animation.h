/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

#include "ui/effects/numbers_animation.h"

namespace Lang {

template <typename ResultString>
struct StartReplacements;

template <>
struct StartReplacements<Ui::StringWithNumbers> {
	static inline Ui::StringWithNumbers Call(QString &&langString) {
		return { std::move(langString) };
	}
};

template <typename ResultString>
struct ReplaceTag;

template <>
struct ReplaceTag<Ui::StringWithNumbers> {
	static Ui::StringWithNumbers Call(
		Ui::StringWithNumbers &&original,
		ushort tag,
		const Ui::StringWithNumbers &replacement);
};

} // namespace Lang
