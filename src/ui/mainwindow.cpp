#include "ui/colormap/lerpcolormap.h"

#include "mainwindow.h"

using namespace Base;

namespace Gui
{
    MainWindow::MainWindow(QWidget* parent):
        QMainWindow{parent},
        tilesGrid(BaseGrid<Scalar>(PixelRect(-8, 4, 16, 8), 1.0)),
        dotsGrid(BaseGrid<Scalar>(PixelRect(-8, 4, 16, 8), 1.0)),
        arrowGrid(BaseGrid<Vector>(PixelRect(-8, 4, 16, 8), 1.0))
    {
        for (const auto point: tilesGrid.getPixelDimensions())
        {
            tilesGrid[point] = point.length() - 7;
            dotsGrid[point] = point.length();
            arrowGrid[point] = point.toRealCoordinate(1.0);
        }

        gridsView = new GridsView;
        this->setCentralWidget(gridsView);
        gridsView->setTilesGrid(&tilesGrid);
        gridsView->setDotsGrid(&dotsGrid);
    }

    MainWindow::~MainWindow()
    {
        delete gridsView;
    }
}
