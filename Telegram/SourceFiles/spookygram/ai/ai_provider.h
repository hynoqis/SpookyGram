#pragma once

#include <QtCore/QString>
#include <functional>

namespace SpookyGram {

class AIProvider {
public:
	virtual ~AIProvider() = default;

	[[nodiscard]] virtual QString name() const = 0;

	virtual void summarize(const QString &text, std::function<void(QString)> callback) = 0;
	virtual void explain(const QString &text, std::function<void(QString)> callback) = 0;
	virtual void translate(const QString &text, const QString &targetLang, std::function<void(QString)> callback) = 0;
	virtual void generateReply(const QString &prompt, std::function<void(QString)> callback) = 0;
	virtual void analyzeSelection(const QString &text, std::function<void(QString)> callback) = 0;
};

} // namespace SpookyGram
