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

    std::unique_ptr<QFile> GetLangFile() {
	    auto file = std::make_unique<QFile>(qsl(":/fa_lang/%1.json").arg(kDefaultLanguage));
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
	    auto lang_file = GetLangFile();
	    if (!lang_file->open(QIODevice::ReadOnly | QIODevice::Text)) {
	    	return key;
	    }

    	QByteArray jsonData = lang_file->readAll();
    	lang_file->close();

	    QJsonParseError parseError;
	    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    	if (parseError.error != QJsonParseError::NoError) {
	    	return key;
    	}

	    QJsonObject jsonObj = jsonDoc.object();
	    QString translation = jsonObj.value(key).toString();

	    return translation.isEmpty() ? key : translation;
    }
}