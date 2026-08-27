// Two hooks let go of at once, and a ring looked over for anything still busy.

class BfmeThingZU;

struct BfmeReachZU
{
	BfmeThingZU *m_bfmeBack;		// 0x0
};

class BfmeThingZU
{
public:
	void bfmeUnhookZU(void);

	unsigned char m_bfmeHead[8];		// 0x00
	BfmeReachZU *m_bfmeFirstOn;		// 0x08
	BfmeThingZU *m_bfmeFirstBack;		// 0x0c
	unsigned char m_bfmeGap[8];		// 0x10
	BfmeReachZU *m_bfmeSecondOn;		// 0x18
	BfmeThingZU *m_bfmeSecondBack;		// 0x1c
};

void BfmeThingZU::bfmeUnhookZU(void)
{
	if (m_bfmeSecondOn != 0)
	{
		if (m_bfmeSecondBack != 0)
			m_bfmeSecondBack->m_bfmeSecondOn = m_bfmeSecondOn;

		m_bfmeSecondOn->m_bfmeBack = m_bfmeSecondBack;
		m_bfmeSecondOn = 0;
	}

	if (m_bfmeFirstBack != 0)
		m_bfmeFirstBack->m_bfmeFirstOn = m_bfmeFirstOn;

	m_bfmeFirstOn->m_bfmeBack = m_bfmeFirstBack;
	m_bfmeFirstOn = 0;
}

struct BfmeOwnerZW
{
	unsigned char m_bfmeHead[0x140];	// 0x000
	void *m_bfmeThing;			// 0x140
	unsigned char m_bfmeBody[0x94];		// 0x144
	int m_bfmeState;			// 0x1d8
};

struct BfmeItemZW
{
	unsigned char m_bfmeHead[0x204];	// 0x000
	BfmeOwnerZW *m_bfmeOwner;		// 0x204
};

struct BfmeNodeZW
{
	BfmeNodeZW *m_bfmeNext;			// 0x0
	unsigned char m_bfmeGap[4];		// 0x4
	BfmeItemZW *m_bfmeItem;			// 0x8
};

class BfmeSubZW
{
public:
	unsigned char bfmeQuietZW(void) const;

	unsigned char m_bfmeHead[4];		// 0x0
};

class BfmeHostZW
{
public:
	BfmeNodeZW *m_bfmeRing;			// 0x000
	unsigned char m_bfmeGap[0xa8];		// 0x004
	BfmeSubZW m_bfmeSub;			// 0x0ac
};

unsigned char BfmeSubZW::bfmeQuietZW(void) const
{
	const BfmeHostZW *host = (const BfmeHostZW *)((const char *)this - 0xac);
	BfmeNodeZW *ring = host->m_bfmeRing;
	BfmeNodeZW *at = ring->m_bfmeNext;

	while (at != ring)
	{
		BfmeItemZW *item = at->m_bfmeItem;

		if (item != 0)
		{
			BfmeOwnerZW *owner = item->m_bfmeOwner;

			if (owner->m_bfmeThing != 0 && owner->m_bfmeState == 4)
				return 0;
		}

		at = at->m_bfmeNext;
	}

	return 1;
}
