#pragma once

#include <QtCore/QString>

namespace SpookyGram {

struct BookmarkItem final {
	uint64 id = 0;
	uint64 peerId = 0;
	int32 msgId = 0;
	QString peerName;
	QString snippet;
	QString category;
	QString note;
	int64 date = 0;
};

} // namespace SpookyGram
