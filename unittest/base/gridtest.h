#ifndef GRIDTEST_H
#define GRIDTEST_H

#include <QObject>
#include <QTest>

class GridTest : public QObject
{
        Q_OBJECT

    private slots:
        void ctor();
        void getDimensionData();
        void dataAccess();
        void interpolation();
        void boundaryInterpolation();
        void minMax();
};

#endif // GRIDTEST_H
