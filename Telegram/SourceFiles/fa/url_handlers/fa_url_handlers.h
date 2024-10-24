/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

// thx ayugram

#pragma once

#include "window/window_session_controller.h"
#include "base/qthelp_regex.h"

namespace FAUrlHandlers
{

using Match = qthelp::RegularExpressionMatch;

bool HandleFA(
	Window::SessionController *controller,
	const Match &match,
	const QVariant &context);

bool HandleNya(
	Window::SessionController *controller,
	const Match &match,
	const QVariant &context);

bool HandleCleanDebugLogs(
	Window::SessionController *controller,
	const Match &match,
	const QVariant &context);

}