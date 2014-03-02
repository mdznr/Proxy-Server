//
//  StringFunctions.h
//  Proxy Server
//
//  Created by Matt Zanchelli on 3/1/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#ifndef Proxy_Server_StringFunctions_h
#define Proxy_Server_StringFunctions_h

#include "Boolean.h"

/// Test the equality of two strings.
/// @param s1 The first string.
/// @param s2 The second string.
/// @return Whether or not the strings are equal.
bool stringEquality(const char *s1, const char *s2);

/// Find the index of the first occurance of a character in a string.
/// @param string The null-terminated byte stream.
/// @param character The character to search for.
/// @return The index at which the first instace of @c character exists in @c string.
/// @discussion Returns -1 if not found.
int indexOfFirstOccuranceOfCharacterInString(const char *string, const char character);

/// Create a substring.
/// @param begin The pointer to the beginning of the string.
/// @param end The pointer to the end of the substring.
/// @return A newly allocated string for the substring.
char *substr(const char *begin, const char *end);

/// Get the prefix of a string until a specific character.
/// @param string The null-terminated byte stream.
/// @param character The character to search for.
/// @return A newly allocated string containing the prefix of @c string up until the first occurance of @c character.
/// @discussion Returns @c NULL if @c character does not exist in @c string.
char *prefixUntilCharacter(const char *string, const char character);

/// Get the prefix of a string until a substring.
/// @param string The null-terminated byte stream.
/// @param substring The substring to end at.
/// @return A newly allocated string containing the prefix of @c string up until the first cocurance of @c substring.
/// @discussion Returns @c NULL if @c substring does not exist in @c string.
char *prefixOfStringUpUntilString(const char *string, const char *substring);

/// Split a string into two with a string separator.
/// @param fullString The full string to split.
/// @param delimiter The delimiter to split on the first occurance of in @c fullString.
/// @param firstString Will be the part of @c fullString that appears before @c delimiter.
/// @param secondString Will be the part of @c secondString that appears after @c delimiter.
void splitStringAtString(const char *fullString, const char *delimiter, char **firstString, char **secondString);

#endif
