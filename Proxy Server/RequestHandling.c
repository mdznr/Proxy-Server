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
#include <arpa/inet.h>

#include "RequestHandling.h"

#include "StringFunctions.h"

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
	struct sockaddr_in server = arg->address;
	char *requestString = arg->msg;
	
	char *ip_addr = inet_ntoa((struct in_addr)server.sin_addr);
	
	HTTPRequest request = processRequest(requestString);
	
	/*
	 When your server detects a request that should be filtered, your server should return an HTTP error 403 (forbidden), which means you need to send back an HTTP status line that indicates an error.
	 */
	
	// Figure out if the request should be filtered out.
	if ( !shouldAllowRequest(request) ) {
#warning The HTTP-Version should not print?
		// Print Request Line
		printf("%s: %s [FILTERED]\n", ip_addr, request[HTTPRequestHeaderField_Request_Line]);
		
		// Return HTTP Error 403 Forbidden
		printf("Return 403\n");
	} else {
#warning The HTTP-Version should not print?
		// Print Request Line
		printf("%s: %s\n", ip_addr, request[HTTPRequestHeaderField_Request_Line]);
	}
	
#warning Handle request
	
	
	// Request is no longer needed.
	HTTPRequestFree(request);
	
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
		
		// Stop when at the end of the header.
		if ( line == NULL ) {
			break;
		}
		
		// Split the line into field name and value.
		char *fieldName = NULL;
		char *fieldValue = NULL;
		
		// Must be the first line, as it is not in the format: "Field Name: Value".
		if ( !splitStringAtString(line, ": ", &fieldName, &fieldValue) ) {
			/*
			 2. Your server must handle GET, HEAD, and POST request methods.
			 */
			
			// The request method is the first token.
			char *requestMethod = prefixOfStringUpUntilCharacter(line, ' ');
			if ( !requestMethod ) {
#warning Something really went wrong.
				continue;
			}
			
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
#warning TODO: send 400 (Bad Request).
		return NULL;
	}
	
	return request;
}

bool shouldAllowRequest(HTTPRequest request)
{
	HTTPRequestHeaderField hostField = HTTPRequestHeaderFieldForFieldNamed(HTTPRequestHeaderFieldName_Host);
	char *server = request[hostField];
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
