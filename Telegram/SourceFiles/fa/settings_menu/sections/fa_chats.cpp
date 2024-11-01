/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

#include <ui/boxes/single_choice_box.h>

#include "fa/settings/fa_settings.h"
#include "fa/settings_menu/sections/fa_chats.h"

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

    rpl::producer<QString> FAChats::title() {
        return FAlang::RplTranslate(QString("fa_chats"));
    }

    FAChats::FAChats(
            QWidget *parent,
            not_null<Window::SessionController *> controller)
            : Section(parent) {
        setupContent(controller);
    }

    void FAChats::SetupChats(not_null<Ui::VerticalLayout *> container) {
        Ui::AddSubsectionTitle(container, FAlang::RplTranslate(QString("fa_chats")));

		const auto recentStickersLimitLabel = container->add(
			object_ptr<Ui::LabelSimple>(
				container,
				st::settingsAudioVolumeLabel),
			st::settingsAudioVolumeLabelPadding);
		const auto recentStickersLimitSlider = container->add(
			object_ptr<Ui::MediaSlider>(
				container,
				st::settingsAudioVolumeSlider),
			st::settingsAudioVolumeSliderPadding);
		const auto updateRecentStickersLimitLabel = [=](int value) {
			recentStickersLimitLabel->setText(
				(value == 0)
					? FAlang::Translate(QString("fa_recent_stickers_hidden"))
					: FAlang::Translate(QString("fa_recent_stickers")).arg(value) );
		};
        const auto updateRecentStickersLimitHeight = [=](int value) {
			updateRecentStickersLimitLabel(value);
			::FASettings::JsonSettings::Set("recent_stickers_limit", value);
			::FASettings::JsonSettings::Write();
		};
		recentStickersLimitSlider->resize(st::settingsAudioVolumeSlider.seekSize);
		recentStickersLimitSlider->setPseudoDiscrete(
			100+1,
			[](int val) { return val; },
			::FASettings::JsonSettings::GetInt("recent_stickers_limit"),
			updateRecentStickersLimitHeight);
		updateRecentStickersLimitLabel(::FASettings::JsonSettings::GetInt("recent_stickers_limit"));
		Ui::AddSkip(container);
        Ui::AddDivider(container);
		Ui::AddSkip(container);
		SettingsMenuJsonSwitch(FAlang::RplTranslate(QString("fa_hide_all_chats_folder")), hide_all_chats_folder)
		Ui::AddDividerText(container, FAlang::RplTranslate(QString("fa_settings_change_after_restart")));
    }

    void FAChats::SetupFAChats(not_null<Ui::VerticalLayout *> container, not_null<Window::SessionController *> controller) {
		Ui::AddSkip(container);
    	SetupChats(container);
    }

    void FAChats::setupContent(not_null<Window::SessionController *> controller) {
        const auto content = Ui::CreateChild<Ui::VerticalLayout>(this);

        SetupFAChats(content, controller);

        Ui::ResizeFitChild(this, content);
    }
} // namespace Settings

// thanks rabbitGram