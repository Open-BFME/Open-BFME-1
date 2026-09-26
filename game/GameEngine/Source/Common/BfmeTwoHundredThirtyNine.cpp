// Three lists let go of at once, each link unmarked on the way past.
//
// The dump row put this body at eighty bytes, which lands in the middle of the
// second walk; it runs to ninety-four, with int3 padding after it up to the
// next row. It is claimed at its true length.

struct BfmeNodeNE
{
	unsigned char m_bfmeHead[4];		// 0x000
	unsigned char m_bfmeFlag;		// 0x004
	unsigned char m_bfmeGap[0xcf];		// 0x005
	BfmeNodeNE *m_bfmeNext;			// 0x0d4
};

class BfmeThingNE
{
public:
	void bfmeClearNE(void);

private:
	unsigned char m_bfmeHead[4];		// 0x0
	BfmeNodeNE *m_bfmeSecond;		// 0x4
	BfmeNodeNE *m_bfmeThird;		// 0x8
	BfmeNodeNE *m_bfmeFirst;		// 0xc
};

void BfmeThingNE::bfmeClearNE(void)
{
	BfmeNodeNE *at = m_bfmeFirst;

	m_bfmeFirst = 0;

	while (at != 0)
	{
		at->m_bfmeFlag = 0;

		at = at->m_bfmeNext;
	}

	at = m_bfmeSecond;

	m_bfmeSecond = 0;

	while (at != 0)
	{
		at->m_bfmeFlag = 0;

		at = at->m_bfmeNext;
	}

	at = m_bfmeThird;

	m_bfmeThird = 0;

	while (at != 0)
	{
		at->m_bfmeFlag = 0;

		at = at->m_bfmeNext;
	}
}
