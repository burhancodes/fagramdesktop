/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

// thx ayugram

#include "fa/url_handlers/fa_url_handlers.h"

#include "fa/utils/telegram_helpers.h"

#include "base/qthelp_url.h"

#include "lang_auto.h"
#include "mainwindow.h"
#include "ui/boxes/confirm_box.h"
#include "fa/utils/telegram_helpers.h"
#include "boxes/abstract_box.h"
#include "core/application.h"
#include "data/data_session.h"
#include "data/data_user.h"

namespace FAUrlHandlers
{
bool HandleFA(
	Window::SessionController *controller,
	const Match &match,
	const QVariant &context)
{
	if (!controller) {
		return false;
	}
	controller->showToast(QString("thx :>"), 500);
	return true;
}

bool HandleNya(
	Window::SessionController *controller,
	const Match &match,
	const QVariant &context)
{
	if (!controller) {
		return false;
	}
	controller->showToast(QString("Meow ^_^"), 500);
	return true;
}

bool HandleCleanDebugLogs(
	Window::SessionController *controller,
	const Match &match,
	const QVariant &context)
{
	if (!controller) {
		return false;
	}
	controller->showToast(QString("Cleaning..."), 500);
	cleanDebugLogs();
	controller->showToast(QString("Debug logs cleaned!" 1000));
	return true;
}
}