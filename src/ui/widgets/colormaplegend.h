#ifndef COLORMAPLEGEND_H
#define COLORMAPLEGEND_H

#include <QWidget>

#include "base/concepts.h"

#include "ui/colormap/colormap.h"

namespace Gui
{
    class ColorMapLegend : public QWidget
    {
        private:
            Q_OBJECT

            ColorMap* colorMap = nullptr;
            std::string numberFormat = "{: .2f}";

        public:
            ColorMapLegend(QWidget* parent, ColorMap *colorMap);

            const ColorMap& getColorMap() const;
            ColorMap& colorMapRef();

            std::string getNumberFormat() const;
            void setNumberFormat(const std::string& newNumberFormat);

        public slots:
            void paintEvent(QPaintEvent* paintEvent);

        private:
            void paintBackground(QPainter& painter, const QRect& rectToUpdate);
            void paintColorBar(QPainter& painter, const QRect& rectToUpdate);
            void paintText(QPainter& painter, const QRect& rectToUpdate);
    };

}
#endif // COLORMAPLEGEND_H
