#pragma once

#include <QtCore/QString>
#include <vector>

class DialogsRow;
class History;

namespace SpookyGram {

enum class SmartFilterType {
	UnreadOnly,
	MediaOnly,
	GroupsOnly,
	ChannelsOnly,
	MutedOnly,
	RecentActivity,
};

struct SmartFolderRule final {
	uint32 id = 0;
	QString title;
	SmartFilterType type = SmartFilterType::UnreadOnly;
	bool enabled = true;
};

class SmartFolders final {
public:
	static SmartFolders &Instance();

	[[nodiscard]] std::vector<SmartFolderRule> rules() const;
	void setRuleEnabled(uint32 id, bool enabled);
	[[nodiscard]] bool matches(SmartFilterType type, not_null<History*> history) const;
};

} // namespace SpookyGram
