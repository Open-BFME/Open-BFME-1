// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"
#include "Common/Player.h"
#include "Common/SpecialPower.h"
#include "Common/ThingTemplate.h"
#include "GameClient/InGameUI.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Object.h"

class BfmeSpecialPowerInterface
{
public:
	virtual Bool slot00(const SpecialPowerTemplate *) const = 0;
	virtual Bool slot04() const = 0;
	virtual Bool slot08() const = 0;
	virtual Real slot0c() const = 0;
	virtual UnsignedInt slot10() const = 0;
	virtual AsciiString getPowerName() const = 0;
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const = 0;
};

class BfmeInGameUI
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0a(); virtual void slot0b();
	virtual void slot0c(); virtual void slot0d(); virtual void slot0e(); virtual void slot0f();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1a(); virtual void slot1b();
	virtual void slot1c(); virtual void slot1d(); virtual void slot1e(); virtual void slot1f();
	virtual void slot20();
	virtual void addSuperweapon(Int, const AsciiString &, ObjectID, const SpecialPowerTemplate *);
};

static __forceinline const SpecialPowerTemplate *bfmeFinal(const SpecialPowerTemplate *power)
{
	return (const SpecialPowerTemplate *)power->friend_getFinalOverride();
}

static __forceinline Bool bfmeShared(const SpecialPowerTemplate *power)
{
	return *(const Bool *)((const char *)bfmeFinal(power) + 0x115);
}

static __forceinline Bool bfmePublicTimer(const SpecialPowerTemplate *power)
{
	return *(const Bool *)((const char *)bfmeFinal(power) + 0x114);
}

void SpecialPowerModule::loadPostProcess(void)
{
	BehaviorModule::loadPostProcess();

	if (m_pausedCount == 0)
	{
		BfmeSpecialPowerInterface *power =
			(BfmeSpecialPowerInterface *)((char *)&m_availableOnFrame - sizeof(void *));
		if (bfmeShared(power->getSpecialPowerTemplate()) == TRUE &&
			bfmePublicTimer(power->getSpecialPowerTemplate()) == TRUE &&
			getObject()->getControllingPlayer() &&
			getObject()->isKindOf(KINDOF_STRUCTURE))
		{
			((BfmeInGameUI *)TheInGameUI)->addSuperweapon(
				getObject()->getControllingPlayer()->getPlayerIndex(),
				power->getPowerName(),
				getObject()->getID(),
				getSpecialPowerModuleData()->m_specialPowerTemplate);
		}
	}
}
