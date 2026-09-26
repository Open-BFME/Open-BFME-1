// A reading chosen by the sort of thing asked about, a flag taken away with a
// side effect when it is the tenth one, and a search that marks the first cell
// carrying a given key.

struct BfmeSlotYX
{
	int m_bfmeFirst;			// 0x00
	int m_bfmeSecond;			// 0x04
	unsigned char m_bfmeBody[0x38];		// 0x08
};

struct BfmeItemYX
{
	unsigned char m_bfmeHead[8];		// 0x0
	int m_bfmeValue;			// 0x8
	int m_bfmeKind;				// 0xc
};

struct BfmeBoxYX
{
	BfmeItemYX *m_bfmeItem;			// 0x0
};

class BfmeThingYX
{
public:
	int bfmePickYX(BfmeBoxYX *box) const;

private:
	unsigned char m_bfmeHead[0xb44];	// 0x000
	BfmeSlotYX *m_bfmeTable;		// 0xb44
};

int BfmeThingYX::bfmePickYX(BfmeBoxYX *box) const
{
	BfmeItemYX *item = box->m_bfmeItem;

	switch (item->m_bfmeKind)
	{
		case 1:
			return item->m_bfmeValue;

		case 2:
			return m_bfmeTable[item->m_bfmeValue].m_bfmeSecond;

		case 4:
			return 0;
	}

	return 0;
}

class BfmeJobYY
{
public:
	unsigned char m_bfmeHead[0x34];		// 0x00
	int m_bfmeDelay;			// 0x34
	unsigned char m_bfmeState;		// 0x38
};

class BfmeThingYY
{
public:
	void bfmeClearYY(unsigned int bit);

private:
	unsigned char m_bfmeHead[0x68];		// 0x000
	BfmeJobYY *m_bfmeJob;			// 0x068
	unsigned char m_bfmeGap[0xa8];		// 0x06c
	unsigned int m_bfmeFlags;		// 0x114
};

void BfmeThingYY::bfmeClearYY(unsigned int bit)
{
	m_bfmeFlags &= ~bit;

	if (bit == 0x10)
	{
		BfmeJobYY *job = m_bfmeJob;

		if (job != 0)
		{
			job->m_bfmeDelay = 10;
			m_bfmeJob->m_bfmeState = 2;
		}
	}
}

struct BfmeCellYZ
{
	unsigned char m_bfmeHead[8];		// 0x00
	int m_bfmeKey;				// 0x08
	unsigned char m_bfmeBody[0x14];		// 0x0c
	int m_bfmeValue;			// 0x20
};

struct BfmeThingYZ
{
	unsigned char m_bfmeHead[0x74];		// 0x00
	int m_bfmeKey;				// 0x74
};

class BfmeTableYZ
{
public:
	void bfmeMarkYZ(BfmeThingYZ *thing, int value);

private:
	unsigned char m_bfmeHead[0xc];		// 0x00
	BfmeCellYZ **m_bfmeBegin;		// 0x0c
	BfmeCellYZ **m_bfmeEnd;			// 0x10
};

void BfmeTableYZ::bfmeMarkYZ(BfmeThingYZ *thing, int value)
{
	if (thing == 0)
		return;

	BfmeCellYZ **end = m_bfmeEnd;
	int key = thing->m_bfmeKey;
	BfmeCellYZ **at = m_bfmeBegin;

	while (at != end)
	{
		BfmeCellYZ *cell = *at;

		if (cell != 0 && cell->m_bfmeKey == key)
		{
			cell->m_bfmeValue = value;
			return;
		}

		++at;
	}
}
