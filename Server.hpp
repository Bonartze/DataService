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
    std::string NameDataBase = "base.bd";
    sqlite3 *DataBase;
    std::vector<std::string> tables;

    std::string ParseColumns(std::string);

    std::string GetResponse(std::string, sqlite3_stmt *);


public:
    Server();

    ~Server();

    std::string SortBy(std::string, std::string);

    std::string FiltrationBy(std::string, std::string);

    bool CreateTable(std::string);

    Tables ColumnsInfo();

    bool RemoveAllTables();


    void Display(std::string);

};


#endif //DATASERVICE_SERVER_HPP
