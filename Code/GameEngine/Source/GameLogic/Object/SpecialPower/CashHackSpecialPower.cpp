// cl: /DNDEBUG /DWIN32 /D_WINDOWS /DBFME_MODULE_NO_MPO /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: CashHackSpecialPower.cpp /////////////////////////////////////////////////////////////
// Author: Amit Kumar, July 2002
// Desc:   The Cash Hack will steal money from an enemy player
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Player.h"
#include "Common/Team.h"
#include "Common/Xfer.h"
#include "GameClient/GameText.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/CashHackSpecialPower.h"
#include "GameClient/InGameUI.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/AI/CashHackSpecialPowerModuleDataCtorThunk.cpp
// ??0CashHackSpecialPowerModuleData@@QAE@XZ present-unmatched
CashHackSpecialPowerModuleData::CashHackSpecialPowerModuleData( void )
{
	m_upgrades.clear();
	m_defaultAmountToSteal = 0;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
static void parseCashHackUpgradePair( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	CashHackSpecialPowerModuleData::Upgrades up;

	INI::parseScience(ini, NULL, &up.m_science, NULL);
	INI::parseInt(ini, NULL, &up.m_amountToSteal, NULL);

	std::vector<CashHackSpecialPowerModuleData::Upgrades>* s = (std::vector<CashHackSpecialPowerModuleData::Upgrades>*)store;
	s->push_back(up);
} 

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/*static*/ void CashHackSpecialPowerModuleData::buildFieldParse(MultiIniFieldParse& p)
{
	SpecialPowerModuleData::buildFieldParse( p );
	
	static const FieldParse dataFieldParse[] = 
	{
		{ "UpgradeMoneyAmount", parseCashHackUpgradePair, NULL, offsetof( CashHackSpecialPowerModuleData, m_upgrades ) },
		{ "MoneyAmount", INI::parseInt, NULL, offsetof( CashHackSpecialPowerModuleData, m_defaultAmountToSteal ) },
		{ 0, 0, 0, 0 }
	};
	p.add(dataFieldParse);
	
}  // end buildFieldParse

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// The module hierarchy needs BFME_MODULE_NO_MPO on this file's own cl line:
// retail's Module has no MemoryPoolObject base, so BehaviorModule spans 0x0C
// and this constructor's second vtable store lands at +0x0C, where the wider
// layout puts a fourth vptr at +0x04 and +0x14 and shifts everything.
CashHackSpecialPower::CashHackSpecialPower( Thing *thing, const ModuleData *moduleData )
												: SpecialPowerModule( thing, moduleData )
{

}  // end CashHackSpecialPower

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??1CashHackSpecialPower@@MAE@XZ present-unmatched
CashHackSpecialPower::~CashHackSpecialPower( void )
{

}  // end ~CashHackSpecialPower

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void CashHackSpecialPower::doSpecialPowerAtLocation( const Coord3D *loc, Real angle, UnsignedInt commandOptions )
{
	if (getObject()->isDisabled())
		return;

	// only allowed at objects
	return;
}  

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?findAmountToSteal@CashHackSpecialPower@@IBEHXZ is emitted by
// CashHackSpecialPowerFindAmountToStealThunk.cpp.

typedef std::vector<CashHackSpecialPowerModuleData::Upgrades> CashHackUpgradesVector;
typedef CashHackUpgradesVector::iterator (CashHackUpgradesVector::*CashHackBegin)();
typedef CashHackUpgradesVector::const_iterator (CashHackUpgradesVector::*CashHackConstBegin)() const;
static volatile CashHackBegin cashHackBeginAnchor = &CashHackUpgradesVector::begin;
static volatile CashHackConstBegin cashHackConstBeginAnchor = &CashHackUpgradesVector::begin;

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/CashHackSpecialPower_doSpecialPowerAtObject_Thunk.cpp
// ?doSpecialPowerAtObject@CashHackSpecialPower@@UAEXPAVObject@@I@Z present-unmatched
void CashHackSpecialPower::doSpecialPowerAtObject( Object *victim, UnsignedInt commandOptions )
{
	if (getObject()->isDisabled())
		return;

	// sanity
	if (!victim)
		return;

	// call the base class action cause we are *EXTENDING* functionality
  SpecialPowerModule::doSpecialPowerAtObject( victim, commandOptions );

	// get our module data
	Object *self = getObject();

	//Steal a thousand cash from the other team!
	Money *targetMoney = victim->getControllingPlayer()->getMoney();
	Money *selfMoney = self->getControllingPlayer()->getMoney();
	if( targetMoney && selfMoney )
	{
		UnsignedInt cash = targetMoney->countMoney();
		UnsignedInt desiredAmount = findAmountToSteal();
		//Check to see if they have 1000 cash, otherwise, take the remainder!
		cash = min( desiredAmount, cash );
		if( cash > 0 )
		{
			//Steal the cash
			targetMoney->withdraw( cash );
			selfMoney->deposit( cash );
			self->getControllingPlayer()->getScoreKeeper()->addMoneyEarned( cash );

			//Display cash income floating over the blacklotus
			UnicodeString moneyString;
			moneyString.format( TheGameText->fetch( "GUI:AddCash" ), cash );
			Coord3D pos;
			pos.zero();
			pos.add( self->getPosition() );
			pos.z += 20.0f; //add a little z to make it show up above the unit.
			TheInGameUI->addFloatingText( moneyString, &pos, GameMakeColor( 0, 255, 0, 255 ) );
		
			//Display cash lost floating over the target
			moneyString.format( TheGameText->fetch( "GUI:LoseCash" ), cash );
			pos.zero();
			pos.add( victim->getPosition() );
			pos.z += 30.0f; //add a little z to make it show up above the unit.
			TheInGameUI->addFloatingText( moneyString, &pos, GameMakeColor( 255, 0, 0, 255 ) );
		}
	}

}  

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@CashHackSpecialPower@@MAEXPAVXfer@@@Z present-unmatched
void CashHackSpecialPower::crc( Xfer *xfer )
{

	// extend base class
	SpecialPowerModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@CashHackSpecialPower@@MAEXPAVXfer@@@Z present-unmatched
void CashHackSpecialPower::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	SpecialPowerModule::xfer( xfer );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@CashHackSpecialPower@@MAEXXZ present-unmatched
void CashHackSpecialPower::loadPostProcess( void )
{

	// extend base class
	SpecialPowerModule::loadPostProcess();

}  // end loadPostProcess
