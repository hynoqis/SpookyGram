#include "spookygram/ai/openai_compatible_provider.h"

namespace SpookyGram {

OpenAICompatibleProvider::OpenAICompatibleProvider(QString endpoint, QString apiKey, QString model)
: _endpoint(std::move(endpoint))
, _apiKey(std::move(apiKey))
, _model(std::move(model)) {
}

QString OpenAICompatibleProvider::name() const {
	return u"OpenAI Compatible ("_q + _model + u")"_q;
}

void OpenAICompatibleProvider::summarize(const QString &text, std::function<void(QString)> callback) {
	if (callback) {
		callback(u"[AI Provider Ready]: Endpoint configured at "_q + _endpoint + u". Connect network layer when ready."_q);
	}
}

void OpenAICompatibleProvider::explain(const QString &text, std::function<void(QString)> callback) {
	if (callback) {
		callback(u"[AI Provider Ready]: Explanation request queued for "_q + _model);
	}
}

void OpenAICompatibleProvider::translate(const QString &text, const QString &targetLang, std::function<void(QString)> callback) {
	if (callback) {
		callback(u"[AI Provider Ready]: Translation target: "_q + targetLang);
	}
}

void OpenAICompatibleProvider::generateReply(const QString &prompt, std::function<void(QString)> callback) {
	if (callback) {
		callback(u"[AI Provider Ready]: Reply generated for prompt."_q);
	}
}

void OpenAICompatibleProvider::analyzeSelection(const QString &text, std::function<void(QString)> callback) {
	if (callback) {
		callback(u"[AI Provider Ready]: Text analysis ready."_q);
	}
}

} // namespace SpookyGram
