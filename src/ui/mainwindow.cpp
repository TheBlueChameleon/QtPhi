#include "ui/colormap/lerpcolormap.h"

#include "mainwindow.h"

using namespace Base;

namespace Gui
{
    MainWindow::MainWindow(QWidget* parent):
        QMainWindow{parent},
        tilesGrid(GridImpl<Scalar>(PixelRect(-16, -8, 32, 16), 1.0)),
        dotsGrid(GridImpl<Scalar>(PixelRect(-16, -8, 32, 16), 1.0)),
        arrowGrid(GridImpl<Vector>(PixelRect(-16, -8, 32, 16), 1.0))
    {
        for (const auto point: tilesGrid.getPixelDimensions())
        {
            tilesGrid[point] = point.length() - 4;
            dotsGrid[point] = point.length() * (point.x > 0 ? 1 : -1);
            arrowGrid[point] = point.toRealCoordinate(1.0);
        }

        gridsView = new GridsView;
        this->setCentralWidget(gridsView);
        gridsView->setTilesGrid(&tilesGrid, "E");
        gridsView->setDotsGrid(&dotsGrid, "B");
        gridsView->setArrowsGrid(&arrowGrid, "F");
    }

    MainWindow::~MainWindow()
    {
        delete gridsView;
    }
}
