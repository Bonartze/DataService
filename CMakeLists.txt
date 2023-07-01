cmake_minimum_required(VERSION 3.25)
project(DataService)

set(CMAKE_CXX_STANDARD 17)


find_package(unofficial-sqlite3 CONFIG REQUIRED)
add_executable(DataService main.cpp Server.cpp Server.hpp Server.hpp Client.cpp Client.hpp SQLiteException.cpp SQLiteException.hpp)
target_link_libraries(DataService PRIVATE unofficial::sqlite3::sqlite3)
