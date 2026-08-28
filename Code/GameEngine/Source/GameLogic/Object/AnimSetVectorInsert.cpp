// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: vector<GenericObjectCreationNugget::AnimSet>::_M_insert_overflow,
// retail 0x00755CA0, 284 bytes (the extent runs to the int3 padding). The name
// was parked on the 5-byte thunk at 0x0000DB2F.
//
// The element is twelve bytes -- the copy loop steps by 0x0C -- and one of them
// is an AsciiString, since each move calls StringBase<char>'s copy constructor.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	StringBase(const StringBase<T> &src);			// retail 0x00887B60

private:
	void releaseBuffer();					// retail 0x00887940

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_string(other.m_string) {}
	~AsciiString() { m_string.releaseBuffer(); }

	StringBase<char> m_string;
};

class GenericObjectCreationNugget
{
public:
	struct AnimSet
	{
		AsciiString m_bfmeName;
		Int m_bfmeFirst;
		Int m_bfmeSecond;
	};
};

void BfmeAnimSetVectorAnchor(_STL::vector<GenericObjectCreationNugget::AnimSet> &v, const GenericObjectCreationNugget::AnimSet &value)
{
	v.insert(v.begin(), value);
}
