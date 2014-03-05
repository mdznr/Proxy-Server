//
//  HTTPRequest.c
//  Proxy Server
//
//  Created by Matt Zanchelli on 3/1/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HTTPRequest.h"

#include "StringFunctions.h"

HTTPRequest HTTPRequestCreate()
{
	// Create an array of strings; one for each header field.
	return (HTTPRequest) calloc(HTTPRequestHeaderFieldsCount, sizeof(char *));
}

void HTTPRequestFree(HTTPRequest request)
{
	// Free all the strings contained in the request.
	for ( int i=0; i<HTTPRequestHeaderFieldsCount; ++i ) {
		// Only if there is a value for this field.
		if ( request[i] != NULL ) {
			free(request[i]);
			request[i] = NULL;
		}
	}
	
	// Free the request itself.
	free(request);
}

bool validateRequest(HTTPRequest request)
{
	/*
	 Request-Line specifications via http://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html
	 Request-Line = Method SP Request-URI SP HTTP-Version CRLF
	 */
	
	char *Request_Line = request[HTTPRequestHeaderField_Request_Line];
	
	char *Method = NULL;
	char *MethodArgs = NULL;
	if ( !splitStringAtString(Request_Line, " ", &Method, &MethodArgs) ) {
		// Invalid Request-Line.
		return false;
	}
	
	char *Request_URI = NULL;
	char *HTTP_Version = NULL;
	if ( !splitStringAtString(MethodArgs, " ", &Request_URI, &HTTP_Version) ) {
		// Invalid Request-Line.
		return false;
	}
	
	// TODO: Check if valid Request-URI.
	
	// Check if supported HTTP-Version.
	if ( stringEquality(HTTP_Version, "HTTP/1.1") ) {
		// HTTP/1.1 is supported.
	} else if ( stringEquality(HTTP_Version, "HTTP/1.0") ) {
		// HTTP/1.0 is supported.
	} else {
		// Unsupported or invalid HTTP-Version.
		return false;
	}
	
	// Must include Host.
	if ( request[HTTPRequestHeaderField_Host] == NULL ) {
		return false;
	}
	
	// If POST, must include Content-Length.
	if ( stringEquality(Method, "POST") ) {
		if ( request[HTTPRequestHeaderField_Content_Length] == NULL ) {
			return false;
		}
	}
	
	// No errors are found.
	return true;
}

char *requestStringFromRequest(HTTPRequest request)
{
	char *requestLine = request[HTTPRequestHeaderField_Request_Line];
	if ( !requestLine ) {
		return NULL;
	}
	
#warning TODO: modify request line.
	
	char *string = strdup(requestLine);
	
	for ( int i=0; i<HTTPRequestHeaderFieldsCount; ++i ) {
		// Skip the request line.
		if ( i == HTTPRequestHeaderField_Request_Line ) {
			continue;
		}
		
		char *line = request[i];
		if ( line ) {
			unsigned long newLength = strlen(string) + strlen("\r\n") + strlen(line);
			char *biggerString = malloc(sizeof(char) * (newLength + 1));
			strcpy(biggerString, string);
			free(string);
			strcat(biggerString, "\r\n");
			strcat(biggerString, line);
			string = biggerString;
		}
	}
	
	// End of message.
	unsigned long newLength = strlen(string) + strlen("\r\n\r\n");
	char *biggerString = malloc(sizeof(char) * (newLength + 1));
	strcpy(biggerString, string);
	strcat(biggerString, "\r\n\r\n");
	free(string);
	string = biggerString;
	
	return string;
}

HTTPRequestHeaderField HTTPRequestHeaderFieldForFieldNamed(HTTPRequestHeaderFieldName fieldName)
{
	if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Accept) ) {
		return HTTPRequestHeaderField_Accept;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Accept_Charset) ) {
		return HTTPRequestHeaderField_Accept_Charset;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Accept_Encoding) ) {
		return HTTPRequestHeaderField_Accept_Encoding;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Accept_Language) ) {
		return HTTPRequestHeaderField_Accept_Language;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Accept_Datetime) ) {
		return HTTPRequestHeaderField_Accept_Datetime;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Authorization) ) {
		return HTTPRequestHeaderField_Authorization;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Cache_Control) ) {
		return HTTPRequestHeaderField_Cache_Control;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Connection) ) {
		return HTTPRequestHeaderField_Connection;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Proxy_Connection) ) {
		return HTTPRequestHeaderField_Proxy_Connection;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Cookie) ) {
		return HTTPRequestHeaderField_Cookie;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Content_Length) ) {
		return HTTPRequestHeaderField_Content_Length;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Content_MD5) ) {
		return HTTPRequestHeaderField_Content_MD5;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Content_Type) ) {
		return HTTPRequestHeaderField_Content_Type;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Date) ) {
		return HTTPRequestHeaderField_Date;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Expect) ) {
		return HTTPRequestHeaderField_Expect;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_From) ) {
		return HTTPRequestHeaderField_From;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Host) ) {
		return HTTPRequestHeaderField_Host;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_If_Match) ) {
		return HTTPRequestHeaderField_If_Match;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_If_Modified_Since) ) {
		return HTTPRequestHeaderField_If_Modified_Since;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_If_None_Match) ) {
		return HTTPRequestHeaderField_If_None_Match;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_If_Range) ) {
		return HTTPRequestHeaderField_If_Range;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_If_Unmodified_Since) ) {
		return HTTPRequestHeaderField_If_Unmodified_Since;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Max_Forwards) ) {
		return HTTPRequestHeaderField_Max_Forwards;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Origin) ) {
		return HTTPRequestHeaderField_Origin;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Pragma) ) {
		return HTTPRequestHeaderField_Pragma;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Proxy_Authorization) ) {
		return HTTPRequestHeaderField_Proxy_Authorization;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Pragma) ) {
		return HTTPRequestHeaderField_Pragma;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Proxy_Authorization) ) {
		return HTTPRequestHeaderField_Proxy_Authorization;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Range) ) {
		return HTTPRequestHeaderField_Range;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Referer) ) {
		return HTTPRequestHeaderField_Referer;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_TE) ) {
		return HTTPRequestHeaderField_TE;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_User_Agent) ) {
		return HTTPRequestHeaderField_User_Agent;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Via) ) {
		return HTTPRequestHeaderField_Via;
	} else if ( stringEquality(fieldName, HTTPRequestHeaderFieldName_Warning) ) {
		return HTTPRequestHeaderField_Warning;
	}
	
	// Conversion failed.
	return -1;
}
