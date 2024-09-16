/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

#include "base/object_ptr.h"

namespace Ui {
class RpWidget;
} // namespace Ui

namespace Calls {

class Call;

[[nodiscard]] std::vector<EmojiPtr> ComputeEmojiFingerprint(
	not_null<Call*> call);

[[nodiscard]] object_ptr<Ui::RpWidget> CreateFingerprintAndSignalBars(
	not_null<QWidget*> parent,
	not_null<Call*> call);

} // namespace Calls
