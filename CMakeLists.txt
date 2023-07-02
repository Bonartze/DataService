cmake_minimum_required(VERSION 3.25)
project(DataService)

set(CMAKE_CXX_STANDARD 17)

find_package(unofficial-sqlite3 CONFIG REQUIRED)

add_executable(DataService main.cpp Server.cpp Server.hpp Client.cpp Client.hpp SQLiteException.cpp SQLiteException.hpp UnitTests.cpp UnitTests.hpp ServerTest.cpp ServerTest.hpp)

target_link_libraries(DataService PRIVATE unofficial::sqlite3::sqlite3)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(DataService PRIVATE GTest::gtest GTest::gtest_main GTest::gmock)

target_include_directories(DataService PRIVATE ${GTEST_INCLUDE_DIRS})
