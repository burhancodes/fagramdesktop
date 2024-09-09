/*
This file is part of FAgram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

#include "data/data_statistics.h"

namespace Info::Statistics {

struct SavedState final {
	Data::AnyStatistics stats;
	base::flat_map<Data::RecentPostId, QImage> recentPostPreviews;
	Data::PublicForwardsSlice publicForwardsFirstSlice;
	int recentPostsExpanded = 0;
};

} // namespace Info::Statistics
