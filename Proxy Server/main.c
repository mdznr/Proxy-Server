//
//  main.c
//  Proxy Server
//
//  Created by Matt Zanchelli on 2/20/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include <limits.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#include <pthread.h>

#include <sys/errno.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "Boolean.h"
#include "MutexLock.h"
#include "RequestHandling.h"
#include "SignalHandling.h"
#include "StringFunctions.h"

extern int errno;

#warning BUFFER_SIZE should be 1024, so fix chunking. Accumulate whole message before sending to processing?
#define BUFFER_SIZE 2048

#define MAX_CLIENTS 128
#define MAX_THREADS 128

#define START_INDEX_FILTERS 2

int main(int argc, const char *argv[])
{
	// Set up signal handler via signal().
	signal(SIGUSR1, &handleSIGUSR1);
	signal(SIGUSR2, &handleSIGUSR2);
	
	// The port number to use for the socket.
	unsigned short port = 8127; // The default port is 8127 (if no arguments are given).
	if ( argc > 1 ) {
		int conversion = atoi(argv[1]);
		// Cannot convert int to unsigned short.
		if ( conversion < 0 || conversion > USHRT_MAX ) {
			perror("Invalid port");
			perror("Usage: ./proxy port [filtered_out_prefixes_and_suffixes ...]");
			exit(1);
		}
		// Assign the port value.
		port = (unsigned short) conversion;
	}
	
	/*
	 Your proxy server must filter based on domain name (or IP address) prefixes/suffixes as described above. All command-line arguments following the port number are domain or IP address prefixes/suffixes that must be filtered. There can be zero or more of these; and there is no limit to the number of arguments.
	 */
	
	filtersCount = malloc(sizeof(unsigned int));
	*filtersCount = 0;
	
	// Contains at least one filter.
	if ( argc > START_INDEX_FILTERS ) {
		// Filters are START_INDEX_FILTERS less than the number of arguments to the program.
		*filtersCount = argc - START_INDEX_FILTERS;
		// Create a pointer to the start of the filters in argv.
		filters = &argv[START_INDEX_FILTERS];
	}
	
	// Create the listener socket as TCP socket. (use SOCK_DGRAM for UDP)
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if ( sock < 0 ) {
		perror("socket()");
		exit(1);
	}
	
	// Create the server.
	struct sockaddr_in server;
	server.sin_family = PF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	
	// htons() is host-to-network-short for marshalling.
	// Internet is "big endian"; Intel is "little endian".
	server.sin_port = htons(port);
	int len = sizeof(server);
	
	if ( bind(sock, (struct sockaddr *) &server, len) < 0 ) {
		perror("bind()");
		exit(1);
	}
	
	// Create the client.
	struct sockaddr_in client;
	unsigned int fromlen = sizeof(client);
	listen(sock, 5); // 5 is the number of backlogged waiting clients.
	printf("Listener socket created and bound to port %d\n", port);
	
	// Client sockets
	int client_sockets[MAX_CLIENTS]; // Client socket fd list
	int client_socket_index = 0;     // Next free spot
	
	// Buffer for receiving messages
	char buffer[BUFFER_SIZE];
	
	// Threads
	pthread_t tid[MAX_THREADS];
	
	while (true)
	{
		struct timeval timeout;
		timeout.tv_sec = 3;
		timeout.tv_usec = 500;  // AND 500 microseconds
		
		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(sock, &readfds);
//		printf("Set FD_SET to include listener fd %d\n", sock);
		
		for ( int i=0; i<client_socket_index; ++i ) {
			FD_SET(client_sockets[i], &readfds);
//			printf("Set FD_SET to include client socket fd %d\n", client_sockets[i]);
		}
		
		// The number of ready file descriptors
		int q = select(FD_SETSIZE, &readfds, NULL, NULL, &timeout);
		if ( q == 0 ) {
			//printf("No activity\n");
			continue;
		}
		
		if ( FD_ISSET(sock, &readfds) ) {
			// We know that this accept() call will NOT block.
			int newsock = accept(sock, (struct sockaddr *)&client, &fromlen);
			printf("Accepted client connection\n");
			client_sockets[client_socket_index++] = newsock;
		}
		
		for ( int i=0; i<client_socket_index; ++i ) {
			int fd = client_sockets[i];
			if ( FD_ISSET(fd, &readfds) ) {
				ssize_t n = recv(fd, buffer, BUFFER_SIZE - 1, 0);
				if ( n == 0 ) {
					int k;
					printf("Client on fd %d closed connection\n", fd);
					// Remove fd from client_sockets[] array:
					for ( k=0; k<client_socket_index; k++ ) {
						if ( fd == client_sockets[k] ) {
							// Found it -- copy remaining elements over fd
							for ( int m=k; m<client_socket_index-1; m++ ) {
								client_sockets[m] = client_sockets[m+1];
							}
							client_socket_index--;
							break;  // All done
						}
					}
					// TODO: Close fd
				} else if ( n < 0 ) {
					// TODO: Close fd?
					perror("recv()");
				} else {
					buffer[n] = '\0';
					printf("Received message from fd %d: %s\n", fd, buffer);
					
					/*
					 6. Your server does must be a concurrent server (i.e. do not use an iterative server).
					 */
					
					// Create a thread to handle message.
					sock_msg *arg = malloc(sizeof(sock_msg));
					arg->sock = fd;
					arg->address = server;
					arg->msg = buffer;
					if ( pthread_create(&tid[i], NULL, handleRequest, (void *) arg) != 0 ) {
						perror( "Could not create thread." );
					}
				}
			}
		}
	}
	
	// We'll never get here.
	return EXIT_SUCCESS;
}
