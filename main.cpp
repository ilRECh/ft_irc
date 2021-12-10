#include "main.hpp"
#define ERROR_S "SERVER ERROR: "
#define DEFAULT_PORT 1602
#define BUFFER_SIZE 256
#define CLIENT_CLOSE_SYMOL '#'


using std::cout;
using std::endl;
using std::cin;

int is_client_close_connection(const char * msg){
	if (strchr(msg, CLIENT_CLOSE_SYMOL)){
		cout << "SERVER: connection to client closed" << endl;
		return (1);
	}
	return (0);
}

int main( void ){
	int client;
	int server;
	struct sockaddr_in server_addres;

	client = socket(AF_INET, SOCK_STREAM, 0);
	if (client < 0){
		cout << ERROR_S << "estabilishing socket error." << endl;
		exit(1);
	}
	cout << "SERVER: Socket for server was succesfully created\n";

	server_addres.sin_port = htons(DEFAULT_PORT);
	server_addres.sin_family = AF_INET;
	server_addres.sin_addr.s_addr = htons(INADDR_ANY);

	int ret = bind(client, reinterpret_cast<struct sockaddr*>(&server_addres),
		sizeof(server_addres));
	
	if (ret < 0){
		cout << ERROR_S
			<< "binding connection. SOcket has already been estabilishing.\n";
		return -1;
	}

	socklen_t size = sizeof(server_addres);
	cout << "SERVER: " << "Listening clients...\n";
	listen(client, 1);
	cout << "ALE MALYO\n";
	server = accept(client, reinterpret_cast<struct sockaddr*>(&server_addres), &size);
	if (server < 0)
		cout << ERROR_S << "Can't accepting client.\n";
	
	char buffer[BUFFER_SIZE];
	strcpy(buffer, "=> Server connected!\n");
	if (0 > send(server, buffer, BUFFER_SIZE, 0))
		exit (96);
	cout << "=> Connected to the client #1" << endl
		<< "Enter " << CLIENT_CLOSE_SYMOL << " to end connection\n" << endl;
	while(server > 0){
		recv(server, buffer, BUFFER_SIZE, 0);
		cout << "Client: " << buffer << endl;
		if (is_client_close_connection(buffer))
			break ;

		cout << "Server: ";
		cin.getline(buffer, BUFFER_SIZE);
		send(server, buffer, BUFFER_SIZE, 0);
		if (is_client_close_connection(buffer))
			break ;
	}
	close(server);
	close(client);
	cout << "Bye\n";
}