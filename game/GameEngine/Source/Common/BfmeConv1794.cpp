class BfmeThingHF;

class BfmeInnerHF
{
public:
	BfmeThingHF *bfmeResolveHF(void);
};

class BfmeThingHF
{
public:
	int m_bfmeSpareHF;
	BfmeInnerHF *m_bfmeInnerHF;
	unsigned char m_bfmeGapHF[0xc0];
	int m_bfmeFlagsHF;
};

class BfmeActorHF
{
public:
	char bfmeCanHF(int what);

	unsigned char m_bfmeHeadHF[0x74];
	void *m_bfmeKeyHF;
};

class BfmeValueHF;

class BfmeListHF
{
public:
	void bfmeAddHF(BfmeValueHF *value);
};

class BfmeSlotHF
{
public:
	unsigned char m_bfmeHeadHF[0x20];
	BfmeListHF m_bfmeListHF;
};

class BfmeUnitHF
{
public:
	int m_bfmeSpareHF;
	BfmeThingHF *m_bfmeThingHF;
	unsigned char m_bfmeGapHF[0x1fc];
	BfmeSlotHF *m_bfmeSlotHF;
};

struct Rva00367E30Logic
{
	BfmeValueHF *bfmeLookupHF(void *key, int flag);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeOwnerHF
{
public:
	void bfmeApplyHF(BfmeActorHF *actor, int spare);
};

void BfmeOwnerHF::bfmeApplyHF(BfmeActorHF *actor, int spare)
{
	BfmeUnitHF *unit = *(BfmeUnitHF **)((char *)this - 8);
	BfmeThingHF *thing = unit->m_bfmeThingHF;

	if (thing && thing->m_bfmeInnerHF)
		thing = thing->m_bfmeInnerHF->bfmeResolveHF();

	if (thing->m_bfmeFlagsHF & 0x4000)
	{
		if (actor && actor->bfmeCanHF(7))
		{
			BfmeSlotHF *slot = unit->m_bfmeSlotHF;

			if (slot)
				slot->m_bfmeListHF.bfmeAddHF(TheBfmeGameLogic->bfmeLookupHF(actor->m_bfmeKeyHF, 0));
		}
	}
}
