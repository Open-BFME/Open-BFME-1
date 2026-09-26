// The retail body at 0x002140B0 calls the pinned BfmeOwnerTM sibling
// ?bfmeSendTM@BfmeOwnerTM@@QAEXPAVBfmeMsgTM@@@Z at 0x0003B372.
// The object field chain and the matching thiscall ABI establish this owner.

class BfmeThingTM;

class BfmeInnerTM
{
public:
	BfmeThingTM *bfmeResolveTM(void);
};

class BfmeThingTM
{
public:
	int m_bfmeSpareTM;
	BfmeInnerTM *m_bfmeInnerTM;
	unsigned char m_bfmeGapTM[0xc0];
	int m_bfmeFlagsTM;
};

class BfmeActorTM
{
public:
	char bfmeCanTM(int what);

	int m_bfmeSpareTM;
	BfmeThingTM *m_bfmeThingTM;
	unsigned char m_bfmeGapTM[0x70];
	void *m_bfmeOwnerTM;
};

class BfmeMsgTM
{
public:
	unsigned char m_bfmeHeadTM[8];
	void *m_bfmeKeyTM;
};

struct Rva00367E30Logic
{
	BfmeActorTM *bfmeFindTM(void *key);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeOwnerTM
{
public:
	void bfmeDoTM(BfmeMsgTM *msg);
	void bfmeSendTM(BfmeMsgTM *msg);
};

void BfmeOwnerTM::bfmeDoTM(BfmeMsgTM *msg)
{
	Rva00367E30Logic *logic = TheBfmeGameLogic;
	BfmeActorTM *actor = logic->bfmeFindTM(msg->m_bfmeKeyTM);

	if (!actor)
		return;

	BfmeThingTM *thing = actor->m_bfmeThingTM;

	if (thing && thing->m_bfmeInnerTM)
		thing = thing->m_bfmeInnerTM->bfmeResolveTM();

	if (thing->m_bfmeFlagsTM & 0x2000000)
	{
		BfmeActorTM *target = logic->bfmeFindTM(actor->m_bfmeOwnerTM);
		if (!target)
			return;
		if (!target->bfmeCanTM(0x59))
			return;
	}
	else if (!actor->bfmeCanTM(0x59))
		return;

	bfmeSendTM(msg);
}
