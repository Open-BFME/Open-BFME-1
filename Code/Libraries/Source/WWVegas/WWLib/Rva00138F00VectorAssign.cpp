// cl: /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME5: byte-twin of vector<GeometryShape>::operator=
// (Code/GameEngine/Source/Common/System/GeometryShapeVectorAssign.cpp,
// retail 0x000FF8F0). Retail 0x00138F00, 294B: same 0x38e38e39 divide-by-9
// magic and 0x24-byte stride, so the element shares GeometryShape's layout
// (seven dwords, a StringBase<char> at +0x1c, trailing byte) rather than the
// fully-POD char[36] already pinned for the unrelated 0x00146940
// insert-overflow body -- that shape inlined to a raw copy loop with no
// callees, while retail here still calls out per-element like the twin.

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

struct Rva00138F00Element
{
	int m_type;
	float m_height;
	float m_majorRadius;
	char m_unmodelled[0x0C];
	float m_offsetZ;
	AsciiString m_name;
	bool m_enabled;
};

template class _STL::vector<Rva00138F00Element>;
