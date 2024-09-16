/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

#include "data/data_abstract_sparse_ids.h"

class PeerData;

namespace Main {
class Session;
} // namespace Main

namespace Data {

using StoriesIdsSlice = AbstractSparseIds<std::vector<StoryId>>;

[[nodiscard]] rpl::producer<StoriesIdsSlice> SavedStoriesIds(
	not_null<PeerData*> peer,
	StoryId aroundId,
	int limit);

[[nodiscard]] rpl::producer<StoriesIdsSlice> ArchiveStoriesIds(
	not_null<PeerData*> peer,
	StoryId aroundId,
	int limit);

} // namespace Data
