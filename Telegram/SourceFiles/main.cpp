/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#include "core/launcher.h"

int main(int argc, char *argv[]) {
	const auto launcher = Core::Launcher::Create(argc, argv);
	return launcher ? launcher->exec() : 1;
}
