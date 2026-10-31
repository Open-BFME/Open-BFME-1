// cl: /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x00425720 (204 bytes, ret 8 at +0xC9): Eva's message-to-name lookup.
// -1 yields "EVA_INVALID", ids below 17 index TheEvaMessageNames (retail data
// 0x010F1AF0), and any other id walks the AsciiString-keyed STLport hash map at
// Eva+0x24 for the entry whose mapped id matches, returning its key, else
// "<Unknown>".  Nothing in retail calls the body or its ILT 0x00014E89, and
// tools/ilt_oracle.py contradicts Eva::messageToName in every decoration, so
// the method keeps an address-derived name.
//
// The walk inlines STLport's _Ht_iterator::operator++ including
// _M_skip_to_next (hash the old key through rts::hash<AsciiString>, then scan
// the buckets).  The out-of-line begin() it calls is retail 0x00423D00 via ILT
// 0x000121FC, a byte-identical hashtable begin whose only ledger name is the
// Player.cpp hash_map<int, Relationship> instantiation, which the ILT
// contradicts, so the call goes through an address-derived view of it.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#define private public
#include <hash_map>
#undef private

#include "string_base.h"

#include "ascii_string.h"

inline bool operator==(const AsciiString &left, const AsciiString &right);

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const;
};
}

extern const char *TheEvaMessageNames[];

typedef _STL::hash_map<AsciiString, int, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > EvaNameMap;
typedef EvaNameMap::_Ht::_Node EvaNameNode;

// Retail 0x00423D00: the table's out-of-line begin() (STLport
// hashtable::begin), returning the iterator through a hidden pointer;
// hash_map::begin() forwards to it inline.  The caller only schedules like
// retail with this body visible.
class Rva00423D00Table : public EvaNameMap::_Ht
{
public:
	EvaNameMap::iterator begin()
	{
		for (size_t n = 0; n < _M_buckets.size(); ++n)
			if (_M_buckets[n])
				return EvaNameMap::iterator((EvaNameNode *)_M_buckets[n], this);
		return end();
	}
};

struct Rva00423D00Map
{
	EvaNameMap::iterator begin() { return m_table.begin(); }

	Rva00423D00Table m_table;
};

class Eva
{
public:
	AsciiString rva00425720(int message);

private:
	char m_unknown[0x24];
	EvaNameMap m_names;
};

// STLport's _Hashtable_iterator::_M_skip_to_next, inlined into the walk.
static __forceinline EvaNameNode *evaSkipToNext(EvaNameNode *cur,
	const EvaNameMap::_Ht *ht)
{
	size_t bucket = ht->_M_bkt_num(cur->_M_val);
	size_t size;
	size = ht->bucket_count();

	EvaNameNode *i = 0;
	while (i == 0 && ++bucket < size)
		i = (EvaNameNode *)ht->_M_buckets[bucket];
	return i;
}

AsciiString Eva::rva00425720(int message)
{
	if (message == -1)
		return AsciiString("EVA_INVALID");

	if (message < 17)
		return AsciiString(TheEvaMessageNames[message]);

	EvaNameMap::iterator it = ((Rva00423D00Map *)&m_names)->begin();
	EvaNameNode *node = it._M_cur;
	const EvaNameMap::_Ht *table = it._M_ht;
	while (node != 0)
	{
		if (node->_M_val.second == message)
			return node->_M_val.first;

		EvaNameNode *next = node->_M_next;
		node = next != 0 ? next : evaSkipToNext(node, table);
	}

	return AsciiString("<Unknown>");
}
