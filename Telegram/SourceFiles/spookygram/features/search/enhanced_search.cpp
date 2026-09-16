#include "spookygram/features/search/enhanced_search.h"

namespace SpookyGram {

std::vector<SearchFilterOption> EnhancedSearch::AvailablePresets() {
	return {
		{ SearchFilterPreset::All, u"All"_q, QString() },
		{ SearchFilterPreset::Media, u"Media"_q, u"#media "_q },
		{ SearchFilterPreset::Links, u"Links"_q, u"#links "_q },
		{ SearchFilterPreset::Files, u"Files"_q, u"#files "_q },
		{ SearchFilterPreset::Audio, u"Music"_q, u"#audio "_q },
		{ SearchFilterPreset::Voice, u"Voice"_q, u"#voice "_q },
		{ SearchFilterPreset::Replies, u"Replies"_q, u"#replies "_q },
	};
}

QString EnhancedSearch::ApplyPresetToQuery(SearchFilterPreset preset, const QString &query) {
	for (const auto &opt : AvailablePresets()) {
		if (opt.preset == preset) {
			if (!opt.queryPrefix.isEmpty() && !query.startsWith(opt.queryPrefix)) {
				return opt.queryPrefix + query;
			}
			break;
		}
	}
	return query;
}

} // namespace SpookyGram
