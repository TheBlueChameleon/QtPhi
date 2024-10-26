#ifndef TEST_TEST_H
#define TEST_TEST_H

#include <QObject>
#include <QTest>

class Test_Test : public QObject
{
        Q_OBJECT

    private slots:
        void foo();
};

#endif // TEST_TEST_H
