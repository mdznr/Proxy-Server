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
#include <ctype.h>

#include "Boolean.h"

char *stringDuplicate(const char *str)
{
	unsigned long n = strlen(str) + 1;
	char *dup = malloc(sizeof(char) * n);
	if ( dup ) {
		strcpy(dup, str);
	}
	return dup;
}

bool stringEquality(const char *s1, const char *s2)
{
	// Strings must be non-NULL.
	if ( !s1 || !s2 ) {
		return false;
	}
	
	return strcmp(s1, s2) == 0;
}

char *lowerCaseVersionOfString(const char *s)
{
	char *dup = stringDuplicate(s);
	for ( char *p = dup; *p != '\0'; ++p) *p = tolower(*p);
	return dup;
}

int caseInsensitiveStringComparison(const char *s1, const char *s2)
{
	// Convert to lower-case.
	char *s3 = lowerCaseVersionOfString(s1);
	char *s4 = lowerCaseVersionOfString(s2);
	
	// Make comparison.
	int result = strcmp(s3, s4);
	
	// Free the no-longer-needed strings.
	free(s3);
	free(s4);
	
	// Return the result.
	return result;
}

int caseInsensitiveStringComparisonLimited(const char *s1, const char *s2, size_t n)
{
	// Convert to lower-case.
	char *s3 = lowerCaseVersionOfString(s1);
	char *s4 = lowerCaseVersionOfString(s2);
	
	// Make comparison.
	int result = strncmp(s3, s4, n);
	
	// Free the no-longer-needed strings.
	free(s3);
	free(s4);
	
	// Return the result.
	return result;
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

char *substring(const char *begin, const char *end)
{
	// End must be after begin.
	if ( end <= begin ) {
		return NULL;
	}
	
	// The length of the string is the difference in pointers
	size_t stringLength = (end-begin);
	
	// Allocate size of the string length plus one for the null-terminator.
	char *sub = malloc(sizeof(char) * (stringLength + 1) );
	
	// Avoid diqualifying const.
	char *beginning = (char *) begin;
	
	// Copy over substring.
	memcpy(sub, beginning, sizeof(char) * stringLength);
	
	// Terminate the substring.
	sub[stringLength] = '\0';
	
	return sub;
}

char *prefixOfStringUpUntilCharacter(const char *string, const char character)
{
	char *occurance = strchr(string, (int) character);
	char *sub = substring(string, occurance);
	
	return sub;
}

char *prefixOfStringUpUntilString(const char *string, const char *end)
{
	char *occurance = strstr(string, end);
	char *prefix = substring(string, occurance);
	
	return prefix;
}

bool splitStringAtString(const char *fullString, const char *delimiter, char **firstString, char **secondString)
{
	// Must have valid fullString and delimiter.
	if ( fullString == NULL || delimiter == NULL ) {
		return false;
	}
	
	// Find the delimiter in the full string.
	char *occurance = strstr(fullString, delimiter);
	
	// Cannot continue if the delimiter is not in full string.
	if ( occurance == NULL ) {
		return false;
	}
	
	// First string is up until the occurance of the delimiter.
	*firstString = substring(fullString, occurance);
	
	// The second string is after the occurance of the delimiter.
	*secondString = stringDuplicate(occurance + strlen(delimiter));
	
	return true;
}
