//
//  StringFunctions.c
//  Proxy Server
//
//  Created by Matt Zanchelli on 3/1/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "Boolean.h"

bool stringEquality(const char *s1, const char *s2)
{
	return strcmp(s1, s2) == 0;
}
