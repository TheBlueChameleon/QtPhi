#include <QTest>

#include "base/coordinatetest.h"

int main(int argc, char* argv[])
{
    // setup lambda
    int status = 0;
    auto runTest = [&status, argc, argv](QObject* obj)
    {
        status |= QTest::qExec(obj, argc, argv);
    };

    // run suite
    runTest(new CoordinateTest);

    return status;
}
