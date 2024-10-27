#include <QTest>

#include "base/basegridtest.h"
#include "base/coordinatetest.h"
#include "base/imposablegridtest.h"
#include "base/recttest.h"

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
    runTest(new RectTest);
    runTest(new BaseGridTest);
    runTest(new ImposableGridTest);

    return status;
}
