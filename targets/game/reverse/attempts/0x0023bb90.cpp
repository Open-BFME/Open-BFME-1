// ?bfmeRunFDB@BfmeThingFDB@@QAEXPAX@Z
// partial score=0.679 date=2026-10-03
// cl: /DNDEBUG /MD /EHs-c-

template <int N> class BitFlags;

class Object
{
public:
	void clearAndSetModelConditionFlags(const BitFlags<320> &clear,
		const BitFlags<320> &set);
};

class BfmeA1165
{
public:
	BfmeA1165(int tag, unsigned int bitIndex1, unsigned int bitIndex2,
		unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5,
		unsigned int bitIndex6, unsigned int bitIndex7, unsigned int bitIndex8,
		unsigned int bitIndex9, unsigned int bitIndex10, unsigned int bitIndex11,
		unsigned int bitIndex12, unsigned int bitIndex13, unsigned int bitIndex14,
		unsigned int bitIndex15);
	unsigned int words[10];
};

struct BfmeMask320
{
	unsigned int words[10];

	void andWith(const BfmeMask320 &other)
	{
		words[0] &= other.words[0];
		words[1] &= other.words[1];
		words[2] &= other.words[2];
		words[3] &= other.words[3];
		words[4] &= other.words[4];
		words[5] &= other.words[5];
		words[6] &= other.words[6];
		words[7] &= other.words[7];
		words[8] &= other.words[8];
		words[9] &= other.words[9];
	}

	void flip()
	{
		words[0] = ~words[0];
		words[1] = ~words[1];
		words[2] = ~words[2];
		words[3] = ~words[3];
		words[4] = ~words[4];
		words[5] = ~words[5];
		words[6] = ~words[6];
		words[7] = ~words[7];
		words[8] = ~words[8];
		words[9] = ~words[9];
	}
};

class BfmeThingFDB
{
public:
	void bfmeRunFDB(void *it);
};

void BfmeThingFDB::bfmeRunFDB(void *it)
{
	if (!it)
		return;

	static BfmeA1165 filter(0, 0x3e, 0xc1, 0xc2, 0x3f,
		0x12f, 0xc3, 0xbf, 0xee, 0xa0, 0x40, 0xbe, 0x119, 0x25,
		0xe4, 0xe5);

	BfmeMask320 filterCopy = *(BfmeMask320 *)&filter;
	Object *source = *(Object **)((char *)this + 8);
	BfmeMask320 sourceFlags = *(BfmeMask320 *)((char *)source + 0x110);
	filterCopy.andWith(sourceFlags);
	BfmeMask320 clearFlags = sourceFlags;
	clearFlags.flip();
	clearFlags.andWith(*(const BfmeMask320 *)&filter);
	((Object *)it)->clearAndSetModelConditionFlags(
		(const BitFlags<320> &)clearFlags,
		(const BitFlags<320> &)filterCopy);
}

void *__cdecl operator new(unsigned int, void *p) throw()
{
	return p;
}
