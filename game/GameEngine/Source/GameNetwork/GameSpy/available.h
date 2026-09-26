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
#ifndef _AVAILABLE_H_
#define _AVAILABLE_H_

#include "stringutil.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GSI_UNICODE
#define GSIStartAvailableCheck   GSIStartAvailableCheckA
#else
#define GSIStartAvailableCheck   GSIStartAvailableCheckW
#endif

// the available check contacts a backend server at "<gamename>.available.gamespy.com"
// an app can resolve the hostname itself and store the IP here before starting the check
extern char GSIACHostname[64];

// these are possible return types for GSIAvailableCheckThink
typedef enum
{
	GSIACWaiting,                 // still waiting for a response from the backend
	GSIACAvailable,               // the game's backend services are available
	GSIACUnavailable,             // the game's backend services are unavailable
	GSIACTemporarilyUnavailable   // the game's backend services are temporarily unavailable
} GSIACResult;

// start an available check for a particular game
// return 0 if no error starting up, non-zero if there's an error
void GSIStartAvailableCheck(const gsi_char * gamename);

// let the available check think
// continue to call this while it returns GSIACWaiting
// if it returns GSIACAvailable, use the GameSpy SDKs as normal
// if it returns GSIACUnavailable or GSIACTemporarilyUnavailable, do NOT
// continue to use the GameSpy SDKs.  the backend services are not available
// for the game.  in this case, you can show the user a
// message based on the particular result.
GSIACResult GSIAvailableCheckThink(void);

// this should only be used if the availability check needs to be aborted
// for example, if the player leaves the game's multiplayer area before the check completes
void GSICancelAvailableCheck(void);

// internal use only
extern GSIACResult __GSIACResult;
extern char __GSIACGamename[64];

#ifdef __cplusplus
}
#endif

#endif
