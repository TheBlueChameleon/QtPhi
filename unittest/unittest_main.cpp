#include <QTest>

#include "base/basegridtest.h"
#include "base/coordinatetest.h"
#include "base/imposablegridtest.h"
#include "base/recttest.h"

int main(int argc, char* argv[])
{
    // *INDENT-OFF*
    const std::vector<std::function<QObject*()>> testConstructors = {
        []() {return new CoordinateTest;},
        []() {return new RectTest;},
        []() {return new BaseGridTest;},
        []() {return new ImposableGridTest;},
    };
    // *INDENT-ON*

    int status = 0;
    for (const auto& ctor : testConstructors)
    {
        auto* test = ctor();
        status |= QTest::qExec(test, argc, argv);
        delete test;
    }

    return status;
}
