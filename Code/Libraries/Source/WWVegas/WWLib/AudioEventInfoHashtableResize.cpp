// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport hashtable<pair<const AsciiString, AudioEventInfo *> >::resize.
// The retail body at 0x000B87C0 is emitted from the concrete AudioEventInfo map
// specialization.  Keep this TU's AsciiString/hash view identical to the
// already verified AudioEventInfo bucket and iterator instantiations.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "string_base.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_string(other.m_string) {}

	const char *str() const
	{
		return m_string.m_data ? &m_string.m_data->data[0] : "";
	}

	StringBase<char> m_string;
};

namespace rts
{
template <class T>
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
	struct hash
	{
	unsigned int operator()(T value) const
	{
		const char *p = value.str();
		unsigned int result = 0;
		while (*p != '\0') {
			result = result * 5 + *p;
			++p;
		}
		return result;
	}
};

template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
struct equal_to
{
};
}

struct AudioEventInfo;

typedef _STL::pair<const AsciiString, AudioEventInfo *> AudioEventInfoPair;
typedef _STL::hashtable<AudioEventInfoPair, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<AudioEventInfoPair>, rts::equal_to<AsciiString>,
	_STL::allocator<AudioEventInfoPair> > AudioEventInfoHashtable;

// retail 0x000B87C0
void BfmeAudioEventInfoHashtableResize(AudioEventInfoHashtable &table, unsigned int count)
{
	table.resize(count);
}
