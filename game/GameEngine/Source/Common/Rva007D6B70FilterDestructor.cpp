// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x007D6AB0: destructor for the filter object constructed at
// 0x007D6B70.  Two reference holders precede a vector of 12-byte POD values.

#include <vector>

class Rva007D6AB0SubPtr
{
public:
	void release();
};

class Rva007D6AB0RefHolder
{
public:
	~Rva007D6AB0RefHolder()
	{
		if (m_ptr)
			m_ptr->release();
	}

private:
	Rva007D6AB0SubPtr *m_ptr;
};

struct Rva007D6AB0Pod12
{
	int value[3];
};

class Rva007D6B70
{
public:
	~Rva007D6B70();

private:
	unsigned char m_unreconstructed_00[0x10];
	Rva007D6AB0RefHolder m_ref10;
	Rva007D6AB0RefHolder m_ref14;
	unsigned char m_unreconstructed_18[0x14];
	_STL::vector<Rva007D6AB0Pod12> m_values;
};

Rva007D6B70::~Rva007D6B70()
{
}
