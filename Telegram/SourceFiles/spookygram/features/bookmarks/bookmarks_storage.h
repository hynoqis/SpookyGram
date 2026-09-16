#pragma once

#include "spookygram/features/bookmarks/bookmark_item.h"
#include <QtCore/QStringList>
#include <vector>

namespace SpookyGram {

class BookmarksStorage final {
public:
	BookmarksStorage();
	~BookmarksStorage();

	static BookmarksStorage &Instance();

	void addBookmark(const BookmarkItem &item);
	void removeBookmark(uint64 id);
	[[nodiscard]] std::vector<BookmarkItem> listBookmarks(const QString &category = QString()) const;
	[[nodiscard]] QStringList categories() const;
	[[nodiscard]] bool hasBookmark(uint64 peerId, int32 msgId) const;

	void load();
	void save() const;

private:
	[[nodiscard]] QString filePath() const;

	std::vector<BookmarkItem> _items;
};

[[nodiscard]] BookmarksStorage &Bookmarks();

} // namespace SpookyGram
