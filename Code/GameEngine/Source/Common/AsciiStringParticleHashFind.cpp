// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: hash_map<AsciiString, ParticleSystemTemplate *>::_M_find, retail
// 0x005C76A0, 159 bytes. The name was parked on the 5-byte thunk at 0x0000F727.
//
// Two things make the body what it is. The hash takes its key BY VALUE, so the
// lookup builds a temporary through StringBase<char>'s copy constructor at
// 0x00887B60 and never destroys it -- MSVC 7.1 leaves that to the callee --
// and the functor itself is a call, rts::hash<AsciiString>::operator() through
// the ILT at 0x0000EC91. The equality, by contrast, inlines whole: the same
// length-halfword, characters-at-eight, empty-literal compare the set bounds
// use, tested against zero.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

class ParticleSystemTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_string(other.m_string) {}

	int compare(const AsciiString &str) const
	{
		const int len = str.m_string.m_data ? str.m_string.m_data->length : 0;
		const char *data = str.m_string.m_data ? &str.m_string.m_data->data[0] : "";
		const int myLen = m_string.m_data ? m_string.m_data->length : 0;
		const char *myData = m_string.m_data ? &m_string.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0) {
			return result;
		}
		return myLen - len;
	}

	StringBase<char> m_string;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

namespace rts
{
template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
struct hash
{
	unsigned int operator()(T value) const;			// ILT 0x0000EC91
};
}

typedef _STL::hash_map<AsciiString, ParticleSystemTemplate *, rts::hash<AsciiString>, _STL::equal_to<AsciiString> > BfmeParticleHash;

Bool BfmeParticleHashFindAnchor(const BfmeParticleHash &table, const AsciiString &key)
{
	return table.find(key) != table.end();
}
