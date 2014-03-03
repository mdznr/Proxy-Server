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

#include "RequestHandling.h"


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

void *handleRequest(void *arg)
{
	char *requestString = (char *) arg;
	printf("Handling Request\n");
	
	HTTPRequest request = processRequest(requestString);
	
	// Figure out if the request should be filtered out.
	if ( !shouldAllowRequest(request) ) {
		// Return HTTP Error 403 Forbidden
		printf("Should return 403");
	}
	
	// Use this to return message back to calling thread and terminate.
	pthread_exit(NULL);
	
	return NULL;
}


#pragma mark - Private API (Implementation)

HTTPRequest processRequest(char *requestString)
{
	printf("Processing Request\n");
	
	HTTPRequest request = HTTPRequestCreate();
#warning TODO: Parse out lines of request and insert into request (array)
	
	//	GET http://rpi.edu/ HTTP/1.1
	//	Host: rpi.edu
	//	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
	//	Pragma: no-cache
	//	Connection: keep-alive
	//	Proxy-Connection: keep-alive
	//	Cookie: __qca=P0-584735642-1384116603868; __unam=7709963-1430791371a-3cb5f2cc-3; __utma=138860844.1352288717.1393057996.1393057996.1393057996.1; __utmz=138860844.1393057996.1.1.utmcsr=rpi.edu|utmccn=(referral)|utmcmd=referral|utmcct=/; _ga=GA1.2.1352288717.1393057996
	//	User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.74.9 (KHTML, like Gecko) Version/7.0.2 Safari/537.74.9
	//	Accept-Language: en-us
	//	Cache-Control: max-age=0
	//	Accept-Encoding: gzip, deflate
	
	
#warning Don't free here, but elsewhere.
//	HTTPRequestFree(request);
	
	return request;
}

bool shouldAllowRequest(HTTPRequest request)
{
	HTTPRequestHeaderField hostField = HTTPRequestHeaderFieldForFieldNamed(HTTPRequestHeaderFieldName_Host);
	char *server = request[hostField];
	return shouldAllowServer(server);
}

bool shouldAllowServer(const char *server)
{
	// The end of the server string (used for finding suffix matches).
	const char *serverEnd = server + strlen(server);
	
	// Check against all of the filters.
	for ( int i=0; i<filtersCount; ++i ) {
		const char *filter = filters[i];
		
#warning Handle case of the string?
		
		// Check prefix.
		if ( strcmp(server, filter) == 0 ) {
			return false;
		}
		
		// Check suffix.
		if ( strcmp(serverEnd - strlen(filter), filter) == 0 ) {
			return false;
		}
		
	}
	
	return true;
}
