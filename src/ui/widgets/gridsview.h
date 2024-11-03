#ifndef GRIDSVIEW_H
#define GRIDSVIEW_H

#include <QGraphicsView>
#include <QHBoxLayout>
#include <QWidget>

#include "base/concepts.h"
#include "base/grid/gridimpl.h"

#include "ui/colormap/lerpcolormap.h"

#include "colormaplegend.h"

namespace Gui
{
    class GridsView : public QWidget
    {
        public:
            template<Base::ScalarOrVector T>
            class BaseGrid;

            using ScalarGrid = Base::GridImpl<Base::Scalar>;
            using VectorGrid = Base::GridImpl<Base::Vector>;

        private:
            Q_OBJECT

            const ScalarGrid* tilesGrid = nullptr;
            const ScalarGrid* dotsGrid = nullptr;
            const VectorGrid* arrowsGrid = nullptr;

            QHBoxLayout* mainLayout;
            QVBoxLayout* legendsLayout;

            QGraphicsScene* scene;
            QGraphicsView* gfxView;

            QWidget* legendsSpace;
            ColorMap* tilesMap = nullptr;
            ColorMapLegend* tilesLegend = nullptr;
            ColorMap* dotsMap = nullptr;
            ColorMapLegend* dotsLegend = nullptr;
            ColorMap* arrowsMap = nullptr;
            ColorMapLegend* arrowsLegend = nullptr;

        public:
            explicit GridsView(QWidget* parent = nullptr);
            ~GridsView();

            void setTilesGrid(const  ScalarGrid* tilesGrid, const  std::string& title);
            void setDotsGrid(const   ScalarGrid* dotsGrid, const   std::string& title);
            void setArrowsGrid(const VectorGrid* arrowsGrid, const std::string& title);

        signals:

        private:
            enum class Component {Tiles, Dots, Arrows};

            void update(const Base::Grid* grid, const Component component, const std::string& title);
            LerpColorMap::ColorScheme colorSchemeForComponent(const Component component);

            void updateScene();
            void updateSceneTiles();
            void updateSceneDots();
            void updateSceneArrows();

            void updateLegend(const Base::Grid* grid, ColorMapLegend*& legend, ColorMap*& map, const Component component, const std::string& title);
            void addLegend(const Base::Grid* grid, ColorMapLegend*& legend, ColorMap*& map, const Component component, const std::string& title);
            void removeLegend(ColorMapLegend*& legend, ColorMap*& map);
    };
}

#endif // GRIDSVIEW_H
