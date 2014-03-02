//
//  HTTPRequest.h
//  Proxy Server
//
//  Created by Matt Zanchelli on 3/1/14.
//  Copyright (c) 2014 Matt Zanchelli. All rights reserved.
//

#ifndef Proxy_Server_HTTPRequest_h
#define Proxy_Server_HTTPRequest_h

#include "Boolean.h"

#pragma mark - Requests

/// A header field name for an HTTP Request.
typedef const char * const HTTPRequestHeaderFieldName;

static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Accept = "Accept";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Accept_Charset = "Accept-Charset";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Accept_Encoding = "Accept-Encoding";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Accept_Language = "Accept-Language";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Accept_Datetime = "Accept-Datetime";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Authorization = "Authorization";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Cache_Control = "Cache-Control";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Connection = "Connection";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Cookie = "Cookie";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Content_Length = "Content-Length";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Content_MD5 = "Content-MD5";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Content_Type = "Content-Type";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Date = "Date";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Expect = "Expect";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_From = "From";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Host = "Host";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_If_Match = "If-Match";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_If_Modified_Since = "If-Modified-Since";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_If_None_Match = "If-None-Match";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_If_Range = "If-Range";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_If_Unmodified_Since = "If-Unmodified-Since";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Max_Forwards = "Max-Forwards";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Origin = "Origin";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Pragma = "Pragma";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Proxy_Authorization = "Proxy-Authorization";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Range = "Range";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Referer = "Referer";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_TE = "TE";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_User_Agent = "User-Agent";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Via = "Via";
static HTTPRequestHeaderFieldName HTTPRequestHeaderFieldName_Warning = "Warning";

/// Enumerated header fields for an HTTP Request.
typedef enum {
	HTTPRequestHeaderField_Accept,
	HTTPRequestHeaderField_Accept_Charset,
	HTTPRequestHeaderField_Accept_Encoding,
	HTTPRequestHeaderField_Accept_Language,
	HTTPRequestHeaderField_Accept_Datetime,
	HTTPRequestHeaderField_Authorization,
	HTTPRequestHeaderField_Cache_Control,
	HTTPRequestHeaderField_Connection,
	HTTPRequestHeaderField_Cookie,
	HTTPRequestHeaderField_Content_Length,
	HTTPRequestHeaderField_Content_MD5,
	HTTPRequestHeaderField_Content_Type,
	HTTPRequestHeaderField_Date,
	HTTPRequestHeaderField_Expect,
	HTTPRequestHeaderField_From,
	HTTPRequestHeaderField_Host,
	HTTPRequestHeaderField_If_Match,
	HTTPRequestHeaderField_If_Modified_Since,
	HTTPRequestHeaderField_If_None_Match,
	HTTPRequestHeaderField_If_Range,
	HTTPRequestHeaderField_If_Unmodified_Since,
	HTTPRequestHeaderField_Max_Forwards,
	HTTPRequestHeaderField_Origin,
	HTTPRequestHeaderField_Pragma,
	HTTPRequestHeaderField_Proxy_Authorization,
	HTTPRequestHeaderField_Range,
	HTTPRequestHeaderField_Referer,
	HTTPRequestHeaderField_TE,
	HTTPRequestHeaderField_User_Agent,
	HTTPRequestHeaderField_Via,
	HTTPRequestHeaderField_Warning,
	
	/// The total number of @c HTTPRequestHeaderField
	HTTPRequestHeaderFieldsTotal
} HTTPRequestHeaderField;

/// Get the HTTPRequestHeaderField enum value for an HTTPRequestHeaderFieldName.
/// @param fieldName The @c HTTPRequestHeaderFieldName.
/// @return The @c HTTPRequestHeaderField enumeration value for the given field name or @c NULL if the conversion failed.
HTTPRequestHeaderField HTTPRequestHeaderFieldForFieldNamed(HTTPRequestHeaderFieldName fieldName);


#pragma mark - Responses

