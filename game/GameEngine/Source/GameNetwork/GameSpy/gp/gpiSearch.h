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
gpiSearch.h
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

#ifndef _GPISEARCH_H_
#define _GPISEARCH_H_

//INCLUDES
//////////
#include "gpi.h"

//TYPES
///////
#define GPI_SEARCH_PROFILE         1
#define GPI_SEARCH_IS_VALID        2
#define GPI_SEARCH_NICKS           3
#define GPI_SEARCH_PLAYERS         4
#define GPI_SEARCH_CHECK           5
#define GPI_SEARCH_NEWUSER         6
#define GPI_SEARCH_OTHERS_BUDDY    7
#define GPI_SEARCH_SUGGEST_UNIQUE  8

// Profile Search operation data.
/////////////////////////////////
typedef struct
{
	int type;
	SOCKET sock;
	GPIBuffer inputBuffer;
	GPIBuffer outputBuffer;
	char nick[GP_NICK_LEN];
	char uniquenick[GP_UNIQUENICK_LEN];
	char email[GP_EMAIL_LEN];
	char firstname[GP_FIRSTNAME_LEN];
	char lastname[GP_LASTNAME_LEN];
	char password[GP_PASSWORD_LEN];
	char cdkey[GP_CDKEY_LEN];
	int icquin;
	int skip;
	int productID;
	GPIBool processing;
	GPIBool remove;
} GPISearchData;

//FUNCTIONS
///////////
GPResult
gpiProfileSearch(
  GPConnection * connection,
  const char nick[GP_NICK_LEN],
  const char uniquenick[GP_UNIQUENICK_LEN],
  const char email[GP_EMAIL_LEN],
  const char firstname[GP_FIRSTNAME_LEN],
  const char lastname[GP_LASTNAME_LEN],
  int icquin,
  int skip,
  GPEnum blocking,
  GPCallback callback,
  void * param
);

GPResult
gpiIsValidEmail(
  GPConnection * connection,
  const char email[GP_EMAIL_LEN],
  GPEnum blocking,
  GPCallback callback,
  void * param
);

GPResult
gpiGetUserNicks(
  GPConnection * connection,
  const char email[GP_EMAIL_LEN],
  const char password[GP_PASSWORD_LEN],
  GPEnum blocking,
  GPCallback callback,
  void * param
);

GPResult
gpiFindPlayers(
  GPConnection * connection,
  int productID,
  GPEnum blocking,
  GPCallback callback,
  void * param
);

GPResult gpiCheckUser(
  GPConnection * connection,
  const char nick[GP_NICK_LEN],
  const char email[GP_EMAIL_LEN],
  const char password[GP_PASSWORD_LEN],
  GPEnum blocking,
  GPCallback callback,
  void * param
);

GPResult gpiNewUser(
  GPConnection * connection,
  const char nick[GP_NICK_LEN],
  const char uniquenick[GP_UNIQUENICK_LEN],
  const char email[GP_EMAIL_LEN],
  const char password[GP_PASSWORD_LEN],
  const char cdkey[GP_CDKEY_LEN],
  GPEnum blocking,
  GPCallback callback,
  void * param
);

GPResult gpiOthersBuddy(
  GPConnection * connection,
  GPEnum blocking,
  GPCallback callback,
  void * param
);

GPResult gpiSuggestUniqueNick(
  GPConnection * connection,
  const char desirednick[GP_NICK_LEN],
  GPEnum blocking,
  GPCallback callback,
  void * param
);

GPResult
gpiProcessSearches(
  GPConnection * connection
);

#endif
