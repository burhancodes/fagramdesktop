/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

#import <AppKit/NSTouchBar.h>

API_AVAILABLE(macos(10.12.2))
@interface TouchBarAudioPlayer : NSTouchBar<NSTouchBarDelegate>
- (rpl::producer<>)closeRequests;
@end
