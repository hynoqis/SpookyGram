#include "spookygram/features/bookmarks/bookmarks_storage.h"

#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QStandardPaths>
#include <QtCore/QDateTime>
#include <algorithm>

namespace SpookyGram {

BookmarksStorage::BookmarksStorage() {
	load();
}

BookmarksStorage::~BookmarksStorage() {
	save();
}

BookmarksStorage &BookmarksStorage::Instance() {
	static auto instance = BookmarksStorage();
	return instance;
}

BookmarksStorage &Bookmarks() {
	return BookmarksStorage::Instance();
}

QString BookmarksStorage::filePath() const {
	const auto dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
	QDir().mkpath(dir);
	return dir + u"/spookygram_bookmarks.json"_q;
}

void BookmarksStorage::addBookmark(const BookmarkItem &item) {
	auto copy = item;
	if (!copy.id) {
		copy.id = static_cast<uint64>(QDateTime::currentMSecsSinceEpoch());
	}
	if (!copy.date) {
		copy.date = QDateTime::currentSecsSinceEpoch();
	}
	const auto it = std::find_if(_items.begin(), _items.end(), [&](const BookmarkItem &b) {
		return (b.peerId == copy.peerId && b.msgId == copy.msgId);
	});
	if (it != _items.end()) {
		*it = copy;
	} else {
		_items.insert(_items.begin(), copy);
	}
	save();
}

void BookmarksStorage::removeBookmark(uint64 id) {
	_items.erase(std::remove_if(_items.begin(), _items.end(), [&](const BookmarkItem &b) {
		return b.id == id;
	}), _items.end());
	save();
}

std::vector<BookmarkItem> BookmarksStorage::listBookmarks(const QString &category) const {
	if (category.isEmpty()) {
		return _items;
	}
	auto result = std::vector<BookmarkItem>();
	for (const auto &item : _items) {
		if (item.category.compare(category, Qt::CaseInsensitive) == 0) {
			result.push_back(item);
		}
	}
	return result;
}

QStringList BookmarksStorage::categories() const {
	auto list = QStringList();
	for (const auto &item : _items) {
		if (!item.category.isEmpty() && !list.contains(item.category, Qt::CaseInsensitive)) {
			list.append(item.category);
		}
	}
	return list;
}

bool BookmarksStorage::hasBookmark(uint64 peerId, int32 msgId) const {
	return std::any_of(_items.begin(), _items.end(), [&](const BookmarkItem &b) {
		return (b.peerId == peerId && b.msgId == msgId);
	});
}

void BookmarksStorage::load() {
	auto file = QFile(filePath());
	if (!file.open(QIODevice::ReadOnly)) {
		return;
	}
	const auto doc = QJsonDocument::fromJson(file.readAll());
	if (!doc.isArray()) {
		return;
	}
	_items.clear();
	const auto arr = doc.array();
	for (const auto &val : arr) {
		if (!val.isObject()) {
			continue;
		}
		const auto obj = val.toObject();
		auto item = BookmarkItem();
		item.id = static_cast<uint64>(obj.value(u"id"_q).toInteger());
		item.peerId = static_cast<uint64>(obj.value(u"peerId"_q).toInteger());
		item.msgId = static_cast<int32>(obj.value(u"msgId"_q).toInt());
		item.peerName = obj.value(u"peerName"_q).toString();
		item.snippet = obj.value(u"snippet"_q).toString();
		item.category = obj.value(u"category"_q).toString();
		item.note = obj.value(u"note"_q).toString();
		item.date = obj.value(u"date"_q).toInteger();
		_items.push_back(std::move(item));
	}
}

void BookmarksStorage::save() const {
	auto arr = QJsonArray();
	for (const auto &item : _items) {
		auto obj = QJsonObject();
		obj[u"id"_q] = static_cast<qint64>(item.id);
		obj[u"peerId"_q] = static_cast<qint64>(item.peerId);
		obj[u"msgId"_q] = item.msgId;
		obj[u"peerName"_q] = item.peerName;
		obj[u"snippet"_q] = item.snippet;
		obj[u"category"_q] = item.category;
		obj[u"note"_q] = item.note;
		obj[u"date"_q] = item.date;
		arr.append(obj);
	}
	auto file = QFile(filePath());
	if (file.open(QIODevice::WriteOnly)) {
		file.write(QJsonDocument(arr).toJson(QJsonDocument::Indented));
	}
}

} // namespace SpookyGram
