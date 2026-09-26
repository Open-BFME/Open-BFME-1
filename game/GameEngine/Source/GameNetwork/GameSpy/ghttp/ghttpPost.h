/* GameSpy SDK, 2004 vintage -- pristine upstream C source.
   Sourced from the Area 51 (Inevitable Entertainment / Midway) source release,
   github.com/bisc67/Area51, Support/NetworkMgr/GameSpy -- the only public
   carrier found with the pre-2005 SDK layout (top-level nonport.c, no common/).
   Dated by nonport.h's own marker "Added by Saad Nader on 08-02-2004".
   That vintage is not assumed, it is measured: against lotrbfme.exe this tree
   scores 440 byte-exact whole functions where the 2007 SDK (nitrocaster/GameSpy,
   GS_Aluigi) scores 51 and 48 on the same TUs.
   Retail linked the DLL CRT, so libc calls are __imp__ indirect -- /MD is what
   makes those call sites byte-exact -- and built the SDK __cdecl: /Gz collapses
   the qr2+GP+ghttp core from 108 exact hits to 6.
   Win32 headers come from inputs/reference/shims/gamespy (see its windows.h): the
   toolchain ships no PlatformSDK, and the sweep shim next door is C++-only. */
 /*
GameSpy GHTTP SDK 
Dan "Mr. Pants" Schoenblum
dan@gamespy.com

Copyright 1999-2001 GameSpy Industries, Inc

18002 Skypark Circle
Irvine, California 92614
949.798.4200 (Tel)
949.798.4299 (Fax)
devsupport@gamespy.com
*/

#ifndef _GHTTPPOST_H_
#define _GHTTPPOST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ghttp.h"
#include "ghttpBuffer.h"
#include "../darray.h"

typedef enum
{
	GHIPostingError,
	GHIPostingDone,
	GHIPostingPosting
} GHIPostingResult;

typedef struct GHIPostingState
{
	DArray states;
	int index;
	int bytesPosted;
	int totalBytes;
	ghttpPostCallback callback;
	void * param;
} GHIPostingState;

GHTTPPost ghiNewPost
(
	void
);

void ghiPostSetAutoFree
(
	GHTTPPost post,
	GHTTPBool autoFree
);

GHTTPBool ghiIsPostAutoFree
(
	GHTTPPost post
);

void ghiFreePost
(
	GHTTPPost post
);

GHTTPBool ghiPostAddString
(
	GHTTPPost post,
	const char * name,
	const char * string
);

GHTTPBool ghiPostAddFileFromDisk
(
	GHTTPPost post,
	const char * name,
	const char * filename,
	const char * reportFilename,
	const char * contentType
);

GHTTPBool ghiPostAddFileFromMemory
(
	GHTTPPost post,
	const char * name,
	const char * buffer,
	int bufferLen,
	const char * reportFilename,
	const char * contentType
);

void ghiPostSetCallback
(
	GHTTPPost post,
	ghttpPostCallback callback,
	void * param
);

const char * ghiPostGetContentType
(
	struct GHIConnection * connection
);

GHTTPBool ghiPostInitState
(
	struct GHIConnection * connection
);

void ghiPostCleanupState
(
	struct GHIConnection * connection
);

GHIPostingResult ghiPostDoPosting
(
	struct GHIConnection * connection
);

#ifdef __cplusplus
}
#endif

#endif
