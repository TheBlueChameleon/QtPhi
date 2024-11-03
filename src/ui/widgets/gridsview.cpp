#include "base/errors.h"

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
                updateLegend(grid, tilesLegend, tilesMap, component);
                break;
            case Component::Dots:
                updateLegend(grid, dotsLegend, dotsMap, component);
                break;
            case Component::Arrows:
                break;
            default:
                break;
        }

        updateScene();
    }

    LerpColorMap::ColorScheme GridsView::colorSchemeForComponent(const Component component)
    {
        switch (component)
        {
            case Component::Tiles:
                return LerpColorMap::ColorScheme::blueToRed;
            case Component::Dots:
                return LerpColorMap::ColorScheme::cyanToYellow;
            default:
                throw IllegalStateError("No ColorScheme defined for GridsView component");
        }
    }

    void GridsView::updateScene()
    {
        scene->clear();
        updateSceneTiles();
        updateSceneDots();
        updateSceneArrows();
    }

    void GridsView::updateSceneTiles()
    {
        if (tilesGrid == nullptr)
        {
            return;
        }

        const auto nullPen = QPen(Qt::NoPen);
        auto brush = QBrush(Qt::SolidPattern);

        for (const auto coord : tilesGrid->getPixelDimensions())
        {
            const auto value = tilesGrid->get(coord);
            const auto color = tilesMap->get(value);
            brush.setColor(color);

            scene->addRect(coord.x * 10, coord.y * 10, 10, 10, nullPen, brush);
        }
    }

    void GridsView::updateSceneDots()
    {

    }

    void GridsView::updateSceneArrows()
    {

    }

    void GridsView::updateLegend(const ScalarGrid* grid, ColorMapLegend*& legend, ColorMap*& map, const Component component)
    {
        if (grid == nullptr || legend != nullptr)
        {
            removeLegend(legend, map);
        }

        if (grid != nullptr)
        {
            addLegend(grid, legend, map, component);
        }
    }

    void GridsView::addLegend(const ScalarGrid* grid, ColorMapLegend*& legend, ColorMap*& map, const Component component)
    {
        const auto [min, max] = grid->getValuesRange();
        const auto colorScheme = colorSchemeForComponent(component);

        map = new LerpColorMap(min, max, colorScheme);
        legend = new ColorMapLegend(nullptr, map);
        switch (component)
        {
            case Component::Tiles:
                legend->setTitle("El. Potential");
                break;
            case Component::Dots:
                legend->setTitle("Magnetic Field");
                break;
        }
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
