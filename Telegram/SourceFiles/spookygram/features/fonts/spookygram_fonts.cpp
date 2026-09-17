#include "spookygram/features/fonts/spookygram_fonts.h"

#include "core/application.h"
#include "core/core_settings.h"
#include "core/file_utilities.h"
#include "storage/localstorage.h"
#include "window/window_session_controller.h"
#include "window/themes/window_theme.h"
#include "window/section_widget.h"
#include "ui/boxes/choose_font_box.h"
#include "ui/boxes/confirm_box.h"
#include "ui/layers/generic_box.h"
#include "ui/widgets/buttons.h"
#include "ui/widgets/fields/input_field.h"
#include "ui/widgets/labels.h"
#include "ui/widgets/scroll_area.h"
#include "ui/vertical_list.h"
#include "ui/toast/toast.h"
#include "ui/chat/chat_theme.h"
#include "ui/painter.h"
#include "lang/lang_keys.h"
#include "styles/style_boxes.h"
#include "styles/style_layers.h"
#include "styles/style_settings.h"

#include <QtGui/QFontDatabase>
#include <QtGui/QPainter>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

namespace SpookyGram::Fonts {
namespace {

struct GoogleFontEntry {
	QString name;
	QString category;
	QString filename;
	QString url;
};

const std::vector<GoogleFontEntry> &GetGoogleFontsList() {
	static const auto kFonts = std::vector<GoogleFontEntry>{
		{ u"Inter"_q, u"Sans-Serif (современный гротеск)"_q, u"inter.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/inter/Inter%5Bopsz%2Cwght%5D.ttf"_q },
		{ u"Roboto"_q, u"Sans-Serif (классический Android/Google)"_q, u"roboto.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/roboto/Roboto%5Bwdth%2Cwght%5D.ttf"_q },
		{ u"Montserrat"_q, u"Geometric Sans (акцентный геометрический)"_q, u"montserrat.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/montserrat/Montserrat%5Bwght%5D.ttf"_q },
		{ u"Poppins"_q, u"Geometric Sans (популярный округлый)"_q, u"poppins.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/poppins/Poppins-Regular.ttf"_q },
		{ u"JetBrains Mono"_q, u"Monospace (шрифт для программистов)"_q, u"jetbrains_mono.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/jetbrainsmono/JetBrainsMono%5Bwght%5D.ttf"_q },
		{ u"Fira Code"_q, u"Monospace (шрифт с лигатурами)"_q, u"fira_code.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/firacode/FiraCode%5Bwght%5D.ttf"_q },
		{ u"Open Sans"_q, u"Sans-Serif (нейтральный читаемый)"_q, u"open_sans.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/opensans/OpenSans%5Bwdth%2Cwght%5D.ttf"_q },
		{ u"Lato"_q, u"Sans-Serif (тёплый дружелюбный)"_q, u"lato.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/lato/Lato-Regular.ttf"_q },
		{ u"Nunito"_q, u"Rounded Sans (мягкий закругленный)"_q, u"nunito.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/nunito/Nunito%5Bwght%5D.ttf"_q },
		{ u"Rubik"_q, u"Sans-Serif (плотный с закругленными углами)"_q, u"rubik.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/rubik/Rubik%5Bwght%5D.ttf"_q },
		{ u"Comfortaa"_q, u"Display Rounded (стильный плавный)"_q, u"comfortaa.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/comfortaa/Comfortaa%5Bwght%5D.ttf"_q },
		{ u"Oswald"_q, u"Condensed Sans (узкий плакатный)"_q, u"oswald.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/oswald/Oswald%5Bwght%5D.ttf"_q },
		{ u"Raleway"_q, u"Elegant Sans (элегантный тонкий)"_q, u"raleway.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/raleway/Raleway%5Bwght%5D.ttf"_q },
		{ u"Merriweather"_q, u"Serif (удобочитаемая антиква)"_q, u"merriweather.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/merriweather/Merriweather-Regular.ttf"_q },
		{ u"Playfair Display"_q, u"Display Serif (заголовочная классика)"_q, u"playfair.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/playfairdisplay/PlayfairDisplay%5Bwght%5D.ttf"_q },
		{ u"Ubuntu"_q, u"Humanist Sans (фирменный Ubuntu)"_q, u"ubuntu.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/ubuntusans/UbuntuSans%5Bwdth%2Cwght%5D.ttf"_q },
		{ u"Caveat"_q, u"Handwriting (рукописный живой)"_q, u"caveat.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/caveat/Caveat%5Bwght%5D.ttf"_q },
		{ u"Pacifico"_q, u"Script (винтажный рукописный)"_q, u"pacifico.ttf"_q,
		  u"https://raw.githubusercontent.com/google/fonts/main/ofl/pacifico/Pacifico-Regular.ttf"_q },
	};
	return kFonts;
}

QString FontsDirectoryPath() {
	return cWorkingDir() + u"tdata/fonts"_q;
}

} // namespace

void InitFonts() {
	const auto dirPath = FontsDirectoryPath();
	const auto dir = QDir(dirPath);
	if (!dir.exists()) {
		return;
	}
	const auto files = dir.entryInfoList(
		{ u"*.ttf"_q, u"*.otf"_q, u"*.woff2"_q },
		QDir::Files);
	for (const auto &file : files) {
		QFontDatabase::addApplicationFont(file.absoluteFilePath());
	}
}

QString CurrentFontName() {
	const auto current = Core::App().settings().customFontFamily();
	if (current.isEmpty()) {
		return u"По умолчанию (системный)"_q;
	}
	return current;
}

void SetAndApplyFont(
		const QString &family,
		not_null<Window::SessionController*> controller) {
	Core::App().settings().setCustomFontFamily(family);
	Local::writeSettings();

	controller->show(Ui::MakeConfirmBox({
		.text = tr::lng_settings_need_restart(),
		.confirmed = [=] {
			Core::Restart();
		},
		.confirmText = tr::lng_settings_restart_now(),
	}));
}

void ResetToDefaultFont(not_null<Window::SessionController*> controller) {
	SetAndApplyFont(QString(), controller);
}

void OpenSystemFontPicker(not_null<Window::SessionController*> controller) {
	const auto theme = std::shared_ptr<Ui::ChatTheme>(
		Window::Theme::DefaultChatThemeOn(controller->lifetime()));
	const auto generateBg = [=] {
		const auto size = st::boxWidth;
		const auto ratio = style::DevicePixelRatio();
		auto result = QImage(
			QSize(size, size) * ratio,
			QImage::Format_ARGB32_Premultiplied);
		auto p = QPainter(&result);
		Window::SectionWidget::PaintBackground(
			p,
			theme.get(),
			QSize(size, size * 3),
			QRect(0, 0, size, size));
		p.end();

		return result;
	};

	const auto save = [=](QString chosen) {
		SetAndApplyFont(chosen, controller);
	};

	controller->show(Box(
		Ui::ChooseFontBox,
		generateBg,
		Core::App().settings().customFontFamily(),
		save));
}

void InstallFontFromFile(not_null<Window::SessionController*> controller) {
	FileDialog::GetOpenPath(
		controller->widget(),
		u"Выберите файл шрифта (.ttf, .otf)"_q,
		u"Шрифты (*.ttf *.otf)"_q,
		[=](FileDialog::OpenResult &&res) {
			if (res.paths.isEmpty()) {
				return;
			}
			const auto sourcePath = res.paths.first();
			const auto fontsDir = FontsDirectoryPath();
			QDir().mkpath(fontsDir);

			const auto fileInfo = QFileInfo(sourcePath);
			const auto destPath = fontsDir + '/' + fileInfo.fileName();
			QFile::remove(destPath);
			if (!QFile::copy(sourcePath, destPath)) {
				Ui::Toast::Show(u"Не удалось скопировать файл шрифта."_q);
				return;
			}

			const auto fontId = QFontDatabase::addApplicationFont(destPath);
			if (fontId < 0) {
				Ui::Toast::Show(u"Не удалось распознать формат шрифта."_q);
				return;
			}

			const auto families = QFontDatabase::applicationFontFamilies(fontId);
			if (families.isEmpty()) {
				Ui::Toast::Show(u"Не удалось извлечь семейство шрифта."_q);
				return;
			}

			const auto family = families.first();
			Ui::Toast::Show(u"Шрифт «%1» успешно установлен!"_q.arg(family));
			SetAndApplyFont(family, controller);
		});
}

void OpenGoogleFontsBox(not_null<Window::SessionController*> controller) {
	controller->show(Box([=](not_null<Ui::GenericBox*> box) {
		box->setTitle(u"Каталог Google Fonts"_q);

		const auto content = box->verticalLayout();
		Ui::AddSkip(content);

		const auto searchField = content->add(
			object_ptr<Ui::InputField>(
				content,
				st::defaultInputField,
				rpl::single(u"Поиск по Google Fonts..."_q)),
			st::boxRowPadding);

		Ui::AddSkip(content);
		Ui::AddDivider(content);
		Ui::AddSkip(content);

		const auto listContainer = content->add(
			object_ptr<Ui::VerticalLayout>(content));

		const auto activeFont = Core::App().settings().customFontFamily();
		const auto &fontsList = GetGoogleFontsList();

		struct RowItem {
			GoogleFontEntry entry;
			not_null<Ui::VerticalLayout*> wrap;
		};
		const auto rows = box->lifetime().make_state<std::vector<RowItem>>();

		const auto netManager = box->lifetime().make_state<QNetworkAccessManager>();

		const auto renderRows = [=](const QString &filterText) {
			const auto query = filterText.trimmed().toLower();
			for (const auto &row : *rows) {
				const auto matches = query.isEmpty()
					|| row.entry.name.toLower().contains(query)
					|| row.entry.category.toLower().contains(query);
				row.wrap->setVisible(matches);
			}
		};

		for (const auto &item : fontsList) {
			auto rowWrap = object_ptr<Ui::VerticalLayout>(listContainer);
			const auto rowPtr = listContainer->add(std::move(rowWrap));

			const auto titleLabel = rowPtr->add(
				object_ptr<Ui::FlatLabel>(
					rowPtr,
					item.name + u" — "_q + item.category,
					st::boxLabel),
				st::boxRowPadding);
			titleLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

			const auto isCurrent = (item.name.compare(activeFont, Qt::CaseInsensitive) == 0);
			const auto actionBtn = rowPtr->add(
				object_ptr<Ui::RoundButton>(
					rowPtr,
					rpl::single(isCurrent ? u"Активен"_q : u"Установить шрифт"_q),
					isCurrent ? st::defaultBoxButton : st::defaultActiveButton),
				st::boxRowPadding);

			if (!isCurrent) {
				actionBtn->setClickedCallback([=] {
					actionBtn->setText(rpl::single(u"Загрузка..."_q));
					actionBtn->setEnabled(false);

					const auto request = QNetworkRequest(QUrl(item.url));
					const auto reply = netManager->get(request);

					QObject::connect(reply, &QNetworkReply::finished, [=] {
						reply->deleteLater();
						if (reply->error() != QNetworkReply::NoError) {
							Ui::Toast::Show(u"Ошибка загрузки шрифта: "_q + reply->errorString());
							actionBtn->setText(rpl::single(u"Повторить"_q));
							actionBtn->setEnabled(true);
							return;
						}

						const auto data = reply->readAll();
						if (data.isEmpty()) {
							Ui::Toast::Show(u"Пустой ответ от сервера Google Fonts."_q);
							actionBtn->setText(rpl::single(u"Повторить"_q));
							actionBtn->setEnabled(true);
							return;
						}

						const auto fontsDir = FontsDirectoryPath();
						QDir().mkpath(fontsDir);
						const auto targetFile = fontsDir + '/' + item.filename;

						QFile file(targetFile);
						if (file.open(QIODevice::WriteOnly)) {
							file.write(data);
							file.close();
						} else {
							Ui::Toast::Show(u"Не удалось сохранить шрифт на диск."_q);
							actionBtn->setEnabled(true);
							return;
						}

						const auto fontId = QFontDatabase::addApplicationFont(targetFile);
						auto fontName = item.name;
						if (fontId >= 0) {
							const auto families = QFontDatabase::applicationFontFamilies(fontId);
							if (!families.isEmpty()) {
								fontName = families.first();
							}
						}

						box->closeBox();
						Ui::Toast::Show(u"Шрифт «%1» загружен и готов к применению!"_q.arg(fontName));
						SetAndApplyFont(fontName, controller);
					});
				});
			} else {
				actionBtn->setEnabled(false);
			}

			Ui::AddSkip(rowPtr);
			Ui::AddDivider(rowPtr);
			Ui::AddSkip(rowPtr);

			rows->push_back({ item, rowPtr });
		}

		searchField->changes(
		) | rpl::on_next([=] {
			renderRows(searchField->getLastText());
		}, searchField->lifetime());

		box->addButton(tr::lng_close(), [=] {
			box->closeBox();
		});
	}));
}

} // namespace SpookyGram::Fonts
