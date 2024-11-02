#include <iostream>

#include <QPaintEvent>
#include <QPainter>
#include <format>

#include "base/interpolation/interpolation.h"

#include "colormaplegend.h"

using namespace Base;

namespace Gui
{
    const auto xMarginLeft = 10;
    const auto yMarginTop = 10;
    const auto xMarginRight = 10;
    const auto yMarginBottom = 10;
    const auto colorBarWidth = 20;
    const auto xSpacing = 5;
    const auto xLineLength = 5;

    ColorMapLegend::ColorMapLegend(QWidget* parent, const ColorMap& colorMap):
        QWidget(parent)
    {
        init();
    }

    ColorMapLegend::ColorMapLegend(QWidget* parent):
        QWidget{parent}
    {
        init();
    }

    ColorMapLegend::ColorMapLegend(const ColorMap& colorMap):
        QWidget(nullptr), colorMap(colorMap)
    {
        init();
    }

    void ColorMapLegend::init()
    {
        this->setMinimumSize(QSize(50, 100));
        colorMap.setMin(0);
    }

    const ColorMap& ColorMapLegend::getColorMap() const
    {
        return colorMap;
    }

    ColorMap& ColorMapLegend::colorMapRef()
    {
        return colorMap;
    }

    std::string ColorMapLegend::getNumberFormat() const
    {
        return numberFormat;
    }

    void ColorMapLegend::setNumberFormat(const std::string& newNumberFormat)
    {
        numberFormat = newNumberFormat;
    }

    void ColorMapLegend::paintEvent(QPaintEvent* paintEvent)
    {
        QPainter painter(this);

        paintBackground(painter, paintEvent->rect());
        paintColorBar(painter, paintEvent->rect());
        paintText(painter, paintEvent->rect());

        QWidget::paintEvent(paintEvent);
    }

    void ColorMapLegend::paintBackground(QPainter& painter, const QRect& rectToUpdate)
    {
        QBrush brush = QBrush(QColor("white"));
        painter.setBrush(brush);
        painter.drawRect(rectToUpdate);
    }

    void ColorMapLegend::paintColorBar(QPainter& painter, const QRect& rectToUpdate)
    {
        const auto& size = this->size();
        const auto& [rMin, rMax] = colorMap.getRange();
        const auto xMin = xMarginLeft;
        const auto yMin = yMarginTop;
        const auto xMax = xMin + colorBarWidth;
        const auto yMax = size.height() - yMarginBottom;
        const auto yHalf = (yMin + yMax) / 2;

        for (auto y = std::max(yMin, rectToUpdate.top()); y < std::min(yMax, rectToUpdate.bottom()); ++y)
        {
            const auto coordinateValue =
                colorMap.crossesZero() ?
                ((y < yHalf) ?
                 Interpolation::linear(
                     y,
                     yMin, rMin,
                     yHalf, 0.
                 ) :
                 Interpolation::linear(
                     y,
                     yHalf, 0.,
                     yMax, rMax
                 ))
                :
                Interpolation::linear(
                    y,
                    yMin, rMin,
                    yMax, rMax
                );
            const auto pen = QPen(colorMap.get(coordinateValue));
            painter.setPen(pen);
            painter.drawLine(xMin, y, xMax, y);
        }
    }

    void ColorMapLegend::paintText(QPainter& painter, const QRect& rectToUpdate)
    {
        painter.setFont(QFont("Arial", 9));
        painter.setPen(QPen(QColor("black")));

        const auto xLineStart = xMarginLeft + colorBarWidth + xSpacing;
        const auto xLineEnd = xLineStart + xLineLength;
        const auto xTextStart = xLineEnd + xSpacing;
        const auto yTop = yMarginTop;
        const auto yBottom = this->size().height() - yMarginBottom - 1;
        const auto yZero = (yTop + yBottom) / 2;

        const auto vMin = colorMap.getMin();
        const auto vMax = colorMap.getMax();

        const auto textTop = std::vformat(numberFormat, std::make_format_args(vMax));
        painter.drawLine(xLineStart, yTop, xLineEnd, yTop);
        painter.drawText(xTextStart, yTop + 3, textTop.c_str());

        if (colorMap.crossesZero())
        {
            const auto zero = 0.0; // cannot use std::make_format_args with rvalue refs (i.e. number literals)
            const auto textZero = std::vformat(numberFormat, std::make_format_args(zero));
            painter.drawLine(xLineStart, yZero, xLineEnd, yZero);
            painter.drawText(xTextStart, yZero + 3, textZero.c_str());
        }

        const auto textBottom = std::vformat(numberFormat, std::make_format_args(vMin));
        painter.drawLine(xLineStart, yBottom, xLineEnd, yBottom);
        painter.drawText(xTextStart, yBottom + 3, textBottom.c_str());
    }
}
