#ifndef TEST_BAR_H
#define TEST_BAR_H

#include <QObject>
#include <QTest>

class test_bar : public QObject
{
        Q_OBJECT

    private slots:
        void bar();
};

#endif // TEST_BAR_H
