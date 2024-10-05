/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

class PeerData;
class DocumentData;

namespace Api {
struct SendOptions;
} // namespace Api

namespace SendMenu {
struct Details;
} // namespace SendMenu

namespace Ui {

class GenericBox;

void SendGifWithCaptionBox(
	not_null<Ui::GenericBox*> box,
	not_null<DocumentData*> document,
	not_null<PeerData*> peer,
	const SendMenu::Details &details,
	Fn<void(Api::SendOptions, TextWithTags)> done);

} // namespace Ui
