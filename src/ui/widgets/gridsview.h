#ifndef GRIDSVIEW_H
#define GRIDSVIEW_H

#include <QGraphicsView>
#include <QWidget>

#include "base/grid/basegrid.h"

namespace Gui
{
    class GridsView : public QWidget
    {
        public:
            using ScalarGrid = Base::BaseGrid<Base::Scalar>;
            using VectorGrid = Base::BaseGrid<Base::Vector>;

        private:
            Q_OBJECT

            ScalarGrid* squareColorGrid = nullptr;
            ScalarGrid* dotsGrid = nullptr;
            VectorGrid* arrowsGrid = nullptr;

            QGraphicsView* gfxView;
            QGraphicsScene* scene;

        public:
            explicit GridsView(QWidget* parent = nullptr);

        signals:
    };
}

#endif // GRIDSVIEW_H
