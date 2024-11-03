#ifndef BASEGRIDTEST_H
#define BASEGRIDTEST_H

#include <QObject>
#include <QTest>

class BaseGridTest : public QObject
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

#endif // BASEGRIDTEST_H
