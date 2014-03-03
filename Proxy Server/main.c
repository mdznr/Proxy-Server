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

#define BUFFER_SIZE 1024
#define MAX_CLIENTS 100
#define MAX_THREADS 100

#define START_INDEX_FILTERS 2

/// Message to send.
char *msg = "ack";

int main(int argc, const char *argv[])
{
#warning This is just a test.
	char *requestString = "GET http://stackoverflow.com/questions/18183633/string-parsing-in-c-using-strtok HTTP/1.1\r\nHost: stackoverflow.com\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nPragma: no-cache\r\nConnection: keep-alive\r\nProxy-Connection: keep-alive\r\nCookie: __qca=P0-411423666-1383243503829; __utma=140029553.441791018.1383243504.1389471284.1389595028.126; __utmz=140029553.1389471284.125.73.utmcsr=duckduckgo.com|utmccn=(referral)|utmcmd=referral|utmcct=/; _ga=GA1.2.441791018.1383243504; sgt=id=51d9348c-b86f-4197-8309-6b750d69b238; usr=t=FecSPNNOLkO6&s=y5ID6CONs0yz\r\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.74.9 (KHTML, like Gecko) Version/7.0.2 Safari/537.74.9\r\nAccept-Language: en-us\r\nCache-Control: max-age=0\r\nAccept-Encoding: gzip, deflate\r\n\r\n";
	
	// Start the parsing at the beginning of the request.
	char *parse = requestString;
	static const char * const delimiter = "\r\n";
	HTTPRequest request = HTTPRequestCreate();
	
	// Parse out the rest of the headers.
	for ( int i=0; i<HTTPRequestHeaderFieldsCount; ++i ) {
		
		// Find the end of the line.
		char *next = strstr(parse, delimiter);
		
		// Get just the line.
		char *line = substr(parse, next);
		
		// Advance the parse pointer to the end of the line, and after the delimiter.
		parse = next + strlen(delimiter);
		
		// Stop when at the end of the header.
		if ( line == NULL ) {
			break;
		}
		
		// Split the line into field
		char *fieldName = NULL;
		char *fieldValue = NULL;
		splitStringAtString(line, ": ", &fieldName, &fieldValue);
		
		// Must be the first line, as it is not in the format: "Field Name: Value".
		if ( fieldName== NULL && fieldValue == NULL ) {
			/*
			 2. Your server must handle GET, HEAD, and POST request methods.
			 */
			
			// The request method is the first token.
			char *requestMethod = prefixOfStringUpUntilCharacter(line, ' ');
			
			/*
			 Your server must forward the appropriate HTTP request headers to the requested server, then send the responses back to the client.
			 */
#warning TODO: Forward HTTP Request Headers
			
#warning Do not hard-code "GET", "HEAD", and "POST".
			if ( stringEquality(requestMethod, "GET") ) {
				request[HTTPRequestHeaderField_Request_Line] = line;
			} else if ( stringEquality(requestMethod, "HEAD")) {
				request[HTTPRequestHeaderField_Request_Line] = line;
			} else if ( stringEquality(requestMethod, "POST") ) {
				request[HTTPRequestHeaderField_Request_Line] = line;
			} else {
				/*
				 3. Your server must refuse to process any HTTP request method other than GET, HEAD, and POST. In such cases, you should send back an HTTP status code of 405 (Method not allowed) or 501 (Not Implemented) if you receive any other request method.
				 */
#warning TODO: Send back a HTTP Status Code of 501.
				break;
			}
			
		}
		// In the format of: "Field Name: Value"
		else {
			HTTPRequestHeaderField field = HTTPRequestHeaderFieldForFieldNamed(fieldName);
			if ( (int) field == -1 ) {
				// Conversion failed.
#warning TODO: Handle unknown field name.
				break;
			}
			request[field] = fieldValue;
		}
		
		// Print the line, for debugging.
		printf("%s\n", line);
	}
	
	/*
	 Your server must send an error to the client whenever appropriate, including such cases as the request line being invalid, a Host: header is not found, or a POST request does not include a Content-Length: header. In these cases, your server must send a 400 (Bad Request) as a result.
	 */
	
	// Check request to see if it's valid.
	bool valid = validateRequest(request);
	
	return EXIT_SUCCESS;
	
	
	
	
	
	// Set up signal handler via signal().
	signal(SIGUSR1, &handleSIGUSR1);
	signal(SIGUSR2, &handleSIGUSR2);
//	signal(SIGCHLD, &kill_zombies);
	
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
	
	// Contains at least one filter.
	if ( argc > START_INDEX_FILTERS ) {
		// Filters are START_INDEX_FILTERS less than the number of arguments to the program.
		filtersCount = argc - START_INDEX_FILTERS;
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
					// TODO: Close thread
				} else if ( n < 0 ) {
					perror("recv()");
					// TODO: Close thread?
				} else {
					buffer[n] = '\0';
					printf("Received message from fd %d: %s\n", fd, buffer);
					n = send(fd, msg, strlen(msg), 0);
					if ( n < strlen(msg) ) {
						perror("send()");
					} else {
						// Create thread to handle message.
						if ( pthread_create(&tid[i], NULL, handleRequest, (void *) buffer) != 0 ) {
							perror( "Could not create thread" );
						}
					}
				}
			}
		}
	}
	
	// We'll never get here.
	return EXIT_SUCCESS;
}
