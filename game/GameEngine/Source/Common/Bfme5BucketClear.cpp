// A bucket-chain clear.
//
// It walks every bucket of a hash table, frees the chain hanging off it, nulls
// the slot and finally zeroes the count. The bucket count is the pointer span
// divided by four and it is recomputed on every pass, which is what a for loop
// with the span in its condition gives.
//
// Both comparisons are unsigned -- jbe at the top, jb at the bottom -- so the
// index and the span are unsigned even though the span itself comes from a
// signed pointer subtraction. The inner walk saves the successor before the
// free rather than after, because the free is not the last thing it does with
// the register.

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

struct BfmeBucketNode
{
	BfmeBucketNode *m_bfmeNext;				// +0x00
	char m_bfmePad[0x64];					// +0x04
};

class Gen_001B03A0
{
public:
	void bfmeClearBuckets(void);

private:
	int m_bfmeHead;						// +0x00
	BfmeBucketNode **m_bfmeStart;				// +0x04
	BfmeBucketNode **m_bfmeEnd;				// +0x08
	int m_bfmeGap;						// +0x0C
	int m_bfmeCount;					// +0x10
};

// ?bfmeClearBuckets@Gen_001B03A0@@QAEXXZ
void Gen_001B03A0::bfmeClearBuckets(void)
{
	for (unsigned int index = 0; index < (unsigned int)(m_bfmeEnd - m_bfmeStart); ++index)
	{
		BfmeBucketNode *node = m_bfmeStart[index];

		while (node)
		{
			BfmeBucketNode *next = node->m_bfmeNext;

			bfmeDeallocate(node, sizeof(BfmeBucketNode));

			node = next;
		}

		m_bfmeStart[index] = 0;
	}

	m_bfmeCount = 0;
}
