/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#include "ui/widgets/label_with_custom_emoji.h"

#include "core/ui_integration.h"
#include "ui/widgets/labels.h"
#include "styles/style_widgets.h"

namespace Ui {

object_ptr<Ui::FlatLabel> CreateLabelWithCustomEmoji(
		QWidget *parent,
		rpl::producer<TextWithEntities> &&text,
		Core::MarkedTextContext context,
		const style::FlatLabel &st) {
	auto label = object_ptr<Ui::FlatLabel>(parent, st);
	const auto raw = label.data();
	if (!context.customEmojiRepaint) {
		context.customEmojiRepaint = [=] { raw->update(); };
	}
	std::move(text) | rpl::start_with_next([=](const TextWithEntities &text) {
		raw->setMarkedText(text, context);
	}, label->lifetime());
	return label;
}

} // namespace Ui
