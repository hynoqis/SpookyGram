#include "spookygram/features/hotkeys/custom_hotkeys.h"
#include "spookygram/core/spookygram_settings.h"

namespace SpookyGram {

QKeySequence CustomHotkeys::GetKeySequence(HotkeyAction action) {
	const auto &cfg = Config();
	switch (action) {
	case HotkeyAction::OpenSearch:
		return QKeySequence(cfg.hotkeySearch());
	case HotkeyAction::OpenBookmarks:
		return QKeySequence(cfg.hotkeyBookmarks());
	case HotkeyAction::OpenSettings:
		return QKeySequence(cfg.hotkeySettings());
	case HotkeyAction::ToggleCompactMode:
		return QKeySequence(cfg.hotkeyCompact());
	case HotkeyAction::TogglePrivacyMode:
		return QKeySequence(u"Ctrl+Shift+P"_q);
	}
	return QKeySequence();
}

void CustomHotkeys::SetKeySequence(HotkeyAction action, const QString &seq) {
	auto &cfg = Config();
	switch (action) {
	case HotkeyAction::OpenSearch:
		cfg.setHotkeySearch(seq);
		break;
	case HotkeyAction::OpenBookmarks:
		cfg.setHotkeyBookmarks(seq);
		break;
	case HotkeyAction::OpenSettings:
		cfg.setHotkeySettings(seq);
		break;
	case HotkeyAction::ToggleCompactMode:
		cfg.setHotkeyCompact(seq);
		break;
	case HotkeyAction::TogglePrivacyMode:
		break;
	}
}

bool CustomHotkeys::Matches(HotkeyAction action, int key, Qt::KeyboardModifiers modifiers) {
	const auto seq = GetKeySequence(action);
	if (seq.isEmpty()) {
		return false;
	}
	const auto combined = int(modifiers) | key;
	return (combined == seq[0]);
}

} // namespace SpookyGram
