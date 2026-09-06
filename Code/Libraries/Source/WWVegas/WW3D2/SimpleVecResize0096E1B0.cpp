// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Open-BFME7: SimpleVecClass<Vector2-like element>::Resize, retail 0x0096E1B0 (201 bytes): the
// nothrow-delete twin (docs/shape_levers.md) that decalmsh.cpp, hmorphanim.cpp, meshmdlio.cpp,
// ringobj.cpp and sphereobj.cpp all compile byte-identically for their own 8-byte elements;
// same preprocessor preamble as decalmsh.cpp, address-tagged element.
void __cdecl operator delete[](void *) throw();
void __cdecl operator delete(void *) throw();
#define Matrix4x4 Matrix4  // BFME renamed it
#include "decalmsh.h"
#include "decalsys.h"
#include "rinfo.h"
#include "mesh.h"
#include "meshmdl.h"
#include "plane.h"
#include "statistics.h"
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "simplevec.h"
#include "texture.h"
#include "dx8wrapper.h"
#include "dx8caps.h"

struct Rva0096E1B0Elem : public Vector2 {};

template class SimpleVecClass<Rva0096E1B0Elem>;
