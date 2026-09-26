// Two more: a six-word complement with a trim and a walk that looks three
// deep.

// The trim takes the word by address, which is what keeps the complement's own
// store alive ahead of the masked one.
inline void bfmeTrimFF(unsigned int *word)
{
	*word = *word & 0x1FFFFF;
}

class Gen_00126900
{
public:
	void bfmeInvert(void);

private:
	unsigned int m_bfmeA;					// +0x00
	unsigned int m_bfmeB;					// +0x04
	unsigned int m_bfmeC;					// +0x08
	unsigned int m_bfmeD;					// +0x0C
	unsigned int m_bfmeE;					// +0x10
	unsigned int m_bfmeF;					// +0x14
};

// ?bfmeInvert@Gen_00126900@@QAEXXZ
void Gen_00126900::bfmeInvert(void)
{
	m_bfmeA = ~m_bfmeA;
	m_bfmeB = ~m_bfmeB;
	m_bfmeC = ~m_bfmeC;
	m_bfmeD = ~m_bfmeD;
	m_bfmeE = ~m_bfmeE;
	m_bfmeF = ~m_bfmeF;

	bfmeTrimFF(&m_bfmeF);
}

class BfmeThingFF
{
public:
	char m_bfmeHead[0x338];					// +0x000
	bool m_bfmeBusy;					// +0x338
};

class BfmeItemFF
{
public:
	char m_bfmeHead[0x204];					// +0x000
	BfmeThingFF *m_bfmeThing;				// +0x204
};

class BfmeNodeFF
{
public:
	BfmeNodeFF *m_bfmeNext;					// +0x00
	int m_bfmeGap;						// +0x04
	BfmeItemFF *m_bfmeItem;					// +0x08
};

class Gen_00151340
{
public:
	bool bfmeAnyBusy(void) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeNodeFF *m_bfmeList;					// +0x04
};

// ?bfmeAnyBusy@Gen_00151340@@QBE_NXZ
bool Gen_00151340::bfmeAnyBusy(void) const
{
	BfmeNodeFF *head = m_bfmeList;

	for (BfmeNodeFF *node = head->m_bfmeNext; node != head; node = node->m_bfmeNext)
	{
		BfmeItemFF *item = node->m_bfmeItem;

		if (item != 0)
		{
			BfmeThingFF *thing = item->m_bfmeThing;

			if (thing != 0 && thing->m_bfmeBusy)
				return true;
		}
	}

	return false;
}
