#pragma once

#include <QtGui/QColor>

namespace SpookyGram::Style {

inline constexpr auto kBrandName = "SpookyGram";

// Core brand palette for SpookyGram (deep purple #7b42f6)
inline const auto kDarkBg = QColor(0x0e, 0x0d, 0x14);
inline const auto kDarkSurface = QColor(0x13, 0x12, 0x1b);
inline const auto kDarkSurfaceOver = QColor(0x1a, 0x18, 0x24);
inline const auto kPurplePrimary = QColor(0x7b, 0x42, 0xf6);
inline const auto kPurpleLight = QColor(0x8b, 0x5c, 0xf6);
inline const auto kPurpleDark = QColor(0x5b, 0x21, 0xb6);
inline const auto kCoolBlue = QColor(0x38, 0xbd, 0xf8);
inline const auto kWineBurgundy = QColor(0x83, 0x18, 0x43);
inline const auto kTextPrimary = QColor(0xf3, 0xf4, 0xf6);
inline const auto kTextSecondary = QColor(0x9c, 0xa3, 0xaf);

} // namespace SpookyGram::Style
