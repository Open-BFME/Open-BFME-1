// Whether this one is ready to be picked. It must be in the third state, its
// partner must not be held back while this one is marked, and the partner must
// have something to work with.

class BfmePartnerXR
{
public:
	unsigned char m_bfmeHead[0x220];	// 0x000
	void *m_bfmeWork;			// 0x220
	unsigned char m_bfmeBody[0x1c];		// 0x224
	unsigned char m_bfmeHeld;		// 0x240
};

class BfmeThingXR
{
public:
	unsigned char bfmeReadyXR(void) const;

private:
	int m_bfmeFirst;			// 0x00
	BfmePartnerXR *m_bfmePartner;		// 0x04
	unsigned char m_bfmeGap[0x28];		// 0x08
	int m_bfmeState;			// 0x30
	unsigned char m_bfmeSpare[0xab];	// 0x34
	unsigned char m_bfmeMarked;		// 0xdf
};

unsigned char BfmeThingXR::bfmeReadyXR(void) const
{
	BfmePartnerXR *partner = m_bfmePartner;

	if (m_bfmeState == 3)
	{
		if (partner->m_bfmeHeld == 0 || m_bfmeMarked == 0)
		{
			if (partner->m_bfmeWork != 0)
				return 1;
		}
	}

	return 0;
}
