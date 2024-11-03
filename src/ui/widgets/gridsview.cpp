#include <string>

#include "base/errors.h"

#include "gridsview.h"

using namespace std::string_literals;
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

    void GridsView::setTilesGrid(const ScalarGrid* newTilesGrid, const std::string& title)
    {
        tilesGrid = newTilesGrid;
        update(newTilesGrid, Component::Tiles, title);
    }

    void GridsView::setDotsGrid(const ScalarGrid* newDotsGrid, const std::string& title)
    {
        dotsGrid = newDotsGrid;
        update(newDotsGrid, Component::Dots, title);
    }

    void GridsView::setArrowsGrid(const VectorGrid* newArrowsGrid, const std::string& title)
    {
        arrowsGrid = newArrowsGrid;
        update(newArrowsGrid, Component::Arrows, title);
    }

    void GridsView::update(const Grid* grid, const Component component, const std::string& title)
    {
        switch (component)
        {
            case Component::Tiles:
                updateLegend(grid, tilesLegend, tilesMap, component, title);
                break;
            case Component::Dots:
                updateLegend(grid, dotsLegend, dotsMap, component, title);
                break;
            case Component::Arrows:
                updateLegend(grid, arrowsLegend, arrowsMap, component, title);
                break;
            default:
                throw IllegalStateError(
                    "GridsView::update: unknown handling for component type "s +
                    std::to_string(static_cast<int>(component)) +
                    " with ScalarGrid"
                );
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
            case Component::Arrows:
                return LerpColorMap::ColorScheme::blackToWhite;
            default:
                throw IllegalStateError(
                    "No ColorScheme defined for GridsView component "s +
                    std::to_string(static_cast<int>(component))
                );
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

    void GridsView::updateLegend(const Grid* grid, ColorMapLegend*& legend, ColorMap*& map, const Component component, const std::string& title)
    {
        if (grid == nullptr || legend != nullptr)
        {
            removeLegend(legend, map);
        }

        if (grid != nullptr)
        {
            addLegend(grid, legend, map, component, title);
        }
    }

    void GridsView::addLegend(const Grid* grid, ColorMapLegend*& legend, ColorMap*& map, const Component component, const std::string& title)
    {
        const auto [min, max] = grid->getAmplitudeRange();
        const auto colorScheme = colorSchemeForComponent(component);

        map = new LerpColorMap(min, max, colorScheme);
        legend = new ColorMapLegend(nullptr, map);
        legend->setTitle(title);
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
