/*
**  GameSpy ghttp shim — minimal declarations for sweep compilation
**  Types match the public ghttp SDK: GHTTPBool enum, int request handle,
**  completed-callback signature used by MainMenuUtils.cpp.
*/

#pragma once

#ifndef __GHTTP_H__
#define __GHTTP_H__

typedef enum { GHTTPFalse = 0, GHTTPTrue = 1 } GHTTPBool;
typedef int GHTTPRequest;
typedef int GHTTPInt;
typedef enum {
	GHTTPSuccess = 0,
	GHTTPOutOfMemory,
	GHTTPBufferOverflow,
	GHTTPParseURLFailed,
	GHTTPSocketFailed,
	GHTTPConnectFailed,
	GHTTPBadResponse,
	GHTTPRequestRejected,
	GHTTPUnauthorized,
	GHTTPForbidden,
	GHTTPFileNotFound,
	GHTTPServerError,
	GHTTPRequestCancelled
} GHTTPResult;

typedef GHTTPBool (*GHTTPCompletedCallback)(GHTTPRequest request, GHTTPResult result,
	char* buffer, GHTTPInt bufferLen, void* param);

void ghttpStartup(void);
void ghttpCleanup(void);
void ghttpSetProxy(const char* proxy);
void ghttpThink(void);
GHTTPBool ghttpGet(const char* URL, GHTTPBool blocking,
	GHTTPCompletedCallback completedCallback, void* param);
GHTTPBool ghttpHead(const char* URL, GHTTPBool blocking,
	GHTTPCompletedCallback completedCallback, void* param);
char* ghttpGetHeaders(GHTTPRequest request);
void ghttpCancelRequest(GHTTPRequest request);

#endif // __GHTTP_H__
