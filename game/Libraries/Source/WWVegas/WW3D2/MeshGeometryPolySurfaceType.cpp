// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// Local semantic ABI slice for retail RVA 0x00924810.
//
// The existing header names this role Get_Poly_Surface_Type, and its inline
// body has the same NDEBUG operations.  Since the retail body has no surviving
// symbol row or direct call edge, this method name is address-qualified and
// records the recovered role without asserting a historical decorated name.

#include "always.h"
#include "sharebuf.h"

class MeshGeometryClass
{
	char _prefix_through_5c[0x60];
	ShareBufferClass<unsigned char> *PolySurfaceType; // retail this+0x60

public:
	// Recovered role/address label only; original standalone symbol is unknown.
	unsigned char Rva00924810PolySurfaceTypeAt(int poly_index) const;
};

unsigned char MeshGeometryClass::Rva00924810PolySurfaceTypeAt(int poly_index) const
{
	unsigned char *type = PolySurfaceType->Get_Array();
	return type[poly_index];
}
