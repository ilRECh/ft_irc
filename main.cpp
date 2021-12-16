#include "main.hpp"
#include <string>

int main(int ac, char **av)
{
    (void)av;
    (void)ac;
    Server server("127.0.0.1", 1602, AF_INET);
    try
    {
        server.run();
    }
    catch(std::exception & e)
    {
        cout << e.what() << endl;
    }
}