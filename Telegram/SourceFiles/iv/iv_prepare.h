/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

namespace Iv {

struct Options;
struct Prepared;

struct Source {
	uint64 pageId = 0;
	MTPPage page;
	std::optional<MTPPhoto> webpagePhoto;
	std::optional<MTPDocument> webpageDocument;
	QString name;
	int updatedCachedViews = 0;
};

[[nodiscard]] Prepared Prepare(const Source &source, const Options &options);

} // namespace Iv
