//
//  Statistics.c
//  Proxy Server
//
//  Created by Matt Zanchelli on 3/10/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>

#include <libkern/OSAtomic.h>

#include "Statistics.h"

void incrementNumberOfSuccessfulRequests()
{
	OSAtomicAdd32(1, &numberOfSuccessfulRequests);
}

void incrementNumberOfFilteredRequests()
{
	OSAtomicAdd32(1, &numberOfFilteredRequests);
}

void incrementNumberOfErroredRequests()
{
	OSAtomicAdd32(1, &numberOfErroredRequests);
}
