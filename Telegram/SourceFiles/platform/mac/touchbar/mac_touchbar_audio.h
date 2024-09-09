/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

#import <AppKit/NSTouchBar.h>

API_AVAILABLE(macos(10.12.2))
@interface TouchBarAudioPlayer : NSTouchBar<NSTouchBarDelegate>
- (rpl::producer<>)closeRequests;
@end
