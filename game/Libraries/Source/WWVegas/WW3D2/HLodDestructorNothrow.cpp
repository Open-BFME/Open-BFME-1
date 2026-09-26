// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// Open-BFME7: retail 0x0097BB40 (152 bytes) is ??1Rva0097BB40HLod from hlod.cpp as built in a TU where
// operator delete/delete[] are declared throw() (docs/shape_levers.md); the port TU cannot
// carry that declaration without changing its other rows, so the class is renamed by macro
// and only this member is defined here.
#define HLodClass Rva0097BB40HLod
void __cdecl operator delete[](void *) throw();
void __cdecl operator delete(void *) throw();
#include "winbase_shim.h"
#include "hlod.h"
#include "assetmgr.h"
#include "hmdldef.h"
#include "w3derr.h"
#include "chunkio.h"
#include "predlod.h"
#include "rinfo.h"
#include <string.h>
#include "winbase_shim.h"
#include "sphere.h"
#include "boxrobj.h"

Rva0097BB40HLod::~Rva0097BB40HLod(void)
{
	Free();
}
