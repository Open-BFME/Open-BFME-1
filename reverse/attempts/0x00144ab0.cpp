// ?calcTimeToBuild@ThingTemplate@@QBEHPBVPlayer@@@Z
// partial score=0.58 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/ini_bfme /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Address-derived ABI carrier for the BFME ThingTemplate build-time body at
// 0x00144AB0.  Retail consumes (Player *, Int override) and returns with ret 8;
// the existing source declaration/callers expose only the semantic method name.

#include "PreRTS.h"
#include "Common/GameCommon.h"
#include "Common/GlobalData.h"
#include "Common/Player.h"
#include "Common/ThingTemplate.h"

class BFMEThingTemplateAccess : public ThingTemplate
{
public:
	Real buildTime() const { return getBuildTime(); }
};

class BFMECalcTimeToBuildCarrier
{
public:
	Int calc(const Player *player, Int overrideTime);
};

Int BFMECalcTimeToBuildCarrier::calc(const Player *player, Int overrideTime)
{
	ThingTemplate *self = (ThingTemplate *)this;
	Real buildTime;
	if (overrideTime == -1)
		buildTime = ((const BFMEThingTemplateAccess *)self)->buildTime();
	else
		buildTime = overrideTime;

	buildTime *= player->getHandicap()->getHandicap(Handicap::BUILDTIME, self);

	const AsciiString &name =
		*(const AsciiString *)((const char *)self + 0x20);
	Real factionModifier = 1 + player->getProductionTimeChangePercent(name);
	buildTime *= factionModifier;

	Real energyPercent = player->getEnergy()->getEnergySupplyRatio();
	if (energyPercent > 1.0f)
		energyPercent = 1.0f;
	Real energyShort = 1.0f - energyPercent;
	energyShort *= TheGlobalData->m_LowEnergyPenaltyModifier;
	Real penaltyRate = 1.0f - energyShort;
	penaltyRate = max(penaltyRate, TheGlobalData->m_MinLowEnergyProductionSpeed);
	if (energyPercent < 1.0f)
		penaltyRate = min(penaltyRate, TheGlobalData->m_MaxLowEnergyProductionSpeed);
	if (penaltyRate <= 0.0f)
		penaltyRate = 0.01f;
	buildTime /= penaltyRate;

	if (*(const unsigned char *)((const char *)self + 0x493) == 1)
	{
		const ThingTemplate *facility = self->getBuildFacilityTemplate(player);
		Int count = 0;
		if (facility)
		{
			player->countObjectsByThingTemplate(1, &facility, false, &count);
			Real factoryMultiplier = TheGlobalData->m_MultipleFactory;
			if (factoryMultiplier > 0.0f)
			{
				for (Int i = 0; i < count - 1; ++i)
					buildTime *= factoryMultiplier;
			}
		}
	}

	return buildTime;
}
