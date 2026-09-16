#pragma once

#include <QtCore/QString>

namespace SpookyGram {

class UIPrivacy final {
public:
	static bool ShouldHideNotificationPreview();
	static bool ShouldHideOnMinimize();
	static bool IsQuickPrivacyMode();
	static void ToggleQuickPrivacyMode();

	static QString FilterNotificationText(const QString &originalText, const QString &senderName);
};

} // namespace SpookyGram
