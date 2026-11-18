// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?canAffordUpgrade@UpgradeCenter@@QBE_NPAVPlayer@@PBVUpgradeTemplate@@PBVThingTemplate@@_N@Z: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/System/Upgrade.cpp
//
// UpgradeCenter::canAffordUpgrade, 0x0010AF70, 86 bytes (ret 0x10). Zero
// Hour's body: a null check, the player's money against the upgrade's cost,
// and the "GUI:NotEnoughMoneyToUpgrade" message through TheInGameUI's
// variadic message(AsciiString, ...) at vtable +0x30.
//
// BFME differences: a third argument, the ThingTemplate the upgrade is bought
// for, is passed to the two-argument calcCostToBuild (0x0010A850, ILT
// 0x0003F8D7). tools/ilt_oracle.py confirms this decoration at 0x0010AF70,
// and the matched AIPlayer::buildUpgrade calls it as
// (player, upgrade, NULL, false).
//
// Layout: Player money count +0x4C.

#include "ascii_string.h"

#include "../../../Include/Common/ScalarTypes.h"



#define NULL 0
#define TRUE true
#define FALSE false

class ThingTemplate;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Money.h
class Money
{
public:
	UnsignedInt countMoney() const { return m_money; }
private:
	UnsignedInt m_money;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Money *getMoney() { return &m_money; }
private:
	char m_unmodelled000[0x4c];
	Money m_money;							// +0x4C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	Int calcCostToBuild(Player *player, const ThingTemplate *thing) const;
};

#define BFME_UI_SLOT(n) virtual void bfmeUISlot##n() = 0;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	BFME_UI_SLOT(0) BFME_UI_SLOT(1) BFME_UI_SLOT(2) BFME_UI_SLOT(3)
	BFME_UI_SLOT(4) BFME_UI_SLOT(5) BFME_UI_SLOT(6) BFME_UI_SLOT(7)
	BFME_UI_SLOT(8) BFME_UI_SLOT(9) BFME_UI_SLOT(10) BFME_UI_SLOT(11)
	virtual void message( AsciiString stringManagerLabel, ... ) = 0;	///< vtable +0x30
};

#undef BFME_UI_SLOT

extern InGameUI *TheInGameUI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeCenter
{
public:
	Bool canAffordUpgrade( Player *player, const UpgradeTemplate *upgradeTemplate,
		const ThingTemplate *thing, Bool displayReason ) const;
};

Bool UpgradeCenter::canAffordUpgrade( Player *player, const UpgradeTemplate *upgradeTemplate,
	const ThingTemplate *thing, Bool displayReason ) const
{

	// sanity
	if( player == NULL || upgradeTemplate == NULL )
		return FALSE;

	// money check
	Money *money = player->getMoney();
	if( money->countMoney() < upgradeTemplate->calcCostToBuild( player, thing ) )
	{
		//Post reason why we can't make upgrade!
		if( displayReason )
		{
			TheInGameUI->message( "GUI:NotEnoughMoneyToUpgrade" );
		}
		return FALSE;
	}

	/// @todo maybe have prereq checks for upgrades???

	return TRUE;  // all is well

}  // end canAffordUpgrade
