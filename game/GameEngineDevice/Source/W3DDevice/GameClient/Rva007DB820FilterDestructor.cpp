// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x007DB700: destructor for the filter object constructed at
// 0x007DB820.  Two ref holders precede two vectors of 12-byte POD values.

#include <vector>

class Rva007D6AB0SubPtr
{
public:
	void release();
};

class Rva007DB700RefHolder
{
public:
	~Rva007DB700RefHolder()
	{
		if (m_ptr)
			m_ptr->release();
	}

private:
	Rva007D6AB0SubPtr *m_ptr;
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
