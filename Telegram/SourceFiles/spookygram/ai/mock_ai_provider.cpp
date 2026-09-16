#include "spookygram/ai/mock_ai_provider.h"

namespace SpookyGram {

QString MockAIProvider::name() const {
	return u"SpookyGram Mock Provider"_q;
}

void MockAIProvider::summarize(const QString &text, std::function<void(QString)> callback) {
	if (callback) {
		const auto preview = text.left(60);
		callback(u"[SpookyGram AI Summary]: Message highlights: \""_q + preview + u"...\" (Key points extracted successfully)."_q);
	}
}

void MockAIProvider::explain(const QString &text, std::function<void(QString)> callback) {
	if (callback) {
		callback(u"[SpookyGram AI Explanation]: This message discusses topic context with 1 key insight."_q);
	}
}

void MockAIProvider::translate(const QString &text, const QString &targetLang, std::function<void(QString)> callback) {
	if (callback) {
		callback(u"[SpookyGram AI Translation to "_q + targetLang + u"]: "_q + text);
	}
}

void MockAIProvider::generateReply(const QString &prompt, std::function<void(QString)> callback) {
	if (callback) {
		callback(u"[SpookyGram AI Suggested Reply]: Thanks for reaching out! I will check this shortly."_q);
	}
}

void MockAIProvider::analyzeSelection(const QString &text, std::function<void(QString)> callback) {
	if (callback) {
		callback(u"[SpookyGram AI Analysis]: Selected text length: "_q + QString::number(text.length()) + u" characters. Tone: Neutral."_q);
	}
}

} // namespace SpookyGram
