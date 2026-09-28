// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#define _STLP_NO_EXCEPTIONS 1

#include "string_base.h"

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

// Reuses the AsciiString/StringBase<char> shim already proven at
// game/Libraries/Source/WWVegas/WWLib/RvaHashFindAsciiString.cpp: the copy
// constructor and inlined compare() there are the same shape this body's
// per-node string copy and comparison need.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}

	int compare(const AsciiString &str) const
	{
		const int len = str.m_data.m_data ? str.m_data.m_data->length : 0;
		const char *data = str.m_data.m_data ? &str.m_data.m_data->data[0] : "";
		const int myLen = m_data.m_data ? m_data.m_data->length : 0;
		const char *myData = m_data.m_data ? &m_data.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0) {
			return result;
		}
		return myLen - len;
	}

	StringBase<char> m_data;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

// Same global table the already-landed pointer-keyed lookup walks
// (game/GameEngine/Source/Common/Bfme5TinyTwentyTwo.cpp, retail 0x012ACB50,
// pinned as g_bfmeTableCN in targets/game/reverse/symbols.csv). This body walks the same
// entry chain but compares the entry's AsciiString name field at +0x08
// instead of the void* key at +0x0C.
class BfmeEntryCN
{
public:
	int m_bfmeHead;				// +0x00
	BfmeEntryCN *m_bfmeNext;			// +0x04
	AsciiString m_bfmeName;			// +0x08
};

class BfmeTableCN
{
public:
	BfmeEntryCN *m_bfmeHead;			// +0x00
};

extern BfmeTableCN *g_bfmeTableCN;			// retail 0x012ACB50

// ?bfmeLookupByName@@YGPAVBfmeEntryCN@@VAsciiString@@@Z
BfmeEntryCN * __stdcall bfmeLookupByName(AsciiString key)
{
	BfmeEntryCN *entry;

	for (entry = g_bfmeTableCN->m_bfmeHead; entry; entry = entry->m_bfmeNext)
	{
		AsciiString entryName = entry->m_bfmeName;
		if (key == entryName)
			return entry;
	}

	return 0;
}
