/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fagramdesktop/fadesktop/blob/dev/LEGAL
*/
#pragma once

#include "base/object_ptr.h"
#include <rpl/producer.h>

enum lngtag_count : int;

namespace Ui {
class VerticalLayout;
class RpWidget;
} // namespace Ui

namespace Window {
class SessionController;
} // namespace Window

namespace FA::Features::RoundNumbers {

[[nodiscard]] bool IsEnabled();
[[nodiscard]] rpl::producer<bool> Value();

[[nodiscard]] bool IsTargetKey(ushort keyBase);

[[nodiscard]] lngtag_count ResolveCountTag(ushort keyBase, lngtag_count tag);

not_null<::Ui::RpWidget*> AddToggle(
	not_null<::Ui::VerticalLayout*> card,
	not_null<Window::SessionController*> controller);

} // namespace FA::Features::RoundNumbers
