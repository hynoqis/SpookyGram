#pragma once

#include "spookygram/core/spookygram_settings.h"
#include "spookygram/features/bookmarks/bookmarks_storage.h"
#include "spookygram/features/compact/compact_mode.h"
#include "spookygram/features/privacy/ui_privacy.h"
#include "spookygram/features/hotkeys/custom_hotkeys.h"
#include "spookygram/features/folders/smart_folder_rules.h"
#include "spookygram/features/search/enhanced_search.h"
#include "spookygram/ai/ai_manager.h"

namespace SpookyGram {

class Facade final {
public:
	static void Initialize();
	static void Deinitialize();
};

} // namespace SpookyGram
