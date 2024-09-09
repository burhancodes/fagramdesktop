/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

namespace Ui {

struct MessageSendingAnimationFrom {
	enum class Type {
		None,
		Sticker,
		Gif,
		Emoji,
	};
	Type type = Type::None;
	std::optional<MsgId> localId;
	QRect globalStartGeometry;
	QImage frame;
	bool crop = false;
};

} // namespace Ui
