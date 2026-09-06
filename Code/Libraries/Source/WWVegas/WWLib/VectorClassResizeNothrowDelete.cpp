// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Open-BFME7: VectorClass<T>::Resize for the WWMath vector types, retail
//   0x009136F0 (480 bytes) VectorClass<Vector2>
//   0x007B9BC0 (515 bytes) VectorClass<Vector3>
//   0x009131E0 (550 bytes) VectorClass<Vector4>
// Every W3D TU that instantiates these compiles them 14-16 bytes too long
// (build/obj_dump_fuzzy.py found them at 0.92-0.93): retail's TU saw
// `operator delete[]` declared throw(), so after the vector-constructor
// iterator MSVC 7.1 has no reason to reset the EH state before the
// `delete[] Vector` of the old storage, and the loop alignment NOP that
// followed from the extra 8 bytes disappears with it.  Declaring the
// nothrow array delete before always.h gives the retail shape.

void __cdecl operator delete[](void *) throw();

#include "always.h"
#include "vector.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

template class VectorClass<Vector2>;
template class VectorClass<Vector3>;
template class VectorClass<Vector4>;
