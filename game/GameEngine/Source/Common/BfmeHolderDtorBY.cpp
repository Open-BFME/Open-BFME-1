// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug
//
// Open-BFME5: a destructor at retail 0x0092A3D0, 90 bytes.  The body resets
// the holder before the eight-element array is torn down by the iterator.
//
// Retail's body is MeshMatDescClass's destructor: it calls the matched
// MeshMatDescClass::Reset at 0x00929310 and hands the vector-destructor
// iterator (0x009F6D76) the eight 4-byte elements at this+0x74 with their
// destructor's address.  This TU keeps the ledger's own class name for the two
// bodies it owns and reaches the two retail callees under their real names, so
// the object resolves against WW3D2/MeshMatDescClass_Reset_BFME.cpp and
// WW3D2/TextureHandleDestructor.cpp.

#include "meshmatdesc.h"

// BfmeHandleCX is the one-pointer owning texture handle BFME keeps in
// MeshMatDescClass's Texture[4][2]; its destructor is the COMDAT copy
// TextureHandleDestructor.cpp emits, so it is declared here and never defined.
// The data member stays public: with it private MSVC binds the array teardown
// to the compiler adapter ??_H@YGXPAXIHP6EPAX0@Z@Z and calls the iterator
// through ??_M@YGXPAXIHP6EPAX0@Z@Z, a helper retail never has.  Public keeps
// the call on the vendored CRT row ??_M@YGXPAXIHP6EX0@Z@Z at 0x009F6D76.
class BfmeHandleCX
{
public:
	~BfmeHandleCX(void);

	void *m_bfmeThing;
};

class BfmeHolderBY
{
public:
	~BfmeHolderBY(void);

	char m_bfmePadBY[0x74];
	BfmeHandleCX m_bfmeElemsBY[8];
};

BfmeHolderBY::~BfmeHolderBY(void)
{
	((MeshMatDescClass *)this)->MeshMatDescClass::Reset(0, 0, 0);
}

// The retail 30-byte wrapper is BfmeHolderBY's scalar-deleting destructor.
// Keep the delete expression separate from the matched body so MSVC emits
// its compiler-owned ??_G wrapper at the original address.
void Force_BfmeHolderBY_DeletingDestructor(BfmeHolderBY *value)
{
	delete value;
}