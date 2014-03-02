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

/// Handle an HTTP request.
/// @param arg The request string.
/// @return @c NULL
/// @discussion Designed for use in new thread.
void *handleRequest(void *arg);

#endif
