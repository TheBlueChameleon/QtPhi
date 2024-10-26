#ifndef COORDINATETEST_H
#define COORDINATETEST_H

#include <QObject>
#include <QTest>

class CoordinateTest : public QObject
{
        Q_OBJECT

    private slots:
        void add_sub_neg();
        void mul_div();
};

#endif // COORDINATETEST_H
