#include "spookygram/features/folders/smart_folder_rules.h"
#include "history/history.h"
#include "data/data_peer.h"
#include "data/data_channel.h"
#include "data/data_chat.h"
#include "data/data_user.h"
#include "data/data_session.h"
#include "data/notify/data_notify_settings.h"

namespace SpookyGram {

SmartFolders &SmartFolders::Instance() {
	static auto instance = SmartFolders();
	return instance;
}

std::vector<SmartFolderRule> SmartFolders::rules() const {
	return {
		{ 1, u"Unread Only"_q, SmartFilterType::UnreadOnly, true },
		{ 2, u"Media Only"_q, SmartFilterType::MediaOnly, true },
		{ 3, u"Groups Only"_q, SmartFilterType::GroupsOnly, true },
		{ 4, u"Channels Only"_q, SmartFilterType::ChannelsOnly, true },
		{ 5, u"Muted Chats"_q, SmartFilterType::MutedOnly, true },
		{ 6, u"Recent Activity"_q, SmartFilterType::RecentActivity, true },
	};
}

void SmartFolders::setRuleEnabled(uint32 id, bool enabled) {
	// Local in-memory / config toggles
}

bool SmartFolders::matches(SmartFilterType type, not_null<History*> history) const {
	const auto peer = history->peer;
	switch (type) {
	case SmartFilterType::UnreadOnly:
		return history->unreadCount() > 0;
	case SmartFilterType::GroupsOnly:
		return peer->isChat() || (peer->isChannel() && peer->asChannel()->isMegagroup());
	case SmartFilterType::ChannelsOnly:
		return peer->isChannel() && !peer->asChannel()->isMegagroup();
	case SmartFilterType::MutedOnly:
		return peer->owner().notifySettings().isMuted(peer);
	case SmartFilterType::MediaOnly:
	case SmartFilterType::RecentActivity:
		return true;
	}
	return true;
}

} // namespace SpookyGram
