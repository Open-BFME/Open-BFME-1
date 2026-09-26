// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <vector>
// Retail 0x002DECC0. Its owner identity is unresolved, so keep it RVA-qualified.
#include "ascii_string.h"

template <>
inline const char *StringBase<char>::str() const
{
	return m_data ? (const char *)m_data + 8 : "";
}

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

class Rva002DECC0Owner
{
public:
	void dispatch(unsigned unused, class Rva001BE220Receiver *receiver);

	unsigned char m_pad00[0x58];
	_STL::vector<AsciiString> m_strings;
	unsigned m_ownerWord;
};

class Rva001BE220Receiver
{
public:
	void dispatch(int bit, unsigned ownerWord);
};

int __cdecl Rva001C0930FindNameIndex(const char *name);

void Rva002DECC0Owner::dispatch(unsigned, Rva001BE220Receiver *receiver)
{
	Rva001BE220Receiver *target = receiver;
	if (target == 0)
		return;

	for (unsigned i = 0;
		 i < m_strings.size();
		 ++i)
	{
		AsciiString local = m_strings[i];
		int bit = Rva001C0930FindNameIndex(local.str());
		target->dispatch(bit, m_ownerWord);
	}
}
