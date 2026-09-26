// Five more: a guarded four-word copy, an indexed read behind a size test, a
// two-flag global check, a three-argument constructor, and a visibility
// test.

class BfmeQuadDO
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeThird;					// +0x08
	int m_bfmeFourth;					// +0x0C
};

class Gen_00478220
{
public:
	int bfmeGet(BfmeQuadDO *out) const;

private:
	int m_bfmeHead[5];					// +0x00
	BfmeQuadDO m_bfmeQuad;					// +0x14
};

// ?bfmeGet@Gen_00478220@@QBEHPAVBfmeQuadDO@@@Z
int Gen_00478220::bfmeGet(BfmeQuadDO *out) const
{
	if (out != 0)
		*out = m_bfmeQuad;

	return 0;
}

class BfmeVecDO
{
public:
	unsigned int bfmeSize(void) const
	{
		return m_bfmeFinish - m_bfmeStart;
	}

	int &bfmeAt(int index) const
	{
		return m_bfmeStart[index];
	}

	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
};

class Gen_0049AFE0
{
public:
	int bfmeCurrent(void) const;

private:
	char m_bfmeHead[0x138];					// +0x000
	BfmeVecDO m_bfmeVector;					// +0x138
	int m_bfmeGap[2];					// +0x140
	int m_bfmeIndex;					// +0x148
};

// ?bfmeCurrent@Gen_0049AFE0@@QBEHXZ
int Gen_0049AFE0::bfmeCurrent(void) const
{
	if (m_bfmeVector.bfmeSize() > 0)
		return m_bfmeVector.bfmeAt(m_bfmeIndex);

	return 0;
}

// Retain the established layout witness here while bfmeReady's definition
// moves beside its caller. This type names the same retail state in both TUs.
class BfmeStateDO
{
public:
	int m_bfmeHead[11];					// +0x00
	bool m_bfmeFirst;					// +0x2C
	bool m_bfmeSecond;					// +0x2D
};

extern BfmeStateDO *g_bfmeStateDO;				// retail 0x012F1028

class BfmeThingDO
{
public:
	int m_bfmeHead[3];					// +0x00
	unsigned int m_bfmeFlags;				// +0x0C
	int m_bfmeGap[2];					// +0x10
	unsigned int m_bfmeOther;				// +0x18
};

class Gen_003D5A80
{
public:
	Gen_003D5A80(int first, int second, int third);

private:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeThird;					// +0x08
	int m_bfmeFourth;					// +0x0C
	bool m_bfmeFlag;					// +0x10
	char m_bfmeGap[3];					// +0x11
	int m_bfmeFifth;					// +0x14
	int m_bfmeSixth;					// +0x18
};

// ??0Gen_003D5A80@@QAE@HHH@Z
Gen_003D5A80::Gen_003D5A80(int first, int second, int third)
{
	m_bfmeFirst = first;
	m_bfmeSecond = second;
	m_bfmeThird = third;
	m_bfmeFourth = 0;
	m_bfmeFlag = false;
	m_bfmeFifth = 0;
	m_bfmeSixth = 0;
}

// ?bfmeVisible@@YG_NPBVBfmeThingDO@@PAXHHHH@Z
bool __stdcall bfmeVisible(const BfmeThingDO *thing, void *other, int a, int b, int c, int d)
{
	unsigned int flags = thing->m_bfmeOther;

	if (flags & 0x20)
		return true;

	if ((flags & 7) != 0)
		return other != 0;

	return false;
}
