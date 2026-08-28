// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the vector<ModuleInfo::Nugget> internals -- _M_clear at
// 0x00771D00, __copy at 0x00770E00 and _M_allocate_and_copy at 0x0076B3B0.
// All three names were parked on 5-byte thunks.
//
// The element is 0x14 bytes, which the stride and the divide-by-twenty in the
// size arithmetic both carry. What fills it is not the reference's Nugget: the
// copy loop assigns an AsciiString at +0, then twelve bytes at +4 through
// vector<AsciiString>::operator=, then moves one dword from +0x10.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef bool Bool;

// Only the two members these bodies reach; declaring the whole of
// string_base.h's StringBase would add its private destructor as a second call.
template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void set(const StringBase<T> &src);			// retail 0x00887C90

private:
	void releaseBuffer();					// retail 0x00887940

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString() { m_string.releaseBuffer(); }

	const AsciiString &operator=(const AsciiString &src) { m_string.set(src.m_string); return *this; }

	StringBase<char> m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ModuleInfo
{
public:
	// Not the reference's Nugget. The copy loop assigns the AsciiString at +0
	// through StringBase<char>::set, the twelve bytes at +4 through
	// vector<AsciiString>::operator= at 0x000DE2C0, and moves one dword from
	// +0x10 -- twenty bytes in all, which is the stride.
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
	struct Nugget
	{
		AsciiString first;
		_STL::vector<AsciiString> m_bfmeStrings;
		Int m_bfmeTail;
	};
};

void BfmeModuleInfoNuggetVectorAnchor(_STL::vector<ModuleInfo::Nugget> &out, const _STL::vector<ModuleInfo::Nugget> &in)
{
	out = in;
	out.erase(out.begin());
}
