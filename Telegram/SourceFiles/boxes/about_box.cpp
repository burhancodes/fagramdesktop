/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#include "boxes/about_box.h"

#include "lang/lang_keys.h"
#include "mainwidget.h"
#include "mainwindow.h"
#include "ui/boxes/confirm_box.h"
#include "ui/widgets/buttons.h"
#include "ui/widgets/labels.h"
#include "ui/text/text_utilities.h"
#include "base/platform/base_platform_info.h"
#include "core/file_utilities.h"
#include "core/click_handler_types.h"
#include "core/update_checker.h"
#include "core/application.h"
#include "styles/style_layers.h"
#include "styles/style_boxes.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QClipboard>

namespace {

constexpr auto kTDesktopLinkTag = lngtag_tdesktoplink; // Если lngtag_tdesktoplink — это тип, нужно использовать его экземпляр
constexpr auto kFAgramTag = lngtag_fagram; // Аналогично для других тегов

rpl::producer<TextWithEntities> Text1() {
	return tr::lng_about_text1(
		kTDesktopLinkTag,  // Исправлено использование типа на константу
		tr::lng_about_text1_tdesktoplink() | Ui::Text::ToLink("https://github.com/telegramdesktop/tdesktop"),
		kFAgramTag,  // Исправлено использование типа на константу
		tr::lng_about_text1_fagram() | Ui::Text::ToLink("https://github.com/fajox1/fagramdesktop"),
		Ui::Text::WithEntities);
}

rpl::producer<TextWithEntities> Text2() {
	constexpr auto kGPLLinkTag = lngtag_gpl_link;  // Замена типа на константу
	constexpr auto kGitHubLinkTag = lngtag_github_link;  // Замена типа на константу
	return tr::lng_about_text2(
		kGPLLinkTag,  
		rpl::single(Ui::Text::Link(
			"GNU GPL",
			"https://github.com/fajox1/fagramdesktop/blob/master/LICENSE")),
		kGitHubLinkTag,  
		rpl::single(Ui::Text::Link(
			"GitHub",
			"https://github.com/fajox1/fagramdesktop")),
		Ui::Text::WithEntities);
}

rpl::producer<TextWithEntities> Text3() {
	constexpr auto kFagramNewsTag = lngtag_fagramnews;  // Замена типа на константу
	constexpr auto kFagramGroupTag = lngtag_fagramgroup;  // Замена типа на константу
	constexpr auto kDeveloperTag = lngtag_developer;  // Замена типа на константу
	return tr::lng_about_text3(
		kFagramNewsTag,
		tr::lng_about_text3_fagramnews() | Ui::Text::ToLink("https://t.me/FAgramNews"),
		kFagramGroupTag,
		tr::lng_about_text3_fagramgroup() | Ui::Text::ToLink("https://t.me/FAgram_Group"),
		kDeveloperTag,
		tr::lng_about_text3_developer() | Ui::Text::ToLink("https://t.me/vecax"),
		Ui::Text::WithEntities);
}
}

// namespace

AboutBox::AboutBox(QWidget *parent)
: _version(this, tr::lng_about_version(tr::now, lngtag_version, currentVersionText()), st::aboutVersionLink)
, _text1(this, Text1(), st::aboutLabel)
, _text2(this, Text2(), st::aboutLabel)
, _text3(this, Text3(), st::aboutLabel) {
}

void AboutBox::prepare() {
	setTitle(rpl::single(u"FAgram Desktop"_q));

	addButton(tr::lng_close(), [this] { closeBox(); });

	_text1->setLinksTrusted();
	_text2->setLinksTrusted();
	_text3->setLinksTrusted();

	_version->setClickedCallback([this] { showVersionHistory(); });

	setDimensions(st::aboutWidth, st::aboutTextTop + _text1->height() + st::aboutSkip + _text2->height() + st::aboutSkip + _text3->height());
}

void AboutBox::resizeEvent(QResizeEvent *e) {
	BoxContent::resizeEvent(e);

	const auto available = width()
		- st::boxPadding.left()
		- st::boxPadding.right();
	_version->moveToLeft(st::boxPadding.left(), st::aboutVersionTop);
	_text1->resizeToWidth(available);
	_text1->moveToLeft(st::boxPadding.left(), st::aboutTextTop);
	_text2->resizeToWidth(available);
	_text2->moveToLeft(st::boxPadding.left(), _text1->y() + _text1->height() + st::aboutSkip);
	_text3->resizeToWidth(available);
	_text3->moveToLeft(st::boxPadding.left(), _text2->y() + _text2->height() + st::aboutSkip);
}

void AboutBox::showVersionHistory() {
	if (cRealAlphaVersion()) {
		auto url = u"https://tdesktop.com/"_q;
		if (Platform::IsWindows32Bit()) {
			url += u"win/%1.zip"_q;
		} else if (Platform::IsWindows64Bit()) {
			url += u"win64/%1.zip"_q;
		} else if (Platform::IsWindowsARM64()) {
			url += u"winarm/%1.zip"_q;
		} else if (Platform::IsMac()) {
			url += u"mac/%1.zip"_q;
		} else if (Platform::IsLinux()) {
			url += u"linux/%1.tar.xz"_q;
		} else {
			Unexpected("Platform value.");
		}
		url = url.arg(u"talpha%1_%2"_q.arg(cRealAlphaVersion()).arg(Core::countAlphaVersionSignature(cRealAlphaVersion())));

		QGuiApplication::clipboard()->setText(url);

		getDelegate()->show(
			Ui::MakeInformBox(
				"The link to the current private alpha "
				"version of FAgram Desktop was copied to the clipboard."),
			Ui::LayerOption::CloseOther);
	} else {
		File::OpenUrl(Core::App().changelogLink());
	}
}

void AboutBox::keyPressEvent(QKeyEvent *e) {
	if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
		closeBox();
	} else {
		BoxContent::keyPressEvent(e);
	}
}

QString telegramFaqLink() {
	const auto result = u"https://telegram.org/faq"_q;
	const auto langpacked = [&](const char *language) {
		return result + '/' + language;
	};
	const auto current = Lang::Id();
	for (const auto language : { "de", "es", "it", "ko" }) {
		if (current.startsWith(QLatin1String(language))) {
			return langpacked(language);
		}
	}
	if (current.startsWith(u"pt-br"_q)) {
		return langpacked("br");
	}
	return result;
}

QString currentVersionText() {
	auto result = QString::fromLatin1(AppVersionStr);
	if (cAlphaVersion()) {
		result += u" alpha %1"_q.arg(cAlphaVersion() % 1000);
	} else if (AppBetaVersion) {
		result += " beta";
	}
	if (Platform::IsWindows64Bit()) {
		result += " x64";
	} else if (Platform::IsWindowsARM64()) {
		result += " arm64";
	}
	return result;
}
