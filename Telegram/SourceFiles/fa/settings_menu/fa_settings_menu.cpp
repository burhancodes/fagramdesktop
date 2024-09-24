/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

// thanks rabbitGram

#include <ui/boxes/single_choice_box.h>

#include "fa/settings_menu/fa_settings_menu.h"
#include "fa/settings_menu/sections/fa_general.h"

#include "core/application.h"
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
#include "apiwrap.h"
#include "api/api_blocked_peers.h"
#include "ui/widgets/continuous_sliders.h"
#include "ui/basic_click_handlers.h"

#define SettingsMenuJsonSwitch(LangKey, Option) container->add(object_ptr<Button>( \
	container, \
    QString(#LangKey), \
	st::settingsButtonNoIcon \
))->toggleOn( \
	rpl::single(::FASettings::JsonSettings::GetBool(#Option)) \
)->toggledValue( \
) | rpl::filter([](bool enabled) { \
	return (enabled != ::FASettings::JsonSettings::GetBool(#Option)); \
}) | rpl::start_with_next([](bool enabled) { \
	::FASettings::JsonSettings::Set(#Option, enabled); \
	::FASettings::JsonSettings::Write(); \
}, container->lifetime());

namespace Settings {

    rpl::producer<QString> FA::title() {
        return rpl::single(QString("FAgram Settings"));
    }

    FA::FA(
            QWidget *parent,
            not_null<Window::SessionController *> controller)
            : Section(parent) {
        setupContent(controller);
    }

    void FA::SetupFASettings(not_null<Ui::VerticalLayout *> container, not_null<Window::SessionController *> controller) {
    	AddSubsectionTitle(container, rpl::single(QString("Categories")));
    	
		const auto addSection = [&](
				rpl::producer<QString> label,
				Type type,
				IconDescriptor &&descriptor) {
			AddButtonWithIcon(
				container,
				std::move(label),
				st::settingsButton,
				std::move(descriptor)
			)->addClickHandler([=] {
				showOther(type);
			});
		};
    	addSection(
			rpl::single(QString("General")),
			FAGeneral::Id(),
			{ &st::menuIconShowAll });
    }

	void FA::SetupLinks(not_null<Ui::VerticalLayout *> container, not_null<Window::SessionController *> controller)
    {
    	AddSubsectionTitle(container, rpl::single(QString("Links")));
    	
	    AddButtonWithLabel(
			container,
			rpl::single(QString("Channel")),
			rpl::single(QString("@FAgramNews")),
			st::settingsButton,
			{ &st::menuIconChannel }
		)->setClickedCallback([=] {
			Core::App().openLocalUrl("tg://resolve?domain=FAgramNews", {});
		});

    	AddButtonWithLabel(
			container,
			rpl::single(QString("Group")),
			rpl::single(QString("@FAgram_Group")),
			st::settingsButton,
			{ &st::menuIconGroups }
		)->setClickedCallback([=] {
			Core::App().openLocalUrl("tg://resolve?domain=FAgram_Group", {});
		});

    	AddButtonWithLabel(
			container,
			rpl::single(QString("Update FAgram")),
			rpl::single(QString("Update")),
			st::settingsButton,
			{ &st::menuIconSettings }
		)->setClickedCallback([=] {
			Core::App().openLocalUrl("tg://resolve?domain=FAgram_Group&thread=11", {});
		});

    	AddButtonWithLabel(
			container,
			rpl::single(QString("Beta")),
			rpl::single(QString("@FAgramBeta")),
			st::settingsButton,
			{ &st::menuIconShowAll }
		)->setClickedCallback([=] {
			Core::App().openLocalUrl("tg://resolve?domain=FAgramBeta", {});
		});

    	AddButtonWithLabel(
			container,
			rpl::single(QString("Source code")),
			rpl::single(QString("Github")),
			st::settingsButton,
			{ &st::menuIconDelete }
		)->setClickedCallback([=] {
			UrlClickHandler::Open("https://github.com/fajox1/fagramdesktop");
		});
    }

    void FA::setupContent(not_null<Window::SessionController *> controller) {
        const auto content = Ui::CreateChild<Ui::VerticalLayout>(this);

    	Ui::AddSkip(content);
        SetupFASettings(content, controller);

    	Ui::AddSkip(content);
    	Ui::AddDivider(content);
    	Ui::AddSkip(content);
    	SetupLinks(content, controller);

        Ui::ResizeFitChild(this, content);
    }
} // namespace Settings