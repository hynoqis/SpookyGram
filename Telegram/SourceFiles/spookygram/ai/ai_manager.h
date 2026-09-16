#pragma once

#include "spookygram/ai/ai_provider.h"
#include <memory>

namespace SpookyGram {

class AIManager final {
public:
	static AIManager &Instance();

	[[nodiscard]] std::shared_ptr<AIProvider> currentProvider();
};

[[nodiscard]] std::shared_ptr<AIProvider> AI();

} // namespace SpookyGram
