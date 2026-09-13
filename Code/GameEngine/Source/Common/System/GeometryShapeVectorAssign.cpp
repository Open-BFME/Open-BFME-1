// cl: /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: vector<GeometryShape>::operator=, retail 0x000FF8F0.
//
// Element is 0x24 bytes: seven dwords, a StringBase<char> at +0x1c, and a
// trailing byte.  The 0x38e38e39 magic is the divide-by-9 of that stride.

#include <vector>

#include "string_base.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	StringBase<char> m_data;

public:
	AsciiString(void) {}
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}
	~AsciiString(void) {}
	AsciiString &operator=(const AsciiString &other)
	{
		m_data = other.m_data;
		return *this;
	}
};

struct GeometryShape
{
	int m_type;
	float m_height;
	float m_majorRadius;
	char m_unmodelled[0x0C];
	float m_offsetZ;
	AsciiString m_name;
	bool m_enabled;
};

template class _STL::vector<GeometryShape>;
