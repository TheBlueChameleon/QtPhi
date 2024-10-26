#include <QTest>

#include "base/test_test.h"
#include "base/test_bar.h"

int main(int argc, char* argv[])
{
    // setup lambda
    int status = 0;
    auto runTest = [&status, argc, argv](QObject* obj)
    {
        status |= QTest::qExec(obj, argc, argv);
    };

    // run suite
    runTest(new Test_Test);
    runTest(new test_bar);

    return status;
}
