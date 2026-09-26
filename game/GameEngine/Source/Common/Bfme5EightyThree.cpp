// Four more: a re-arm that puts back the byte it borrowed, a readiness test
// over eight slots, a bounds-checked pair read and a cursor that stops on the
// first live entry.

class Gen_0035EFF0
{
public:
	void bfmeArm(int a, int b, int c, int d, int e);
private:
	int m_bfmeA;								// +0x00
	int m_bfmeB;								// +0x04
	int m_bfmeC;								// +0x08
	int m_bfmeD;								// +0x0c
	int m_bfmeE;								// +0x10
	int m_bfmeGap[2];							// +0x14
	int m_bfmeF;								// +0x1c
	unsigned char *m_bfmeHold;					// +0x20
	unsigned char m_bfmeSaved;					// +0x24
	unsigned char m_bfmeGap2[3];				// +0x25
	int m_bfmeG;								// +0x28
};

// Whatever byte the last arming borrowed goes back before the new one takes
// its place.
void Gen_0035EFF0::bfmeArm(int a, int b, int c, int d, int e)
{
	unsigned char *hold = m_bfmeHold;
	if (hold != 0)
	{
		*hold = m_bfmeSaved;
		m_bfmeHold = 0;
		m_bfmeSaved = 0;
	}

	m_bfmeA = a;
	m_bfmeF = 0;
	m_bfmeG = 0;
	m_bfmeB = b;
	m_bfmeC = c;
	m_bfmeD = d;
	m_bfmeE = e;
}

extern int g_bfmeGateGN;

class Gen_00383610
{
public:
	bool bfmeReady(void) const;
private:
	int m_bfmeGap[67];							// +0x000
	int m_bfmeKind;								// +0x10c
	int m_bfmeGap2[4];							// +0x110
	unsigned char m_bfmeSlots[8];				// +0x120
	unsigned char m_bfmeGap3[0x148 - 0x128];	// +0x128
	unsigned char m_bfmeSkip;					// +0x148
};

bool Gen_00383610::bfmeReady(void) const
{
	int kind = m_bfmeKind;
	if ((kind == 1 || kind == 5) && g_bfmeGateGN != 0 && !m_bfmeSkip)
	{
		for (int index = 0; index < 8; ++index)
		{
			if (m_bfmeSlots[index] == 0)
				return false;
		}
	}
	return true;
}

class BfmePairGM
{
public:
	int m_bfmeA;
	int m_bfmeB;
};

class BfmeOwnerGM
{
public:
	int m_bfmeGap[8];							// +0x00
	BfmePairGM *m_bfmeBegin;					// +0x20
	BfmePairGM *m_bfmeEnd;						// +0x24
};

class Gen_003C7D50
{
public:
	bool bfmePairAt(int index, BfmePairGM *out) const;
private:
	int m_bfmeGap[1];							// +0x00
	BfmeOwnerGM *m_bfmeOwner;					// +0x04
};

bool Gen_003C7D50::bfmePairAt(int index, BfmePairGM *out) const
{
	BfmeOwnerGM *owner = m_bfmeOwner;
	if (owner != 0 && index >= 0)
	{
		BfmePairGM *begin = owner->m_bfmeBegin;
		if ((unsigned int)index < (unsigned int)(owner->m_bfmeEnd - begin))
		{
			out->m_bfmeA = begin[index].m_bfmeA;
			out->m_bfmeB = begin[index].m_bfmeB;
			return true;
		}
	}
	return false;
}

class BfmeEntryGO
{
public:
	int m_bfmeGap[10];							// +0x00
	int m_bfmeValue;							// +0x28
};

class Gen_003D6440
{
public:
	int bfmeFirstLive(void);
private:
	int m_bfmeGap[13];							// +0x000
	BfmeEntryGO *m_bfmeSlots[512];				// +0x034
	int m_bfmeCursor;							// +0x834
};

int Gen_003D6440::bfmeFirstLive(void)
{
	while (m_bfmeCursor < 512)
	{
		if (m_bfmeSlots[m_bfmeCursor] != 0)
			return m_bfmeSlots[m_bfmeCursor]->m_bfmeValue;
		++m_bfmeCursor;
	}
	return 0;
}
