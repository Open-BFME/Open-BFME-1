// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AttributeHandleStandIn's destructor, retail 0x0039D550, 76 bytes.
// The body carried only a machine byte-dump row; the symbols.csv pin names it
// from the AttributeModifierAuraUpdateModuleData destructor call site.
//
// The stand-in holds one index. Releasing it drops the use count of the pool
// entry it names and then marks itself empty. Nothing happens for an empty
// stand-in, and nothing happens either when the index is past the end of the
// pool, which is the global at 0x012F1000 the pin goes in for.
//
// The entry size comes out of the divide: magic 0x78787879 with a shift of six
// is 2^38 / 0x78787879, which is 136. The bound test is unsigned even though
// the pointer difference is signed, because the index is not.

typedef int Int;
typedef unsigned int UnsignedInt;

enum { BFME_NO_ATTRIBUTE_HANDLE = 0xFFFFFFFF };

class BfmeAttributeEntry
{
public:
	unsigned char m_bfmeHead[0x84];
	Int m_bfmeUseCount;					// +0x84, ends the entry at 0x88
};

struct BfmeAttributePool
{
	BfmeAttributeEntry *m_bfmeStart;			// +0x00
	BfmeAttributeEntry *m_bfmeFinish;			// +0x04
};

extern BfmeAttributePool TheBfmeAttributePool;			// 0x012F1000

class AttributeHandleStandIn
{
public:
	~AttributeHandleStandIn();

private:
	UnsignedInt m_bfmeHandle;				// +0x00
};

// ??1AttributeHandleStandIn@@QAE@XZ
AttributeHandleStandIn::~AttributeHandleStandIn()
{
	if (m_bfmeHandle == BFME_NO_ATTRIBUTE_HANDLE)
		return;

	if (m_bfmeHandle > (UnsignedInt)(TheBfmeAttributePool.m_bfmeFinish
			- TheBfmeAttributePool.m_bfmeStart))
		return;

	--TheBfmeAttributePool.m_bfmeStart[m_bfmeHandle].m_bfmeUseCount;

	m_bfmeHandle = BFME_NO_ATTRIBUTE_HANDLE;
}
