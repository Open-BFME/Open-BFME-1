// cl: /DNDEBUG /MD /EHsc /Od /Oi

#pragma intrinsic(memset)
extern "C" void *__cdecl memset(void *destination, int value, unsigned int bytes);

void bfmeBigFreePM(void *block);
void bfmeSmallFreePM(void *block, unsigned int bytes);

struct DebugAllocHeader
{
	unsigned int m_magic : 16;
	unsigned int m_typeSize : 16;
	unsigned int m_size;
};

extern "C" void __cdecl bfme_DebugNodeAllocDeallocate_82EED0(
	void *block, unsigned int bytes)
{
	struct Locals
	{
		unsigned char *scan;
		unsigned int realBytes;
		DebugAllocHeader *realBlock;
	} locals;

	locals.realBlock = (DebugAllocHeader *)((char *)block - 16);
	for (locals.scan = (unsigned char *)(locals.realBlock + 1);
		locals.scan < (unsigned char *)block;
		locals.scan++)
	{
	}

	locals.realBytes = bytes + 24;
	for (locals.scan = (unsigned char *)block + bytes;
		locals.scan < (unsigned char *)locals.realBlock + locals.realBytes;
		locals.scan++)
	{
	}

	locals.realBlock->m_magic = 0xDEBD;
	memset(block, 0xA3, bytes);
	if (locals.realBytes > 0x80)
	{
		bfmeBigFreePM(locals.realBlock);
	}
	else
	{
		bfmeSmallFreePM(locals.realBlock, locals.realBytes);
	}
}
