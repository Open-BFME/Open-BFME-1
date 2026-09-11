// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DBFME_MODULE_NO_MPO

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
// stlport

#include "Precompiled/PreRTS.h"

#include "Common/Player.h"
#include "GameLogic/Module/CollideModule.h"
#include "GameLogic/Object.h"
#include "GameLogic/GameLogic.h"
#include "GameClient/Anim2D.h"
#include "GameClient/InGameUI.h"

// The BFME FXList keeps this object-effect method public and adds an emptiness
// test. The local declaration preserves those names while the upstream header
// supplies the rest of the game-client type.
class FXList
{
public:
	virtual ~FXList();
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary = NULL)
	{
		fx->doFXObj(primary, secondary);
	}
	Bool isEmpty() const;
	void doFXObj(const Object *primary, const Object *secondary) const;
};

// CrateCollideModuleData fields are at these BFME offsets after ModuleData.
struct CrateCollideModuleDataSlice
{
	char m_prefix[8];
	UnsignedByte m_kindof[0x18];
	UnsignedByte m_kindofnot[0x18];
	Bool m_isForbidOwnerPlayer;
	Bool m_isBuildingPickup;
	Bool m_isHumanOnlyPickup;
	char m_padding3b;
	ScienceType m_pickupScience;
	FXList *m_executeFX;
	AsciiString m_executionAnimationTemplate;
	Real m_executeAnimationDisplayTimeInSeconds;
	Real m_executeAnimationZRisePerSecond;
	Bool m_executeAnimationFades;
};

// The official CrateCollide declaration proves the class and its caller-facing
// signature. BFME places executeCrateBehavior at primary vtable slot +0x28 and
// isValidToExecute at +0x2C, so this ABI view dispatches those two slots.
class CrateCollide : public CollideModule
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
	virtual Bool wouldLikeToCollideWith(const Object *other) const;
	virtual Bool isHijackedVehicleCrateCollide() const;
	virtual Bool isSabotageBuildingCrateCollide() const;
	virtual Bool isCarBombCrateCollide() const;
	virtual Bool isRailroad() const;
	virtual Bool isSalvageCrateCollide() const;

protected:
	virtual Bool executeCrateBehavior(Object *other) = 0;
	virtual Bool isValidToExecute(const Object *other) const;

	const CrateCollideModuleDataSlice *getCrateCollideModuleData() const
	{
		return (const CrateCollideModuleDataSlice *)getModuleData();
	}

	Bool m_everExecuted;
};

class CrateDispatch
{
public:
	virtual ~CrateDispatch() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual Bool executeCrateBehavior(Object *other) = 0;
	virtual Bool isValidToExecute(const Object *other) const = 0;
};

struct BfmeAsciiStringData
{
	Int refCount;
	unsigned short length;
};

class BfmeAsciiString
{
public:
	BfmeAsciiStringData *m_data;

	Bool isEmpty() const
	{
		return m_data == 0 || m_data->length == 0;
	}
};

inline Bool bfmeAsciiIsEmpty(const AsciiString *string)
{
	return ((const BfmeAsciiString *)string)->isEmpty();
}

inline Bool bfmeGetDrawIconUI(GameLogic *logic)
{
	return *(const Bool *)((const char *)logic + 0x92);
}

struct BfmeObjectStateView
{
	char m_prefix[0x204];
	const AIUpdateInterface *m_ai;
	char m_padding208[0x344 - 0x208];
	UnsignedByte m_privateStatus;
};

inline const BfmeObjectStateView *bfmeObjectState(const Object *object)
{
	return reinterpret_cast<const BfmeObjectStateView *>(object);
}

struct BfmePlayerView
{
	char m_prefix[0x2c];
	PlayerType m_playerType;
};

// ?onCollide@CrateCollide@@UAEXPAVObject@@PBUCoord3D@@1@Z
void CrateCollide::onCollide(Object *other, const Coord3D *, const Coord3D *)
{
	CrateCollideModuleDataSlice *modData =
		(CrateCollideModuleDataSlice *)getCrateCollideModuleData();
	FXList *executeFX;
	CrateDispatch *dispatch =
		reinterpret_cast<CrateDispatch *>(static_cast<CollideModule *>(this));

	if (dispatch->isValidToExecute(other))
	{
		if (dispatch->executeCrateBehavior(other))
		{
			executeFX = modData->m_executeFX;
			if (executeFX != NULL && executeFX->isEmpty() == FALSE)
			{
				FXList::doFXObj(executeFX, other);
			}

			m_everExecuted = TRUE;
			TheGameLogic->destroyObject(getObject());
		}

		if (TheAnim2DCollection &&
			bfmeAsciiIsEmpty(&modData->m_executionAnimationTemplate) == FALSE &&
			bfmeGetDrawIconUI(TheGameLogic))
		{
			Anim2DTemplate *animTemplate = TheAnim2DCollection->findTemplate(
				modData->m_executionAnimationTemplate);

			TheInGameUI->addWorldAnimation(animTemplate,
				getObject()->getPosition(),
				WORLD_ANIM_FADE_ON_EXPIRE,
				modData->m_executeAnimationDisplayTimeInSeconds,
				modData->m_executeAnimationZRisePerSecond);
		}
	}
}

Bool CrateCollide::isValidToExecute(const Object *other) const
{
	if (other == NULL)
	{
		return FALSE;
	}
	else
	{
		if (m_everExecuted)
			return FALSE;
		if (other->isNeutralControlled())
			return FALSE;

		const CrateCollideModuleDataSlice *modData = getCrateCollideModuleData();
		Bool validBuildingAttempt =
			modData->m_isBuildingPickup && other->isKindOf(KINDOF_STRUCTURE);
		if (bfmeObjectState(other)->m_ai == NULL && !validBuildingAttempt)
			return FALSE;
		if (!other->isKindOfMulti(
			*reinterpret_cast<const KindOfMaskType *>(modData->m_kindof),
			*reinterpret_cast<const KindOfMaskType *>(modData->m_kindofnot)))
			return FALSE;
		if (bfmeObjectState(other)->m_privateStatus & 1)
			return FALSE;
		if (getObject()->isAboveTerrain() && !validBuildingAttempt)
			return FALSE;
		if (modData->m_isForbidOwnerPlayer &&
			getObject()->getControllingPlayer() == other->getControllingPlayer())
			return FALSE;
		if (modData->m_isHumanOnlyPickup && other->getControllingPlayer() != NULL &&
			reinterpret_cast<const BfmePlayerView *>(
				other->getControllingPlayer())->m_playerType != PLAYER_HUMAN)
			return FALSE;
		if (modData->m_pickupScience != SCIENCE_INVALID &&
			other->getControllingPlayer() != NULL &&
			!other->getControllingPlayer()->hasScience(modData->m_pickupScience))
			return FALSE;

		UnsignedByte status = bfmeObjectState(getObject())->m_privateStatus;
		status >>= 1;
		status = ~status;
		status &= 1;
		return status;
	}
}
