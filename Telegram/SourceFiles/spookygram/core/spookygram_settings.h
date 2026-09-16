#pragma once

#include <QtCore/QString>
#include "rpl/variable.h"

namespace SpookyGram {

class Settings final {
public:
	Settings();
	~Settings();

	static Settings &Instance();

	[[nodiscard]] bool compactMode() const;
	void setCompactMode(bool value);
	[[nodiscard]] rpl::producer<bool> compactModeValue() const;

	[[nodiscard]] bool hidePreviewInNotifications() const;
	void setHidePreviewInNotifications(bool value);

	[[nodiscard]] bool hideOnMinimize() const;
	void setHideOnMinimize(bool value);

	[[nodiscard]] bool quickPrivacyMode() const;
	void setQuickPrivacyMode(bool value);

	[[nodiscard]] bool autoClearHistory() const;
	void setAutoClearHistory(bool value);

	[[nodiscard]] QString hotkeySearch() const;
	void setHotkeySearch(const QString &value);

	[[nodiscard]] QString hotkeyBookmarks() const;
	void setHotkeyBookmarks(const QString &value);

	[[nodiscard]] QString hotkeySettings() const;
	void setHotkeySettings(const QString &value);

	[[nodiscard]] QString hotkeyCompact() const;
	void setHotkeyCompact(const QString &value);

	[[nodiscard]] QString aiProviderType() const;
	void setAiProviderType(const QString &value);

	[[nodiscard]] QString aiEndpoint() const;
	void setAiEndpoint(const QString &value);

	[[nodiscard]] QString aiApiKey() const;
	void setAiApiKey(const QString &value);

	[[nodiscard]] QString aiModel() const;
	void setAiModel(const QString &value);

	[[nodiscard]] bool quickActionCopyClean() const;
	void setQuickActionCopyClean(bool value);

	[[nodiscard]] bool quickActionCopyId() const;
	void setQuickActionCopyId(bool value);

	[[nodiscard]] bool quickActionCopyLink() const;
	void setQuickActionCopyLink(bool value);

	[[nodiscard]] bool quickActionSenderProfile() const;
	void setQuickActionSenderProfile(bool value);

	[[nodiscard]] bool quickActionSaveBookmark() const;
	void setQuickActionSaveBookmark(bool value);

	[[nodiscard]] bool quickActionResend() const;
	void setQuickActionResend(bool value);

	void load();
	void save() const;

private:
	[[nodiscard]] QString configFilePath() const;

	rpl::variable<bool> _compactMode = false;
	bool _hidePreviewInNotifications = false;
	bool _hideOnMinimize = false;
	bool _quickPrivacyMode = false;
	bool _autoClearHistory = false;

	QString _hotkeySearch = u"Ctrl+Shift+F"_q;
	QString _hotkeyBookmarks = u"Ctrl+Shift+B"_q;
	QString _hotkeySettings = u"Ctrl+Shift+S"_q;
	QString _hotkeyCompact = u"Ctrl+Shift+C"_q;

	QString _aiProviderType = u"mock"_q;
	QString _aiEndpoint = u"https://api.openai.com/v1"_q;
	QString _aiApiKey;
	QString _aiModel = u"gpt-4o-mini"_q;

	bool _quickActionCopyClean = true;
	bool _quickActionCopyId = true;
	bool _quickActionCopyLink = true;
	bool _quickActionSenderProfile = true;
	bool _quickActionSaveBookmark = true;
	bool _quickActionResend = true;
};

[[nodiscard]] Settings &Config();

} // namespace SpookyGram
