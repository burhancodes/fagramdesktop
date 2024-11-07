/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/

#include "fa/lang/fa_lang.h"

#include "base/parse_helper.h"
#include "lang/lang_tag.h"

namespace FAlang {
    const auto kDefaultLanguage = qsl("en");

    QString langCode = kDefaultLanguage;

    std::unique_ptr<QFile> GetLangFile() {
        auto file = std::make_unique<QFile>(qsl(":/fa_lang/%1.json").arg(langCode));
        if (!file->exists()) {
            file->setFileName(qsl(":/fa_lang/en.json"));
        }
        return file;
    }

    rpl::producer<QString> RplTranslate(const QString &key) {
        auto translated = rpl::single(Translate(key));
        return translated;
    }

    QString Translate(const QString &key) {
        auto langFile = GetLangFile();
        if (!langFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
            return key;
        }

        QByteArray jsonData = langFile->readAll();
        langFile->close();

        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            return key;
        }

        QJsonObject jsonObj = jsonDoc.object();
        QString translation = jsonObj.value(key).toString();

        return translation.isEmpty() ? key : translation;
    }

    void Load(const QString &baseLangCode, const QString &lang_code) {
	//	if (BaseLangCode.endsWith("-raw")) {
	//		BaseLangCode.chop(4);
	//	}
	//	lang_code = lang_code.isEmpty() ? baseLangCode : lang_code;
	//	if (lang_code.endsWith("-raw")) {
	//		lang_code.chop(4);
	//	}

		langCode = lang_code;
    }
}