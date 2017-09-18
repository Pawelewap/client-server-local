#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h> // for close()
#include <netinet/in.h>

int main(int argc, char **argv)
{

    // save port from argv
    int port_number = 9002;

    // if something in arguments table
    if(argc > 1)
        port_number = atoi(argv[1]);

    // create a socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0); 
    // AF_INET - adress family (i.e. IPv4, AF_INET6 - IPv6, AF_IPX etc.)
    // SOCK_STREAM for TCP, SOCK_DGRAM for UDP 
    // 0 - default protocol TCP 

    // specify an adress for the socket
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_number);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status =  connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address)); 
    // if 0 - ok, if -1 - some errorwith connection)
    
    // check for error with the connection
    if(connection_status == -1)
    {
        printf("!error! PANIC!!! CALL CPTN OBVIOUS!\n");
    }

    // receive data from the server
    char server_response[256] = "0xDEADBEEF";
    recv(network_socket, &server_response, sizeof(server_response), 0);
    // socket 
    // place to hold the data from server
    // size of buffer
    // optional flag parameter

    // print out the server response
    printf("Server response: %s\n", server_response);
   
    recv(network_socket, &server_response, sizeof(server_response), 0);
    printf("%s", server_response);
    // close the socket
    close(network_socket);

    return 0;
} 
