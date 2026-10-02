// The retail body at 0x002140B0 calls the pinned BfmeOwnerTM sibling
// ?bfmeSendTM@BfmeOwnerTM@@QAEXPAVBfmeMsgTM@@@Z at 0x0003B372.
// The object field chain and the matching thiscall ABI establish this owner.

// stlport
// The lookup below is GameLogic::findObjectByID; GameLogicObjectLookup.h holds
// the declaration (its body stays in Thing/GameLogicFindObjectByID.cpp).
#include "Thing/GameLogicObjectLookup.h"

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

// Retail's global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined once
// in game/GameEngine/Source/GameLogic/System/GameLogic.cpp; Thing/GameLogicObjectLookup.h
// above already declares the real GameLogic view this TU calls through.
extern GameLogic *TheGameLogic;

class BfmeOwnerTM
{
public:
	void bfmeDoTM(BfmeMsgTM *msg);
	void bfmeSendTM(BfmeMsgTM *msg);
};

void BfmeOwnerTM::bfmeDoTM(BfmeMsgTM *msg)
{
	GameLogic *gamelogic = TheGameLogic;
	BfmeActorTM *actor = reinterpret_cast<BfmeActorTM *>(
		gamelogic->findObjectByID(reinterpret_cast<int>(msg->m_bfmeKeyTM)));

	if (!actor)
		return;

	BfmeThingTM *thing = actor->m_bfmeThingTM;

	if (thing && thing->m_bfmeInnerTM)
		thing = thing->m_bfmeInnerTM->bfmeResolveTM();

	if (thing->m_bfmeFlagsTM & 0x2000000)
	{
		BfmeActorTM *target = reinterpret_cast<BfmeActorTM *>(
			gamelogic->findObjectByID(reinterpret_cast<int>(actor->m_bfmeOwnerTM)));
		if (!target)
			return;
		if (!target->bfmeCanTM(0x59))
			return;
	}
	else if (!actor->bfmeCanTM(0x59))
		return;

	bfmeSendTM(msg);
}
