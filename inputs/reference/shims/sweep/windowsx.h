/*
**  windowsx.h shim — framgrab.h includes it; FramGrab.cpp uses the Win16-era
**  GlobalAllocPtr/GlobalFreePtr aliases that the real windowsx.h provided
*/

#pragma once

#define GlobalAllocPtr(flags, cb)  GlobalLock(GlobalAlloc((flags), (cb)))
#define GlobalFreePtr(lp)          (GlobalUnlock((HGLOBAL)(lp)), GlobalFree((HGLOBAL)(lp)))
