//
// Created by ivan on 02.07.23.
//

#include "ServerTest.hpp"

void ServerTest::SetUp() {
    server = new Server();
}

void ServerTest::TearDown() {
    server->RemoveAllTables();
    delete server;
}