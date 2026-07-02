// Minimal stand-in for GameEngine/Include/Common/Debug.h, which was not part of
// the GPL Generals release. wwdebug.h includes it to obtain DEBUG_LOGGING /
// DEBUG_CRASHING and the DEBUG_LOG / DEBUG_ASSERTCRASH / DEBUG_CRASH macros.
// The retail (Release) BFME build defines neither DEBUG_LOGGING nor
// DEBUG_CRASHING, so every WWASSERT / WWDEBUG_ERROR / WWDEBUG_SAY used by the
// ported code expands to nothing. Leaving both undefined here reproduces that.
#pragma once
#ifndef DEBUG_H
#define DEBUG_H
#endif // DEBUG_H
