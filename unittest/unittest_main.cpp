#include <iostream>

#include <QTest>

#include "base/basegridtest.h"
#include "base/coordinatetest.h"
#include "base/imposablegridtest.h"
#include "base/recttest.h"
#include "base/interpolationtest.h"

void reportOverall(const std::vector<std::string>& failedTests);

int main(int argc, char* argv[])
{
    // *INDENT-OFF*
    const std::vector<std::function<QObject*()>> testConstructors = {
        []() {return new CoordinateTest;},
        []() {return new RectTest;},
        []() {return new BaseGridTest;},
        []() {return new ImposableGridTest;},
        []() {return new InterpolationTest;},
    };
    // *INDENT-ON*

    int status = 0;
    std::vector<std::string> failedTests;

    for (const auto& ctor : testConstructors)
    {
        auto* test = ctor();
        auto partialResult = QTest::qExec(test, argc, argv);
        if (partialResult)
        {
            failedTests.push_back(test->metaObject()->className());
        }
        status |= partialResult;
        delete test;
    }

    reportOverall(failedTests);
    return status;
}

void reportOverall(const std::vector<std::string>& failedTests)
{
    std::cout << std::string(80, '#') << std::endl;
    std::cout.width(79);
    std::cout << std::left << "# OVERALL RESULT"  << "#" << std::endl;
    if (failedTests.empty())
    {
        std::cout.width(79);
        std::cout << std::left << "# SUCCESS" << "#" << std::endl;
    }
    else
    {
        std::cout.width(79);
        std::cout << std::left << "# THE FOLLOWING TEST(S) FAIL:" << "#" << std::endl;
        for (const auto& testName: failedTests)
        {
            std::cout << "#  * ";
            std::cout.width(74);
            std::cout << std::left << testName << "#" << std::endl;
        }
    }
    std::cout << std::string(80, '#') << std::endl;
}
