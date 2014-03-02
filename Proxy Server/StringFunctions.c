//
//  StringFunctions.c
//  Proxy Server
//
//  Created by Matt Zanchelli on 3/1/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Boolean.h"

bool stringEquality(const char *s1, const char *s2)
{
	return strcmp(s1, s2) == 0;
}

int indexOfFirstOccuranceOfCharacterInString(const char *string, const char character)
{
	// Must not be NULL.
	if ( string == NULL ) {
		return -1;
	}
	
	// The index of the character.
	int index = 0;
	while ( string[index] != '\0' ) {
		if ( string[index] == character ) {
			return index;
		}
		++index;
	}
	
	// Could not find the character in the string.
	return -1;
}

char *substr(const char *begin, const char *end)
{
	// End must be after begin.
	if ( end <= begin ) {
		return NULL;
	}
	
	// The length of the string is the difference in pointers
	size_t stringLength = (end-begin);
	
	// Allocate size of the string length plus one for the null-terminator.
	char *substring = malloc(sizeof(char) * (stringLength + 1) );
	
	// Avoid diqualifying const.
	char *beginning = (char *) begin;
	
	// Copy over substring.
	memcpy(substring, beginning, sizeof(char) * stringLength);
	
	// Terminate the substring.
	substring[stringLength] = '\0';
	
	return substring;
}

char *prefixOfStringUpUntilCharacter(const char *string, const char character)
{
	char *occurance = strchr(string, (int) character);
	char *substring = substr(string, occurance);
	
	return substring;
}

char *prefixOfStringUpUntilString(const char *string, const char *substring)
{
	char *occurance = strstr(string, substring);
	char *prefix = substr(string, occurance);
	
	return prefix;
}

bool splitStringAtString(const char *fullString, const char *delimiter, char **firstString, char **secondString)
{
	// Find the delimiter in the full string.
	char *occurance = strstr(fullString, delimiter);
	
	// Cannot continue if the delimiter is not in full string.
	if ( occurance == NULL ) {
		return false;
	}
	
	// First string is up until the occurance of the delimiter.
	*firstString = substr(fullString, occurance);
	
	// The second string is after the occurance of the delimiter.
	*secondString = strdup(occurance + strlen(delimiter));
	
	return true;
}
