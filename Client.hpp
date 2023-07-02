#ifndef DATASERVICE_CLIENT_HPP
#define DATASERVICE_CLIENT_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <sqlite3.h>
#include "Server.hpp"
#include <fstream>
#include <limits>

class Client {
private:
    static Server *server;
    std::string request;
public:
    Client() = default;

    ~Client();

    void ClearServer();

    std::string GetRequest();

};


#endif //DATASERVICE_CLIENT_HPP
