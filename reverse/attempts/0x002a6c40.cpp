// ?bfmeCheckXR@BfmeOwnerXR@@QAE_NPAX@Z
// partial score=0.25 date=2026-09-07
// Retail body 0x002A6C40, reached through the 0x00040390 ILT.

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
typedef unsigned int NameKeyType;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern UnsignedInt g_bfmeCheckXRInit;
extern NameKeyType g_bfmeCheckXRKey;

class StealthUpdate
{
public:
	unsigned char m_pad00[0x2d];
	Bool m_field2d;
};

class BfmeXRChain
{
public:
	unsigned char m_pad00[4];
	BfmeXRChain *m_next;
	BfmeXRChain *friend_getFinalOverride();
};

class BfmeXRResult
{
public:
	unsigned char m_pad00[0x14];
	int m_value14;
};

class BfmeContain
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0;
	virtual UnsignedInt slot23();
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0; virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0; virtual void slot42() = 0; virtual void slot43() = 0;
	virtual void slot44() = 0; virtual void slot45() = 0; virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0; virtual void slot50() = 0; virtual void slot51() = 0;
	virtual void slot52() = 0; virtual void slot53() = 0; virtual void slot54() = 0; virtual void slot55() = 0;
	virtual void slot56() = 0; virtual void slot57() = 0; virtual void slot58() = 0; virtual void slot59() = 0;
	virtual void slot60() = 0; virtual void slot61() = 0; virtual void slot62() = 0; virtual void slot63() = 0;
	virtual UnsignedInt slot64(Bool argument);
};

class BfmePlayerXR
{
public:
	unsigned char m_pad1d8[0x1d8];
	BfmeXRChain *m_chain1d8;
	unsigned char m_pad1dc[0x238 - 0x1dc];
	UnsignedInt m_flags238;
	UnsignedInt m_flags23c;
	unsigned char m_pad240[0x24d - 0x240];
	Bool m_flag24d;
};

class BfmeObjectXR
{
public:
	unsigned char m_pad128[0x128];
	UnsignedInt m_status128;
	UnsignedInt m_status12c;
	UnsignedInt m_status130;
	unsigned char m_pad134[0x1fc - 0x134];
	BfmeContain *m_contain;
	StealthUpdate *findUpdateModule(NameKeyType key);
};

class BfmeOwnerXR
{
public:
	bool bfmeCheckXR(void *argument);
};

class BfmeCheckXRSentry
{
public:
	BfmeCheckXRSentry() {}
	~BfmeCheckXRSentry() {}
};

bool BfmeOwnerXR::bfmeCheckXR(void *argument)
{
	BfmeCheckXRSentry sentry;
	BfmePlayerXR *player = *(BfmePlayerXR **)((char *)this - 0x1c);
	BfmeObjectXR *object = *(BfmeObjectXR **)((char *)this - 0x18);

	UnsignedInt flags238 = *(volatile UnsignedInt *)((char *)player + 0x238);
	if ((flags238 & 1) != 0)
	{
		if ((*(volatile UnsignedInt *)((char *)object + 0x128) & 0x800) == 0)
			return 0;
		if ((*(volatile UnsignedInt *)((char *)object + 0x130) & 0x1000) == 0)
			return 0;
	}

	UnsignedInt flags23c = *(volatile UnsignedInt *)((char *)player + 0x23c);
	if ((flags23c & 1) != 0)
	{
		if ((*(volatile UnsignedInt *)((char *)object + 0x128) & 0x800) != 0)
			return 0;
		if ((*(volatile UnsignedInt *)((char *)object + 0x130) & 0x1000) != 0)
			return 0;
	}

	if (player->m_flag24d)
	{
		if ((g_bfmeCheckXRInit & 1) == 0)
		{
			g_bfmeCheckXRInit |= 1;
			g_bfmeCheckXRKey = TheNameKeyGenerator->nameToKey("StealthUpdate");
		}

		StealthUpdate *module = object->findUpdateModule(g_bfmeCheckXRKey);
		if (module != 0 && module->m_field2d)
			return 0;

		BfmeXRChain *chain = player->m_chain1d8;
		if (chain->m_next != 0)
		{
			BfmeXRChain *resolved = chain->m_next->m_next;
			if (resolved != 0)
			{
				BfmeXRResult *final = (BfmeXRResult *)resolved->friend_getFinalOverride();
				if (final->m_value14 >= 0x27 && final->m_value14 <= 0x28)
				{
					BfmeContain *contain = object->m_contain;
					if (contain == 0)
						return 0;
					UnsignedInt begin = contain->slot64(0);
					UnsignedInt end = contain->slot23();
					if (begin < end)
						return 0;
				}
			}
		}
	}

	return 1;
}
