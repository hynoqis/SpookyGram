#include "spookygram/settings/spookygram_settings_box.h"
#include "spookygram/core/spookygram_settings.h"
#include "spookygram/features/bookmarks/bookmarks_box.h"
#include "spookygram/features/bookmarks/bookmarks_storage.h"
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

namespace SpookyGram {

void SpookyGramSettingsBox(
		not_null<Ui::GenericBox*> box,
		not_null<Window::SessionController*> controller) {
	box->setTitle(u"SpookyGram Settings"_q);

	auto &cfg = Config();
	const auto content = box->verticalLayout();

	const auto addHeader = [&](const QString &title) {
		Ui::AddSkip(content);
		Ui::AddSubsectionTitle(content, rpl::single(title), st::boxRowPadding);
	};

	// 1. Appearance
	addHeader(u"Appearance"_q);
	const auto compactCheck = content->add(
		object_ptr<Ui::Checkbox>(
			content,
			u"Compact Mode (reduced spacing, compact chat list)"_q,
			cfg.compactMode(),
			st::defaultCheckbox),
		st::boxRowPadding);
	compactCheck->checkedChanges(
	) | rpl::start_with_next([&](bool checked) {
		cfg.setCompactMode(checked);
	}, content->lifetime());

	content->add(
		object_ptr<Ui::FlatLabel>(
			content,
			u"Active Brand Palette: Spooky Dark-First with Deep Purple Accent."_q,
			st::boxLabel),
		st::boxRowPadding);

	// 2. Behavior & Quick Actions
	addHeader(u"Behavior & Quick Actions"_q);
	content->add(
		object_ptr<Ui::FlatLabel>(
			content,
			u"Enable or disable custom actions in message context menu:"_q,
			st::boxLabel),
		st::boxRowPadding);

	const auto addActionToggle = [&](const QString &label, bool current, auto setter) {
		const auto cb = content->add(
			object_ptr<Ui::Checkbox>(content, label, current, st::defaultCheckbox),
			st::boxRowPadding);
		cb->checkedChanges() | rpl::start_with_next([&cfg, setter](bool checked) {
			(cfg.*setter)(checked);
		}, content->lifetime());
	};

	addActionToggle(u"Copy without formatting"_q, cfg.quickActionCopyClean(), &Settings::setQuickActionCopyClean);
	addActionToggle(u"Copy message ID"_q, cfg.quickActionCopyId(), &Settings::setQuickActionCopyId);
	addActionToggle(u"Copy message link"_q, cfg.quickActionCopyLink(), &Settings::setQuickActionCopyLink);
	addActionToggle(u"Open sender profile"_q, cfg.quickActionSenderProfile(), &Settings::setQuickActionSenderProfile);
	addActionToggle(u"Save to Bookmarks"_q, cfg.quickActionSaveBookmark(), &Settings::setQuickActionSaveBookmark);
	addActionToggle(u"Quick resend"_q, cfg.quickActionResend(), &Settings::setQuickActionResend);

	// 3. Hotkeys
	addHeader(u"Custom Hotkeys"_q);
	content->add(
		object_ptr<Ui::FlatLabel>(
			content,
			u"Configured keyboard shortcuts:\n"
			u"\u2022 Open Search: Ctrl+Shift+F\n"
			u"\u2022 Open Bookmarks: Ctrl+Shift+B\n"
			u"\u2022 Open SpookyGram Settings: Ctrl+Shift+S\n"
			u"\u2022 Toggle Compact Mode: Ctrl+Shift+C"_q,
			st::boxLabel),
		st::boxRowPadding);

	// 4. Privacy
	addHeader(u"Privacy"_q);
	const auto hideNotifyCheck = content->add(
		object_ptr<Ui::Checkbox>(
			content,
			u"Hide message text preview in notifications"_q,
			cfg.hidePreviewInNotifications(),
			st::defaultCheckbox),
		st::boxRowPadding);
	hideNotifyCheck->checkedChanges(
	) | rpl::start_with_next([&](bool checked) {
		cfg.setHidePreviewInNotifications(checked);
	}, content->lifetime());

	const auto hideMinCheck = content->add(
		object_ptr<Ui::Checkbox>(
			content,
			u"Hide chat contents when minimized / unfocused"_q,
			cfg.hideOnMinimize(),
			st::defaultCheckbox),
		st::boxRowPadding);
	hideMinCheck->checkedChanges(
	) | rpl::start_with_next([&](bool checked) {
		cfg.setHideOnMinimize(checked);
	}, content->lifetime());

	const auto autoClearCheck = content->add(
		object_ptr<Ui::Checkbox>(
			content,
			u"Auto-clear SpookyGram local action history on exit"_q,
			cfg.autoClearHistory(),
			st::defaultCheckbox),
		st::boxRowPadding);
	autoClearCheck->checkedChanges(
	) | rpl::start_with_next([&](bool checked) {
		cfg.setAutoClearHistory(checked);
	}, content->lifetime());

	// 5. Bookmarks
	addHeader(u"Bookmarks"_q);
	const auto count = Bookmarks().listBookmarks().size();
	content->add(
		object_ptr<Ui::FlatLabel>(
			content,
			u"Total saved bookmarks: "_q + QString::number(count),
			st::boxLabel),
		st::boxRowPadding);

	const auto openBookmarksBtn = content->add(
		object_ptr<Ui::RoundButton>(
			content,
			u"Open Bookmarks Manager"_q,
			st::defaultRoundButton),
		st::boxRowPadding);
	openBookmarksBtn->setClickedCallback([=] {
		controller->show(Box(BookmarksBox, controller));
	});

	// 6. AI Integration
	addHeader(u"AI Integration (Foundation)"_q);
	content->add(
		object_ptr<Ui::FlatLabel>(
			content,
			u"Provider: "_q + AI()->name() + u"\n"
			u"Architecture prepared for OpenAI-compatible and Local endpoints."_q,
			st::boxLabel),
		st::boxRowPadding);

	const auto testAiBtn = content->add(
		object_ptr<Ui::RoundButton>(
			content,
			u"Test AI Provider (Mock)"_q,
			st::defaultRoundButton),
		st::boxRowPadding);
	testAiBtn->setClickedCallback([=] {
		AI()->summarize(
			u"SpookyGram is a customized Telegram Desktop client featuring dark purple theme and local productivity enhancements."_q,
			[=](QString result) {
				Ui::Toast::Show(result);
			});
	});

	// 7. Experimental
	addHeader(u"Experimental"_q);
	content->add(
		object_ptr<Ui::FlatLabel>(
			content,
			u"Smart Folders and Message Context Bar are enabled locally."_q,
			st::boxLabel),
		st::boxRowPadding);

	Ui::AddSkip(content);
	box->addButton(tr::lng_close(), [=] { box->closeBox(); });
	box->setWidth(st::boxWideWidth);
}

} // namespace SpookyGram
