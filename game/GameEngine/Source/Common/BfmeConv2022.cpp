class BfmeUStrTL
{
public:
	~BfmeUStrTL();

	void *m_bfmeDataTL;
};

struct BfmeKeyTL
{
	int m_bfmeIdTL;
	unsigned short m_bfmeTagTL;
	unsigned short m_bfmePadTL;
};

struct BfmeArgTL
{
	int m_bfmeATL;
	unsigned short m_bfmeBTL;
	unsigned short m_bfmePadTL;
};

class BfmeThingTL
{
public:
	virtual void bfmeSlotA00TL();
	virtual void bfmeSlotA01TL();
	virtual void bfmeSlotA02TL();
	virtual void bfmeSlotA03TL();
	virtual void bfmeSlotA04TL();
	virtual void bfmeSlotA05TL();
	virtual void bfmeStopTL();

	unsigned char m_bfmeHeadTL[0x84];
	int m_bfmeIdTL;
	unsigned short m_bfmeTagTL;
};

struct BfmeObj935C
{
	unsigned char m_bfmeHeadTL[0x26c];
	char m_bfmeFlagTL;
};

extern BfmeObj935C *g_bfme935GlobC;

void __stdcall bfmeFallbackTL();

class BfmeHostTL
{
public:
	virtual void bfmeSlotB00TL();
	virtual void bfmeSlotB01TL();
	virtual void bfmeSlotB02TL();
	virtual void bfmeSlotB03TL();
	virtual void bfmeSlotB04TL();
	virtual void bfmeSlotB05TL();
	virtual void bfmeSlotB06TL();
	virtual void bfmeSlotB07TL();
	virtual void bfmeSlotB08TL();
	virtual void bfmeSlotB09TL();
	virtual void bfmeSlotB10TL();
	virtual void bfmeSlotB11TL();
	virtual void bfmeSlotB12TL();
	virtual void bfmeSlotB13TL();
	virtual void bfmeSlotB14TL();
	virtual void bfmeSlotB15TL();
	virtual void bfmeSlotB16TL();
	virtual void bfmeSlotB17TL();
	virtual void bfmeSlotB18TL();
	virtual void bfmeSlotB19TL();
	virtual void bfmeSlotB20TL();
	virtual void bfmeNotifyTL(int mode, BfmeArgTL *arg);
	virtual void bfmeSlotC22TL();
	virtual void bfmeSlotC23TL();
	virtual void bfmeSlotC24TL();
	virtual void bfmeSlotC25TL();
	virtual void bfmeSlotC26TL();
	virtual void bfmeSlotC27TL();
	virtual void bfmeSlotC28TL();
	virtual void bfmeSlotC29TL();
	virtual void bfmeSlotC30TL();
	virtual void bfmeSlotC31TL();
	virtual void bfmeSlotC32TL();
	virtual void bfmeSlotC33TL();
	virtual void bfmeSlotC34TL();
	virtual void bfmeSlotC35TL();
	virtual void bfmeSlotC36TL();
	virtual void bfmeSlotC37TL();
	virtual void bfmeSlotC38TL();
	virtual void bfmeSlotC39TL();
	virtual void bfmeSlotC40TL();
	virtual void bfmeSlotC41TL();
	virtual void bfmeSlotC42TL();
	virtual void bfmeSlotC43TL();
	virtual void bfmeSlotC44TL();
	virtual void bfmeSlotC45TL();
	virtual void bfmeSlotC46TL();
	virtual void bfmeSlotC47TL();
	virtual void bfmeSlotC48TL();
	virtual void bfmeSlotC49TL();
	virtual void bfmeSlotC50TL();
	virtual void bfmeSlotC51TL();
	virtual void bfmeSlotC52TL();
	virtual void bfmeSlotC53TL();
	virtual void bfmeSlotC54TL();
	virtual BfmeKeyTL *bfmeCurrentTL();

	void bfmeApplyTL(int unused, BfmeUStrTL text);

	unsigned char m_bfmeHeadTL[0x3c];
	BfmeThingTL *m_bfmeThingTL;
};

void BfmeHostTL::bfmeApplyTL(int unused, BfmeUStrTL text)
{
	BfmeThingTL *thing = m_bfmeThingTL;

	if (thing != 0)
	{
		BfmeKeyTL *key = bfmeCurrentTL();

		if (thing->m_bfmeIdTL == key->m_bfmeIdTL && thing->m_bfmeTagTL == key->m_bfmeTagTL)
		{
			m_bfmeThingTL->bfmeStopTL();

			BfmeArgTL arg;

			arg.m_bfmeATL = 0;
			arg.m_bfmeBTL = 0;

			bfmeNotifyTL(1, &arg);
		}
	}

	if (g_bfme935GlobC != 0)
		g_bfme935GlobC->m_bfmeFlagTL = 1;
	else
		bfmeFallbackTL();
}
