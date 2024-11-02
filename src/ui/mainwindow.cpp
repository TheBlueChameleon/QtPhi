#include "mainwindow.h"

namespace Gui
{
    MainWindow::MainWindow(QWidget* parent)
        : QMainWindow{parent}
    {
        cmap = new ColorMapLegend();
        this->setCentralWidget(cmap);
    }

    MainWindow::~MainWindow()
    {
        delete cmap;
    }
}
