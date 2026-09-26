// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME5: BfmeLivingWorldCampaignManager lookup of the 32-byte record
// vector at this+0x10. Retail 0x003B4590, 216 bytes. Neighbour of findArmy
// (0x003B43D0) and bfmeReplenishPair (0x003B4510). Inlined AsciiString
// compare against the name at record+4; empty fallback 0x0107388B.

extern const char g_bfmeEmptyAscii[];
extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

typedef int Int;
typedef unsigned short UnsignedShort;

struct BfmeAsciiStringData
{
	char m_pad00[4];
	UnsignedShort m_length;
	UnsignedShort m_pad06;
	char m_text[1];
};

#include "ascii_string.h"

class BfmeLwcmFindResult
{
public:
	char m_pad00[4];
	AsciiString m_name;
	char m_rest[0x18];
};

class BfmeVec32
{
public:
	unsigned int size(void) const
	{
		BfmeLwcmFindResult *finish = m_end;
		BfmeLwcmFindResult *start = m_begin;
		return (unsigned int)(finish - start);
	}
	BfmeLwcmFindResult *m_begin;
	BfmeLwcmFindResult *m_end;
};

class BfmeLivingWorldCampaignManager
{
public:
	BfmeLwcmFindResult *findByKey(void *key);

private:
	char m_pad00[0x10];
	BfmeVec32 m_items;
};

BfmeLwcmFindResult *BfmeLivingWorldCampaignManager::findByKey(void *key)
{
	unsigned int i = 0;
	for (; i < m_items.size(); ++i)
	{
		if (m_items.m_begin[i].m_name.compare(*(const AsciiString *)key) == 0)
			return m_items.m_begin + i;
	}
	return 0;
}
