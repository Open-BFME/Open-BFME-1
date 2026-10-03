// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// stlport
//
// Retail 0x007DB700: destructor for the filter object constructed at
// 0x007DB820.  Two ref holders precede two vectors of 12-byte POD values.

#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h supplies array placement new
#include <texture.h>
#include <vector>

class Rva007DB700RefHolder
{
public:
	~Rva007DB700RefHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

private:
	TextureBaseClass *m_ptr;
};

struct Rva007DB700Pod12
{
	int value[3];
};

class Rva007DB820
{
public:
	~Rva007DB820();

private:
	unsigned char m_unreconstructed_00[0x10];
	Rva007DB700RefHolder m_ref10;
	Rva007DB700RefHolder m_ref14;
	unsigned char m_unreconstructed_18[0x14];
	_STL::vector<Rva007DB700Pod12> m_values2C;
	_STL::vector<Rva007DB700Pod12> m_values38;
};

Rva007DB820::~Rva007DB820()
{
}
