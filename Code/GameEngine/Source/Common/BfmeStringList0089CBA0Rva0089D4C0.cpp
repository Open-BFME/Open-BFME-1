// cl: /DNDEBUG /MD

// Retail RVA 0x0089D4C0 (238 bytes). No named caller, vtable slot, or
// canonical BFME method name identifies this body (tools/callers_of.py
// finds no reaching caller). Its this-relative fields (a count at +0x0, an
// 8-byte-entry array pointer at +0x4, each entry's first field a
// BfmeStringData0089CBA0*) are byte-for-byte the same layout the already
// landed Code/GameEngine/Source/Common/BfmeStringList0089CBA0.cpp
// documents for BfmeStringList0089CBA0::find, so this is another method of
// that same class; the method name itself is unproven, so it keeps the
// address-derived Rva0089D4C0 spelling.
//
// WHAT THE BYTES SHOW.  Two forbidden-key membership tests up front
// (find() against two fixed BfmeString0089CBA0 constants at 0x01338480 --
// already pinned g_bfmeRouteKeys1282 -- and 0x01338660): if either is
// present, return false immediately. Otherwise, for every entry i whose
// data pointer is neither null nor the shared empty-string sentinel
// (g_bfmeDefaultString1284, the same VA already pinned as
// g_bfmeEmptyString1285 in the find() sibling), call the still-dump
// BfmeTab1024::bfmeFind1024 (pinned ?bfmeFind1024@BfmeTab1024@@QAEHH@Z,
// called with entry i's address reinterpreted as its int argument) and
// bail false if it answers zero; then compare entry i against every later
// entry j, treating a null or sentinel entry j as "stop scanning this row"
// (not a mismatch), an identical data pointer or an equal hash followed by
// a zero bfmeCompareVSC (the same _strcmpi import
// BfmeStringList0089CBA0::find already calls) as "duplicate -> return
// false", and anything else as "keep scanning". Reaching the end of every
// row returns true.

struct BfmeStringData0089CBA0
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

struct BfmeStringEntry0089CBA0
{
	BfmeStringData0089CBA0 *m_data;
	void *m_value;
};

class BfmeString0089CBA0
{
	BfmeStringData0089CBA0 *m_data;
};

extern "C" char g_bfmeDefaultString1284[];
int bfmeCompareVSC(const char *left, const char *right);

class BfmeTab1024
{
public:
	int bfmeFind1024(int value);
};

class BfmeStringList0089CBA0
{
public:
	bool Rva0089D4C0();

	BfmeStringEntry0089CBA0 *find(const BfmeString0089CBA0 &key);

private:
	int m_count;
	BfmeStringEntry0089CBA0 *m_array;
};

#define g_bfmeRouteKeys1282Ref (*(const BfmeString0089CBA0 *)0x01338480)
#define g_bfmeRouteKeys1282SecondRef (*(const BfmeString0089CBA0 *)0x01338660)

// ?Rva0089D4C0@BfmeStringList0089CBA0@@QAE_NXZ
bool BfmeStringList0089CBA0::Rva0089D4C0()
{
	if (m_array == 0)
		return true;

	if (find(g_bfmeRouteKeys1282Ref))
		return false;

	if (find(g_bfmeRouteKeys1282SecondRef))
		return false;

	for (int i = 0; i < m_count; ++i)
	{
		BfmeStringEntry0089CBA0 *outer = m_array + i;
		if (outer->m_data == 0 || (void *)outer->m_data == (void *)g_bfmeDefaultString1284)
			continue;

		if (!((BfmeTab1024 *)this)->bfmeFind1024((int)outer))
			return false;

		for (int j = i + 1; j < m_count; ++j)
		{
			BfmeStringEntry0089CBA0 *inner = m_array + j;
			if (inner->m_data == 0)
				break;
			if ((void *)inner->m_data == (void *)g_bfmeDefaultString1284)
				continue;

			if (inner->m_data == outer->m_data)
				return false;

			if (inner->m_data->m_hash == outer->m_data->m_hash)
			{
				volatile unsigned char equal = (unsigned char)(bfmeCompareVSC(
					reinterpret_cast<const char *>(inner->m_data) + 8,
					reinterpret_cast<const char *>(outer->m_data) + 8) == 0);
				if (equal)
					return false;
			}
		}
	}

	return true;
}
