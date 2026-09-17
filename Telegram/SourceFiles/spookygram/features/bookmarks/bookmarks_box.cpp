#include "spookygram/features/bookmarks/bookmarks_box.h"
#include "spookygram/features/bookmarks/bookmarks_storage.h"

#include "window/window_session_controller.h"
#include "main/main_session.h"
#include "data/data_session.h"
#include "data/data_peer.h"
#include "history/history.h"
#include "history/history_item.h"
#include "ui/widgets/labels.h"
#include "ui/widgets/buttons.h"
#include "ui/widgets/scroll_area.h"
#include "ui/vertical_list.h"
#include "ui/ui_utility.h"
#include "styles/style_boxes.h"
#include "styles/style_layers.h"
#include "styles/style_settings.h"
#include "lang/lang_keys.h"

#include <QtCore/QDateTime>

namespace SpookyGram {

void BookmarksBox(
		not_null<Ui::GenericBox*> box,
		not_null<Window::SessionController*> controller) {
	box->setTitle(u"SpookyGram Bookmarks"_q);

	const auto items = Bookmarks().listBookmarks();
	if (items.empty()) {
		box->addRow(
			object_ptr<Ui::FlatLabel>(
				box,
				u"No bookmarks saved yet. Use message context menu -> 'Save to Bookmarks' to add some."_q,
				st::boxLabel),
			st::boxRowPadding);
		box->addButton(tr::lng_close(), [=] { box->closeBox(); });
		box->setWidth(st::boxWideWidth);
		return;
	}

	for (const auto &item : items) {
		const auto row = box->addRow(
			object_ptr<Ui::VerticalLayout>(box),
			st::boxRowPadding);

		auto headerText = item.peerName;
		if (!item.category.isEmpty()) {
			headerText += u" ["_q + item.category + u"]"_q;
		}
		if (item.date > 0) {
			const auto dt = QDateTime::fromSecsSinceEpoch(item.date);
			headerText += u" \u2022 "_q + dt.toString(u"yyyy-MM-dd hh:mm"_q);
		}

		row->add(
			object_ptr<Ui::FlatLabel>(
				row,
				headerText,
				st::defaultFlatLabel));

		row->add(
			object_ptr<Ui::FlatLabel>(
				row,
				item.snippet,
				st::boxLabel));

		if (!item.note.isEmpty()) {
			row->add(
				object_ptr<Ui::FlatLabel>(
					row,
					u"Note: "_q + item.note,
					st::boxLabel));
		}

		const auto btnWrap = row->add(
			object_ptr<Ui::FixedHeightWidget>(row, st::defaultActiveButton.height));
		const auto jumpBtn = Ui::CreateChild<Ui::RoundButton>(
			btnWrap,
			rpl::single(u"Go to Message"_q),
			st::defaultActiveButton);
		jumpBtn->moveToLeft(0, 0);
		jumpBtn->setClickedCallback([=, peerId = item.peerId, msgId = item.msgId] {
			controller->showPeerHistory(PeerId(peerId), Window::SectionShow(), MsgId(msgId));
			box->closeBox();
		});

		const auto removeBtn = Ui::CreateChild<Ui::RoundButton>(
			btnWrap,
			rpl::single(u"Remove"_q),
			st::defaultLightButton);
		removeBtn->moveToLeft(jumpBtn->width() + st::defaultBoxButton.textTop, 0);
		removeBtn->setClickedCallback([=, id = item.id] {
			Bookmarks().removeBookmark(id);
			box->closeBox();
			controller->show(Box(BookmarksBox, controller));
		});

		Ui::AddSkip(row);
		Ui::AddDivider(row);
		Ui::AddSkip(row);
	}

	box->addButton(tr::lng_close(), [=] { box->closeBox(); });
	box->setWidth(st::boxWideWidth);
}

} // namespace SpookyGram
