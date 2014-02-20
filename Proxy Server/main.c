//
//  main.c
//  Proxy Server
//
//  Created by Matt Zanchelli on 2/20/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#include <sys/errno.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>

extern int errno;

#define BUFFER_SIZE 1024
#define MAX_CLIENTS 100

/// Message to send.
char *msg = "ack";

/// The port number to use for the socket.
const unsigned short port = 8127;

int main(int argc, const char *argv[])
{
	fd_set readfds;
	int client_sockets[MAX_CLIENTS]; // Client socket fd list
	int client_socket_index = 0;     // Next free spot
	
	// Create the listener socket as TCP socket.
	// (use SOCK_DGRAM for UDP)
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	
	if ( sock < 0 ) {
		perror("socket()");
		exit(1);
	}
	
	struct sockaddr_in server;
	server.sin_family = PF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	
	// htons() is host-to-network-short for marshalling
	// Internet is "big endian"; Intel is "little endian".
	server.sin_port = htons(port);
	int len = sizeof(server);
	
	if ( bind(sock, (struct sockaddr *) &server, len) < 0 ) {
		perror("bind()");
		exit(1);
	}
	
	struct sockaddr_in client;
	unsigned int fromlen = sizeof(client);
	listen(sock, 5);  // 5 is the number of backlogged waiting clients.
	printf("Listener socket created and bound to port %d\n", port);
	
	while (1)
	{
		int q;
		
		/** Add **/
		struct timeval timeout;
		timeout.tv_sec = 3;
		timeout.tv_usec = 500;  // AND 500 microseconds
		/** Add **/
		
		FD_ZERO(&readfds);
		FD_SET(sock, &readfds);
		printf("Set FD_SET to include listener fd %d\n", sock);
		
		for ( q = 0 ; q < client_socket_index ; q++ ) {
			FD_SET(client_sockets[q], &readfds);
			printf("Set FD_SET to include client socket fd %d\n", client_sockets[q]);
		}
		
#if 0
		// BLOCK
		q = select(FD_SETSIZE, &readfds, NULL, NULL, NULL); // q is the number of ready file descriptors
#endif
		
		/** A **/
		q = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
		if (q == 0) {
			printf("No activity\n");
			continue;
		}
		/** A **/
		
		if ( FD_ISSET(sock, &readfds) ) {
			// We know that this accept() call will NOT block.
			int newsock = accept(sock, (struct sockaddr *)&client, &fromlen);
			printf("Accepted client connection\n");
			client_sockets[client_socket_index++] = newsock;
		}
		
		for ( q = 0 ; q < client_socket_index ; q++ ) {
			int fd = client_sockets[q];
			if ( FD_ISSET(fd, &readfds) ) {
				char buffer[BUFFER_SIZE];
				ssize_t n = recv(fd, buffer, BUFFER_SIZE - 1, 0);
				if ( n == 0 ) {
					int k;
					printf("Client on fd %d closed connection\n", fd);
					// Remove fd from client_sockets[] array:
					for ( k = 0 ; k < client_socket_index ; k++ ) {
						if ( fd == client_sockets[k] ) {
							// Found it -- copy remaining elements over fd
							int m;
							for ( m = k; m < client_socket_index - 1; m++ ) {
								client_sockets[m] = client_sockets[m+1];
							}
							client_socket_index--;
							break;  // All done
						}
					}
				} else if ( n < 0 ) {
					perror("recv()");
				} else {
					buffer[n] = '\0';
					printf("Received message from fd %d: %s\n", fd, buffer);
					n = send(fd, msg, strlen(msg), 0);
					if ( n < strlen(msg) ) {
						perror("send()");
					}
				}
			}
		}
	}
	
	// We never get here
	return 0;
}


