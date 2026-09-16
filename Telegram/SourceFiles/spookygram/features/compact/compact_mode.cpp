#include "spookygram/features/compact/compact_mode.h"
#include "spookygram/core/spookygram_settings.h"

namespace SpookyGram {

bool CompactMode::IsEnabled() {
	return Config().compactMode();
}

void CompactMode::Toggle() {
	SetEnabled(!IsEnabled());
}

void CompactMode::SetEnabled(bool enabled) {
	Config().setCompactMode(enabled);
}

rpl::producer<bool> CompactMode::Changes() {
	return Config().compactModeValue();
}

int CompactMode::DialogRowHeight(int defaultHeight) {
	return IsEnabled() ? (defaultHeight * 80 / 100) : defaultHeight;
}

int CompactMode::ChatPadding(int defaultPadding) {
	return IsEnabled() ? (defaultPadding * 70 / 100) : defaultPadding;
}

} // namespace SpookyGram
