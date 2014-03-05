//
//  RequestHandling.c
//  Proxy Server
//
//  Created by Matt Zanchelli on 3/1/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "RequestHandling.h"

#include "StringFunctions.h"

#warning Should this be 1024 and handle chunking?
#define RECEIVED_MESSAGE_BUFFER_SIZE 2048

#pragma mark - Private API (Prototypes)

/// Parse an HTTP request.
/// @param request The HTTP request.
/// @return The parsed HTTP request.
HTTPRequest processRequest(char *requestString);

/// Determine whether a request should be filtered out or not.
/// @param request The HTTP request.
/// @return Whether or not the request should be allowed.
bool shouldAllowRequest(HTTPRequest request);

/// Determine whether a server should be filtered out or not.
/// @param server The server in the HTTP request.
/// @return Whether or not the server should be allowed.
bool shouldAllowServer(const char *server);


#pragma mark - Public API Implementation

void *handleRequest(void *argument)
{
	sock_msg *arg = (sock_msg *)argument;
	int sock = arg->sock;
	struct sockaddr_in client = arg->address;
	char *requestString = arg->msg;
	
	char *ip_addr = inet_ntoa((struct in_addr)client.sin_addr);
	
	// Process the request string into a HTTPRequest.
	HTTPRequest request = processRequest(requestString);
	if ( !request ) {
		// Send back HTTP Error 400 Bad Request.
		char *badRequest = "HTTP/1.1 400 Bad Request\r\n\r\n";
		ssize_t send_client_n = send(sock, badRequest, strlen(badRequest), 0);
		if ( send_client_n < strlen(badRequest) ) {
			perror("send()");
			goto end;
		}
	}
	
	/*
	 When your server detects a request that should be filtered, your server should return an HTTP error 403 (forbidden), which means you need to send back an HTTP status line that indicates an error.
	 */
	
	// Figure out if the request should be filtered out.
	if ( !shouldAllowRequest(request) ) {
#warning The HTTP-Version should not print?
		// Print Request Line
		printf("%s: %s [FILTERED]\n", ip_addr, request[HTTPRequestHeaderField_Request_Line]);
		
		// Send back HTTP Error 403 Forbidden.
		char *badRequest = "HTTP/1.1 403 Forbidden\r\n\r\n";
		ssize_t send_client_n = send(sock, badRequest, strlen(badRequest), 0);
		if ( send_client_n < strlen(badRequest) ) {
			perror("send()");
			goto end;
		}
		
	} else {
#warning The HTTP-Version should not print?
		// Print Request Line
		printf("%s: %s\n", ip_addr, request[HTTPRequestHeaderField_Request_Line]);
	}
	
	/*
	 Your server must forward the appropriate HTTP request headers to the requested server, then send the responses back to the client.
	 */
	
	// Modify request string
#warning move to cleaner solution.
	char *serverRequestString = requestStringFromRequest(request);
	
	int serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	if ( serverSocket < 0 ) {
		perror("socket()");
#warning Don't use gotos?
		goto end;
	}
	
	// Server
	struct sockaddr_in server;
	server.sin_family = PF_INET;
	
	struct hostent *hp = gethostbyname(request[HTTPRequestHeaderField_Host]);
	if ( hp == NULL ) {
		perror("Unknown host");
		goto end;
	}
	
	// Could also use memcpy
	bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);
	unsigned short port = 80;
	server.sin_port = htons(port);
	
	// Connect.
	if ( connect(serverSocket, (struct sockaddr *)&server, sizeof(server) ) < 0 ) {
		perror("connect()");
		goto end;
	}
	
	// Send.
	ssize_t send_n = send(serverSocket, serverRequestString, strlen(serverRequestString), 0);
	if ( send_n < strlen(serverRequestString) ) {
		perror("send()");
		goto end;
	}
	
	// Buffer to load received messages into.
	char buffer[RECEIVED_MESSAGE_BUFFER_SIZE];
	
	// Receive.
	while (1) {
		// BLOCK
		ssize_t received_n = recv(serverSocket, buffer, RECEIVED_MESSAGE_BUFFER_SIZE - 1, 0);
		if ( received_n == 0 ) {
			// Peer has closed its half side of the (TCP) connection.
			break;
		} else if ( received_n < 0 ) {
			// Error.
			perror("recv()");
			goto end;
		} else {
			// End the buffer with a null-terminator.
			buffer[received_n] = '\0';
			// Print out the received message for debugging.
			printf("\n\nReceived message from %s:\n%s\n\n", inet_ntoa((struct in_addr)server.sin_addr), buffer);
			
			ssize_t send_client_n = send(sock, buffer, strlen(buffer), 0);
			if ( send_client_n < strlen(buffer) ) {
				perror("send()");
				goto end;
			}
		}
	}
		
