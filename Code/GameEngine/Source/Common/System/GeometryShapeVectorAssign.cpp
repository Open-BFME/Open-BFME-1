// cl: /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME: vector<GeometryShape>::operator=, retail 0x000FF8F0.
//
// Element is 0x24 bytes: seven dwords, a StringBase<char> at +0x1c, and a
// trailing byte.  The 0x38e38e39 magic is the divide-by-9 of that stride.

#include <vector>

template <typename T>
class StringBase
{
	void *m_data;

public:
	StringBase(void);
	StringBase(const StringBase &other);
	~StringBase(void);
	StringBase &operator=(const StringBase &other);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	StringBase<char> m_string;

public:
	AsciiString(void) {}
	AsciiString(const AsciiString &other) : m_string(other.m_string) {}
	~AsciiString(void) {}
	AsciiString &operator=(const AsciiString &other)
	{
		m_string = other.m_string;
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
