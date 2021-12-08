#include "main.hpp"
#define DEFAULT_PORT 1601

using std::cout;
using std::endl;

int main(int ac, char ** av){
    int client;
    int server;
    struct sockaddr_in server_addres;

    //* Создание сокета!
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0){
        cout << "SERVER ERROR: estabilishing socket error" << endl;
        exit(1);
    }
    cout << client << endl;
    cout << "SERVER: socket for server was succesful created" << endl;

    //* Привязка сокета к сетевому интерфейсу
    server_addres.sin_port = htons(DEFAULT_PORT);
    server_addres.sin_family = AF_INET;
    server_addres.sin_addr.s_addr = htons(INADDR_ANY);
    int ret = bind(client, reinterpret_cast<struct sockaddr *>(&server_addres), sizeof(server_addres));
    if (ret < 0){
        cout << "BIND ERROR" << endl;
        exit (1);
    }
    cout << ret << endl;
    cout << "Bind succesful" << endl;


    
    (void)ac;
    (void)av;
    (void)server;
}