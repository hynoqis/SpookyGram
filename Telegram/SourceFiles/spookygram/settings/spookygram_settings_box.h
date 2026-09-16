#pragma once

#include "ui/layers/generic_box.h"

namespace Window {
class SessionController;
} // namespace Window

namespace SpookyGram {

void SpookyGramSettingsBox(
	not_null<Ui::GenericBox*> box,
	not_null<Window::SessionController*> controller);

} // namespace SpookyGram
