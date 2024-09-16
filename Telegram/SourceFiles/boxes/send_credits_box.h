/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

class HistoryItem;

namespace Main {
class Session;
} // namespace Main

namespace Payments {
struct CreditsFormData;
} // namespace Payments

namespace Ui {

class GenericBox;

void SendCreditsBox(
	not_null<Ui::GenericBox*> box,
	std::shared_ptr<Payments::CreditsFormData> data,
	Fn<void()> sent);

[[nodiscard]] TextWithEntities CreditsEmoji(
	not_null<Main::Session*> session);

[[nodiscard]] TextWithEntities CreditsEmojiSmall(
	not_null<Main::Session*> session);

} // namespace Ui
