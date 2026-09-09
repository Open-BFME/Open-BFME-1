// ?localApplyBattlePlanBonusesToObject@@YAXPAVObject@@PAX@Z
// partial score=0.78 date=2026-09-09
// cl: /DNDEBUG /DRELEASE_DEBUG_LOGGING /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"

#include "Common/KindOf.h"
#include "Common/Player.h"
#include "Common/CRCDebug.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Weapon.h"

extern GameLogic *TheBfmeGameLogic;

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed_008[0xC8 - sizeof(Overridable)];
	unsigned int m_kindOf;
};

struct BfmeKindOfMask
{
	UnsignedInt m_bits[6];
};

struct BattlePlanBonuses
{
	Real m_armorScalar;
	Int m_bombardment;
	Int m_searchAndDestroy;
	Int m_holdTheLine;
	Real m_sightRangeScalar;
	BfmeKindOfMask m_validKindOf;
	BfmeKindOfMask m_invalidKindOf;
};

static void localApplyBattlePlanBonusesToObject(Object *obj, void *userData)
{
	const BattlePlanBonuses *bonus = (const BattlePlanBonuses *)userData;
	Object *objectToValidate = obj;
	Object *objectToModify = obj;

	ThingTemplate *thing = *(ThingTemplate **)((unsigned char *)obj + 0x04);
	Overridable *nextOverride = thing ? *(Overridable **)((unsigned char *)thing + 0x04) : NULL;
	if (thing && nextOverride)
		thing = (ThingTemplate *)nextOverride->getFinalOverride();
	// BFME's retail kind-of numbering puts projectile at bit 25; the shared
	// Zero Hour enum is not the retail numbering at this point.
	Bool isProjectile = (thing->m_kindOf & 0x02000000) != 0;
	if (isProjectile)
		objectToValidate = TheBfmeGameLogic->findObjectByID(*(ObjectID *)((unsigned char *)obj + 0x78));

	if (objectToValidate && objectToValidate->isAnyKindOf(
		*(const KindOfMaskType *)((const unsigned char *)bonus + 0x14)))
	{
		if (!objectToValidate->isAnyKindOf(
			*(const KindOfMaskType *)((const unsigned char *)bonus + 0x2c)))
		{
			if (!isProjectile)
			{
				if (bonus->m_armorScalar != 1.0f)
				{
					BodyModuleInterface *body = *(BodyModuleInterface **)((unsigned char *)objectToModify + 0x200);
					body->applyDamageScalar(bonus->m_armorScalar);
				}

				if (bonus->m_sightRangeScalar != 1.0f)
				{
					objectToModify->setVisionRange(obj->getVisionRange() * bonus->m_sightRangeScalar);
					objectToModify->setShroudClearingRange(obj->getShroudClearingRange() * bonus->m_sightRangeScalar);
				}
			}

			volatile UnsignedInt *conditionFlags =
				(volatile UnsignedInt *)((unsigned char *)objectToModify + 0x2a0);
			UnsignedInt flags = *conditionFlags;
			if (bonus->m_bombardment > 0)
				flags |= (1u << WEAPONBONUSCONDITION_BATTLEPLAN_BOMBARDMENT);
			else
				flags &= ~(1u << WEAPONBONUSCONDITION_BATTLEPLAN_BOMBARDMENT);
			*conditionFlags = flags;

			flags = *conditionFlags;
			if (bonus->m_holdTheLine > 0)
				flags |= (1u << WEAPONBONUSCONDITION_BATTLEPLAN_HOLDTHELINE);
			else
				flags &= ~(1u << WEAPONBONUSCONDITION_BATTLEPLAN_HOLDTHELINE);
			*conditionFlags = flags;

			flags = *conditionFlags;
			if (bonus->m_searchAndDestroy > 0)
				flags |= (1u << WEAPONBONUSCONDITION_BATTLEPLAN_SEARCHANDDESTROY);
			else
				flags &= ~(1u << WEAPONBONUSCONDITION_BATTLEPLAN_SEARCHANDDESTROY);
			*conditionFlags = flags;
		}
	}
}

static void (*volatile keepLocalApplyBattlePlanBonusesToObject)(Object *, void *) =
	&localApplyBattlePlanBonusesToObject;
