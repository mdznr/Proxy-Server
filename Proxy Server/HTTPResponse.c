//
//  HTTPResponse.c
//  Proxy Server
//
//  Created by Matt Zanchelli on 3/1/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HTTPResponse.h"

#include "StringFunctions.h"

HTTPResponse HTTPResponseCreate()
{
	return (HTTPResponse) malloc(sizeof(char *) * HTTPResponseHeaderFieldsCount);
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
