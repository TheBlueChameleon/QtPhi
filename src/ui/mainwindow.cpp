#include "ui/colormap/lerpcolormap.h"

#include "mainwindow.h"

namespace Gui
{
    MainWindow::MainWindow(QWidget* parent)
        : QMainWindow{parent}
    {
        cmap = new LerpColorMap(-2, 3, LerpColorMap::ColorScheme::blueToRed);
        cmapLegend = new ColorMapLegend(nullptr, cmap);
        this->setCentralWidget(cmapLegend);
    }

    MainWindow::~MainWindow()
    {
        delete cmapLegend;
        delete cmap;
    }
}
