//
// Created by ivan on 30.06.23.
//
#ifndef DATASERVICE_SERVER_HPP
#define DATASERVICE_SERVER_HPP

#include <iostream>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <sqlite3.h>
#include <exception>
#include <string>
#include <fstream>
#include <vector>
#include "SQLiteException.hpp"

using Tables = std::unordered_map<std::string, std::string>;

class Server {
private:
    std::string name_data_base = "base.bd";
    sqlite3 *data_base;
    std::vector<std::string> tables;

    std::string parse_columns(std::string);

    std::string get_response(std::string, sqlite3_stmt *);


public:
    Server();

    ~Server();

    std::string sort_by(std::string, std::string);

    std::string filtration_by(std::string, std::string);

    void CreateTable(std::string);

    Tables columns_info();

    void RemoveAllTables();


    void display(std::string);

};


#endif //DATASERVICE_SERVER_HPP
