#include "spookygram/features/hotkeys/custom_hotkeys.h"
#include "spookygram/core/spookygram_settings.h"
#include "spookygram/settings/spookygram_settings_box.h"
#include "spookygram/features/bookmarks/bookmarks_box.h"
#include "window/window_controller.h"
#include "window/window_session_controller.h"
#include "ui/toast/toast.h"

#include <QtGui/QKeyEvent>

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
	return (seq.matches(QKeySequence(modifiers | Qt::Key(key))) == QKeySequence::ExactMatch);
}

bool CustomHotkeys::HandleKeyEvent(QKeyEvent *e, Window::Controller *window) {
	if (!e) {
		return false;
	}
	const auto key = e->key();
	const auto modifiers = e->modifiers();

	if (Matches(HotkeyAction::ToggleCompactMode, key, modifiers)) {
		const auto next = !Config().compactMode();
		Config().setCompactMode(next);
		Ui::Toast::Show(next
			? u"Компактный режим включен"_q
			: u"Компактный режим выключен"_q);
		return true;
	} else if (Matches(HotkeyAction::TogglePrivacyMode, key, modifiers)) {
		const auto next = !Config().quickPrivacyMode();
		Config().setQuickPrivacyMode(next);
		Ui::Toast::Show(next
			? u"Режим скрытности включен"_q
			: u"Режим скрытности выключен"_q);
		return true;
	} else if (Matches(HotkeyAction::OpenBookmarks, key, modifiers)) {
		if (window) {
			if (const auto session = window->sessionController()) {
				session->show(Box(BookmarksBox, session));
				return true;
			}
		}
	} else if (Matches(HotkeyAction::OpenSettings, key, modifiers)) {
		if (window) {
			if (const auto session = window->sessionController()) {
				session->show(Box(SpookyGramSettingsBox, session));
				return true;
			}
		}
	}
	return false;
}

} // namespace SpookyGram
