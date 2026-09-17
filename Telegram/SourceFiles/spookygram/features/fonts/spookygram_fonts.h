#pragma once

#include <QtCore/QString>
#include "base/basic_types.h"

namespace Window {
class SessionController;
} // namespace Window

namespace Ui {
class GenericBox;
} // namespace Ui

namespace SpookyGram::Fonts {

void InitFonts();
[[nodiscard]] QString CurrentFontName();
void SetAndApplyFont(const QString &family, not_null<Window::SessionController*> controller);
void ResetToDefaultFont(not_null<Window::SessionController*> controller);
void OpenSystemFontPicker(not_null<Window::SessionController*> controller);
void InstallFontFromFile(not_null<Window::SessionController*> controller);
void OpenGoogleFontsBox(not_null<Window::SessionController*> controller);

} // namespace SpookyGram::Fonts
