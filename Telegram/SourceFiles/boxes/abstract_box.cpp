/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#include "boxes/abstract_box.h"

#include "core/application.h"
#include "window/window_controller.h"
#include "mainwidget.h"
#include "mainwindow.h"

namespace Ui {
namespace internal {

void showBox(
		object_ptr<BoxContent> content,
		LayerOptions options,
		anim::type animated) {
	const auto window = Core::IsAppLaunched()
		? Core::App().activePrimaryWindow()
		: nullptr;
	if (window) {
		window->show(std::move(content), options, animated);
	}
}

} // namespace internal

void hideLayer(anim::type animated) {
	const auto window = Core::IsAppLaunched()
		? Core::App().activePrimaryWindow()
		: nullptr;
	if (window) {
		window->hideLayer(animated);
	}
}

bool isLayerShown() {
	const auto window = Core::IsAppLaunched()
		? Core::App().activePrimaryWindow()
		: nullptr;
	return window && window->isLayerShown();
}

} // namespace Ui
