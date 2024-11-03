#include "gridsview.h"

using namespace Base;

namespace Gui
{
    GridsView::GridsView(QWidget* parent)
        : QWidget{parent}
    {
        mainLayout = new QHBoxLayout;
        setLayout(mainLayout);

        scene = new QGraphicsScene;
        gfxView = new QGraphicsView(scene);
        mainLayout->addWidget(gfxView);

        legendsSpace = new QWidget;
        legendsLayout = new QVBoxLayout;
        legendsSpace->setLayout(legendsLayout);
        mainLayout->addWidget(legendsSpace);
    }

    GridsView::~GridsView()
    {
        delete mainLayout;
        delete legendsLayout;

        delete legendsSpace;
        delete gfxView;
        delete scene;
    }

    void GridsView::setTilesGrid(const ScalarGrid* newTilesGrid)
    {
        tilesGrid = newTilesGrid;
        update(newTilesGrid, Component::Tiles);
    }

    void GridsView::setDotsGrid(const ScalarGrid* newDotsGrid)
    {
        dotsGrid = newDotsGrid;
        update(newDotsGrid, Component::Dots);
    }

    void GridsView::setArrowsGrid(const VectorGrid* newArrowsGrid)
    {
        arrowsGrid = newArrowsGrid;
    }

    void GridsView::update(const ScalarGrid* grid, const Component component)
    {
        switch (component)
        {
            case Component::Tiles:
                updateLegend(grid, tilesLegend, tilesMap, LerpColorMap::ColorScheme::blueToRed);
                break;
            case Component::Dots:
                updateLegend(grid, dotsLegend, dotsMap, LerpColorMap::ColorScheme::cyanToYellow);
                break;
            case Component::Arrows:
                break;
            default:
                break;
        }
    }

    void GridsView::updateLegend(const ScalarGrid* grid, ColorMapLegend*& legend, ColorMap*& map, const LerpColorMap::ColorScheme colorScheme)
    {
        if (grid == nullptr || legend != nullptr)
        {
            removeLegend(legend, map);
        }

        if (grid != nullptr)
        {
            addLegend(grid, legend, map, colorScheme);
        }
    }

    void GridsView::addLegend(const ScalarGrid* grid, ColorMapLegend*& legend, ColorMap*& map, const LerpColorMap::ColorScheme colorScheme)
    {
        const auto [min, max] = grid->getValuesRange();
        map = new LerpColorMap(min, max, colorScheme);
        legend = new ColorMapLegend(nullptr, map);
        legendsLayout->addWidget(legend);
    }

    void GridsView::removeLegend(ColorMapLegend*& legend, ColorMap*& map)
    {
        if (legend != nullptr)
        {
            legendsLayout->removeWidget(legend);
            delete legend;
            delete map;
        }

        map = nullptr;
        legend = nullptr;
    }
}
