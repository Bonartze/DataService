//
// Created by ivan on 30.06.23.
//

#include "Client.hpp"

Server *Client::server = new Server();

Client::~Client() {
    clear_server();
}

Client::Client() {
    is_registered = true;
    if (!is_registered) {
        std::cout << "Please register " << std::endl;
        registration();
        enter();
        is_registered = true;
    }
}

void Client::enter() {
    while (true) {
        std::cout << "Enter your login ";
        std::string t_login, t_password;
        std::cin >> t_login;
        std::cout << "Enter your password: ";
        std::cin >> t_password;
        if (t_login != login || t_password != password)
            std::cout << "Incorrect login or password" << std::endl;
        else
            break;
    }
    is_online = true;
}

void Client::leave() {
    if (is_online)
        is_online = false;
}

void Client::registration() {
    std::cout << "Come up with a login: ";
    std::cin >> login;
    std::cout << "Come up with a password: ";
    std::cin >> password;
}

std::string Client::get_request() {
    is_online = true;
    if (is_online) {
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
                if (s == "{") {             //request form: GETFIL {"filename", "filter"}
                    ss.ignore(2);
                    ss >> s;
                    s.resize(s.size() - 2);
                    ss.ignore(2);
                    getline(ss, filter);
                    filter.resize(filter.size() - 3);
                    return server->filtration_by(filter, s);
                }
            }
        } else if (command == "GETSORT") {     //getting sort table
            std::string s, filter;
            while (ss >> s) {
                if (s == "{") {             //request form: GETSORT {"filename", "sort by and order by"}
                    ss.ignore(2);
                    ss >> s;
                    s.resize(s.size() - 2);
                    ss.ignore(2);
                    getline(ss, filter);
                    filter.resize(filter.size() - 3);
                    return server->sort_by(filter, s);
                }
            }
        } else if (command == "GETCOLUMNS") {         //getting columns info
            std::string column_info = "";
            auto tables = server->columns_info();       //request form: GETCOLUMN { "filename" }
            for (auto &[table_name, col_info]: tables)
                column_info += table_name + "\n" + col_info + "\n\n";
            return column_info;
        }
    }
}

void Client::clear_server() {
    server->RemoveAllTables();
}
