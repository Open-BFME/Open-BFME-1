// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define Matrix4x4 Matrix4

#include "PreRTS.h"
#include "Common/GameState.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/RandomValue.h"
#include "Common/Team.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"

#include "GameLogic/AIPathfind.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/GarrisonContain.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Weapon.h"

#include "GameClient/Drawable.h"
#include "GameClient/GameClient.h"
#include "GameClient/InGameUI.h"
#include "GameClient/View.h"

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

class HealContain
{
	protected:
	Bool doHeal( Object *obj, UnsignedInt framesForFullHeal );
};

struct BFMEDamageInfoInput
{
	unsigned char m_unreconstructed_00[8];
	ObjectID m_sourceID;
	unsigned char m_unreconstructed_0c[4];
	DamageType m_damageType;
	unsigned char m_unreconstructed_14[4];
	DeathType m_deathType;
	Real m_amount;
	Bool m_kill;
};

struct BFMEDamageInfo
{
	BFMEDamageInfo();
	BFMEDamageInfoInput in;
	unsigned char m_unreconstructed_24[0x5c - 0x24];
};

struct BFMEBodyHealingShim
{
	virtual void bfmeSlot00() = 0;
	virtual void attemptHealing( BFMEDamageInfo *damageInfo ) = 0;
	virtual void bfmeSlot08() = 0;
	virtual void bfmeSlot0C() = 0;
	virtual void bfmeSlot10() = 0;
	virtual void bfmeSlot14() = 0;
	virtual Real getMaxHealth() const = 0;
};

struct BFMEObjectBodyField
{
	unsigned char m_unreconstructed_000[0x200];
	BFMEBodyHealingShim *m_body;
};

struct BFMEObjectIdentity
{
	unsigned char m_unreconstructed_000[0x74];
	ObjectID m_id;
};

struct BFMEHealContainOwner
{
	unsigned char m_unreconstructed_000[8];
	Object *m_object;
};

// ?doHeal@HealContain@@IAE_NPAVObject@@I@Z
Bool HealContain::doHeal( Object *obj, UnsignedInt framesForFullHeal )
{
	Bool doneHealing = FALSE;
	BFMEDamageInfo healInfo;
	healInfo.in.m_damageType = (DamageType)7;
	healInfo.in.m_deathType = DEATH_NONE;
	healInfo.in.m_sourceID = reinterpret_cast<BFMEObjectIdentity *>(
		reinterpret_cast<BFMEHealContainOwner *>(this)->m_object)->m_id;

	BFMEBodyHealingShim *body = reinterpret_cast<BFMEObjectBodyField *>(obj)->m_body;
	if( TheGameLogic->getFrame() -
		*reinterpret_cast<UnsignedInt *>(reinterpret_cast<char *>(obj) + 0x21c) >= framesForFullHeal )
	{
		healInfo.in.m_amount = body->getMaxHealth();
		body->attemptHealing( &healInfo );
		doneHealing = TRUE;
	}
	else
	{
		healInfo.in.m_amount = body->getMaxHealth() / (Real)framesForFullHeal;
		body->attemptHealing( &healInfo );
	}

	return doneHealing;
}
