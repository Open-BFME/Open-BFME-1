// Zero Hour's Common/AsciiString.h, replaced by BFME's canonical AsciiString.
//
// A Zero Hour source compiled against the vendored tree gets Zero Hour's
// standalone AsciiString, whose inline destructor, copy constructor and
// releaseBuffer are not the bodies retail shipped: its ??1AsciiString@@QAE@XZ
// COMDAT is an InterlockedDecrement + freeBytes sequence where retail's
// (0x0005EE90) is a bare `jmp` to StringBase<char>::releaseBuffer
// (0x00887940). A TU that puts this directory ahead of the vendored include
// dirs compiles game/Libraries/Source/WWVegas/WWLib/ascii_string.h instead.
// Everything below the canonical include is what the vendored header brought
// in for its dependents.
#ifndef ASCIISTRING_H
#define ASCIISTRING_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "Lib/BaseType.h"
#include "Common/Debug.h"
#include "Common/Errors.h"

#include "../../../../../game/Libraries/Source/WWVegas/WWLib/ascii_string.h"

#include "windows.h"

#endif
