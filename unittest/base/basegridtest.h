#ifndef BASEGRIDTEST_H
#define BASEGRIDTEST_H

#include <QObject>
#include <QTest>

class BaseGridTest : public QObject
{
        Q_OBJECT

    private slots:
        void ctor();
        void getters();
};

#endif // BASEGRIDTEST_H