end:
	
	close(serverSocket);
	
	if ( request != NULL ) {
		// Request is no longer needed.
		HTTPRequestFree(request);
	}
	
	// The socket is no longer needed.
	close(sock);
	
	// Use this to return message back to calling thread and terminate.
	pthread_exit(NULL);
	
	return NULL;
}


#pragma mark - Private API (Implementation)

HTTPRequest processRequest(char *requestString)
{
	HTTPRequest request = HTTPRequestCreate();
	
	// Start the parsing at the beginning of the request.
	char *parse = requestString;
	static const char * const delimiter = "\r\n";
	
	// Parse out the rest of the headers.
	for ( int i=0; i<HTTPRequestHeaderFieldsCount; ++i ) {
		
		// Find the end of the line.
		char *next = strstr(parse, delimiter);
		
		// Get just the line.
		char *line = substring(parse, next);
		
		// Advance the parse pointer to the end of the line, and after the delimiter.
		parse = next + strlen(delimiter);
#warning There's sometimes an issue where \n appears at the beginning of the line.
		
		// Stop when at the end of the header.
		if ( line == NULL ) {
			break;
		}
		
		// The first line is different.
		if ( i == 0 ) {
			/*
			 2. Your server must handle GET, HEAD, and POST request methods.
			 */
			
			// The request method is the first token.
			char *requestMethod = prefixOfStringUpUntilCharacter(line, ' ');
			if ( !requestMethod ) {
#warning Something really went wrong.
				continue;
			}
			
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
			
		} else {
			// In the format of: "Field Name: Value"
			
			// Split the line into field name and value.
			char *fieldName = NULL;
			char *fieldValue = NULL;
			if ( !splitStringAtString(line, ": ", &fieldName, &fieldValue) ) {
				// Line isn't in the correct format.
				continue;
			}
			
			HTTPRequestHeaderField field = HTTPRequestHeaderFieldForFieldNamed(fieldName);
			if ( (int) field == -1 ) {
				// Conversion failed.
				continue;
			}
			request[field] = fieldValue;
		}
		
		// Print the line, for debugging.
		printf("%s\n", line);
	}
	
	/*
	 Your server must send an error to the client whenever appropriate, including such cases as the request line being invalid, a Host: header is not found, or a POST request does not include a Content-Length: header. In these cases, your server must send a 400 (Bad Request) as a result.
	 */
	
	// Check request to see if the request's valid.
	if ( !validateRequest(request) ) {
		// Free unused request.
		HTTPRequestFree(request);
		return NULL;
	}
	
	return request;
}

bool shouldAllowRequest(HTTPRequest request)
{
	// Request must be non-NULL.
	if ( request == NULL ) {
		return false;
	}
	
	char *server = request[HTTPRequestHeaderField_Host];
#warning Base off of HOST or the second param in Request Line?
	return shouldAllowServer(server);
}

bool shouldAllowServer(const char *server)
{
	// The end of the server string (used for finding suffix matches).
	const char *serverEnd = server + strlen(server);
	
	// Check against all of the filters.
	for ( int i=0; i<*filtersCount; ++i ) {
		const char *filter = filters[i];
		
#warning Handle case of the string?
		// Length of filter string.
		size_t filterLen = strlen(filter);
		
		// Check prefix.
		if ( strncmp(server, filter, filterLen) == 0 ) {
			return false;
		}
		
		// Check suffix.
		if ( strncmp(serverEnd - filterLen, filter, filterLen) == 0 ) {
			return false;
		}
		
	}
	
	return true;
}
