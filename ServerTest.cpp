#include "ServerTest.hpp"

void ServerTest::SetUp() {
    server = new Server();
}

void ServerTest::TearDown() {
    server->RemoveAllTables();
    delete server;
}