/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

namespace ChatHelpers {
class Show;
} // namespace ChatHelpers

namespace Media::Stories {

void SetupStealthMode(std::shared_ptr<ChatHelpers::Show> show);

[[nodiscard]] QString TimeLeftText(int left);

} // namespace Media::Stories
