// The retail body at 0x002140B0 calls the pinned BfmeOwnerTM sibling
// ?bfmeSendTM@BfmeOwnerTM@@QAEXPAVBfmeMsgTM@@@Z at 0x0003B372.
// The object field chain and the matching thiscall ABI establish this owner.

// stlport
// The lookup below is GameLogic::findObjectByID; GameLogicObjectLookup.h holds
// the declaration (its body stays in Thing/GameLogicFindObjectByID.cpp).
#include "Thing/GameLogicObjectLookup.h"

class BfmeThingTM;

// Retail's override-chain getter (row ?getFinalOverride@Overridable@@QBEPBV1@XZ, 0x00087A80, ILT 0x000022BB).
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;
};

class BfmeInnerTM
{
};

class BfmeThingTM
{
public:
	int m_bfmeSpareTM;
	BfmeInnerTM *m_bfmeInnerTM;
	unsigned char m_bfmeGapTM[0xc0];
	int m_bfmeFlagsTM;
};

// Retail's kind-of test (row ?isKindOf@Thing@@QBE_NW4KindOfType@@@Z, 0x000A2CF0, ILT 0x0003251F).
enum KindOfType { KindOfTypeValue59 = 0x59 };

class Thing
{
public:
	bool isKindOf(KindOfType kind) const;
};

class BfmeActorTM
{
public:

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

// The pinned send is ILT 0x0003B372 (the defined ?j_0003b372 row; body ActiveBody::attemptDamage, 0x00211D40).
extern void j_0003b372();

class BfmeOwnerTM
{
public:
	void bfmeDoTM(BfmeMsgTM *msg);
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
		thing = (BfmeThingTM *)((const Overridable *)thing->m_bfmeInnerTM)->getFinalOverride();

	if (thing->m_bfmeFlagsTM & 0x2000000)
	{
		BfmeActorTM *target = reinterpret_cast<BfmeActorTM *>(
			gamelogic->findObjectByID(reinterpret_cast<int>(actor->m_bfmeOwnerTM)));
		if (!target)
			return;
		if (!((Thing *)target)->isKindOf((KindOfType)0x59))
			return;
	}
	else if (!((Thing *)actor)->isKindOf((KindOfType)0x59))
		return;

	union { void (*raw)(); void (BfmeOwnerTM::*member)(BfmeMsgTM *); } send;
	send.raw = j_0003b372;
	(this->*send.member)(msg);
}
