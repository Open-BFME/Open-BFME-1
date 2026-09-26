// Three more: a walk that tolerates a null this, a guarded value read, and a
// global reset.

extern float g_bfmeADL;						// retail 0x0107533C

class BfmeThingEB
{
public:
	int m_bfmeHead[11];					// +0x00
	float m_bfmeValue;					// +0x2C
};

class Gen_008D1EB0
{
public:
	bool bfmeIdle(void) const;

private:
	int m_bfmeHead[18];					// +0x00
	BfmeThingEB *m_bfmeThing;				// +0x48
	Gen_008D1EB0 *m_bfmeNext;				// +0x4C
};

// ?bfmeIdle@Gen_008D1EB0@@QBE_NXZ
bool Gen_008D1EB0::bfmeIdle(void) const
{
	const Gen_008D1EB0 *node = this;

	while (node != 0)
	{
		BfmeThingEB *thing = node->m_bfmeThing;

		if (thing != 0 && thing->m_bfmeValue < g_bfmeADL)
			return false;

		node = node->m_bfmeNext;
	}

	return true;
}

class BfmeItemEB
{
public:
	int m_bfmeHead[4];					// +0x00
	int m_bfmeValue;					// +0x10
};

class Gen_008C41D0
{
public:
	int bfmeValue(void) const;

private:
	int m_bfmeHead;						// +0x00
	unsigned int m_bfmeBits;				// +0x04
	int m_bfmeGap[18];					// +0x08
	BfmeItemEB *m_bfmeItem;					// +0x50
};

// ?bfmeValue@Gen_008C41D0@@QBEHXZ
int Gen_008C41D0::bfmeValue(void) const
{
	unsigned int bits = m_bfmeBits;

	if ((bits & 0x3F) == 0x13)
	{
		unsigned char flag = (unsigned char)(bits >> 15);

		flag = ~flag;

		if ((flag & 1) == 0)
			return 0;
	}

	BfmeItemEB *item = m_bfmeItem;

	// Both rejections jump forward to one zero at the end, so the read has to
	// be the fall-through.
	if (item != 0 && item != (BfmeItemEB *)0xBAADF00D)
		return item->m_bfmeValue;

	return 0;
}

extern int g_bfmeFirstEB;					// retail 0x01346DDC
extern int g_bfmeSecondEB;					// retail 0x01346DE0
extern int g_bfmeThirdEB;					// retail 0x012D718C
extern int g_bfmeFourthEB;					// retail 0x012D7190
extern int g_bfmeFifthEB;					// retail 0x012D7194

// ?bfmeResetGlobals@@YAXXZ
void __cdecl bfmeResetGlobals(void)
{
	g_bfmeSecondEB = 0;
	g_bfmeFirstEB = 0;

	g_bfmeThirdEB = 7;
	g_bfmeFourthEB = 2;
	g_bfmeFifthEB = 5;
}
