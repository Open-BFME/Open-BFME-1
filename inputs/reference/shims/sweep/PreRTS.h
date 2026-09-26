#pragma once
// PreRTS.h shim for sweeping GeneralsMD GameEngine sources. The real one
// (GameEngine/Include/Precompiled/PreRTS.h) drags in atlbase + the whole
// PlatformSDK, which the vendored toolchain doesn't have. This shim keeps the
// CRT + our windows.h stand-in, then includes the same ENGINE headers the real
// one does — those resolve from the actual reference tree, so class layouts
// and inlines are the real thing.
#ifndef __PRERTS_H__
#define __PRERTS_H__

// Retail is built against STLport's node allocator, not plain new/delete: an
// erase() expansion deallocates with the node size (push 0x18; call
// 0x0082E5F0, which buckets by (n-1)>>3 into the free-list array at
// 0x0130B1C0), where __new_alloc would emit a bare operator delete. Most TUs
// never show the difference because their container bodies are pinned rather
// than compiled, so the override stays the default; a TU that does show it
// defines BFME_STLP_NODE_ALLOC to opt out.
#ifndef BFME_STLP_NODE_ALLOC
#define _STLP_USE_NEWALLOC 1
#endif
class STLSpecialAlloc;

// GameMemory.h defines the ARRAY placement new/delete itself (unguarded); keep
// VC7.1's <new> from also defining them. Its SCALAR placement new is commented
// out, so the CRT's must remain visible — only the VEC guard goes on.
#define __PLACEMENT_VEC_NEW_INLINE

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <memory.h>
#include <mmsystem.h>
#include <snmp.h>
#include <process.h>
#include <direct.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <time.h>

#include "Lib/Basetype.h"
#include "Common/STLTypedefs.h"
#include "Common/Errors.h"
#include "Common/Debug.h"
#include "Common/AsciiString.h"
#include "Common/SubsystemInterface.h"
#include "Common/GameCommon.h"
#include "Common/GameMemory.h"
#include "Common/GameType.h"
#include "Common/GlobalData.h"
#include "Common/INI.h"
#include "Common/KindOf.h"
#include "Common/DisabledTypes.h"
#include "Common/NameKeyGenerator.h"
#include "GameClient/ClientRandomValue.h"
#include "GameLogic/LogicRandomValue.h"
#include "Common/ObjectStatusTypes.h"
#include "Common/Thing.h"
#include "Common/UnicodeString.h"

#endif /* __PRERTS_H__ */
