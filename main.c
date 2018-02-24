#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

int createSocket(int *sin_family, int *socket_type, int *protocol_number);
void setTarget(int *sin_family, char *address, int *port, sockaddr_in *server);
char *getAddress();
int getPort();

int main(){
	int connection_socket, sin_family, socket_type, protocol_number, port, msg_flag;
	sockaddr_in server;
	char *request = "GET / HTTP/1.1\r\n\r\n", buffer[1000], *address;

	sin_family = AF_INET;
	socket_type = SOCK_STREAM;
	protocol_number = 0;
	msg_flag = MSG_PEEK;

	printf("Host: ");
	address = getAddress();

	printf("Port: ");
	port = getPort();

	connection_socket = createSocket(&sin_family, &socket_type, &protocol_number);
	setTarget(&sin_family, address, &port, &server);

	connect(connection_socket, (sockaddr *)&server, sizeof(server));
	send(connection_socket, request, strlen(request), protocol_number);
	recv(connection_socket, buffer, sizeof(buffer), msg_flag);

	printf("\nResponse:\n\n");
	printf("%s", buffer);
	
	return 0;
}

int createSocket(int *sin_family, int *socket_type, int *protocol_number){
	int connection_socket = socket(*sin_family , *socket_type , *protocol_number);
	if(connection_socket != -1)
		return connection_socket;
	else
		exit(1);
}

void setTarget(int *sin_family, char *address, int *port, sockaddr_in *server){
	server->sin_addr.s_addr = inet_addr(address);
	server->sin_family = *sin_family;
	server->sin_port = htons(*port);
}

char *getAddress(){

	char a, *address = NULL;
	int k = 0;

	do{
		a = getchar();
		address = (char *) realloc(address, (k + 1) * sizeof(char));
		address[k] = a;
		k++;
	}while(a != '\n');
	address[k-1] = '\0';

	return address;
}

int getPort(){
	int port;
	scanf("%d", &port);
	return port;
}