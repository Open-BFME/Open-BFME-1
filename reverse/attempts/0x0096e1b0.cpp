// ?Resize@?$SimpleVecClass@VVector2@@@@UAE_NH@Z
// partial score=0.85 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Open-BFME: byte-exact reconstruction of the retail
// SimpleVecClass<Vector2>::Resize(int) virtual method (RVA 0x0096E1B0), vtable
// slot 1 of 0x0113E684 (the same SimpleVecClass<Vector2> vtable landed piecemeal
// in decalmsh.cpp -- dtor, scalar-deleting dtor and Uninitialised_Grow already
// matched there via DecalMeshClass::TexCoords / IntersectDecalMeshClass::TexCoords,
// both SimpleDynVecClass<Vector2> members). That TU's copy of this same template
// method folded onto a different codegen (see assetmgr.cpp's alias with
// SimpleVecClass<FontCharsClass*>::Resize at 0x0078C820, a different byte
// sequence for the identical source); this retail body is a second, distinct
// compiland of the same header method, so it needs its own explicit
// instantiation in a fresh TU rather than editing decalmsh.cpp.
//
// simplevec.h's Resize(int newsize) is used unmodified:
//   if (newsize == VectorMax) return true;
//   if (newsize > 0) { T *newptr = new T[newsize]; if (Vector) { memcpy old,
//   delete[] old; } Vector = newptr; VectorMax = newsize; }
//   else { VectorMax = 0; if (Vector) { delete[] Vector; Vector = NULL; } }
// Vector2's constructor is a trivial-but-user-declared no-op, so `new
// Vector2[n]` still routes through the compiler's array constructor-iterator
// helper (retail call to 0x0005C600) under an EH scope for unwind-safety --
// no manual asm needed, just the ordinary array-new of a class with a
// user-declared (if empty) constructor.

#include "simplevec.h"
#include "vector2.h"

template bool SimpleVecClass<Vector2>::Resize(int);
