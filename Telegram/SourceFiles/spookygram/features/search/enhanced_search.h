#pragma once

#include <QtCore/QString>
#include <vector>

namespace SpookyGram {

enum class SearchFilterPreset {
	All,
	Media,
	Links,
	Files,
	Audio,
	Voice,
	Replies,
};

struct SearchFilterOption final {
	SearchFilterPreset preset = SearchFilterPreset::All;
	QString title;
	QString queryPrefix;
};

class EnhancedSearch final {
public:
	static std::vector<SearchFilterOption> AvailablePresets();
	static QString ApplyPresetToQuery(SearchFilterPreset preset, const QString &query);
};

} // namespace SpookyGram
