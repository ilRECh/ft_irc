#include "client.hpp"
#define DEFAULT_PORT 1602
#define BUFFER_SIZE 256
#define CLIENT_CLOSE_SYMOL '#'
#define SERVER_IP "127.0.0.1"

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
	struct sockaddr_in server_addres;

	server_addres.sin_port = htons(DEFAULT_PORT);
	server_addres.sin_family = AF_INET;
	inet_pton(AF_INET, SERVER_IP, &server_addres.sin_addr);

	client = socket(AF_INET, SOCK_STREAM, 0);
	if (client < 0)
		exit(22);
	cout << "\nCLient socket created.\n";

	int ret = connect(client,
		reinterpret_cast<struct sockaddr*>(&server_addres),
		sizeof(server_addres));
	if (ret == 0)
		cout << "=> Connection to sercver "
			<< inet_ntoa(server_addres.sin_addr)
			<< " with port number: " << DEFAULT_PORT << endl;
	char buffer[BUFFER_SIZE];
	cout << "=> Waiting for server confirmation...\n";
	recv(client, buffer, BUFFER_SIZE, 0);
	cout << "=> Connection estabilished.\n"
			<< "Enter " << CLIENT_CLOSE_SYMOL << " for close connection\n";
	while(client > 0){
		cout << "Client: ";
		cin.getline(buffer, BUFFER_SIZE);
		send(client, buffer, BUFFER_SIZE, 0);
		if (is_client_close_connection(buffer))
			break ;

		recv(client, buffer, BUFFER_SIZE, 0);
		cout << "Server: " << buffer << endl;
		if (is_client_close_connection(buffer))
			break ;
	}
	close(client);
	cout << "Bye\n";
}