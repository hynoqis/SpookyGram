#include "spookygram/features/privacy/ui_privacy.h"
#include "spookygram/core/spookygram_settings.h"

namespace SpookyGram {

bool UIPrivacy::ShouldHideNotificationPreview() {
	return Config().hidePreviewInNotifications() || Config().quickPrivacyMode();
}

bool UIPrivacy::ShouldHideOnMinimize() {
	return Config().hideOnMinimize();
}

bool UIPrivacy::IsQuickPrivacyMode() {
	return Config().quickPrivacyMode();
}

void UIPrivacy::ToggleQuickPrivacyMode() {
	Config().setQuickPrivacyMode(!IsQuickPrivacyMode());
}

QString UIPrivacy::FilterNotificationText(const QString &originalText, const QString &senderName) {
	if (ShouldHideNotificationPreview()) {
		return u"New message"_q;
	}
	return originalText;
}

} // namespace SpookyGram
