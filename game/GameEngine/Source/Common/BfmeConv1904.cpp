struct BfmeInfoAX
{
	unsigned char m_bfmeFlagAX;
	unsigned char m_bfmeLevelAX;
};

class BfmeThingAX
{
public:
	unsigned char m_bfmeHeadAX[4];
	int m_bfmeIdAX;
};

class BfmeAgentAX
{
public:
	virtual void bfmeSlot00AX();
	virtual char bfmeReadingAX();
	virtual void bfmeSlot02AX();
	virtual void bfmeSlot03AX();
	virtual char bfmeSkipAX();
	virtual void bfmeSlot05AX();
	virtual void bfmeSlot06AX();
	virtual void bfmeSlot07AX();
	virtual void bfmeSlot08AX();
	virtual void bfmeSlot09AX();
	virtual void bfmeFillAX(BfmeInfoAX *info);
	virtual void bfmeSlot11AX();
	virtual void bfmeSlot12AX();
	virtual void bfmeSlot13AX();
	virtual void bfmeSlot14AX();
	virtual void bfmeSlot15AX();
	virtual void bfmeSlot16AX();
	virtual void bfmeSlot17AX();
	virtual void bfmeSlot18AX();
	virtual void bfmeSlot19AX();
	virtual void bfmeSlot20AX();
	virtual void bfmeSlot21AX();
	virtual void bfmeSlot22AX();
	virtual void bfmeSlot23AX();
	virtual void bfmeSlot24AX();
	virtual void bfmeSlot25AX();
	virtual void bfmeSlot26AX();
	virtual void bfmeSlot27AX();
	virtual void bfmeSlot28AX();
	virtual void bfmeSlot29AX();
	virtual void bfmeSlot30AX();
	virtual void bfmeSlot31AX();
	virtual void bfmeSlot32AX();
	virtual void bfmeSlot33AX();
	virtual void bfmeSlot34AX();
	virtual void bfmeByteAX(unsigned char *dst);
};

struct Rva003FD060TerrainLogic
{
	virtual void bfmeSlot00TL();
	virtual void bfmeSlot01TL();
	virtual void bfmeSlot02TL();
	virtual void bfmeSlot03TL();
	virtual void bfmeSlot04TL();
	virtual void bfmeSlot05TL();
	virtual void bfmeSlot06TL();
	virtual void bfmeSlot07TL();
	virtual void bfmeSlot08TL();
	virtual void bfmeSlot09TL();
	virtual void bfmeSlot10TL();
	virtual void bfmeSlot11TL();
	virtual void bfmeSlot12TL();
	virtual void bfmeSlot13TL();
	virtual void bfmeSlot14TL();
	virtual void bfmeSlot15TL();
	virtual void bfmeSlot16TL();
	virtual void bfmeSlot17TL();
	virtual void bfmeSlot18TL();
	virtual void bfmeSlot19TL();
	virtual void bfmeSlot20TL();
	virtual void bfmeSlot21TL();
	virtual void bfmeSlot22TL();
	virtual void bfmeSlot23TL();
	virtual void bfmeSlot24TL();
	virtual void bfmeSlot25TL();
	virtual void bfmeSlot26TL();
	virtual void bfmeSlot27TL();
	virtual void bfmeSlot28TL();
	virtual void bfmeSlot29TL();
	virtual void bfmeSlot30TL();
	virtual void bfmeSlot31TL();
	virtual BfmeThingAX *bfmeLookupAX(int id);
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;

extern "C" void __cdecl bfmeXferIntAX(BfmeAgentAX *ag, int *value);

class BfmeHostAX
{
public:
	void bfmeSaveAX(BfmeAgentAX *ag);
	void bfmeBeginAX(BfmeAgentAX *ag);

	unsigned char m_bfmeHeadAX[0x24];
	BfmeThingAX *m_bfmeArrayAX[6];
	unsigned char m_bfmeFirstAX;
	unsigned char m_bfmeSecondAX;
};

void BfmeHostAX::bfmeSaveAX(BfmeAgentAX *ag)
{
	bfmeBeginAX(ag);

	if (ag->bfmeSkipAX() != 0)
		return;

	BfmeInfoAX info;

	info.m_bfmeFlagAX = 1;
	info.m_bfmeLevelAX = 2;
	ag->bfmeFillAX(&info);

	int out;
	BfmeThingAX **p = m_bfmeArrayAX;

	for (int i = 0; i < 6; i++)
	{
		if (ag->bfmeReadingAX() != 0)
		{
			int id;

			bfmeXferIntAX(ag, &id);

			BfmeThingAX *t;

			if (id == 0x7fffffff)
				t = 0;
			else
				t = TheTerrainLogic->bfmeLookupAX(id);

			*p = t;
		}
		else
		{
			int v;

			if (*p != 0)
				v = (*p)->m_bfmeIdAX;
			else
				v = 0x7fffffff;

			out = v;
			bfmeXferIntAX(ag, &out);
		}

		p++;
	}

	ag->bfmeByteAX(&m_bfmeFirstAX);

	if (info.m_bfmeLevelAX >= 2)
		ag->bfmeByteAX(&m_bfmeSecondAX);
}
