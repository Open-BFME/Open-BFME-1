// Two short errands that only read and write their own record: the room a
// record will take, and three settings pinned to their nearest allowed value.

class BfmeThingNH
{
public:
	int bfmeSizeNH(void);

private:
	unsigned char m_bfmeHead[8];		// 0x00
	void *m_bfmeWide;			// 0x08
	unsigned char m_bfmeGap[0x14];		// 0x0c
	void *m_bfmeOne;			// 0x20
	void *m_bfmeTwo;			// 0x24
	void *m_bfmeThree;			// 0x28
	void *m_bfmeFour;			// 0x2c
	void *m_bfmeFive;			// 0x30
	void *m_bfmeSix;			// 0x34
	void *m_bfmeSeven;			// 0x38
	void *m_bfmeEight;			// 0x3c
};

int BfmeThingNH::bfmeSizeNH(void)
{
	int room = 0x6c;

	if (m_bfmeWide != 0)
		room = 0xb0;

	if (m_bfmeOne != 0)
		room += 0x20;

	if (m_bfmeTwo != 0)
		room += 0x20;

	if (m_bfmeThree != 0)
		room += 0x20;

	if (m_bfmeFour != 0)
		room += 0x20;

	if (m_bfmeFive != 0)
		room += 0x20;

	if (m_bfmeSix != 0)
		room += 0x20;

	if (m_bfmeSeven != 0)
		room += 0x20;

	if (m_bfmeEight != 0)
		room += 0x20;

	return room;
}

class BfmeThingNJ
{
public:
	void bfmeFixNJ(void);

private:
	unsigned char m_bfmeHead[0x4d28];	// 0x0000
	void *m_bfmeOne;			// 0x4d28
	int m_bfmeOneWhat;			// 0x4d2c
	unsigned char m_bfmeGap1[4];		// 0x4d30
	void *m_bfmeTwo;			// 0x4d34
	int m_bfmeTwoWhat;			// 0x4d38
	unsigned char m_bfmeGap2[4];		// 0x4d3c
	void *m_bfmeThree;			// 0x4d40
	int m_bfmeThreeWhat;			// 0x4d44
	unsigned char m_bfmeGap3[0x20];		// 0x4d48
	int m_bfmeOneKind;			// 0x4d68
	unsigned char m_bfmeGap4[8];		// 0x4d6c
	int m_bfmeTwoKind;			// 0x4d74
	unsigned char m_bfmeGap5[8];		// 0x4d78
	int m_bfmeThreeKind;			// 0x4d80
};

void BfmeThingNJ::bfmeFixNJ(void)
{
	if (m_bfmeOne != 0)
	{
		int kind = m_bfmeOneKind;

		if (kind == 5 || kind == 8)
			m_bfmeOneWhat = 8;
	}

	if (m_bfmeTwo != 0)
	{
		int kind = m_bfmeTwoKind;

		if (kind == 0xd || kind == 0x10)
			m_bfmeTwoWhat = 0x10;
	}

	if (m_bfmeThree != 0)
	{
		int kind = m_bfmeThreeKind;

		if (kind == 9 || kind == 0xc)
			m_bfmeThreeWhat = 0xc;
	}
}
