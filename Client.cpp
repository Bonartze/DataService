#include "Client.hpp"

Server *Client::server = new Server();

Client::~Client() = default;


std::string Client::GetRequest() {
    getline(std::cin, request);
    std::stringstream ss{request};
    std::string command;
    ss >> command;
    if (command == "POST") {       // create table in database
        std::string s;
        while (ss >> s) {
            if (s == "{") {
                ss.ignore(2);
                ss >> s;
                s.resize(s.size() - 1);
                server->CreateTable(s);       //request form: POST { "filename" }
                return {};
            }
        }
    } else if (command == "GETFIL") {       //getting filtrate data
        std::string s, filter;
        while (ss >> s) {
            if (s == "{") {             //request form: GETFIL { "filename", "filter" }
                ss.ignore(2);
                ss >> s;
                s.resize(s.size() - 2);
                ss.ignore(2);
                getline(ss, filter);
                filter.resize(filter.size() - 3);
                return server->FiltrationBy(filter, s);
            }
        }
    } else if (command == "GETSORT") {     //getting sort table
        std::string s, filter;
        while (ss >> s) {
            if (s == "{") {             //request form: GETSORT { "filename", "sort by and order by" }
                ss.ignore(2);
                ss >> s;
                s.resize(s.size() - 2);
                ss.ignore(2);
                getline(ss, filter);
                filter.resize(filter.size() - 3);
                return server->SortBy(filter, s);
            }
        }
    } else if (command == "GETCOLUMNS") {         //getting columns info
        std::string column_info = "";
        auto tables = server->ColumnsInfo();       //request form: GETCOLUMN { "filename" }
        for (auto &[table_name, col_info]: tables)
            column_info += table_name + "\n" + col_info + "\n\n";
        return column_info;
    }
}

void Client::ClearServer() {
    server->RemoveAllTables();
}