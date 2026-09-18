#pragma once

#include <QtCore/QString>
#include <QtGui/QKeySequence>

class QKeyEvent;

namespace Window {
class Controller;
} // namespace Window

namespace SpookyGram {

enum class HotkeyAction {
	OpenSearch,
	OpenBookmarks,
	OpenSettings,
	ToggleCompactMode,
	TogglePrivacyMode,
};

class CustomHotkeys final {
public:
	static QKeySequence GetKeySequence(HotkeyAction action);
	static void SetKeySequence(HotkeyAction action, const QString &seq);
	static bool Matches(HotkeyAction action, int key, Qt::KeyboardModifiers modifiers);
	static bool HandleKeyEvent(QKeyEvent *e, Window::Controller *window);
};

} // namespace SpookyGram
