// Two more: the kind byte of a grid cell, and a one-shot that only fires while
// nothing blocks it.

class BfmeCellID
{
public:
	unsigned char m_bfmeKind;					// +0x00
	unsigned char m_bfmeGap[7];					// +0x01
};

class Gen_008814C0
{
public:
	int bfmeKindAt(int x, int y) const;
private:
	int m_bfmeGap[8];							// +0x00
	int m_bfmeWidth;							// +0x20
	int m_bfmeHeight;							// +0x24
	BfmeCellID *m_bfmeCells;					// +0x28
};

int Gen_008814C0::bfmeKindAt(int x, int y) const
{
	if (x < 0 || x >= m_bfmeWidth)
		return 0x80;
	if (y < 0 || y >= m_bfmeHeight)
		return 0x80;

	BfmeCellID *cell = &m_bfmeCells[y * m_bfmeWidth + x];
	if (cell == 0)
		return 0x80;
	return cell->m_bfmeKind;
}

class BfmeThingIA
{
public:
	int m_bfmeGap[10];							// +0x00
	float m_bfmeTime;							// +0x28
	unsigned char m_bfmeGap2[0x35 - 0x2c];		// +0x2c
	unsigned char m_bfmeMark;					// +0x35
	unsigned char m_bfmeGap3[6];				// +0x36
	unsigned char m_bfmeReady;					// +0x3c
};

class BfmeOwnerIA
{
public:
	int m_bfmeGap[15];							// +0x00
	int m_bfmeTicks;							// +0x3c
};

class Gen_0069ADF0
{
public:
	void bfmeTouch(BfmeThingIA **ref);
private:
	int m_bfmeGap[3];							// +0x000
	BfmeOwnerIA *m_bfmeOwner;					// +0x00c
	unsigned char m_bfmeGap2[0x637 - 0x010];	// +0x010
	unsigned char m_bfmeBlocked;				// +0x637
	int m_bfmeHeld;								// +0x638
};

void Gen_0069ADF0::bfmeTouch(BfmeThingIA **ref)
{
	if ((*ref)->m_bfmeReady && !m_bfmeBlocked)
	{
		(*ref)->m_bfmeReady = 0;
		if (m_bfmeHeld == 0)
		{
			(*ref)->m_bfmeMark = 1;
			(*ref)->m_bfmeTime = (float)m_bfmeOwner->m_bfmeTicks;
		}
	}
}
