// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// stlport
//
// Retail 0x007DC9A0: destructor for the filter object constructed at
// 0x007DCA80.  A vector of 12-byte POD values precedes two ref holders.

#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "../../../../Libraries/Source/WWVegas/WW3D2/texture.h"

class Rva007DC9A0RefHolder
{
public:
	~Rva007DC9A0RefHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

private:
	TextureBaseClass *m_ptr;
};

struct Rva007DC9A0Pod12
{
	int value[3];
};

class Rva007DCA80
{
public:
	~Rva007DCA80();

private:
	unsigned char m_unreconstructed_00[0x34];
	_STL::vector<Rva007DC9A0Pod12> m_values;
	unsigned char m_unreconstructed_40[0x18];
	Rva007DC9A0RefHolder m_ref58;
	Rva007DC9A0RefHolder m_ref5C;
};

Rva007DCA80::~Rva007DCA80()
{
}
