#include "spookygram/core/spookygram_settings.h"

#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QStandardPaths>

namespace SpookyGram {

Settings::Settings() {
	load();
}

Settings::~Settings() {
	save();
}

Settings &Settings::Instance() {
	static auto instance = Settings();
	return instance;
}

Settings &Config() {
	return Settings::Instance();
}

QString Settings::configFilePath() const {
	const auto dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
	QDir().mkpath(dir);
	return dir + u"/spookygram_config.json"_q;
}

bool Settings::compactMode() const {
	return _compactMode.current();
}

void Settings::setCompactMode(bool value) {
	_compactMode = value;
	save();
}

rpl::producer<bool> Settings::compactModeValue() const {
	return _compactMode.value();
}

bool Settings::hidePreviewInNotifications() const {
	return _hidePreviewInNotifications;
}

void Settings::setHidePreviewInNotifications(bool value) {
	_hidePreviewInNotifications = value;
	save();
}

bool Settings::hideOnMinimize() const {
	return _hideOnMinimize;
}

void Settings::setHideOnMinimize(bool value) {
	_hideOnMinimize = value;
	save();
}

bool Settings::quickPrivacyMode() const {
	return _quickPrivacyMode;
}

void Settings::setQuickPrivacyMode(bool value) {
	_quickPrivacyMode = value;
	save();
}

bool Settings::autoClearHistory() const {
	return _autoClearHistory;
}

void Settings::setAutoClearHistory(bool value) {
	_autoClearHistory = value;
	save();
}

QString Settings::hotkeySearch() const {
	return _hotkeySearch;
}

void Settings::setHotkeySearch(const QString &value) {
	_hotkeySearch = value;
	save();
}

QString Settings::hotkeyBookmarks() const {
	return _hotkeyBookmarks;
}

void Settings::setHotkeyBookmarks(const QString &value) {
	_hotkeyBookmarks = value;
	save();
}

QString Settings::hotkeySettings() const {
	return _hotkeySettings;
}

void Settings::setHotkeySettings(const QString &value) {
	_hotkeySettings = value;
	save();
}

QString Settings::hotkeyCompact() const {
	return _hotkeyCompact;
}

void Settings::setHotkeyCompact(const QString &value) {
	_hotkeyCompact = value;
	save();
}

QString Settings::aiProviderType() const {
	return _aiProviderType;
}

void Settings::setAiProviderType(const QString &value) {
	_aiProviderType = value;
	save();
}

QString Settings::aiEndpoint() const {
	return _aiEndpoint;
}

void Settings::setAiEndpoint(const QString &value) {
	_aiEndpoint = value;
	save();
}

QString Settings::aiApiKey() const {
	return _aiApiKey;
}

void Settings::setAiApiKey(const QString &value) {
	_aiApiKey = value;
	save();
}

QString Settings::aiModel() const {
	return _aiModel;
}

void Settings::setAiModel(const QString &value) {
	_aiModel = value;
	save();
}

bool Settings::quickActionCopyClean() const {
	return _quickActionCopyClean;
}

void Settings::setQuickActionCopyClean(bool value) {
	_quickActionCopyClean = value;
	save();
}

bool Settings::quickActionCopyId() const {
	return _quickActionCopyId;
}

void Settings::setQuickActionCopyId(bool value) {
	_quickActionCopyId = value;
	save();
}

bool Settings::quickActionCopyLink() const {
	return _quickActionCopyLink;
}

void Settings::setQuickActionCopyLink(bool value) {
	_quickActionCopyLink = value;
	save();
}

bool Settings::quickActionSenderProfile() const {
	return _quickActionSenderProfile;
}

void Settings::setQuickActionSenderProfile(bool value) {
	_quickActionSenderProfile = value;
	save();
}

bool Settings::quickActionSaveBookmark() const {
	return _quickActionSaveBookmark;
}

void Settings::setQuickActionSaveBookmark(bool value) {
	_quickActionSaveBookmark = value;
	save();
}

bool Settings::quickActionResend() const {
	return _quickActionResend;
}

void Settings::setQuickActionResend(bool value) {
	_quickActionResend = value;
	save();
}

void Settings::load() {
	auto file = QFile(configFilePath());
	if (!file.open(QIODevice::ReadOnly)) {
		return;
	}
	const auto doc = QJsonDocument::fromJson(file.readAll());
	if (!doc.isObject()) {
		return;
	}
	const auto obj = doc.object();

	if (obj.contains(u"compactMode"_q)) {
		_compactMode = obj.value(u"compactMode"_q).toBool(false);
	}
	if (obj.contains(u"hidePreviewInNotifications"_q)) {
		_hidePreviewInNotifications = obj.value(u"hidePreviewInNotifications"_q).toBool(false);
	}
	if (obj.contains(u"hideOnMinimize"_q)) {
		_hideOnMinimize = obj.value(u"hideOnMinimize"_q).toBool(false);
	}
	if (obj.contains(u"quickPrivacyMode"_q)) {
		_quickPrivacyMode = obj.value(u"quickPrivacyMode"_q).toBool(false);
	}
	if (obj.contains(u"autoClearHistory"_q)) {
		_autoClearHistory = obj.value(u"autoClearHistory"_q).toBool(false);
	}

	if (obj.contains(u"hotkeySearch"_q)) {
		_hotkeySearch = obj.value(u"hotkeySearch"_q).toString(_hotkeySearch);
	}
	if (obj.contains(u"hotkeyBookmarks"_q)) {
		_hotkeyBookmarks = obj.value(u"hotkeyBookmarks"_q).toString(_hotkeyBookmarks);
	}
	if (obj.contains(u"hotkeySettings"_q)) {
		_hotkeySettings = obj.value(u"hotkeySettings"_q).toString(_hotkeySettings);
	}
	if (obj.contains(u"hotkeyCompact"_q)) {
		_hotkeyCompact = obj.value(u"hotkeyCompact"_q).toString(_hotkeyCompact);
	}

	if (obj.contains(u"aiProviderType"_q)) {
		_aiProviderType = obj.value(u"aiProviderType"_q).toString(_aiProviderType);
	}
	if (obj.contains(u"aiEndpoint"_q)) {
		_aiEndpoint = obj.value(u"aiEndpoint"_q).toString(_aiEndpoint);
	}
	if (obj.contains(u"aiApiKey"_q)) {
		_aiApiKey = obj.value(u"aiApiKey"_q).toString();
	}
	if (obj.contains(u"aiModel"_q)) {
		_aiModel = obj.value(u"aiModel"_q).toString(_aiModel);
	}

	if (obj.contains(u"quickActionCopyClean"_q)) {
		_quickActionCopyClean = obj.value(u"quickActionCopyClean"_q).toBool(true);
	}
	if (obj.contains(u"quickActionCopyId"_q)) {
		_quickActionCopyId = obj.value(u"quickActionCopyId"_q).toBool(true);
	}
	if (obj.contains(u"quickActionCopyLink"_q)) {
		_quickActionCopyLink = obj.value(u"quickActionCopyLink"_q).toBool(true);
	}
	if (obj.contains(u"quickActionSenderProfile"_q)) {
		_quickActionSenderProfile = obj.value(u"quickActionSenderProfile"_q).toBool(true);
	}
	if (obj.contains(u"quickActionSaveBookmark"_q)) {
		_quickActionSaveBookmark = obj.value(u"quickActionSaveBookmark"_q).toBool(true);
	}
	if (obj.contains(u"quickActionResend"_q)) {
		_quickActionResend = obj.value(u"quickActionResend"_q).toBool(true);
	}
}

void Settings::save() const {
	auto obj = QJsonObject();
	obj[u"compactMode"_q] = _compactMode.current();
	obj[u"hidePreviewInNotifications"_q] = _hidePreviewInNotifications;
	obj[u"hideOnMinimize"_q] = _hideOnMinimize;
	obj[u"quickPrivacyMode"_q] = _quickPrivacyMode;
	obj[u"autoClearHistory"_q] = _autoClearHistory;

	obj[u"hotkeySearch"_q] = _hotkeySearch;
	obj[u"hotkeyBookmarks"_q] = _hotkeyBookmarks;
	obj[u"hotkeySettings"_q] = _hotkeySettings;
	obj[u"hotkeyCompact"_q] = _hotkeyCompact;

	obj[u"aiProviderType"_q] = _aiProviderType;
	obj[u"aiEndpoint"_q] = _aiEndpoint;
	obj[u"aiApiKey"_q] = _aiApiKey;
	obj[u"aiModel"_q] = _aiModel;

	obj[u"quickActionCopyClean"_q] = _quickActionCopyClean;
	obj[u"quickActionCopyId"_q] = _quickActionCopyId;
	obj[u"quickActionCopyLink"_q] = _quickActionCopyLink;
	obj[u"quickActionSenderProfile"_q] = _quickActionSenderProfile;
	obj[u"quickActionSaveBookmark"_q] = _quickActionSaveBookmark;
	obj[u"quickActionResend"_q] = _quickActionResend;

	auto file = QFile(configFilePath());
	if (file.open(QIODevice::WriteOnly)) {
		file.write(QJsonDocument(obj).toJson(QJsonDocument::Indented));
	}
}

} // namespace SpookyGram
