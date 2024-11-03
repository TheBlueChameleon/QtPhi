#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "base/grid/gridimpl.h"

#include "ui/widgets/gridsview.h"

namespace Gui
{
    class MainWindow : public QMainWindow
    {
        private:
            Q_OBJECT

            Base::GridImpl<Base::Scalar> tilesGrid;
            Base::GridImpl<Base::Scalar> dotsGrid;
            Base::GridImpl<Base::Vector> arrowGrid;

            GridsView* gridsView;

        public:
            explicit MainWindow(QWidget* parent = nullptr);
            ~MainWindow();

        signals:
    };
}

#endif // MAINWINDOW_H
