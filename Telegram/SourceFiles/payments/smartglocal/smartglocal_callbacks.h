/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

#include <functional>

namespace SmartGlocal {

class Token;
class Error;

using TokenCompletionCallback = std::function<void(Token, Error)>;

} // namespace SmartGlocal
