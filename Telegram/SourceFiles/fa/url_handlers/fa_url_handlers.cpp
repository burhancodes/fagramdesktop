/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

// thx ayugram

#include "fa/url_handlers/fa_url_handlers.h"

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

bool ResolveUser(
	Window::SessionController *controller,
	const Match &match,
	const QVariant &context)
{
	if (!controller) {
		return false;
	}
	const auto params = url_parse_params(
		match->captured(1),
		qthelp::UrlParamNameTransform::ToLower);
	const auto userId = params.value(qsl("id")).toLongLong();
	if (!userId) {
		return false;
	}
	const auto peer = controller->session().data().peerLoaded(static_cast<PeerId>(userId));
	if (peer != nullptr) {
		controller->showPeerInfo(peer);
		return true;
	}

	searchById(userId, &controller->session(), false, [=](const QString &title, UserData *data)
	{
		if (data) {
			controller->showPeerInfo(data);
			return;
		}

		Core::App().hideMediaView();
		Ui::show(Ui::MakeInformBox(rpl::single(QString("User not found"))));
	});

	return true;
}

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

}