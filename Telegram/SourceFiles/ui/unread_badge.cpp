/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#include "ui/unread_badge.h"

#include "data/data_peer.h"
#include "data/data_user.h"
#include "data/data_session.h"
#include "data/stickers/data_custom_emoji.h"
#include "main/main_session.h"
#include "lang/lang_keys.h"
#include "ui/painter.h"
#include "ui/power_saving.h"
#include "ui/unread_badge_paint.h"
#include "styles/style_dialogs.h"

namespace Ui {
namespace {

constexpr auto kPlayStatusLimit = 2;

} // namespace

struct PeerBadge::EmojiStatus {
	DocumentId id = 0;
	std::unique_ptr<Ui::Text::CustomEmoji> emoji;
	int skip = 0;
};

struct PeerBadge::BotVerifiedData {
	QImage cache;
	std::unique_ptr<Text::CustomEmoji> icon;
};

void UnreadBadge::setText(const QString &text, bool active) {
	_text = text;
	_active = active;
	const auto st = Dialogs::Ui::UnreadBadgeStyle();
	resize(
		std::max(st.font->width(text) + 2 * st.padding, st.size),
		st.size);
	update();
}

int UnreadBadge::textBaseline() const {
	const auto st = Dialogs::Ui::UnreadBadgeStyle();
	return ((st.size - st.font->height) / 2) + st.font->ascent;
}

void UnreadBadge::paintEvent(QPaintEvent *e) {
	if (_text.isEmpty()) {
		return;
	}

	auto p = QPainter(this);

	UnreadBadgeStyle unreadSt;
	unreadSt.muted = !_active;
	auto unreadRight = width();
	auto unreadTop = 0;
	PaintUnreadBadge(
		p,
		_text,
		unreadRight,
		unreadTop,
		unreadSt);
}

QSize ScamBadgeSize(bool fake) {
	const auto phrase = fake
		? tr::lng_fake_badge(tr::now)
		: tr::lng_scam_badge(tr::now);
	const auto phraseWidth = st::dialogsScamFont->width(phrase);
	const auto width = st::dialogsScamPadding.left()
		+ phraseWidth
		+ st::dialogsScamPadding.right();
	const auto height = st::dialogsScamPadding.top()
		+ st::dialogsScamFont->height
		+ st::dialogsScamPadding.bottom();
	return { width, height };
}

void DrawScamFakeBadge(
		Painter &p,
		QRect rect,
		int outerWidth,
		const style::color &color,
		const QString &phrase,
		int phraseWidth) {
	PainterHighQualityEnabler hq(p);
	auto pen = color->p;
	pen.setWidth(st::lineWidth);
	p.setPen(pen);
	p.setBrush(Qt::NoBrush);
	p.drawRoundedRect(rect, st::dialogsScamRadius, st::dialogsScamRadius);
	p.setFont(st::dialogsScamFont);
	p.drawTextLeft(
		rect.x() + st::dialogsScamPadding.left(),
		rect.y() + st::dialogsScamPadding.top(),
		outerWidth,
		phrase,
		phraseWidth);
}

void DrawScamBadge(
		bool fake,
		Painter &p,
		QRect rect,
		int outerWidth,
		const style::color &color) {
	const auto phrase = fake
		? tr::lng_fake_badge(tr::now)
		: tr::lng_scam_badge(tr::now);
	DrawScamFakeBadge(
		p,
		rect,
		outerWidth,
		color,
		phrase,
		st::dialogsScamFont->width(phrase));
}

PeerBadge::PeerBadge() = default;

PeerBadge::~PeerBadge() = default;

int PeerBadge::drawGetWidth(
		Painter &p,
		QRect rectForName,
		int nameWidth,
		int outerWidth,
		const Descriptor &descriptor) {
	Expects(descriptor.customEmojiRepaint != nullptr);

	const auto peer = descriptor.peer;
	if (descriptor.scam && (peer->isScam() || peer->isFake())) {
		const auto phrase = peer->isScam()
			? tr::lng_scam_badge(tr::now)
			: tr::lng_fake_badge(tr::now);
		const auto phraseWidth = st::dialogsScamFont->width(phrase);
		const auto width = st::dialogsScamPadding.left()
			+ phraseWidth
			+ st::dialogsScamPadding.right();
		const auto height = st::dialogsScamPadding.top()
			+ st::dialogsScamFont->height
			+ st::dialogsScamPadding.bottom();
		const auto rect = QRect(
			(rectForName.x()
				+ qMin(
					nameWidth + st::dialogsScamSkip,
					rectForName.width() - width)),
			rectForName.y() + (rectForName.height() - height) / 2,
			width,
			height);
		DrawScamFakeBadge(
			p,
			rect,
			outerWidth,
			*descriptor.scam,
			phrase,
			phraseWidth);
		return st::dialogsScamSkip + width;
	} else if (descriptor.premium
		&& peer->emojiStatusId()
		&& (peer->isPremium() || peer->isChannel())
		&& peer->session().premiumBadgesShown()) {
		const auto id = peer->emojiStatusId();
		const auto iconw = descriptor.premium->width();
		const auto iconx = rectForName.x()
			+ qMin(nameWidth, rectForName.width() - iconw);
		const auto icony = rectForName.y();
		if (!_emojiStatus) {
			_emojiStatus = std::make_unique<EmojiStatus>();
			const auto size = st::emojiSize;
			const auto emoji = Ui::Text::AdjustCustomEmojiSize(size);
			_emojiStatus->skip = (size - emoji) / 2;
		}
		if (_emojiStatus->id != id) {
			using namespace Ui::Text;
			auto &manager = peer->session().data().customEmojiManager();
			_emojiStatus->id = id;
			_emojiStatus->emoji = std::make_unique<LimitedLoopsEmoji>(
				manager.create(
					id,
					descriptor.customEmojiRepaint),
				kPlayStatusLimit);
		}
		_emojiStatus->emoji->paint(p, {
			.textColor = (*descriptor.premiumFg)->c,
			.now = descriptor.now,
			.position = QPoint(
				iconx - 2 * _emojiStatus->skip,
				icony + _emojiStatus->skip),
			.paused = descriptor.paused || On(PowerSaving::kEmojiStatus),
		});
		return iconw - 4 * _emojiStatus->skip;
	} else if (descriptor.verified && peer->isVerified()) {
		const auto iconw = descriptor.verified->width();
		descriptor.verified->paint(
			p,
			rectForName.x() + qMin(nameWidth, rectForName.width() - iconw),
			rectForName.y(),
			outerWidth);
		return iconw;
	} else if (descriptor.premium
		&& peer->isPremium()
		&& peer->session().premiumBadgesShown()) {
		const auto iconw = descriptor.premium->width();
		const auto iconx = rectForName.x()
			+ qMin(nameWidth, rectForName.width() - iconw);
		const auto icony = rectForName.y();
		_emojiStatus = nullptr;
		descriptor.premium->paint(p, iconx, icony, outerWidth);
		return iconw;
	}
	return 0;
}

void PeerBadge::unload() {
	_emojiStatus = nullptr;
}

bool PeerBadge::ready(const BotVerifyDetails *details) const {
	if (!details || !*details) {
		_botVerifiedData = nullptr;
		return true;
	} else if (!_botVerifiedData) {
		return false;
	}
	if (!details->iconId) {
		_botVerifiedData->icon = nullptr;
	} else if (!_botVerifiedData->icon
		|| (_botVerifiedData->icon->entityData()
			!= Data::SerializeCustomEmojiId(details->iconId))) {
		return false;
	}
	return true;
}

void PeerBadge::set(
		not_null<const BotVerifyDetails*> details,
		Ui::Text::CustomEmojiFactory factory,
		Fn<void()> repaint) {
	if (!_botVerifiedData) {
		_botVerifiedData = std::make_unique<BotVerifiedData>();
	}
	if (details->iconId) {
		_botVerifiedData->icon = factory(
			Data::SerializeCustomEmojiId(details->iconId),
			repaint);
	}
}

int PeerBadge::drawVerified(
		QPainter &p,
		QPoint position,
		const style::VerifiedBadge &st) {
	const auto data = _botVerifiedData.get();
	if (!data) {
		return 0;
	}
	if (const auto icon = data->icon.get()) {
		icon->paint(p, {
			.textColor = st.color->c,
			.now = crl::now(),
			.position = position,
		});
		return icon->width();
	}
	return 0;
}

} // namespace Ui
