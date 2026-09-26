// Four more: a limit picked by a global switch, a search through a two-level
// list, a commit of two pending bytes, and a mask add.

class BfmeSwitchDR
{
public:
	int m_bfmeHead[7];					// +0x00
	bool m_bfmeUseHigh;					// +0x1C
};

class BfmeBaseDS
{
public:
	char m_bfmeHead[0xEB8];					// +0xEB8
	int m_bfmeLow;						// +0xEB8
	int m_bfmeHigh;						// +0xEBC
};

extern BfmeSwitchDR *g_bfmeSwitchDR;				// retail 0x012F1024
extern BfmeBaseDS *g_bfmeBaseDS;				// retail 0x012ED5C8

// ?bfmeLimit@@YAHXZ
int __cdecl bfmeLimit(void)
{
	BfmeSwitchDR *state = g_bfmeSwitchDR;

	int high = state != 0 ? state->m_bfmeUseHigh : 0;

	if (state != 0 && high != 0)
		return g_bfmeBaseDS->m_bfmeHigh;

	return g_bfmeBaseDS->m_bfmeLow;
}

class BfmeItemDS
{
public:
	int m_bfmeHead;						// +0x00
	void *m_bfmeKey;					// +0x04
};

class BfmeNodeDS
{
public:
	BfmeNodeDS *m_bfmeNext;					// +0x00
	int m_bfmeGap;						// +0x04
	BfmeItemDS *m_bfmeItem;					// +0x08
};

class Gen_00428090
{
public:
	bool bfmeContains(void *key) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeNodeDS *m_bfmeList;					// +0x04
};

// ?bfmeContains@Gen_00428090@@QBE_NPAX@Z
bool Gen_00428090::bfmeContains(void *key) const
{
	BfmeNodeDS *head = m_bfmeList;

	for (BfmeNodeDS *node = head->m_bfmeNext; node != head; node = node->m_bfmeNext)
	{
		if (node->m_bfmeItem->m_bfmeKey == key)
			return true;
	}

	return false;
}

class Gen_005A4470
{
public:
	void bfmeCommit(void);

private:
	char m_bfmeHead[0x4DA1];				// +0x0000
	unsigned char m_bfmeFirst;				// +0x4DA1
	unsigned char m_bfmeSecond;				// +0x4DA2
	unsigned char m_bfmePendingFirst;			// +0x4DA3
	unsigned char m_bfmePendingSecond;			// +0x4DA4
	bool m_bfmeDirty;					// +0x4DA5
};

// ?bfmeCommit@Gen_005A4470@@QAEXXZ
void Gen_005A4470::bfmeCommit(void)
{
	if (m_bfmeDirty)
	{
		m_bfmeFirst = m_bfmePendingFirst;
		m_bfmeSecond = m_bfmePendingSecond;

		m_bfmeDirty = false;
	}
}

class BfmeStateDS
{
public:
	char m_bfmeHead[0x4DA8];				// +0x0000
	int m_bfmeValue;					// +0x4DA8
};

extern BfmeStateDS *g_bfmeStateDS;				// retail 0x012F4C5C

class Gen_005B4260
{
public:
	void bfmeAddMask(int mask);

private:
	int m_bfmeHead;						// +0x00
	int m_bfmeFlags;					// +0x04
	int m_bfmeBase;						// +0x08
	int m_bfmeGap[8];					// +0x0C
	bool m_bfmeDirty;					// +0x2C
};

// ?bfmeAddMask@Gen_005B4260@@QAEXH@Z
void Gen_005B4260::bfmeAddMask(int mask)
{
	int flags = m_bfmeFlags;

	if (flags == 0)
		m_bfmeBase = g_bfmeStateDS->m_bfmeValue;

	m_bfmeDirty = true;

	if ((mask & flags) == 0)
		m_bfmeFlags = flags + mask;
}
