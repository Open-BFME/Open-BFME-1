// ?bfmeFind1024@BfmeTab1024@@QAEHH@Z
// partial score=0.36 date=2026-09-21
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// BfmeTab1024::bfmeFind1024(int key), retail 0x0089CEF0, size 520.
// Identity: pinned per this lane's brief (?bfmeFind1024@BfmeTab1024@@QAEHH@Z)
// and independently confirmed by the landed caller
// Code/Libraries/Source/EA/Apt/Rva00899C20NodePredicate.cpp, which calls
// `g_Va013387D8->m_table.bfmeFind1024(reinterpret_cast<int>(&g_Va013385F8))`
// and casts the int result straight to a lookup-result pointer. The
// string-header shape (refCount/size/maxSize/hash, data at +8, hash at +6)
// and the data==key / hash-match / bfmeCompareVSC probe idiom are lifted
// from the landed sibling BfmeStringList0089CBA0::find (0x0089CBA0,
// Code/GameEngine/Source/Common/BfmeStringList0089CBA0.cpp), the closest
// matched neighbour, except this table is open-addressed (mask + bucket
// array with linear-probe wraparound) rather than a plain array scan.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

extern "C" int __cdecl bfmeCompareVSC(const char *left, const char *right);	// pinned retail 0x009F6FA0
class BfmeString1024Base
{
public:
	void bfmeInit929G();				// pinned retail 0x0089E700
};

struct BfmeStringData1024
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

// The `int key` parameter is really the address of one of these, reinterpreted.
class BfmeString1024 : public BfmeString1024Base
{
public:
	BfmeStringData1024 *m_data;
};

extern BfmeStringData1024 g_bfmeDefaultString1284;	// VA 0x012D5298

struct Bucket1024
{
	BfmeStringData1024 *m_data;
	Int m_value;
};

class BfmeTab1024
{
public:
	Int bfmeFind1024(Int key);

	Int m_size;			// +0x00 (bucket count)
	Bucket1024 *m_buckets;		// +0x04
	Int m_specialSlot;		// +0x0c
};

// The two literal-name special cases handled once every regular probe has
// walked off the end of the chain and landed on the shared default/empty
// string bucket.
extern const char g_bfmeApt1136034[];	// VA 0x01136034
extern const char g_bfmeApt1136040[];	// VA 0x01136040

Int BfmeTab1024::bfmeFind1024(Int key)
{
	BfmeString1024 *self = (BfmeString1024 *)key;
	BfmeStringData1024 *keyData = self->m_data;

	if (keyData->m_hash == 0)
		self->bfmeInit929G();

	keyData = self->m_data;
	unsigned short hash = keyData->m_hash;

	if (m_buckets == 0)
		return 0;

	int mask = m_size - 1;
	int index = mask & (int)hash;
	int probeCount = mask - index;

	for (int step = 0; step <= probeCount; ++step)
	{
		Bucket1024 *bucket = &m_buckets[index + step];
		BfmeStringData1024 *data = bucket->m_data;
		if (data == 0)
			return 0;

		if (data == (BfmeStringData1024 *)&g_bfmeDefaultString1284)
			break;

		if (data == keyData)
			return (Int)bucket;

		if (data->m_hash == hash)
		{
			int equal = bfmeCompareVSC((const char *)data + 8, (const char *)keyData + 8) == 0;
			if (equal)
				return bucket->m_value & ~1;
		}
	}

	for (int step = 0; step < index; ++step)
	{
		Bucket1024 *bucket = &m_buckets[step];
		BfmeStringData1024 *data = bucket->m_data;
		if (data == 0)
			return 0;

		if (data == (BfmeStringData1024 *)&g_bfmeDefaultString1284)
			break;

		if (data->m_hash == hash)
		{
			int equal = bfmeCompareVSC((const char *)data + 8, (const char *)keyData + 8) == 0;
			if (equal)
				return bucket->m_value & ~1;
		}
	}

	if (hash == 0x699)
	{
		if (bfmeCompareVSC((const char *)keyData + 8, g_bfmeApt1136034) != 0)
			return 0;
		return m_specialSlot & ~1;
	}

	if (hash == 0x6bbd)
	{
		if (bfmeCompareVSC((const char *)keyData + 8, g_bfmeApt1136040) != 0)
			return 0;
		return 0;
	}

	return 0;
}
