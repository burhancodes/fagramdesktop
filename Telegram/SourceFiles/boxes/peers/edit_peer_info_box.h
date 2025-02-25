/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

#include "ui/layers/box_content.h"

namespace Settings {
struct IconDescriptor;
} // namespace Settings

namespace style {
struct SettingsCountButton;
} // namespace style

namespace Window {
class SessionNavigation;
} // namespace Window

namespace Ui {
class VerticalLayout;
class SettingsButton;
} // namespace Ui

class EditPeerInfoBox : public Ui::BoxContent {
public:
	EditPeerInfoBox(
		QWidget*,
		not_null<Window::SessionNavigation*> navigation,
		not_null<PeerData*> peer);

	void setInnerFocus() override {
		_focusRequests.fire({});
	}

	static bool Available(not_null<PeerData*> peer);

	[[nodiscard]] static object_ptr<Ui::SettingsButton> CreateButton(
		not_null<QWidget*> parent,
		rpl::producer<QString> &&text,
		rpl::producer<QString> &&count,
		Fn<void()> callback,
		const style::SettingsCountButton &st,
		Settings::IconDescriptor &&descriptor);

protected:
	void prepare() override;

private:
	rpl::event_stream<> _focusRequests;
	not_null<Window::SessionNavigation*> _navigation;
	not_null<PeerData*> _peer;

};
