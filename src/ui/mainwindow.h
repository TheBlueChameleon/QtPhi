#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "base/grid/basegrid.h"

#include "ui/widgets/gridsview.h"

namespace Gui
{
    class MainWindow : public QMainWindow
    {
        private:
            Q_OBJECT

            Base::BaseGrid<Base::Scalar> tilesGrid;
            Base::BaseGrid<Base::Scalar> dotsGrid;
            Base::BaseGrid<Base::Vector> arrowGrid;

            GridsView* gridsView;

        public:
            explicit MainWindow(QWidget* parent = nullptr);
            ~MainWindow();

        signals:
    };
}

#endif // MAINWINDOW_H
