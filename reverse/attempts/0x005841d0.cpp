// ?rva005841D0@BannerUI@@QAEHXZ
// partial score=0.92 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// FILE: BannerUIRva005841D0.cpp //////////////////////////////////////////////
//
// BannerUI member at retail 0x005841D0 (280 B). The receiver is proven by the
// matched forwarder Gen_002ed8c0 (0x002ED8C0), which loads TheBannerUI
// (0x012F4B70) into ECX and tail-jumps here through ILT 0x0003514D. The method
// name is not recoverable, so it keeps its address.
//
// The body scans the movie-entry vector (+0x30) with the matched tagged-pair
// scanner (0x00581B70) for the two banner slots, picks the first free one,
// looks up the "BannerRohan" BannerType in the store at +0x08 (the hash_map
// parseBannerType fills), shows it through AddBanner and records a 28-byte
// movie entry with the matched push_back (0x00583AE0).
//
// Retail passes the scanner a copy of a zeroed local and discards the
// returned pair, then tests the still-zero local; that is preserved.
//
///////////////////////////////////////////////////////////////////////////////

#include <stddef.h>

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <vector>

#include "Common/AsciiString.h"

struct BfmeTaggedRecord;

struct BfmeTaggedPair
{
	BfmeTaggedPair()
	{
		m_bfmeRecords[0] = m_bfmeRecords[1] = 0;
	}
	BfmeTaggedRecord *m_bfmeRecords[2];
};

BfmeTaggedPair bfmeScanTaggedPair(BfmeTaggedRecord *first, BfmeTaggedRecord *last, BfmeTaggedPair found);

void AddBanner(int slot, const AsciiString &first, const AsciiString &second);

// The four 4-byte members parseBannerType fills; their meanings are not recovered.
class BannerType
{
public:
	BannerType() {}
	BannerType(const BannerType &other);
	~BannerType();

	AsciiString m_field0;
	AsciiString m_field1;
	AsciiString m_field2;
	AsciiString m_field3;
};

namespace rts
{
	template <class T> struct hash
	{
		unsigned int operator()(T value) const;
	};
}

typedef _STL::hash_map<AsciiString, BannerType, rts::hash<AsciiString> > BannerTypeStore;

// 28-byte movie entry: flag byte, slot id, then five dwords this body sets.
struct BannerMovieEntry
{
	bool m_flag00;
	int m_id;
	int m_value08;
	class BannerType *m_type;
	int m_value10;
	int m_value14;
	int m_value18;
};

class BannerUI
{
public:
	int rva005841D0();

private:
	unsigned char m_unmodelled_00[8];
	BannerTypeStore m_bannerTypes;							// +0x08
	unsigned char m_unmodelled_1C[0x14];
	_STL::vector<BannerMovieEntry> m_movieEntries;			// +0x30
};

// ?rva005841D0@BannerUI@@QAEHXZ
static inline int firstFreeSlot(const BfmeTaggedPair &used)
{
	for (int i = 0; i < 2; ++i)
	{
		if (used.m_bfmeRecords[i] == 0)
			return i;
	}
	return 2;
}

int BannerUI::rva005841D0()
{
	BfmeTaggedPair used;
	BannerMovieEntry entry;
	entry.m_flag00 = true;
	entry.m_value08 = -1;
	entry.m_type = 0;
	entry.m_value18 = 0;
	entry.m_value10 = 0;
	entry.m_value14 = 0;

	bfmeScanTaggedPair((BfmeTaggedRecord *)m_movieEntries.begin(),
		(BfmeTaggedRecord *)m_movieEntries.end(), used);

	int slot = firstFreeSlot(used);
	entry.m_id = slot;
	if ((unsigned int)slot >= 2)
		return -1;

	AsciiString name("BannerRohan");
	BannerTypeStore::iterator it;
	it = m_bannerTypes.find(name);
	if (it == m_bannerTypes.end())
		return -1;

	BannerType *type = &it->second;
	entry.m_type = type;
	AddBanner(slot, type->m_field0, type->m_field1);
	m_movieEntries.push_back(entry);
	return slot;
}
