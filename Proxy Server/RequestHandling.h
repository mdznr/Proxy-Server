//
//  RequestHandling.h
//  Proxy Server
//
//  Created by Matt Zanchelli on 3/1/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#ifndef Proxy_Server_RequestHandling_h
#define Proxy_Server_RequestHandling_h

#include "Boolean.h"
#include "HTTP.h"

/// A structure to hold a file descriptor and a message.
typedef struct {
	/// Socket/File Descriptor.
	int sock;
	
	/// The address in the communications space of the socket.
	struct sockaddr_in address;
	
	/// Message sent by fd.
	char *msg;
} sock_msg;

/// The filters to ignore.
/// @discussion Filters out any request to a server that starts or ends with the filter string.
const char **filters;

/// The total count of filters.
unsigned int *filtersCount;

/// Handle an HTTP request.
/// @param arg The request string.
/// @return @c NULL
/// @discussion Designed for use in new thread.
void *handleRequest(void *arg);

#endif
