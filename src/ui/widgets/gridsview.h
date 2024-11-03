#ifndef GRIDSVIEW_H
#define GRIDSVIEW_H

#include <QGraphicsView>
#include <QHBoxLayout>
#include <QWidget>

#include "base/concepts.h"
#include "base/grid/basegrid.h"

#include "ui/colormap/lerpcolormap.h"

#include "colormaplegend.h"

namespace Gui
{
    class GridsView : public QWidget
    {
        public:
            template<Base::ScalarOrVector T>
            class BaseGrid;

            using ScalarGrid = Base::BaseGrid<Base::Scalar>;
            using VectorGrid = Base::BaseGrid<Base::Vector>;

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

        public:
            explicit GridsView(QWidget* parent = nullptr);
            ~GridsView();

            void setTilesGrid(const  ScalarGrid* tilesGrid);
            void setDotsGrid(const   ScalarGrid* dotsGrid);
            void setArrowsGrid(const VectorGrid* arrowsGrid);

        signals:

        private:
            enum class Component {Tiles, Dots, Arrows};

            void update(const ScalarGrid* grid, const Component component);
            LerpColorMap::ColorScheme colorSchemeForComponent(const Component component);

            void updateScene();
            void updateSceneTiles();
            void updateSceneDots();
            void updateSceneArrows();

            void updateLegend(const ScalarGrid* grid, ColorMapLegend*& legend, ColorMap*& map, const Component component);
            void addLegend(const ScalarGrid* grid, ColorMapLegend*& legend, ColorMap*& map, const Component component);
            void removeLegend(ColorMapLegend*& legend, ColorMap*& map);
    };
}

#endif // GRIDSVIEW_H
