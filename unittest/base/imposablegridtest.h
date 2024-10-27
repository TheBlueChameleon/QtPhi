#ifndef IMPOSABLEGRIDTEST_H
#define IMPOSABLEGRIDTEST_H

#include <QObject>
#include <QTest>

class ImposableGridTest : public QObject
{
        Q_OBJECT

    private slots:
        void clipping();
        void impose();
};

#endif // IMPOSABLEGRIDTEST_H
