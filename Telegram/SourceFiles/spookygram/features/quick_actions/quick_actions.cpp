#include "spookygram/features/quick_actions/quick_actions.h"
#include "spookygram/core/spookygram_settings.h"
#include "spookygram/features/bookmarks/bookmarks_storage.h"

#include "history/history_item.h"
#include "history/history.h"
#include "data/data_peer.h"
#include "data/data_user.h"
#include "ui/widgets/popup_menu.h"
#include "ui/toast/toast.h"
#include "window/window_session_controller.h"
#include "main/main_session.h"
#include "apiwrap.h"
#include "api/api_common.h"
#include "styles/style_menu_icons.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QClipboard>

namespace SpookyGram::QuickActions {

void AddMenuItems(
		not_null<Ui::PopupMenu*> menu,
		not_null<Window::SessionController*> controller,
		not_null<HistoryItem*> item) {
	const auto &cfg = Config();
	const auto itemId = item->fullId();
	const auto bareId = itemId.msg.bare;

	if (cfg.quickActionCopyClean() && !item->originalText().text.isEmpty()) {
		menu->addAction(u"Copy without formatting"_q, [=] {
			if (const auto current = controller->session().data().message(itemId)) {
				QGuiApplication::clipboard()->setText(current->originalText().text);
				Ui::Toast::Show(u"Text copied without formatting."_q);
			}
		}, &st::menuIconCopy);
	}

	if (cfg.quickActionCopyId()) {
		menu->addAction(u"Copy message ID"_q, [=] {
			QGuiApplication::clipboard()->setText(QString::number(bareId));
			Ui::Toast::Show(u"Message ID copied: "_q + QString::number(bareId));
		}, &st::menuIconCopy);
	}

	if (cfg.quickActionSenderProfile() && item->from()) {
		menu->addAction(u"Open sender profile"_q, [=] {
			if (const auto current = controller->session().data().message(itemId)) {
				if (const auto sender = current->from()) {
					controller->showPeerInfo(sender);
				}
			}
		}, &st::menuIconProfile);
	}

	if (cfg.quickActionSaveBookmark()) {
		menu->addAction(u"Save to SpookyGram Bookmarks"_q, [=] {
			if (const auto current = controller->session().data().message(itemId)) {
				auto bookmark = BookmarkItem();
				bookmark.peerId = current->history()->peer->id.value;
				bookmark.msgId = current->fullId().msg.bare;
				bookmark.peerName = current->history()->peer->name();
				bookmark.snippet = current->originalText().text.left(160);
				bookmark.category = u"General"_q;
				Bookmarks().addBookmark(bookmark);
				Ui::Toast::Show(u"Saved to SpookyGram Bookmarks!"_q);
			}
		}, &st::menuIconShowInFolder);
	}

	if (cfg.quickActionResend() && !item->originalText().text.isEmpty()) {
		menu->addAction(u"Quick Resend"_q, [=] {
			if (const auto current = controller->session().data().message(itemId)) {
				auto message = Api::MessageToSend(Api::SendAction(current->history()));
				message.textWithTags = current->originalText();
				current->history()->session().api().sendMessage(std::move(message));
				Ui::Toast::Show(u"Message resent."_q);
			}
		}, &st::menuIconForward);
	}
}

} // namespace SpookyGram::QuickActions
