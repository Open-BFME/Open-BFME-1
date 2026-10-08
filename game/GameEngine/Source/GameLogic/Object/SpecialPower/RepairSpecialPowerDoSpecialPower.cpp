// RepairSpecialPower::doSpecialPower (0x00264870, slot 11) and
// ::doSpecialPowerAtObject (0x002649F0, slot 12) of the SpecialPowerModuleInterface
// table 0x010B69A0, which the registered RepairSpecialPower constructor 0x002647F0
// stores at +0x10. Each body is reached only through its ILT stub (0x00009BDD,
// 0x0003A814), and each stub's VA appears once in the image.
// Object::doSpecialPower (0x001C3790) and Object::doSpecialPowerAtObject
// (0x001C37F0) call slots 11 and 12. doSpecialPower is empty (`ret 4`).
// Evidence: targets/game/reverse/identity_evidence/specialpower-slot11-12-dospecialpower.md

typedef unsigned int UnsignedInt;

class Object;

// Retail mangles KindOfType unsigned (W4KindOfType); VC7.1 picks the signed
// underlying type only when an enumerator is negative.
enum KindOfType
{
	KINDOF_INVALID = 0
};

#define THING_TU_MEMBERS \
	bool isKindOf( KindOfType kind ) const;
#include "../../../Common/Thing/thing.h"
#undef THING_TU_MEMBERS

class BfmeThingHF;

// Retail ILT 0x000022BB lands on 0x00087A80, matched as
// Overridable::getFinalOverride() const.
class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

typedef Overridable BfmeInnerHF;

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
	unsigned char m_bfmeHeadHF[0x74];
	void *m_bfmeKeyHF;
};

// Retail ILT 0x00029C08 lands on 0x00153D10, matched as
// AICommandInterface::aiRepair(Object *, CommandSourceType).
enum CommandSourceType { CMD_FROM_PLAYER = 0 };

class AICommandInterface
{
public:
	void aiRepair(Object *obj, CommandSourceType cmdSource);
};

typedef AICommandInterface BfmeListHF;

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

// Retail's GameLogic singleton at 0x012F0898; the one canonical spelling.
// Retail ILT 0x0001F253 lands on 0x0009A510, matched as
// GameLogic::findObjectByID(int).
class GameLogic
{
public:
	Object *findObjectByID(int id);
};
extern GameLogic *TheGameLogic;

class RepairSpecialPower
{
public:
	virtual void doSpecialPower(UnsignedInt commandOptions);
	virtual void doSpecialPowerAtObject(Object *obj, UnsignedInt commandOptions);
};

void RepairSpecialPower::doSpecialPower(UnsignedInt)
{
}

void RepairSpecialPower::doSpecialPowerAtObject(Object *obj, UnsignedInt)
{
	BfmeActorHF *actor = (BfmeActorHF *)obj;
	BfmeUnitHF *unit = *(BfmeUnitHF **)((char *)this - 8);
	BfmeThingHF *thing = unit->m_bfmeThingHF;

	if (thing && thing->m_bfmeInnerHF)
		thing = (BfmeThingHF *)thing->m_bfmeInnerHF->getFinalOverride();

	if (thing->m_bfmeFlagsHF & 0x4000)
	{
		if (actor && ((const Thing *)actor)->isKindOf((KindOfType)7))
		{
			BfmeSlotHF *slot = unit->m_bfmeSlotHF;

			if (slot)
				slot->m_bfmeListHF.aiRepair(
					TheGameLogic->findObjectByID((int)actor->m_bfmeKeyHF), CMD_FROM_PLAYER);
		}
	}
}
