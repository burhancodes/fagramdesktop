/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fagramdesktop/fadesktop/blob/dev/LEGAL
*/
#include "fa/ui/md3/fa_top_bar.h"

#include "fa/ui/md3/svg_assets.h"
#include "ui/painter.h"
#include "ui/style/style_core_direction.h"
#include "ui/wrap/fade_wrap.h"
#include "styles/style_basic.h"
#include "styles/style_settings.h"

#include <QtSvg/QSvgRenderer>

#include <cmath>

namespace FA::Ui {
namespace {

constexpr auto kPillMarginRight = 12;
constexpr auto kPillMarginLeft = 12;
constexpr auto kPillPadding = 4;
constexpr auto kButtonWidth = 36;
constexpr auto kPillHeight = 36;
constexpr auto kContentSpacing = 12;

bool IsButtonVisible(const ::Ui::RpWidget *button) {
	if (!button || button->isHidden()) {
		return false;
	}
	if (const auto fade = dynamic_cast<const ::Ui::FadeWrap<::Ui::RpWidget>*>(button)) {
		return fade->toggled() || (fade->animating() && fade->width() > 0);
	}
	return button->width() > 0;
}

QImage PrepareMaterialShapeImage(int size, QColor color, float64 ratio) {
	const auto deviceSize = QSize(
		int(std::round(size * ratio)),
		int(std::round(size * ratio)));
	auto result = QImage(deviceSize, QImage::Format_ARGB32_Premultiplied);
	result.fill(Qt::transparent);

	auto svg = QSvgRenderer(QByteArray::fromRawData(
		fa::svg::material_shape2.data(),
		fa::svg::material_shape2.size()));

	const auto margin = float(deviceSize.width()) * 0.04f;
	const auto targetRect = QRectF(
		margin,
		margin,
		deviceSize.width() - 2 * margin,
		deviceSize.height() - 2 * margin);

	QPainter p(&result);
	p.setRenderHint(QPainter::Antialiasing);
	svg.render(&p, targetRect);
	p.setCompositionMode(QPainter::CompositionMode_SourceIn);
	p.fillRect(result.rect(), color);
	p.end();

	result.setDevicePixelRatio(ratio);
	return result;
}

void PaintMaterialShape(
		QPainter &p,
		const QRectF &targetRect,
		QColor color,
		float64 opacity) {
	if (opacity <= 0.) {
		return;
	}
	const auto size = int(std::round(targetRect.width()));
	const auto ratio = style::DevicePixelRatio();

	struct Cache {
		QColor color;
		int size = 0;
		float64 ratio = 0.;
		QImage image;
	};
	static auto cache = Cache();
	if (cache.color != color || cache.size != size || cache.ratio != ratio) {
		cache = { color, size, ratio, PrepareMaterialShapeImage(size, color, ratio) };
	}

	const auto prevOpacity = p.opacity();
	if (opacity < 1.0) {
		p.setOpacity(prevOpacity * opacity);
	}
	p.drawImage(targetRect, cache.image);
	if (opacity < 1.0) {
		p.setOpacity(prevOpacity);
	}
}

} // namespace

int TopBarBackPillSkip() {
	return kPillMarginLeft + kButtonWidth + kContentSpacing;
}

int LayoutTopBarBackButton(
		int newWidth,
		int topBarHeight,
		::Ui::RpWidget *backButton) {
	if (!IsButtonVisible(backButton)) {
		if (backButton) {
			backButton->setGeometryToLeft(
				kPillMarginLeft,
				(topBarHeight - kPillHeight) / 2,
				0,
				kPillHeight,
				newWidth);
		}
		return 0;
	}
	const auto pillTop = (topBarHeight - kPillHeight) / 2;

	backButton->setGeometryToLeft(
		kPillMarginLeft,
		pillTop,
		kButtonWidth,
		kPillHeight,
		newWidth);
	if (const auto wrap = dynamic_cast<::Ui::Wrap<::Ui::RpWidget>*>(backButton)) {
		if (const auto wrapped = wrap->wrapped()) {
			wrapped->setGeometry(0, 0, kButtonWidth, kPillHeight);
		}
	}
	return TopBarBackPillSkip();
}

int LayoutTopBarPillButtons(
		int newWidth,
		int topBarHeight,
		const std::vector<base::unique_qptr<::Ui::RpWidget>> &buttons) {
	auto visibleButtonsCount = 0;
	for (const auto &button : buttons) {
		if (IsButtonVisible(button.get())) {
			++visibleButtonsCount;
		}
	}
	const auto pillTop = (topBarHeight - kPillHeight) / 2;
	const auto totalPillWidth = (visibleButtonsCount > 0)
		? (visibleButtonsCount * kButtonWidth + kPillPadding * 2)
		: 0;

	auto currentRight = kPillMarginRight + kPillPadding;
	for (const auto &button : buttons) {
		if (!button) {
			continue;
		}
		if (IsButtonVisible(button.get())) {
			button->setGeometryToRight(
				currentRight,
				pillTop,
				kButtonWidth,
				kPillHeight,
				newWidth);
			if (const auto wrap = dynamic_cast<::Ui::Wrap<::Ui::RpWidget>*>(button.get())) {
				if (const auto wrapped = wrap->wrapped()) {
					wrapped->setGeometry(0, 0, kButtonWidth, kPillHeight);
				}
			}
			currentRight += kButtonWidth;
		} else {
			button->setGeometryToRight(
				kPillMarginRight,
				pillTop,
				0,
				kPillHeight,
				newWidth);
		}
	}
	return (visibleButtonsCount > 0)
		? (kPillMarginRight + totalPillWidth + kContentSpacing)
		: 0;
}

void PaintTopBarPill(
		QPainter &p,
		int widgetWidth,
		int topBarHeight,
		const std::vector<base::unique_qptr<::Ui::RpWidget>> &buttons,
		const ::Ui::RpWidget *backButton,
		bool searchModeEnabled,
		bool selectionMode) {
	if (selectionMode) {
		return;
	}

	const auto rtl = style::RightToLeft();
	const auto pillTop = (topBarHeight - kPillHeight) / 2;

	if (IsButtonVisible(backButton)) {
		const auto fade = dynamic_cast<const ::Ui::FadeWrap<::Ui::RpWidget>*>(backButton);
		const auto opacity = fade ? fade->shownProgress() : 1.0;
		if (opacity > 0.) {
			const auto backLeft = rtl
				? (widgetWidth - kPillMarginLeft - kButtonWidth)
				: kPillMarginLeft;
			const auto backRect = QRectF(
				backLeft,
				pillTop,
				kButtonWidth,
				kPillHeight);

			PaintMaterialShape(
				p,
				backRect,
				st::settingsThemeNotSupportedBg->c,
				opacity);
		}
	}

	if (!searchModeEnabled) {
		auto visibleButtonsCount = 0;
		for (const auto &button : buttons) {
			if (IsButtonVisible(button.get())) {
				++visibleButtonsCount;
			}
		}
		if (visibleButtonsCount > 0) {
			const auto totalPillWidth = visibleButtonsCount * kButtonWidth + kPillPadding * 2;
			const auto rightPillLeft = rtl
				? kPillMarginRight
				: (widgetWidth - kPillMarginRight - totalPillWidth);
			const auto rightPillRect = QRectF(
				rightPillLeft,
				pillTop,
				totalPillWidth,
				kPillHeight);

			PainterHighQualityEnabler hq(p);
			p.setPen(Qt::NoPen);
			p.setBrush(st::settingsThemeNotSupportedBg);
			p.drawRoundedRect(rightPillRect, kPillHeight / 2.0, kPillHeight / 2.0);
		}
	}
}

} // namespace FA::Ui
