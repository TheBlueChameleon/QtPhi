#ifndef INTERPOLATIONTEST_H
#define INTERPOLATIONTEST_H

#include <QObject>
#include <QTest>

class InterpolationTest : public QObject
{
        Q_OBJECT

    private slots:
        void percentage();
        void linear();
        void planar();
};

#endif // INTERPOLATIONTEST_H
