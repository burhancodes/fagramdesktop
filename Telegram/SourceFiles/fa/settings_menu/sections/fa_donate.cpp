/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

#include <ui/boxes/single_choice_box.h>

#include "fa/settings/fa_settings.h"
#include "fa/settings_menu/sections/fa_donate.h"

#include "fa/lang/fa_lang.h"

#include "lang_auto.h"
#include "mainwindow.h"
#include "settings/settings_common.h"
#include "ui/wrap/vertical_layout.h"
#include "ui/wrap/slide_wrap.h"
#include "ui/widgets/buttons.h"
#include "ui/widgets/labels.h"
#include "ui/widgets/checkbox.h"
#include "ui/vertical_list.h"
#include "boxes/connection_box.h"
#include "platform/platform_specific.h"
#include "window/window_session_controller.h"
#include "lang/lang_instance.h"
#include "core/application.h"
#include "storage/localstorage.h"
#include "data/data_session.h"
#include "main/main_session.h"
#include "styles/style_settings.h"
#include "styles/style_layers.h"
#include "styles/style_menu_icons.h"
#include "styles/style_payments.h"
#include "apiwrap.h"
#include "api/api_blocked_peers.h"
#include "ui/widgets/continuous_sliders.h"

#define SettingsMenuJsonSwitch(LangKey, Option) container->add(object_ptr<Button>( \
	container, \
    #LangKey, \
	st::settingsButtonNoIcon \
))->toggleOn( \
	rpl::single(::FASettings::JsonSettings::GetBool(#Option)) \
)->toggledValue( \
) | rpl::filter([](bool enabled) { \
	return (enabled != ::FASettings::JsonSettings::GetBool(#Option)); \
}) | rpl::start_with_next([](bool enabled) { \
	::FASettings::JsonSettings::Write(); \
	::FASettings::JsonSettings::Set(#Option, enabled); \
	::FASettings::JsonSettings::Write(); \
}, container->lifetime());

namespace Settings {

    rpl::producer<QString> FADonate::title() {
        return FAlang::RplTranslate("fa_donate");
    }

    FADonate::FADonate(
            QWidget *parent,
            not_null<Window::SessionController *> controller)
            : Section(parent) {
        setupContent(controller);
    }

    void FADonate::SetupDonate(not_null<Ui::VerticalLayout *> container, not_null<Window::SessionController *> controller) {
        Ui::AddSubsectionTitle(container, rpl::single(QString("Choose method")));

		AddButtonWithLabel(
			container,
			rpl::single(QString("CryptoBot")),
			rpl::single(QString("")),
			st::settingsButton,
			{ &st::menuIconSettings }
		)->setClickedCallback([=] {
			Core::App().openLocalUrl("tg://resolve?domain=send&start=IVY4MTNvUux2", {});
		});

		AddButtonWithLabel(
			container,
			rpl::single(QString("xRocket (USDT)")),
			rpl::single(QString("")),
			st::settingsButton,
			{ &st::menuIconSettings }
		)->setClickedCallback([=] {
			Core::App().openLocalUrl("tg://resolve?domain=xrocket&start=inv_Kk0LIqQEOsXinPt", {});
		});

		AddButtonWithLabel(
			container,
			rpl::single(QString("xRocket (TON)")),
			rpl::single(QString("")),
			st::settingsButton,
			{ &st::menuIconSettings }
		)->setClickedCallback([=] {
			Core::App().openLocalUrl("tg://resolve?domain=xrocket&start=inv_dPm8Mly2RSUY2OH", {});
		});

		AddButtonWithLabel(
			container,
			rpl::single(QString("xRocket (BTC)")),
			rpl::single(QString("")),
			st::settingsButton,
			{ &st::menuIconSettings }
		)->setClickedCallback([=] {
			Core::App().openLocalUrl("tg://resolve?domain=xrocket&start=inv_BXdIdAYYhYuh2l1", {});
		});

		AddButtonWithLabel(
			container,
			FAlang::RplTranslate("fa_ton_wallet"),
			rpl::single(QString("")),
			st::settingsButton,
			{ &st::menuIconSettings }
		)->setClickedCallback([=] {
			QGuiApplication::clipboard()->setText(QString("UQAZN72cWgDpsjssz7gv5NUJiV5vo9xoGrbzy7Z3qDUmVMvX"));
            controller->showToast(QString("Address copied."), 1000);
		});

		Ui::AddDividerText(container, FAlang::RplTranslate("fa_thank_you"));
    }

    void FADonate::SetupFADonate(not_null<Ui::VerticalLayout *> container, not_null<Window::SessionController *> controller) {
		Ui::AddSkip(container);
    	SetupDonate(container, controller);
    }

    void FADonate::setupContent(not_null<Window::SessionController *> controller) {
        const auto content = Ui::CreateChild<Ui::VerticalLayout>(this);

        SetupFADonate(content, controller);

        Ui::ResizeFitChild(this, content);
    }
} // namespace Settings

// thanks rabbitGram