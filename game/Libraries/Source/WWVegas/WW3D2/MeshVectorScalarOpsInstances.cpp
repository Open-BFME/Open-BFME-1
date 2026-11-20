// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
#define Matrix4x4 Matrix4
#include "winbase_shim.h"

// Westwood vector template instances that retail took from an object built
// without always.h's operator new[]/delete[]: their array new/delete call
// ::operator new/delete (??2 0x00881F30, ??3 0x00881EB0), unlike meshmdl.obj and
// pointgr.obj.  Same flags and headers as meshmdl.cpp otherwise.
#define _OPERATOR_NEW_DEFINED_
#include "meshmdl.h"
#include "vector.h"
#include "vector4.h"

template void DynamicVectorClass<Vector4>::Clear(void);
template bool VectorClass<unsigned long>::Resize(int, unsigned long const *);
template class DynamicVectorClass<unsigned long>;
template void VectorClass<unsigned char>::Clear(void);
