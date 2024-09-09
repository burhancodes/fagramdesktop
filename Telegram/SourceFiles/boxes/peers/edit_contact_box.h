/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

#include "ui/layers/generic_box.h"

class UserData;

namespace Window {
class SessionController;
} // namespace Window

void EditContactBox(
	not_null<Ui::GenericBox*> box,
	not_null<Window::SessionController*> window,
	not_null<UserData*> user);
