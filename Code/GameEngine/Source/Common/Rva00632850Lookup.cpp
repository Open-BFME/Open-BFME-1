// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Retail RVA 0x00632850, full184B.
// Read-only traversal witnesses a four-byte key followed by a record prefix:
// return node+0x14; compare its AsciiString at+4 (node+0x18).
// No allocation or key-ordering behavior is inferred from this lookup.
// Address-derived owner and method identity; retail uses thiscall despite the
// generated placeholder's free-function spelling.

#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#include <map>
#include "ascii_string.h"

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
extern "C" unsigned int __cdecl strlen(const char *);
#pragma intrinsic(memcmp)
#pragma intrinsic(strlen)

template <> inline int StringBase<char>::compare(const char *text) const
{
	int textLength = text != 0 ? static_cast<int>(strlen(text)) : 0;
	int keyLength = m_data != 0 ? m_data->length : 0;
	const char *keyData = m_data != 0 ? m_data->data :
		"";
	int count = keyLength < textLength ? keyLength : textLength;
	int result = memcmp(keyData, text, count);
	if (result != 0)
		return result;
	return keyLength - textLength;
}

struct Rva00632850Record
{
	unsigned int m_unmodelled_00[1];
	AsciiString m_unmodelled_04;
	int compare(const char *text) const { return m_unmodelled_04.compare(text); }
};

// Only the four-byte key footprint is witnessed; this lookup never reads it.
struct Rva00632850Key { unsigned char opaque[4]; };
typedef _STL::map<Rva00632850Key, Rva00632850Record> Rva00632850Map;

struct Rva00632850Owner
{
	unsigned char m_unmodelled_00[0x4C];
	Rva00632850Map m_unmodelled_4C;

	Rva00632850Record *Rva00632850Lookup(const char *text);
};

Rva00632850Record *Rva00632850Owner::Rva00632850Lookup(const char *text)
{
	for (Rva00632850Map::iterator it = m_unmodelled_4C.begin();
		it != m_unmodelled_4C.end(); ++it)
	{
		Rva00632850Record *record = &it->second;
		if (record->compare(text) == 0)
			return record;
	}
	return 0;
}
