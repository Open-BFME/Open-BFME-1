// ?Clone@VertexMaterialClass@@QAEPAV1@XZ
// partial score=0.6 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
//
// FUZZY-TWIN of ?newCommandSet@ControlBar@@IAEPAVCommandSet@@ABVAsciiString@@@Z
// (0x0049CD10, 104B): same "allocate, default-construct, assign, return
// pointer" shell, but this is VertexMaterialClass::Clone(void), defined
// INLINE in Code/Libraries/Source/WWVegas/WW3D2/vertmaterial.h:
//   VertexMaterialClass *Clone(void)
//   { VertexMaterialClass *mat = NEW_REF(VertexMaterialClass,()); *mat = *this; return mat; }
// Taking its address forces MSVC to emit the real out-of-line body under its
// own mangled name instead of inlining it away; the default ctor and
// operator= it calls are already matched in vertmaterial.cpp, so this file
// only needs to reference the header, not redefine anything.

#include "vertmaterial.h"

typedef VertexMaterialClass *(VertexMaterialClass::*Clone0092EF30Ptr)(void);
Clone0092EF30Ptr g_forceEmitClone0092EF30 = &VertexMaterialClass::Clone;
