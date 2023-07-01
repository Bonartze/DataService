#ifndef DATASERVICE_CLIENT_HPP
#define DATASERVICE_CLIENT_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <sqlite3.h>
#include "Server.hpp"
#include <fstream>

class Client {
private:
    static Server *server;
    bool is_registered = false;
    bool is_online = false;
    std::string login;
    std::string password;
    std::string request;

    void registration();

public:
    Client();
    ~Client();
    void clear_server();
    std::string get_request();

    inline void enter();

    inline void leave();
};


#endif //DATASERVICE_CLIENT_HPP
