#pragma once

#include "base/basic_types.h"

namespace Ui {
class PopupMenu;
} // namespace Ui

namespace Window {
class SessionController;
} // namespace Window

class HistoryItem;

namespace SpookyGram::QuickActions {

void AddMenuItems(
	not_null<Ui::PopupMenu*> menu,
	not_null<Window::SessionController*> controller,
	not_null<HistoryItem*> item);

} // namespace SpookyGram::QuickActions
