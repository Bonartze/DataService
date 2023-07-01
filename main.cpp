#include <iostream>
#include "Client.hpp"

int main() {
    {
        Client c;
        c.get_request();
        c.get_request();
        auto t = c.get_request();
        std::cout << t << std::endl;
    }

    return 0;
}