/// A header field name for an HTTP Response.
typedef const char * const HTTPResponseHeaderFieldName;

static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Access_Control_Allow_Origin = "Access-Control-Allow-Origin";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Accept_Ranges = "Accept-Ranges";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Age = "Age";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Allow = "Allow";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Cache_Control = "Cache-Control";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Connection = "Connection";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Content_Encoding = "Content-Encoding";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Content_Language = "Content-Language";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Content_Length = "Content-Length";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Content_Location = "Content-Location";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Content_MD5 = "Content-MD5";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Content_Disposition = "Content-Disposition";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Content_Range = "Content-Range";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Content_Type = "Content-Type";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Date = "Date";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_ETag = "ETag";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Expires = "Expires";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Last_Modified = "Last-Modified";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Link = "Link";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Location = "Location";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_P3P = "P3P";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Pragma = "Pragma";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Proxy_Authenticate = "Proxy-Authenticate";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Refresh = "Refresh";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Retry_After = "Retry-After";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Server = "Server";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Set_Cookie = "Set-Cookie";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Status = "Status";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Strict_Transport_Security = "Strict-Transport-Security";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Trailer = "Trailer";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Transfer_Encoding = "Transfer-Encoding";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Upgrade = "Upgrade";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Vary = "Vary";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Via = "Via";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_Warning = "Warning";
static HTTPResponseHeaderFieldName HTTPResponseHeaderFieldName_WWW_Authenticate = "WWW-Authenticate";

/// Enumerated header fields for an HTTP Response.
typedef enum {
	HTTPResponseHeaderField_Access_Control_Allow_Origin,
	HTTPResponseHeaderField_Accept_Ranges,
	HTTPResponseHeaderField_Age,
	HTTPResponseHeaderField_Allow,
	HTTPResponseHeaderField_Cache_Control,
	HTTPResponseHeaderField_Connection,
	HTTPResponseHeaderField_Content_Encoding,
	HTTPResponseHeaderField_Content_Language,
	HTTPResponseHeaderField_Content_Length,
	HTTPResponseHeaderField_Content_Location,
	HTTPResponseHeaderField_Content_MD5,
	HTTPResponseHeaderField_Content_Disposition,
	HTTPResponseHeaderField_Content_Range,
	HTTPResponseHeaderField_Content_Type,
	HTTPResponseHeaderField_Date,
	HTTPResponseHeaderField_ETag,
	HTTPResponseHeaderField_Expires,
	HTTPResponseHeaderField_Last_Modified,
	HTTPResponseHeaderField_Link,
	HTTPResponseHeaderField_Location,
	HTTPResponseHeaderField_P3P,
	HTTPResponseHeaderField_Pragma,
	HTTPResponseHeaderField_Proxy_Authenticate,
	HTTPResponseHeaderField_Refresh,
	HTTPResponseHeaderField_Retry_After,
	HTTPResponseHeaderField_Server,
	HTTPResponseHeaderField_Set_Cookie,
	HTTPResponseHeaderField_Status,
	HTTPResponseHeaderField_Strict_Transport_Security,
	HTTPResponseHeaderField_Trailer,
	HTTPResponseHeaderField_Transfer_Encoding,
	HTTPResponseHeaderField_Upgrade,
	HTTPResponseHeaderField_Vary,
	HTTPResponseHeaderField_Via,
	HTTPResponseHeaderField_Warning,
	HTTPResponseHeaderField_WWW_Authenticate,
	
	/// The total number of HTTPResponseHeaderField
	HTTPResponseHeaderFieldsTotal
} HTTPResponseHeaderField;

/// Get the HTTPResponseHeaderField enum value for an HTTPResponseHeaderFieldName.
/// @param fieldName The @c HTTPResponseHeaderFieldName.
/// @return The @c HTTPResponseHeaderField enumeration value for the given field name or @c NULL if the conversion failed.
HTTPResponseHeaderField HTTPResponseHeaderFieldForFieldNamed(HTTPResponseHeaderFieldName fieldName);

#endif
