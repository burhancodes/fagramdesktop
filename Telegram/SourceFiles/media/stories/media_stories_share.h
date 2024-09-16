/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

#include "base/object_ptr.h"

namespace ChatHelpers {
class Show;
} // namespace ChatHelpers

namespace Ui {
class BoxContent;
} // namespace Ui

namespace Media::Stories {

[[nodiscard]] object_ptr<Ui::BoxContent> PrepareShareBox(
	std::shared_ptr<ChatHelpers::Show> show,
	FullStoryId id,
	bool viewerStyle = false);

} // namespace Media::Stories
