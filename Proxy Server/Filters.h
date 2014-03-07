//
//  Filters.h
//  Proxy Server
//
//  Created by Matt Zanchelli on 3/7/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#ifndef Proxy_Server_Filters_h
#define Proxy_Server_Filters_h

/// The filters to ignore.
/// @discussion Filters out any request to a server that starts or ends with the filter string.
const char **filters;

/// The total count of filters.
unsigned int *filtersCount;

#endif
