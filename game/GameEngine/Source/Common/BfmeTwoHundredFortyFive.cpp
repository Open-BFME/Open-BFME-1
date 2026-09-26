// Two errands over plain memory: a record unhooked from the list its owner
// keeps, and a block of another record cleared when the first says so.


struct BfmeLinkOF
{
	unsigned char m_bfmeHead[4];		// 0x0
	BfmeLinkOF *m_bfmeBack;			// 0x4
	BfmeLinkOF *m_bfmeOn;			// 0x8
};

struct BfmeOwnerOF
{
	unsigned char m_bfmeHead[0x98];		// 0x00
	BfmeLinkOF *m_bfmeFirst;		// 0x98
	BfmeLinkOF *m_bfmeLast;			// 0x9c
};

class BfmeThingOF
{
public:
	void bfmeUnlinkOF(void);

private:
	unsigned char m_bfmeHead[0x7c];		// 0x00
	BfmeOwnerOF *m_bfmeOwner;		// 0x7c
	BfmeLinkOF *m_bfmeBack;			// 0x80
	BfmeLinkOF *m_bfmeOn;			// 0x84
};

void BfmeThingOF::bfmeUnlinkOF(void)
{
	BfmeOwnerOF *owner = m_bfmeOwner;

	if (owner == 0)
		return;

	if (m_bfmeBack != 0)
		m_bfmeBack->m_bfmeOn = m_bfmeOn;
	else
		owner->m_bfmeFirst = m_bfmeOn;

	if (m_bfmeOn != 0)
		m_bfmeOn->m_bfmeBack = m_bfmeBack;
	else
		m_bfmeOwner->m_bfmeLast = m_bfmeBack;

	m_bfmeBack = 0;
	m_bfmeOn = 0;
	m_bfmeOwner = 0;
}

struct BfmeThingOG
{
	unsigned char m_bfmeHead[0xac8];	// 0x000
	int m_bfmeOn;				// 0xac8
};

struct BfmeOtherOG
{
	unsigned char m_bfmeHead[0x68];		// 0x00
	int m_bfmeRest[18];			// 0x68
};

int bfmeResetOG(const BfmeThingOG *from, BfmeOtherOG *out)
{
	if (from->m_bfmeOn != 0)
	{
		out->m_bfmeRest[0] = 0;
		out->m_bfmeRest[1] = 0;
		out->m_bfmeRest[2] = 0;
		out->m_bfmeRest[3] = 0;
		out->m_bfmeRest[4] = 0;
		out->m_bfmeRest[5] = 0;
		out->m_bfmeRest[6] = 0;
		out->m_bfmeRest[7] = 0;
		out->m_bfmeRest[8] = 0;
		out->m_bfmeRest[9] = 0;
		out->m_bfmeRest[10] = 0;
		out->m_bfmeRest[11] = 0;
		out->m_bfmeRest[12] = 0;
		out->m_bfmeRest[13] = 0;
		out->m_bfmeRest[14] = 0;
		out->m_bfmeRest[15] = 0;
		out->m_bfmeRest[16] = 0;
		out->m_bfmeRest[17] = 0;
	}

	return 1;
}

