// The first link of the chain whose number is set in the mask the caller
// brought, or nothing when no link is.

struct BfmeNodeND
{
	unsigned char m_bfmeHead[0x20];		// 0x000
	unsigned int m_bfmeBit;			// 0x020
	unsigned char m_bfmeGap[0xe4];		// 0x024
	BfmeNodeND *m_bfmeNext;			// 0x108
};

class BfmeThingND
{
public:
	BfmeNodeND *bfmeFindND(const unsigned int *mask);

private:
	unsigned char m_bfmeHead[8];		// 0x0
	BfmeNodeND *m_bfmeFirst;		// 0x8
};

BfmeNodeND *BfmeThingND::bfmeFindND(const unsigned int *mask)
{
	BfmeNodeND *at = m_bfmeFirst;

	while (at != 0)
	{
		unsigned int bit = at->m_bfmeBit;

		if ((mask[bit >> 5] & (1u << (bit & 0x1f))) != 0)
			return at;

		at = at->m_bfmeNext;
	}

	return 0;
}
