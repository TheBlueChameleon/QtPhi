#include <QWheelEvent>
#include <iostream>
#include <string>

#include "base/interpolation/interpolation.h"
#include "base/errors.h"

#include "gridsview.h"

using namespace std::string_literals;
using namespace Base;

namespace Gui
{
    const int tileSize = 15;
    const int dotSize  = 10;

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

    void GridsView::wheelEvent(QWheelEvent* event)
    {
        // TODO: enable only if also CTRL is pressed

        const auto yRoll = event->angleDelta().y();
        if (yRoll > 0)
        {
            gfxView->scale(1.25, 1.25);
        }
        if (yRoll < 0)
        {
            gfxView->scale(0.8, 0.8);
        }

        QWidget::wheelEvent(event);
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

            scene->addRect(coord.x * tileSize, coord.y * tileSize,
                           tileSize, tileSize,
                           nullPen, brush
                          );
        }
    }

    void GridsView::updateSceneDots()
    {
        if (dotsGrid == nullptr)
        {
            return;
        }

        auto pen = QPen(Qt::SolidLine);
        pen.setWidth(0);
        const auto nullBrush = QBrush(Qt::NoBrush);

        for (const auto coord : dotsGrid->getPixelDimensions())
        {
            const auto value = dotsGrid->get(coord);
            const auto color = dotsMap->get(value);

            const auto [min, max] = dotsMap->getRange();
            const int thisDotSize =  Interpolation::linear<Real>(
                                         std::abs(value),
                                         (min < 0 ? 0: min), 0,
                                         max, dotSize
                                     );
            const int dotSpacing = (tileSize - thisDotSize) / 2;

            pen.setColor(color);

            const auto xBase = coord.x * tileSize;
            const auto yBase = coord.y * tileSize;

            if (value > 0)
            {
                scene->addLine(xBase + dotSpacing, yBase + dotSpacing,
                               xBase + tileSize - dotSpacing, yBase + tileSize - dotSpacing,
                               pen
                              );
                scene->addLine(xBase + tileSize - dotSpacing, yBase + dotSpacing,
                               xBase + dotSpacing, yBase + tileSize - dotSpacing,
                               pen
                              );
            }
            else
            {
                scene->addEllipse(xBase + dotSpacing, yBase + dotSpacing,
                                  thisDotSize, thisDotSize,
                                  pen, nullBrush
                                 );
            }
        }
    }

    void GridsView::updateSceneArrows()
    {
        if (arrowsGrid == nullptr)
        {
            return;
        }

        const auto nullBrush = QBrush(Qt::NoBrush);
        auto pen = QPen(Qt::SolidLine);


        const auto half = tileSize / 2;
        const auto [min, max] = arrowsMap->getRange();

        for (const auto coord : arrowsGrid->getPixelDimensions())
        {
            const auto value = arrowsGrid->get(coord);
            const auto length = value.length();
            if (length == 0)
            {
                continue;
            }

            const auto scale = Interpolation::linear<Real>(
                                   length,
                                   min, 0,
                                   max, tileSize / (2 * length)
                               );
            const auto width = Interpolation::linear<Real>(
                                   length,
                                   min, 0,
                                   max, 2
                               );

            const auto color = arrowsMap->get(length);

            pen.setColor(color);
            pen.setWidthF(width);

            const auto xBase = coord.x * tileSize + half;
            const auto yBase = coord.y * tileSize + half;

            scene->addLine(xBase, yBase,
                           xBase + value.x * scale, yBase + value.y * scale,
                           pen
                          );
        }
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
