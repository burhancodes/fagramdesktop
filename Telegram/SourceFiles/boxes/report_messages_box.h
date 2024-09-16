/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

template <typename Object>
class object_ptr;

namespace Ui {
class BoxContent;
} // namespace Ui

namespace Window {
class SessionController;
} // namespace Main

class PeerData;

[[nodiscard]] object_ptr<Ui::BoxContent> ReportItemsBox(
	not_null<PeerData*> peer,
	MessageIdsList ids);
[[nodiscard]] object_ptr<Ui::BoxContent> ReportProfilePhotoBox(
	not_null<PeerData*> peer,
	not_null<PhotoData*> photo);
void ShowReportPeerBox(
	not_null<Window::SessionController*> window,
	not_null<PeerData*> peer);
