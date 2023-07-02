#include "UnitTests.hpp"
#include "Client.hpp"

int main(int argc, char **argv) {
    {                                //unit testing of server handling
        UnitTests test;
        test.InitTests(argc, argv);
        test.RunTests();

    }
    {
        Client c;
        c.GetRequest();
        auto t = c.GetRequest();
        c.ClearServer();
        std::cout << t;
    }
    return 0;
}
