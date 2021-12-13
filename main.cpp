#include "main.hpp"
#include <string>

int main(int ac, char **av)
{
    (void)av;
    (void)ac;
    Client client(AF_INET);
    Client client2(client);
    client2.setName("Вася петров");
    cout << client2.getName() << endl;
    cout << client.getName() << endl;
    client2.setPassword("qweksfKMfsddaFDf.");

    Server server("127.0.0.0", 1601, AF_INET);
    server.addClient();
    try
    {
        server.binding();
    }
    catch(std::exception & e)
    {
        cout << e.what() << endl;
    }
}