// cl: /DNDEBUG /MD
// Twin of ?bfmeReadyXR@BfmeThingXR@@QBEEXZ at 0x002A5F70: state must be 4,
// the partner must not be held while this one is marked, and the partner
// must have work at +0x21c.

class BfmePartner5F30
{
public:
	unsigned char m_bfmeHead[0x21c];
	void *m_bfmeWork;
	unsigned char m_bfmeBody[0x20];
	unsigned char m_bfmeHeld;
};

class BfmeThing5F30
{
public:
	unsigned char bfmeReady5F30(void) const;

private:
	int m_bfmeFirst;
	BfmePartner5F30 *m_bfmePartner;
	unsigned char m_bfmeGap[0x28];
	int m_bfmeState;
	unsigned char m_bfmeSpare[0xab];
	unsigned char m_bfmeMarked;
};

unsigned char BfmeThing5F30::bfmeReady5F30(void) const
{
	BfmePartner5F30 *partner = m_bfmePartner;

	if (m_bfmeState == 4)
	{
		if (partner->m_bfmeHeld == 0 || m_bfmeMarked == 0)
		{
			if (partner->m_bfmeWork != 0)
				return 1;
		}
	}

	return 0;
}
