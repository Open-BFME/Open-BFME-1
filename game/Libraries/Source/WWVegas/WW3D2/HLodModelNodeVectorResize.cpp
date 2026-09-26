// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// Open-BFME7: VectorClass<HLodClass::ModelNodeClass>::Resize, retail 0x0097ADF0
// (588 bytes).  Two things fix the shape: retail's TU saw operator delete[]
// declared throw() (no EH-state reset after the vector-constructor iterator,
// see VectorClassResizeNothrowDelete.cpp), and the element must copy through
// the compiler-generated assignment -- hlod.h's ModelNodeClass, with its
// user-written comparison operators and constructor, hoists the copy loop's
// three invariant loads in a different order (10 bytes off), so the 20-byte
// node (RenderObjClass pointer, bone index, Vector3 offset) is spelled here as
// an address-tagged twin of that class.

void __cdecl operator delete[](void *) throw();

#include "winbase_shim.h"
#include "hlod.h"

class Rva0097ADF0Node
{
public:
	bool operator==( const Rva0097ADF0Node &o ) const;
	bool operator!=( const Rva0097ADF0Node &o ) const;
	RenderObjClass *Model;
	int BoneIndex;
	Vector3 Offset;
};

template class VectorClass<Rva0097ADF0Node>;
