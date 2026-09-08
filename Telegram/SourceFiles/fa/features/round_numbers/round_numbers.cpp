/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fagramdesktop/fadesktop/blob/dev/LEGAL
*/
#include "fa/features/round_numbers/round_numbers.h"

#include "fa/settings/fa_settings.h"
#include "fa/settings_menu/fa_deeplink_context_menu.h"
#include "fa/ui/md3/fa_cards.h"

#include "fa_lang_auto.h"
#include "lang_auto.h"
#include "ui/wrap/vertical_layout.h"
#include "window/window_session_controller.h"

namespace FA::Features::RoundNumbers {

bool IsEnabled() {
	return FASettings::FASettings::getInstance().roundGroupChannelNumbers();
}

rpl::producer<bool> Value() {
	return FASettings::FASettings::getInstance().roundGroupChannelNumbersValue();
}

bool IsTargetKey(ushort keyBase) {
	return (keyBase == tr::lng_chat_status_members.base)
		|| (keyBase == tr::lng_chat_status_subscribers.base)
		|| (keyBase == tr::lng_chat_status_online.base)
		|| (keyBase == tr::lng_group_invite_members.base);
}

lngtag_count ResolveCountTag(ushort keyBase, lngtag_count tag) {
	if (IsEnabled() && IsTargetKey(keyBase)) {
		return lt_count_short;
	}
	return tag;
}

not_null<::Ui::RpWidget*> AddToggle(
		not_null<::Ui::VerticalLayout*> card,
		not_null<Window::SessionController*> controller) {
	auto &settings = FASettings::FASettings::getInstance();

	const auto roundNumbersRow = FA::Ui::AddCardToggle(
		card,
		fatr::fa_round_group_channel_numbers(),
		fatr::fa_round_group_channel_numbers_desc(),
		settings.roundGroupChannelNumbersValue(),
		[&settings](bool enabled) {
			settings.setRoundGroupChannelNumbers(enabled);
		});

	Settings::FADeepLinkMenu::AttachSettingsContextMenu(
		roundNumbersRow, u"fa/chats/round-numbers"_q, controller);

	return roundNumbersRow;
}

} // namespace FA::Features::RoundNumbers
