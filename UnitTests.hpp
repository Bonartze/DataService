#ifndef DATASERVICE_UNITTESTS_HPP
#define DATASERVICE_UNITTESTS_HPP


#include <gtest/gtest.h>
#include <gmock/gmock.h>


class UnitTests {
public:
    static void InitTests(int, char **);

    UnitTests() = default;

    ~UnitTests() = default;

    int RunTests();
};


#endif //DATASERVICE_UNITTESTS_HPP
