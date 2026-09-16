#include "spookygram/ai/ai_manager.h"
#include "spookygram/ai/mock_ai_provider.h"
#include "spookygram/ai/openai_compatible_provider.h"
#include "spookygram/core/spookygram_settings.h"

namespace SpookyGram {

AIManager &AIManager::Instance() {
	static auto instance = AIManager();
	return instance;
}

std::shared_ptr<AIProvider> AIManager::currentProvider() {
	const auto &cfg = Config();
	const auto type = cfg.aiProviderType();
	if (type == u"openai"_q || type == u"local"_q) {
		return std::make_shared<OpenAICompatibleProvider>(
			cfg.aiEndpoint(),
			cfg.aiApiKey(),
			cfg.aiModel());
	}
	return std::make_shared<MockAIProvider>();
}

std::shared_ptr<AIProvider> AI() {
	return AIManager::Instance().currentProvider();
}

} // namespace SpookyGram
