// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;

enum { BFME_NO_ATTRIBUTE_HANDLE = 0xFFFFFFFF };

class BfmeAttributeEntry
{
public:
	unsigned char m_bfmeHead[0x84];
	Int m_bfmeUseCount;
};

struct BfmeAttributePool
{
	BfmeAttributeEntry *m_bfmeStart;
	BfmeAttributeEntry *m_bfmeFinish;
};

extern BfmeAttributePool TheBfmeAttributePool;

struct BfmeAttributeHandle
{
	UnsignedInt m_bfmeHandle;
};

void bfmeReleaseAttributeHandle(BfmeAttributeHandle *handle)
{
	if (handle->m_bfmeHandle == BFME_NO_ATTRIBUTE_HANDLE)
		return;

	if (handle->m_bfmeHandle > (UnsignedInt)(TheBfmeAttributePool.m_bfmeFinish
			- TheBfmeAttributePool.m_bfmeStart))
		return;

	--TheBfmeAttributePool.m_bfmeStart[handle->m_bfmeHandle].m_bfmeUseCount;
	handle->m_bfmeHandle = BFME_NO_ATTRIBUTE_HANDLE;
}
