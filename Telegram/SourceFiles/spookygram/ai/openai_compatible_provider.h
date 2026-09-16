#pragma once

#include "spookygram/ai/ai_provider.h"

namespace SpookyGram {

class OpenAICompatibleProvider final : public AIProvider {
public:
	OpenAICompatibleProvider(QString endpoint, QString apiKey, QString model);

	[[nodiscard]] QString name() const override;

	void summarize(const QString &text, std::function<void(QString)> callback) override;
	void explain(const QString &text, std::function<void(QString)> callback) override;
	void translate(const QString &text, const QString &targetLang, std::function<void(QString)> callback) override;
	void generateReply(const QString &prompt, std::function<void(QString)> callback) override;
	void analyzeSelection(const QString &text, std::function<void(QString)> callback) override;

private:
	QString _endpoint;
	QString _apiKey;
	QString _model;
};

} // namespace SpookyGram
