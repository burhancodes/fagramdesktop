/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fajox1/fagramdesktop/blob/master/LEGAL
*/
#pragma once

#include <QtCore/QTimer>

struct AVFrame;

namespace Media {
namespace Capture {

struct Update {
	int samples = 0;
	ushort level = 0;
};

struct Result;

void Start();
void Finish();

class Instance final : public QObject {
public:
	Instance();
	~Instance();

	void check();
	[[nodiscard]] bool available() const {
		return _available;
	}

	[[nodiscard]] rpl::producer<Update, rpl::empty_error> updated() const {
		return _updates.events();
	}

	[[nodiscard]] bool started() const {
		return _started.current();
	}
	[[nodiscard]] rpl::producer<bool> startedChanges() const {
		return _started.changes();
	}

	void start();
	void stop(Fn<void(Result&&)> callback = nullptr);
	void pause(bool value, Fn<void(Result&&)> callback);

private:
	class Inner;
	friend class Inner;

	bool _available = false;
	rpl::variable<bool> _started = false;
	rpl::event_stream<Update, rpl::empty_error> _updates;
	QThread _thread;
	std::unique_ptr<Inner> _inner;

};

[[nodiscard]] Instance *instance();

} // namespace Capture
} // namespace Media

