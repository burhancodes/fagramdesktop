/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

#include <AppKit/NSImageView.h>

namespace Main {
class Session;
} // namespace Main

API_AVAILABLE(macos(10.12.2))
@interface PinnedDialogsPanel : NSImageView
- (id)init:(not_null<Main::Session*>)session
	destroyEvent:(rpl::producer<>)touchBarSwitches;
@end
