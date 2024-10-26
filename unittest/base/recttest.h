#ifndef RECTTEST_H
#define RECTTEST_H

#include <QObject>
#include <QTest>

class RectTest: public QObject
{
        Q_OBJECT

    private slots:
        void ctor();
        void getMinMax();
        void contains();
};

#endif // RECTTEST_H
