// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x000B5A30 is the copy constructor for the three AudioEventInfo
// vectors. The AudioEventInfo copy constructor reaches it through ILT
// 0x00028D58, and the element copy contains an AsciiString followed by one
// scalar dword.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "ascii_string.h"

struct Gen_t_000b0c00_p8cd
{
	AsciiString m_name;
	int m_value;

	Gen_t_000b0c00_p8cd() : m_value(0) {}
	Gen_t_000b0c00_p8cd(const Gen_t_000b0c00_p8cd &other)
		: m_name(other.m_name),
		  m_value(other.m_value)
	{
	}
	~Gen_t_000b0c00_p8cd() {}
	Gen_t_000b0c00_p8cd &operator=(const Gen_t_000b0c00_p8cd &other)
	{
		m_name = other.m_name;
		m_value = other.m_value;
		return *this;
	}
};

template _STL::vector<Gen_t_000b0c00_p8cd,
	_STL::allocator<Gen_t_000b0c00_p8cd> >::vector(
	const _STL::vector<Gen_t_000b0c00_p8cd,
		_STL::allocator<Gen_t_000b0c00_p8cd> > &);
