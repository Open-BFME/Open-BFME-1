// ?doUpgradesAndSkills@AIPlayer@@MAEXXZ
// partial score=0.25 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "PreRTS.h"
#include "Common/GameMemory.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/PerfTimer.h"
#include "Common/AsciiString.h"
#include "Common/NameKeyGenerator.h"
#include "Common/Science.h"
#include "Common/SpecialPower.h"
#include "Common/Team.h"
#include "Common/ThingFactory.h"
#include "Common/PlayerList.h"
#include "Common/BuildAssistant.h"
#include "Common/ThingTemplate.h"
#include "Common/Upgrade.h"
#include "Common/WellKnownKeys.h"
#include "Common/Xfer.h"
#include "GameClient/ControlBar.h"
#include "GameClient/TerrainVisual.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/SidesList.h"
#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/DozerAIUpdate.h"
#include "GameLogic/Module/UpdateModule.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/Module/RebuildHoleBehavior.h"
#include "GameLogic/Module/SupplyTruckAIUpdate.h"
#include "GameLogic/Module/SupplyWarehouseDockUpdate.h"
#include "GameLogic/PartitionManager.h"

class MemoryPool;

// The BFME Player fields used here are at different offsets from the ZH
// header's facade.  Keep the real value types and the retail field positions.
class Player
{
public:
	NameKeyType getPlayerNameKey() const
	{
		return m_playerNameKey;
	}
	AsciiString getSide() const
	{
		return m_side;
	}
	Int getSciencePurchasePoints() const
	{
		return m_sciencePurchasePoints;
	}
	Bool isCapableOfPurchasingScience(ScienceType) const;
	Bool attemptToPurchaseScience(ScienceType);

private:
	char m_beforeNameKey[0x24];
	NameKeyType m_playerNameKey;
	AsciiString m_side;
	char m_beforeSciencePoints[0x264 - 0x2c];
	Int m_sciencePurchasePoints;
};

// BFME retail layout slice: the complete source body only touches these two
// members, while the vtable call to isSkirmishAI is at slot 11 (+0x2c).
class AIPlayer
{
public:
	enum { INVALID_SKILLSET_SELECTION = -1 };
	virtual MemoryPool *getObjectMemoryPool();
	virtual Bool computeSuperweaponTarget(const SpecialPowerTemplate *, Coord3D *, Int, Real);
	virtual void update();
	virtual void newMap();
	virtual void onUnitProduced(Object *, Object *);
	virtual void onStructureProduced(Object *, Object *);
	virtual void buildSpecificAITeam(TeamPrototype *, Bool);
	virtual void buildAIBaseDefense(Bool);
	virtual void buildAIBaseDefenseStructure(const AsciiString &, Bool);
	virtual void buildSpecificAIBuilding(const AsciiString &);
	virtual void recruitSpecificAITeam(TeamPrototype *, Real);
	virtual Bool isSkirmishAI();

protected:
	virtual void doUpgradesAndSkills();

	char m_beforePlayer[0x08];
	Player *m_player;
	char m_beforeSkillsetSelector[0x20];
	Int m_skillsetSelector;
};

// ?doUpgradesAndSkills@AIPlayer@@MAEXXZ
void AIPlayer::doUpgradesAndSkills(void)
{
	if (TheGameLogic->getFrame() < 2) {
		return;
	}

	Bool checkScience = m_player->getSciencePurchasePoints()>0;
	if (!checkScience) {
		return;
	}
	const AISideInfo *sideInfo = TheAI->getAiData()->m_sideInfo;
	while (sideInfo) {
		if (sideInfo->m_side == m_player->getSide()) {
			break;
		}
		sideInfo = sideInfo->m_next;
	}
	if (sideInfo == NULL) return;

	if (m_skillsetSelector == INVALID_SKILLSET_SELECTION) {
		Int limit = 0;
		if (sideInfo->m_skillSet2.m_numSkills>0) {
			limit = 1;
			if (sideInfo->m_skillSet3.m_numSkills>0) {
				limit = 2;
				if (sideInfo->m_skillSet4.m_numSkills>0) {
					limit = 3;
					if (sideInfo->m_skillSet5.m_numSkills>0) {
						limit = 4;
					}
				}
			}
		}
		if (isSkirmishAI()) {
			m_skillsetSelector = GameLogicRandomValue(0, limit);
		} else {
			m_skillsetSelector = 0;
		}
	}

	if (m_player->getSciencePurchasePoints()>0) {
		const TSkillSet *skillset;
		switch(m_skillsetSelector) {
			default:
			case 0: skillset = &sideInfo->m_skillSet1; break;
			case 1: skillset = &sideInfo->m_skillSet2; break;
			case 2: skillset = &sideInfo->m_skillSet3; break;
			case 3: skillset = &sideInfo->m_skillSet4; break;
			case 4: skillset = &sideInfo->m_skillSet5; break;
		}
		Int i;
		for (i=0; i<skillset->m_numSkills; i++) {
			ScienceType science = skillset->m_skills[i];
			if (m_player->isCapableOfPurchasingScience(science)) {
				if (m_player->attemptToPurchaseScience(science)) {
					AsciiString msg = TheNameKeyGenerator->keyToName(m_player->getPlayerNameKey());
					msg.concat(" purchases from SkillSet");
					msg.concat('1'+m_skillsetSelector);
					msg.concat(' ');
					msg.concat(TheScienceStore->getInternalNameForScience(science));
					msg.concat(".");
					TheScriptEngine->AppendDebugMessage(msg, false);
				}
			}
		}
	}
}
