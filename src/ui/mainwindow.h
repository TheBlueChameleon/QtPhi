#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui/widgets/colormaplegend.h"

namespace Gui
{
    class MainWindow : public QMainWindow
    {
        private:
            Q_OBJECT

            ColorMap* cmap;
            ColorMapLegend* cmapLegend;

        public:
            explicit MainWindow(QWidget* parent = nullptr);
            ~MainWindow();

        signals:
    };
}

#endif // MAINWINDOW_H
