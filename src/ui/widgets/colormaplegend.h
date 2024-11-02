#ifndef COLORMAPLEGEND_H
#define COLORMAPLEGEND_H

#include <QWidget>

#include "base/concepts.h"

#include "colormap.h"

namespace Gui
{
    class ColorMapLegend : public QWidget
    {
        private:
            Q_OBJECT

            ColorMap colorMap = ColorMap(0, 1);
            std::string numberFormat = "{: .2f}";

        public:
            ColorMapLegend(QWidget* parent, const ColorMap& colorMap);
            ColorMapLegend(QWidget* parent = nullptr);
            ColorMapLegend(const ColorMap& colorMap);

            const ColorMap& getColorMap() const;
            ColorMap& colorMapRef();

            std::string getNumberFormat() const;
            void setNumberFormat(const std::string& newNumberFormat);

        public slots:
            void paintEvent(QPaintEvent* paintEvent);

        private:
            void init();

            void paintBackground(QPainter& painter, const QRect& rectToUpdate);
            void paintColorBar(QPainter& painter, const QRect& rectToUpdate);
            void paintText(QPainter& painter, const QRect& rectToUpdate);
    };

}
#endif // COLORMAPLEGEND_H
