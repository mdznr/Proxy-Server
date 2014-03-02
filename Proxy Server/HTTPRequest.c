//
//  HTTPRequest.c
//  Proxy Server
//
//  Created by Matt Zanchelli on 3/1/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "HTTPRequest.h"

#include "StringFunctions.h"

#pragma mark - Public API

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

HTTPResponseHeaderField HTTPResponseHeaderFieldForFieldNamed(HTTPResponseHeaderFieldName fieldName)
{
	if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Access_Control_Allow_Origin) ) {
		return HTTPResponseHeaderField_Access_Control_Allow_Origin;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Accept_Ranges) ) {
		return HTTPResponseHeaderField_Accept_Ranges;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Age) ) {
		return HTTPResponseHeaderField_Age;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Allow) ) {
		return HTTPResponseHeaderField_Allow;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Cache_Control) ) {
		return HTTPResponseHeaderField_Cache_Control;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Connection) ) {
		return HTTPResponseHeaderField_Connection;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Content_Encoding) ) {
		return HTTPResponseHeaderField_Content_Encoding;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Content_Language) ) {
		return HTTPResponseHeaderField_Content_Language;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Content_Length) ) {
		return HTTPResponseHeaderField_Content_Length;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Content_Location) ) {
		return HTTPResponseHeaderField_Content_Location;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Content_Type) ) {
		return HTTPResponseHeaderField_Content_Type;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Date) ) {
		return HTTPResponseHeaderField_Date;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_ETag) ) {
		return HTTPResponseHeaderField_ETag;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Expires) ) {
		return HTTPResponseHeaderField_Expires;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Last_Modified) ) {
		return HTTPResponseHeaderField_Last_Modified;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Link) ) {
		return HTTPResponseHeaderField_Link;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Location) ) {
		return HTTPResponseHeaderField_Location;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_P3P) ) {
		return HTTPResponseHeaderField_P3P;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Pragma) ) {
		return HTTPResponseHeaderField_Pragma;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Proxy_Authenticate) ) {
		return HTTPResponseHeaderField_Proxy_Authenticate;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Refresh) ) {
		return HTTPResponseHeaderField_Refresh;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Retry_After) ) {
		return HTTPResponseHeaderField_Retry_After;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Server) ) {
		return HTTPResponseHeaderField_Server;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Set_Cookie) ) {
		return HTTPResponseHeaderField_Set_Cookie;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Status) ) {
		return HTTPResponseHeaderField_Status;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Strict_Transport_Security) ) {
		return HTTPResponseHeaderField_Strict_Transport_Security;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Trailer) ) {
		return HTTPResponseHeaderField_Trailer;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Transfer_Encoding) ) {
		return HTTPResponseHeaderField_Transfer_Encoding;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Upgrade) ) {
		return HTTPResponseHeaderField_Upgrade;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Vary) ) {
		return HTTPResponseHeaderField_Vary;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Via) ) {
		return HTTPResponseHeaderField_Via;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_Warning) ) {
		return HTTPResponseHeaderField_Warning;
	} else if ( stringEquality(fieldName, HTTPResponseHeaderFieldName_WWW_Authenticate) ) {
		return HTTPResponseHeaderField_WWW_Authenticate;
	}
	
	// Conversion failed.
	return (HTTPResponseHeaderField) NULL;
}
