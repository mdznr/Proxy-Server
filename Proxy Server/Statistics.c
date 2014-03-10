//
//  Statistics.c
//  Proxy Server
//
//  Created by Matt Zanchelli on 3/10/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>

#include "Statistics.h"

#include "MutexLock.h"

void incrementNumberOfSuccessfulRequests()
{
	printf("Incrementing numberOfSuccessfulRequests: %u\n", *numberOfSuccessfulRequests);
	SYNCHRONOUS_BLOCK((*numberOfSuccessfulRequests)++);
	printf("Incremented numberOfSuccessfulRequests: %u\n", *numberOfSuccessfulRequests);
}

void incrementNumberOfFilteredRequests()
{
	printf("Incrementing numberOfFilteredRequests: %u\n", *numberOfFilteredRequests);
	SYNCHRONOUS_BLOCK((*numberOfFilteredRequests)++);
	printf("Incremented numberOfFilteredRequests: %u\n", *numberOfFilteredRequests);
}

void incrementNumberOfErroredRequests()
{
	printf("Incrementing numberOfErroredRequests: %u\n", *numberOfErroredRequests);
	SYNCHRONOUS_BLOCK((*numberOfErroredRequests)++);
	printf("Incremented numberOfErroredRequests: %u\n", *numberOfErroredRequests);
}
