#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> // for close()

int main()
{
    char server_message[256] = "Welcome R2D2!\n";
    char end_message[256]    = "Client disconnected";

    // create the server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0); // AF - Address Family
    
    // create address structure
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address)); // set structure server adress to null (to avoid errors with connection)
    
    server_address.sin_family      = AF_INET;
    server_address.sin_port        = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;
    
    // bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // listen to connections
    listen(server_socket, 5);

    // write to client socket
    int client_socket;
    client_socket =  accept(server_socket, NULL, NULL);

    send(client_socket, server_message, sizeof(server_message), 0);
    send(client_socket, end_message, sizeof(end_message), 0 );

    // close the socket
    close(server_socket);
    
    return 0;
}
