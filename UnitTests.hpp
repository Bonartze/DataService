//
// Created by ivan on 02.07.23.
//

#ifndef DATASERVICE_UNITTESTS_HPP
#define DATASERVICE_UNITTESTS_HPP


#include <gtest/gtest.h>
#include <gmock/gmock.h>


class UnitTests {
public:
    static void init_tests(int, char **);

    UnitTests()=default;

    ~UnitTests() = default;

    int run_tests();
};


#endif //DATASERVICE_UNITTESTS_HPP
