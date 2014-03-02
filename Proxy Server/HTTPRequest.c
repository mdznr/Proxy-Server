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
	return (HTTPRequest) malloc(sizeof(char *) * HTTPRequestHeaderFieldsCount);
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
	return (HTTPRequestHeaderField) NULL;
}
