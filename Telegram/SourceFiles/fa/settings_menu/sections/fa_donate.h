/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

#pragma once

#include "settings/settings_common.h"
#include "settings/settings_common_session.h"

#include <QtGui/QGuiApplication>

class BoxContent;

namespace Window {
    class Controller;

    class SessionController;
} // namespace Window

namespace Settings {
    class FADonate : public Section<FADonate> {
    public:
        FADonate(QWidget *parent, not_null<Window::SessionController *> controller);

        [[nodiscard]] rpl::producer<QString> title() override;

    private:
        void SetupDonate(not_null<Ui::VerticalLayout *> container, not_null<Window::SessionController *> controller);
        
        void SetupFADonate(not_null<Ui::VerticalLayout *> container, not_null<Window::SessionController *> null);
        void setupContent(not_null<Window::SessionController *> controller);
    };

} // namespace Settings