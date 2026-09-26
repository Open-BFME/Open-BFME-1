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
gpiUtility.h
GameSpy Presence SDK 
Dan "Mr. Pants" Schoenblum

Copyright 1999-2001 GameSpy Industries, Inc

18002 Skypark Circle
Irvine, California 92614
949.798.4200 (Tel)
949.798.4299 (Fax)
devsupport@gamespy.com

***********************************************************************
Please see the GameSpy Presence SDK documentation for more information
**********************************************************************/

#ifndef _GPIUTILITY_H_
#define _GPIUTILITY_H_

//INCLUDES
//////////
#include "gpi.h"

//DEFINES
/////////
// Buffer read size.
////////////////////
#define GPI_READ_SIZE                  (16 * 1024)

//MACROS
////////
#define freeclear(mem)      { gsifree(mem); (mem) = NULL; }

#define Error(connection, result, string)       { gpiSetErrorString(connection, string);\
                                                       return (result);}

#define CallbackError(connection, result, code, string)  { gpiSetError(connection, code, string);\
                                                           gpiCallErrorCallback(connection, result, GP_NON_FATAL);\
                                                           return result;}

#define CallbackFatalError(connection, result, code, string)  { gpiSetError(connection, code, string);\
                                                                 gpiCallErrorCallback(connection, result, GP_FATAL);\
                                                                 return result;}

#define CHECK_RESULT(result)                          { GPResult __result__ = (result);\
                                                        if(__result__ != GP_NO_ERROR){\
                                                          return __result__;}}

//FUNCTIONS
///////////
void
strzcpy(
  char * dest,
  const char * src,
  size_t len  // length of buffer, including space for '\0'
);

void
UTF8ToUCS2StringLen(
  const char * src,
  unsigned short * dest,
  size_t len  // length of buffer, including space for '\0'
);

void
gpiDebug(
  GPConnection * connection,
  const char * fmt,
  ...
);

GPIBool
gpiValueForKey(
  const char * command,
  const char * key,
  char * value,
  int len
);

char *
gpiValueForKeyAlloc(
  const char * command,
  const char * key
);

GPResult
gpiCheckSocketConnect(
  GPConnection * connection,
  SOCKET sock,
  int * state
);

GPResult
gpiReadKeyAndValue(
  GPConnection * connection,
  const char * buffer,
  int * index,
  char key[512],
  char value[512]
);

GPIBool
gpiCheckForError(
  GPConnection * connection,
  const char * input,
  GPIBool callErrorCallback
);

void
gpiSetError(
  GPConnection * connection,
  GPErrorCode errorCode,
  const char * errorString
);

void
gpiSetErrorString(
  GPConnection * connection,
  const char * errorString
);

#endif
