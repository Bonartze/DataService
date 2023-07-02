#ifndef DATASERVICE_SERVERTEST_HPP
#define DATASERVICE_SERVERTEST_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Server.hpp"

struct ServerTest : public testing::Test {
    Server *server;

    void SetUp();

    void TearDown();

};


#endif //DATASERVICE_SERVERTEST_HPP
