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
#include "Filters.h"
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
	server.sin_port = htons(port);
	
	// Bind.
	socklen_t len = sizeof(server);
	if ( bind(sock, (struct sockaddr *) &server, len) < 0 ) {
		perror("bind()");
		exit(1);
	}
	
	// Create the client.
	struct sockaddr_in client;
	socklen_t fromlen = sizeof(client);
	listen(sock, 5); // 5 is the number of backlogged waiting clients.
	printf("Listener socket created and bound to port %d\n", port);
	
	// Threads
	pthread_t tid[MAX_THREADS];
	
	// Keep taking requests from client.
	while (true) {
		// Accept client connection.
		int fd = accept(sock, (struct sockaddr *) &client, &fromlen);
		
#ifdef DEBUG
		printf("Accepted client connection on fd: %d\n", fd);
#endif
		
		// Create a buffer to read the message into.
		char buffer[BUFFER_SIZE];
		
		// Receive the message.
		ssize_t n = recv(fd, buffer, BUFFER_SIZE - 1, 0);
		// Check recv() return value.
		
		// Stream has errored or ended.
		if ( n <= 0 ) {
			// Errored.
			perror("recv()");
			continue;
		} else {
			// Stream received message.
			buffer[n] = '\0';
#ifdef DEBUG
			//printf("Received message from fd %d: %s\n", fd, buffer);
#endif
		}
		
		/*
		 6. Your server does must be a concurrent server (i.e. do not use an iterative server).
		 */
		
		// Create a thread to handle message.
		sock_msg *arg = malloc(sizeof(sock_msg));
		arg->sock = fd;
		arg->address = server;
		arg->msg = strdup(buffer);
		if ( pthread_create(&tid[fd], NULL, handleRequest, (void *) arg) != 0 ) {
			perror("Could not create thread.");
			free(arg->msg);
		}
	}
	
	// We'll never get here.
	return EXIT_SUCCESS;
}
