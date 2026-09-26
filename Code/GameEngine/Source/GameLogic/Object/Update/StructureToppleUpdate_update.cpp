// cl: /ICode/GameEngine/Include /DNDEBUG /MD /EHsc /Ireference/shims/asciistring_copyctor_outofline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /ICode/GameEngine/Source/Common/System /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#include "PreRTS.h"
#include "Common/BitFlags.h"
#include "Common/RandomValue.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/StructureToppleUpdate.h"
#include "GameLogic/Object.h"

class FXList
{
public:
	Bool bfmeIsBlocked() const;
	void doFXObj(const Object *, const Object *) const;
};

class Rva00132200Target
{
public:
	void rva00132200(const Matrix3D *);
};

struct BfmeStructureToppleModuleDataView
{
	unsigned char padding[0x34];
	Int minToppleDelay;
	Int maxToppleDelay;
	Real structuralIntegrity;
	Real structuralDecay;
	Real bfmeUnknown44;
	UnsignedInt damageFXTypes;
	FXList *toppleStartFXList;
	FXList *toppleDelayFXList;
	FXList *toppleFXList;
	FXList *toppleDoneFXList;
	FXList *crushingFXList;
	unsigned char padding60[4];
	Int minToppleBurstDelay;
	Int maxToppleBurstDelay;
	unsigned char padding6c[0x48];
	Real toppleAngle;
};

class BfmeStructureToppleBodyModuleView
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void updateBodyParticleSystems();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual const DamageInfo *getLastDamageInfo() const;
};

class BfmeStructureToppleBodyObjectView
{
public:
	unsigned char padding[0x200];
	BfmeStructureToppleBodyModuleView *bodyModule;

	BfmeStructureToppleBodyModuleView *getBodyModule() const
	{
		return bodyModule;
	}
};

struct BfmeStructureToppleLastDamageInfoView
{
	unsigned char padding[0x10];
	Int damageType;
};

class BfmeObjectModelCondition
{
	public:
	void notifyModelConditionChanged();
};

#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@BfmeObjectModelCondition@@QAEXXZ=?j_0002191d@@YAXXZ")

static __forceinline Bool bfmeStructureToppleDamageTypeFlag(Int damageType, UnsignedInt flags)
{
	return (flags & (1u << (damageType - 1))) != 0;
}

// The constructor at 0x002AF1E0 installs vtable 0x010C4924.
// Slot 0 reaches this body through ILT 0x00016FA4.
UpdateSleepTime StructureToppleUpdate::update( void )
{
	const BfmeStructureToppleModuleDataView *moduleData =
		(const BfmeStructureToppleModuleDataView *)getStructureToppleUpdateModuleData();

	if (m_toppleState == TOPPLESTATE_STANDING)
		return UPDATE_SLEEP_FOREVER;

	const BfmeStructureToppleBodyObjectView *objectView =
		(const BfmeStructureToppleBodyObjectView *)getObject();
	const DamageInfo *lastDamageInfo = objectView->getBodyModule()->getLastDamageInfo();

	if (m_toppleState == TOPPLESTATE_WAITINGFORTOPPLESTART) {
		UnsignedInt currentFrame = TheGameLogic->getFrame();
		if (currentFrame >= m_nextBurstFrame) {
			doToppleDelayBurstFX();
			#line 230 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\StructureToppleUpdate.cpp"
			m_nextBurstFrame = currentFrame + GameLogicRandomValue(moduleData->minToppleBurstDelay, moduleData->maxToppleBurstDelay);
		}
		if (currentFrame >= m_toppleFrame) {
			m_toppleState = TOPPLESTATE_TOPPLING;
			m_structuralIntegrity = moduleData->structuralIntegrity;
		}
	}

	if (m_toppleState == TOPPLESTATE_TOPPLING) {
		UnsignedInt currentFrame = TheGameLogic->getFrame();
		Real toppleAcceleration =
			(Sin(m_accumulatedAngle) * (1.0 - m_structuralIntegrity)) * moduleData->bfmeUnknown44;
		m_toppleVelocity += toppleAcceleration;

		if (m_structuralIntegrity > 0.0f) {
			m_structuralIntegrity *= moduleData->structuralDecay;
			if (m_structuralIntegrity < 0.0f)
				m_structuralIntegrity = 0.0f;
		}

		doAngleFX(m_accumulatedAngle, m_accumulatedAngle + m_toppleVelocity);

		m_accumulatedAngle += m_toppleVelocity;

		applyCrushingDamage(PI/2 - m_accumulatedAngle);

		if (m_accumulatedAngle >= PI/2) {
			m_toppleVelocity -= m_accumulatedAngle - PI/2;
			m_accumulatedAngle = PI/2;
			m_toppleState = TOPPLESTATE_WAITINGFORDONE;

			applyCrushingDamage(0.0f);
			doPhaseStuff(STPHASE_FINAL, getObject()->getPosition());

			if (lastDamageInfo == NULL || bfmeStructureToppleDamageTypeFlag(
				((const BfmeStructureToppleLastDamageInfoView *)lastDamageInfo)->damageType,
				moduleData->damageFXTypes))
			{
				Object *building = getObject();
				FXList *toppleDoneFX = moduleData->toppleDoneFXList;
				if (toppleDoneFX != NULL && !toppleDoneFX->bfmeIsBlocked())
					toppleDoneFX->doFXObj(building, NULL);
			}

			m_toppleFrame = TheGameLogic->getFrame();
		}

		if (currentFrame >= m_nextBurstFrame) {
			doToppleDelayBurstFX();
			#line 279 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\StructureToppleUpdate.cpp"
			m_nextBurstFrame = currentFrame + GameLogicRandomValue(moduleData->minToppleBurstDelay, moduleData->maxToppleBurstDelay);
		}

		Object *building = getObject();
		Matrix3D buildingTransform = *building->getTransformMatrix();
		buildingTransform.In_Place_Pre_Rotate_X(-m_toppleVelocity * m_toppleDirection.y);
		buildingTransform.In_Place_Pre_Rotate_Y(m_toppleVelocity * m_toppleDirection.x);
		((Rva00132200Target *)building)->rva00132200(&buildingTransform);
	}

	if (m_toppleState == TOPPLESTATE_WAITINGFORDONE)
	{
		if (m_toppleFrame <= TheGameLogic->getFrame())
		{
			Object *building = getObject();
			UnsignedInt *conditionFlags = (UnsignedInt *)((char *)building + 0x110);
			if (*((unsigned char *)conditionFlags) & 0x20) {
				conditionFlags[0] &= ~0x20;
				((BfmeObjectModelCondition *)building)->
					notifyModelConditionChanged();
			}
			{
				BitFlags<320> *modelConditions =
					(BitFlags<320> *)((char *)building + 0x110);
				if (!modelConditions->test(59)) {
					modelConditions->set(59);
					((BfmeObjectModelCondition *)building)->
						notifyModelConditionChanged();
				}
			}

			BfmeStructureToppleBodyModuleView *bodyModule =
				((BfmeStructureToppleBodyObjectView *)building)->getBodyModule();
			bodyModule->updateBodyParticleSystems();

			doToppleDoneStuff();

			m_toppleState = TOPPLESTATE_DONE;

			return UPDATE_SLEEP_FOREVER;
		}
	}

	return UPDATE_SLEEP_NONE;
}
