// An allocation that clears what it just took.
//
// The element count is read twice -- once for the allocation and once for the
// clear -- while the block itself is only read once, because the store into
// the member and the destination of the clear are the same value.

extern void * (*WideAllocPtr)(unsigned int bytes);

extern "C" void * __cdecl memset(void *block, int value, unsigned int bytes);

#pragma intrinsic(memset)

class Gen_0089C9E0
{
public:
	void bfmeAllocate(void);

private:
	int m_bfmeCount;					// +0x00
	char *m_bfmeBlock;					// +0x04
};

// ?bfmeAllocate@Gen_0089C9E0@@QAEXXZ
void Gen_0089C9E0::bfmeAllocate(void)
{
	m_bfmeBlock = (char *)WideAllocPtr(m_bfmeCount * 8);

	memset(m_bfmeBlock, 0, m_bfmeCount * 8);
}
