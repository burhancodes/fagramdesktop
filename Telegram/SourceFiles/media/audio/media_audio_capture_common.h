/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

namespace Media::Capture {

struct Result {
	QByteArray bytes;
	VoiceWaveform waveform;
	int samples = 0;
};

} // namespace Media::Capture
