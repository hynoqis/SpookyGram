#include "spookygram/settings/spookygram_settings_box.h"
#include "spookygram/core/spookygram_settings.h"
#include "spookygram/features/bookmarks/bookmarks_box.h"
#include "spookygram/features/bookmarks/bookmarks_storage.h"
#include "spookygram/features/fonts/spookygram_fonts.h"
#include "spookygram/ai/ai_manager.h"

#include "ui/widgets/checkbox.h"
#include "ui/widgets/buttons.h"
#include "ui/widgets/labels.h"
#include "ui/vertical_list.h"
#include "ui/ui_utility.h"
#include "ui/toast/toast.h"
#include "styles/style_boxes.h"
#include "styles/style_layers.h"
#include "styles/style_settings.h"
#include "lang/lang_keys.h"
#include "window/window_session_controller.h"
#include <rpl/rpl.h>

namespace SpookyGram {

void SpookyGramSettingsBox(
		not_null<Ui::GenericBox*> box,
		not_null<Window::SessionController*> controller) {
	box->setTitle(u"Настройки SpookyGram"_q);

	auto &cfg = Config();
	const auto content = box->verticalLayout();

	const auto addHeader = [&](const QString &title) {
		Ui::AddSkip(content);
		Ui::AddSubsectionTitle(content, rpl::single(title), st::boxRowPadding);
	};

	const auto addSectionDivider = [&] {
		Ui::AddSkip(content);
		Ui::AddDivider(content);
		Ui::AddSkip(content);
	};

	const auto addBoxCheckbox = [&](
			const QString &text,
			bool current,
			auto onChange) {
		const auto cb = content->add(
			object_ptr<Ui::Checkbox>(
				content,
				text,
				current,
				st::defaultBoxCheckbox),
			st::boxRowPadding);
		cb->setAllowTextLines(0);
		cb->setCheckAlignment(style::al_top);
		cb->checkedChanges(
		) | rpl::on_next(std::move(onChange), content->lifetime());
		return cb;
	};

	// 1. Внешний вид
	addHeader(u"Внешний вид"_q);
	addBoxCheckbox(
		u"Компактный режим (уменьшенные отступы в списке чатов и сообщений)"_q,
		cfg.compactMode(),
		[&](bool checked) { cfg.setCompactMode(checked); });

	content->add(
		object_ptr<Ui::FlatLabel>(
			content,
			u"Фирменная тема: Spooky Dark с глубоким фиолетовым акцентом (#7b42f6)."_q,
			st::boxLabel),
		st::boxRowPadding);

	// 2. Шрифты и оформление
	addSectionDivider();
	addHeader(u"Шрифты и типографика"_q);

	content->add(
		object_ptr<Ui::FlatLabel>(
			content,
			u"Текущий шрифт: "_q + Fonts::CurrentFontName(),
			st::boxLabel),
		st::boxRowPadding);

	const auto openFontPickerBtn = content->add(
		object_ptr<Ui::RoundButton>(
			content,
			rpl::single(u"Выбрать из системных шрифтов..."_q),
			st::defaultActiveButton),
		st::boxRowPadding);
	openFontPickerBtn->setClickedCallback([=] {
		Fonts::OpenSystemFontPicker(controller);
	});

	const auto openGoogleFontsBtn = content->add(
		object_ptr<Ui::RoundButton>(
			content,
			rpl::single(u"Каталог Google Fonts..."_q),
			st::defaultLightButton),
		st::boxRowPadding);
	openGoogleFontsBtn->setClickedCallback([=] {
		Fonts::OpenGoogleFontsBox(controller);
	});

	const auto installFontFileBtn = content->add(
		object_ptr<Ui::RoundButton>(
			content,
			rpl::single(u"Установить шрифт из файла (.ttf, .otf)..."_q),
			st::defaultLightButton),
		st::boxRowPadding);
	installFontFileBtn->setClickedCallback([=] {
		Fonts::InstallFontFromFile(controller);
	});

	if (Fonts::CurrentFontName() != u"По умолчанию (системный)"_q) {
		const auto resetFontBtn = content->add(
			object_ptr<Ui::RoundButton>(
				content,
				rpl::single(u"Сбросить шрифт на стандартный"_q),
				st::defaultBoxButton),
			st::boxRowPadding);
		resetFontBtn->setClickedCallback([=] {
			Fonts::ResetToDefaultFont(controller);
		});
	}

	// 3. Быстрые действия
	addSectionDivider();
	addHeader(u"Быстрые действия (ПКМ по сообщению)"_q);
	content->add(
		object_ptr<Ui::FlatLabel>(
			content,
			u"Выберите действия для контекстного меню сообщений:"_q,
			st::boxLabel),
		st::boxRowPadding);

	const auto addActionToggle = [&](const QString &label, bool current, auto setter) {
		addBoxCheckbox(label, current, [&cfg, setter](bool checked) {
			(cfg.*setter)(checked);
		});
	};

	addActionToggle(u"Копировать чистый текст (без скрытых ссылок и мусора)"_q, cfg.quickActionCopyClean(), &Settings::setQuickActionCopyClean);
	addActionToggle(u"Копировать ID сообщения"_q, cfg.quickActionCopyId(), &Settings::setQuickActionCopyId);
	addActionToggle(u"Копировать ссылку на сообщение"_q, cfg.quickActionCopyLink(), &Settings::setQuickActionCopyLink);
	addActionToggle(u"Открыть профиль автора сообщения"_q, cfg.quickActionSenderProfile(), &Settings::setQuickActionSenderProfile);
	addActionToggle(u"Сохранить в закладки SpookyGram"_q, cfg.quickActionSaveBookmark(), &Settings::setQuickActionSaveBookmark);
	addActionToggle(u"Быстрая пересылка сообщения"_q, cfg.quickActionResend(), &Settings::setQuickActionResend);

	// 4. Горячие клавиши
	addSectionDivider();
	addHeader(u"Горячие клавиши"_q);
	content->add(
		object_ptr<Ui::FlatLabel>(
			content,
			u"Настроенные быстрые комбинации клавиш:\n"
			u" \u2022 Быстрый поиск: Ctrl+Shift+F\n"
			u" \u2022 Открыть закладки: Ctrl+Shift+B\n"
			u" \u2022 Настройки SpookyGram: Ctrl+Shift+S\n"
			u" \u2022 Переключить компактный режим: Ctrl+Shift+C"_q,
			st::boxLabel),
		st::boxRowPadding);

	// 5. Конфиденциальность
	addSectionDivider();
	addHeader(u"Конфиденциальность"_q);

	addBoxCheckbox(
		u"👻 Режим призрака (не отмечать сообщения как прочитанные)"_q,
		cfg.ghostMode(),
		[&](bool checked) { cfg.setGhostMode(checked); });

	addBoxCheckbox(
		u"🗑️ Anti-Delete (сохранять удалённые собеседником сообщения)"_q,
		cfg.antiDeleteEnabled(),
		[&](bool checked) { cfg.setAntiDeleteEnabled(checked); });

	addBoxCheckbox(
		u"Скрывать текст сообщений во всплывающих уведомлениях"_q,
		cfg.hidePreviewInNotifications(),
		[&](bool checked) { cfg.setHidePreviewInNotifications(checked); });

	addBoxCheckbox(
		u"Скрывать содержимое чатов при сворачивании или потере фокуса"_q,
		cfg.hideOnMinimize(),
		[&](bool checked) { cfg.setHideOnMinimize(checked); });

	addBoxCheckbox(
		u"Автоматически очищать историю действий SpookyGram при выходе"_q,
		cfg.autoClearHistory(),
		[&](bool checked) { cfg.setAutoClearHistory(checked); });

	// 6. Закладки
	addSectionDivider();
	addHeader(u"Локальные закладки"_q);
	const auto count = Bookmarks().listBookmarks().size();
	content->add(
		object_ptr<Ui::FlatLabel>(
			content,
			u"Всего сохранено закладок: "_q + QString::number(count),
			st::boxLabel),
		st::boxRowPadding);

	const auto openBookmarksBtn = content->add(
		object_ptr<Ui::RoundButton>(
			content,
			rpl::single(u"Открыть менеджер закладок"_q),
			st::defaultActiveButton),
		st::boxRowPadding);
	openBookmarksBtn->setClickedCallback([=] {
		controller->show(Box(BookmarksBox, controller));
	});

	// 7. Искусственный интеллект
	addSectionDivider();
	addHeader(u"Искусственный интеллект (AI)"_q);
	content->add(
		object_ptr<Ui::FlatLabel>(
			content,
			u"Провайдер: "_q + AI()->name() + u"\n"
			u"Архитектура подготовлена для подключения OpenAI и локальных моделей."_q,
			st::boxLabel),
		st::boxRowPadding);

	const auto testAiBtn = content->add(
		object_ptr<Ui::RoundButton>(
			content,
			rpl::single(u"Проверить работу AI (тестовый запрос)"_q),
			st::defaultLightButton),
		st::boxRowPadding);
	testAiBtn->setClickedCallback([=] {
		AI()->summarize(
			u"SpookyGram — кастомизированный клиент Telegram Desktop с тёмно-фиолетовой темой и локальными улучшениями продуктивности."_q,
			[=](QString result) {
				Ui::Toast::Show(result);
			});
	});

	// 8. Экспериментальные функции
	addSectionDivider();
	addHeader(u"Экспериментальные функции"_q);
	content->add(
		object_ptr<Ui::FlatLabel>(
			content,
			u"Умные правила фильтрации папок и быстрый контекстный тулбар активны локально."_q,
			st::boxLabel),
		st::boxRowPadding);

	Ui::AddSkip(content);
	box->addButton(tr::lng_close(), [=] { box->closeBox(); });
	box->setWidth(st::boxWideWidth);
}

} // namespace SpookyGram
