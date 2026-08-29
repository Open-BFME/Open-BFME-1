// cl: /DNDEBUG /MD /EHsc /Ireference/shims/asciistring8 /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
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

// FILE: Upgrade.cpp //////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, March 2002
// Desc:   Upgrade system for players
///////////////////////////////////////////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_VETERANCY_NAMES
#include "Common/Upgrade.h"
#include "Common/Player.h"
#include "Common/Xfer.h"
#include "GameClient/InGameUI.h"
#include "GameClient/Image.h"


const char *TheUpgradeTypeNames[] = 
{
	"PLAYER",
	"OBJECT",
	NULL
};

// PUBLIC /////////////////////////////////////////////////////////////////////////////////////////
class UpgradeCenter *TheUpgradeCenter = NULL;

///////////////////////////////////////////////////////////////////////////////////////////////////
// UPGRADE ////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0Upgrade@@QAE@PBVUpgradeTemplate@@@Z present-unmatched
Upgrade::Upgrade( const UpgradeTemplate *upgradeTemplate )
{

	m_template = upgradeTemplate;
	m_status = UPGRADE_STATUS_INVALID;
	m_next = NULL;
	m_prev = NULL;

}  // end Upgrade

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
Upgrade::~Upgrade( void )
{

}  // end ~Upgrade

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@Upgrade@@MAEXPAVXfer@@@Z present-unmatched
void Upgrade::crc( Xfer *xfer )
{

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@Upgrade@@MAEXPAVXfer@@@Z present-unmatched
void Upgrade::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// status
	xfer->xferUser( &m_status, sizeof( UpgradeStatusType ) );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/Upgrade_loadPostProcessMethodThunk.cpp
// ?loadPostProcess@Upgrade@@MAEXXZ present-unmatched
void Upgrade::loadPostProcess( void )
{

}  // end loadPostProcess

///////////////////////////////////////////////////////////////////////////////////////////////////
// UPGRADE TEMPLATE ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
const FieldParse UpgradeTemplate::m_upgradeFieldParseTable[] = 
{

	{ "DisplayName",				INI::parseAsciiString,		NULL, offsetof( UpgradeTemplate, m_displayNameLabel ) },
	{ "Type",								INI::parseIndexList,			TheUpgradeTypeNames, offsetof( UpgradeTemplate, m_type ) },
	{ "BuildTime",					INI::parseReal,						NULL, offsetof( UpgradeTemplate, m_buildTime ) },
	{ "BuildCost",					INI::parseInt,						NULL, offsetof( UpgradeTemplate, m_cost ) },
	{ "ButtonImage",				INI::parseAsciiString,		NULL, offsetof( UpgradeTemplate, m_buttonImageName ) },
	{ "ResearchSound",			INI::parseAudioEventRTS,	NULL, offsetof( UpgradeTemplate, m_researchSound ) }, 
	{ "UnitSpecificSound",	INI::parseAudioEventRTS,	NULL, offsetof( UpgradeTemplate, m_unitSpecificSound ) }, 
	{ "AcademyClassify",		INI::parseIndexList,			TheAcademyClassificationTypeNames, offsetof( UpgradeTemplate, m_academyClassificationType ) },
	{ NULL,						NULL,												 NULL, 0 }  // keep this last

};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0UpgradeTemplate@@QAE@XZ present-unmatched
UpgradeTemplate::UpgradeTemplate( void )
{
	//Added By Sadullah Nader
	//Initialization(s) inserted
	m_cost = 0;
	//
	m_type = UPGRADE_TYPE_PLAYER;
	m_nameKey = NAMEKEY_INVALID;
	m_buildTime = 0.0f;
	m_next = NULL;
	m_prev = NULL;
	m_buttonImage = NULL;
	m_academyClassificationType = ACT_NONE;

}  // end UpgradeTemplate

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/UpgradeTemplateDestructorThunk.cpp
// ??1UpgradeTemplate@@MAE@XZ present-unmatched
UpgradeTemplate::~UpgradeTemplate( void )
{

}  // end ~UpgradeTemplate

//-------------------------------------------------------------------------------------------------
/** Calculate the time it takes (in logic frames) for a player to build this UpgradeTemplate */
//-------------------------------------------------------------------------------------------------
// ?calcTimeToBuild@UpgradeTemplate@@QBEHPAVPlayer@@@Z present-unmatched
Int UpgradeTemplate::calcTimeToBuild( Player *player ) const
{
#if defined(_DEBUG) || defined(_INTERNAL) || defined(_ALLOW_DEBUG_CHEATS_IN_RELEASE)
	if( player->buildsInstantly() )
	{
		return 1;
	}
#endif

	///@todo modify this by power state of player
	return m_buildTime * LOGICFRAMES_PER_SECOND;

}  // end calcTimeToBuild

//-------------------------------------------------------------------------------------------------
/** Calculate the cost takes this player to build this upgrade */
//-------------------------------------------------------------------------------------------------
// ?calcCostToBuild@UpgradeTemplate@@QBEHPAVPlayer@@@Z present-unmatched
Int UpgradeTemplate::calcCostToBuild( Player *player ) const
{

	///@todo modify this by any player handicaps
	return m_cost;

}  // end calcCostToBuild

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
static AsciiString getVetUpgradeName(VeterancyLevel v)
{
	AsciiString tmp;
	tmp = "Upgrade_Veterancy_";
	tmp.concat(TheVeterancyNames[v]);
	return tmp;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?friend_makeVeterancyUpgrade@UpgradeTemplate@@QAEXW4VeterancyLevel@@@Z
// Body in Upgrade_friend_makeVeterancyUpgrade.asm (exact 156B retail @ 0x10B010;
// queue 0x79CE61 was unrelated SEH epilogue+int3).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?cacheButtonImage@UpgradeTemplate@@QAEXXZ present-unmatched
void UpgradeTemplate::cacheButtonImage()
{
	if( m_buttonImageName.isNotEmpty() )
	{
		m_buttonImage = TheMappedImageCollection->findImageByName( m_buttonImageName );
		DEBUG_ASSERTCRASH( m_buttonImage, ("UpgradeTemplate: %s is looking for button image %s but can't find it. Skipping...", m_name.str(), m_buttonImageName.str() ) );
		m_buttonImageName.clear();	// we're done with this, so nuke it
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// UPGRADE CENTER /////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
UpgradeCenter::UpgradeCenter( void )
{

	m_upgradeList = NULL;
	m_nextTemplateMaskBit = 0;
	buttonImagesCached = FALSE;

}  // end UpgradeCenter

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
UpgradeCenter::~UpgradeCenter( void )
{
	
	// delete all the upgrades loaded from the INI database
	UpgradeTemplate *next;
	while( m_upgradeList )
	{

		// get next
		next = m_upgradeList->friend_getNext();

		// delete head of list
		m_upgradeList->deleteInstance();

		// set head to next element
		m_upgradeList = next;

	}  // end while

}  // end ~UpgradeCenter

//-------------------------------------------------------------------------------------------------
/** Upgrade center initialization */
//-------------------------------------------------------------------------------------------------
// What tools/locate.py says about this file, run at --min-size 24 and again at
// 14: two functions placed uniquely (both deleting destructors, now claimed) and
// everything else came back "unlocated -- drifted or not in this binary". That
// verdict is worth more than it looks. locate.py masks relocations before
// scanning, so unlocated does not mean the address is unknown; it means these
// compiled bodies do not appear ANYWHERE in .text. Zero Hour's UpgradeCenter is
// not BFME's, and each of these needs reconstructing rather than placing.
//
// Do not try to pair them off by size. reset compiles to 138 bytes and there is
// an unclaimed 133-byte body two functions along at 0x0010B550; they share
// nothing -- 114 of 133 bytes differ, starting at the prologue. Size proximity
// in a dense region is coincidence, and the ledger has enough rows placed that
// way already.
//
// ?init@UpgradeCenter@@UAEXXZ present-unmatched
void UpgradeCenter::init( void )
{
	UpgradeTemplate* up;
	
	// name will be overridden by friend_makeVeterancyUpgrade

// no, there ISN'T an upgrade for this one...
//up = newUpgrade("");
//up->friend_makeVeterancyUpgrade(LEVEL_REGULAR);

	up = newUpgrade("");
	up->friend_makeVeterancyUpgrade(LEVEL_VETERAN);

	up = newUpgrade("");
	up->friend_makeVeterancyUpgrade(LEVEL_ELITE);

	up = newUpgrade("");
	up->friend_makeVeterancyUpgrade(LEVEL_HEROIC);

}

//-------------------------------------------------------------------------------------------------
/** Upgrade center system reset */
//-------------------------------------------------------------------------------------------------
// ?reset@UpgradeCenter@@UAEXXZ present-unmatched
void UpgradeCenter::reset( void )
{
	if( TheMappedImageCollection && !buttonImagesCached )
	{
		UpgradeTemplate *upgrade;
		for( upgrade = m_upgradeList; upgrade; upgrade = upgrade->friend_getNext() )
		{
			upgrade->cacheButtonImage();
		}
		buttonImagesCached = TRUE;
	}
}

//-------------------------------------------------------------------------------------------------
/** Find upgrade matching name key */
//-------------------------------------------------------------------------------------------------
// ?findVeterancyUpgrade@UpgradeCenter@@QBEPBVUpgradeTemplate@@W4VeterancyLevel@@@Z
// Body in Upgrade_findVeterancyUpgrade.asm (exact 101B retail @ 0x10B480;
// queue 0x60810D was unrelated bitset loop body).


//-------------------------------------------------------------------------------------------------
/** Find upgrade matching name key */
//-------------------------------------------------------------------------------------------------
// ?findNonConstUpgradeByKey@UpgradeCenter@@IAEPAVUpgradeTemplate@@W4NameKeyType@@@Z present-unmatched
UpgradeTemplate *UpgradeCenter::findNonConstUpgradeByKey( NameKeyType key )
{
	UpgradeTemplate *upgrade;

	// search list
	for( upgrade = m_upgradeList; upgrade; upgrade = upgrade->friend_getNext() )
		if( upgrade->getUpgradeNameKey() == key )
			return upgrade;

	// item not found
	return NULL;

}

// ------------------------------------------------------------------------------------------------
/** Return the first upgrade template */
// ------------------------------------------------------------------------------------------------
// ?firstUpgradeTemplate@UpgradeCenter@@QAEPAVUpgradeTemplate@@XZ present-unmatched
UpgradeTemplate *UpgradeCenter::firstUpgradeTemplate( void )
{
	
	return m_upgradeList;

}  // end firstUpgradeTemplate

//-------------------------------------------------------------------------------------------------
/** Find upgrade matching name key */
//-------------------------------------------------------------------------------------------------
// The link to the next template is at UpgradeTemplate+0x108, not the vendored
// +0xF8. The name key at +0x0C and the list head at UpgradeCenter+0x08 are both
// already right, and this walk is what retail inlines into findUpgrade below.
struct BfmeUpgradeTemplateLink
{
	unsigned char m_unreconstructed_000[ 0x108 ];
	const UpgradeTemplate *m_next;				///< retail this+0x108
};

// ?findUpgradeByKey@UpgradeCenter@@QBEPBVUpgradeTemplate@@W4NameKeyType@@@Z present-unmatched
const UpgradeTemplate *UpgradeCenter::findUpgradeByKey( NameKeyType key ) const
{
	const UpgradeTemplate *upgrade;

	// search list
	for( upgrade = m_upgradeList; upgrade; upgrade = ((const BfmeUpgradeTemplateLink *)upgrade)->m_next )
		if( upgrade->getUpgradeNameKey() == key )
			return upgrade;

	// item not found
	return NULL;
}

//-------------------------------------------------------------------------------------------------
/** Find upgrade matching name */
//-------------------------------------------------------------------------------------------------
const UpgradeTemplate *UpgradeCenter::findUpgrade( const AsciiString& name ) const
{

	return findUpgradeByKey( TheNameKeyGenerator->nameToKey( name ) );

}  // end findUpgrade

//-------------------------------------------------------------------------------------------------
/** Allocate a new upgrade template */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/UpgradeCenter_newUpgrade_Thunk.cpp
// ?newUpgrade@UpgradeCenter@@QAEPAVUpgradeTemplate@@ABVAsciiString@@@Z present-unmatched
UpgradeTemplate *UpgradeCenter::newUpgrade( const AsciiString& name )
{
	UpgradeTemplate *newUpgrade = newInstance(UpgradeTemplate);

	// copy data from the default upgrade
	const UpgradeTemplate *defaultUpgrade = findUpgrade( "DefaultUpgrade" );
	if( defaultUpgrade )
		*newUpgrade = *defaultUpgrade;

	// assign name and starting data
	newUpgrade->setUpgradeName( name );
	newUpgrade->setUpgradeNameKey( TheNameKeyGenerator->nameToKey( name ) );

	// Make a unique bitmask for this new template by keeping track of what bits have been assigned
	// damn MSFT! proper ANSI syntax for a proper 64-bit constant is "1LL", but MSVC doesn't recognize it
	UpgradeMaskType newMask;
	newMask.set( m_nextTemplateMaskBit );
	//Int64 newMask = 1i64 << m_nextTemplateMaskBit;
	m_nextTemplateMaskBit++;
	DEBUG_ASSERTCRASH( m_nextTemplateMaskBit < UPGRADE_MAX_COUNT, ("Can't have over %d types of Upgrades and have a Bitfield function.", UPGRADE_MAX_COUNT) );
	newUpgrade->friend_setUpgradeMask( newMask );

	// link upgrade
	linkUpgrade( newUpgrade );

	// return new upgrade
	return newUpgrade;

}  // end newUnlinkedUpgrade

//-------------------------------------------------------------------------------------------------
/** Link an upgrade to our list */
//-------------------------------------------------------------------------------------------------
// ?linkUpgrade@UpgradeCenter@@IAEXPAVUpgradeTemplate@@@Z present-unmatched
void UpgradeCenter::linkUpgrade( UpgradeTemplate *upgrade )
{

	// sanity
	if( upgrade == NULL )
		return;

	// link
	upgrade->friend_setPrev( NULL );
	upgrade->friend_setNext( m_upgradeList );
	if( m_upgradeList )
		m_upgradeList->friend_setPrev( upgrade );
	m_upgradeList = upgrade;

}  // end linkUpgrade

//-------------------------------------------------------------------------------------------------
/** Unlink an upgrade from our list */
//-------------------------------------------------------------------------------------------------
// ?unlinkUpgrade@UpgradeCenter@@IAEXPAVUpgradeTemplate@@@Z present-unmatched
void UpgradeCenter::unlinkUpgrade( UpgradeTemplate *upgrade )
{

	// sanity
	if( upgrade == NULL )
		return;

	if( upgrade->friend_getNext() )
		upgrade->friend_getNext()->friend_setPrev( upgrade->friend_getPrev() );
	if( upgrade->friend_getPrev() )
		upgrade->friend_getPrev()->friend_setNext( upgrade->friend_getNext() );
	else
		m_upgradeList = upgrade->friend_getNext();

}  // end unlinkUpgrade

//-------------------------------------------------------------------------------------------------
/** does this player have all the necessary things to make this upgrade */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/UpgradeCenter_canAffordUpgrade_Thunk.cpp
// ?canAffordUpgrade@UpgradeCenter@@QBE_NPAVPlayer@@PBVUpgradeTemplate@@_N@Z present-unmatched
Bool UpgradeCenter::canAffordUpgrade( Player *player, const UpgradeTemplate *upgradeTemplate, Bool displayReason ) const
{
 
	// sanity
	if( player == NULL || upgradeTemplate == NULL )
		return FALSE;

	// money check
	Money *money = player->getMoney();
	if( money->countMoney() < upgradeTemplate->calcCostToBuild( player ) )
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

//-------------------------------------------------------------------------------------------------
/** generate a list of upgrade names for WorldBuilder */
//-------------------------------------------------------------------------------------------------
std::vector<AsciiString> UpgradeCenter::getUpgradeNames( void ) const
{
	std::vector<AsciiString> upgradeNames;

	for( UpgradeTemplate *upgrade = m_upgradeList; upgrade; upgrade = upgrade->friend_getNext() )
		upgradeNames.push_back(upgrade->getUpgradeName());

	return upgradeNames;

}  // end getUpgradeNames

// Retail AsciiString(const char*) is the thin 0x888BC0 body (not ZH ensureUniqueBufferOfSize).
// Same local shim pattern as DifficultySelect / PlayerTemplate.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *string );
	~BFMERetailAsciiString() { releaseBuffer(); }

	const char *str() const
	{
		return m_data ? m_data + 8 : "";
	}

private:
	void releaseBuffer();
	char *m_data;
};

//-------------------------------------------------------------------------------------------------
/** Parse an upgrade definition */
//-------------------------------------------------------------------------------------------------
void UpgradeCenter::parseUpgradeDefinition( INI *ini )
{
	// read the name (retail thin AsciiString ctor @ 0x888BC0)
	BFMERetailAsciiString name( ini->getNextToken() );

	// find existing item if present — walk retail layout (nameKey@+0xC, next@+0x108)
	NameKeyType key = TheNameKeyGenerator->nameToKey( name.str() );
	UpgradeTemplate *upgrade = NULL;
	{
		unsigned char *node = *reinterpret_cast<unsigned char **>(
			reinterpret_cast<unsigned char *>(TheUpgradeCenter) + 0x8 );
		while( node )
		{
			if( *reinterpret_cast<NameKeyType *>(node + 0xC) == key )
			{
				upgrade = reinterpret_cast<UpgradeTemplate *>(node);
				break;
			}
			node = *reinterpret_cast<unsigned char **>(node + 0x108);
		}
	}
	if( upgrade == NULL )
	{
		// allocate a new item
		upgrade = TheUpgradeCenter->newUpgrade( *reinterpret_cast<AsciiString *>(&name) );
	}

	// parse the ini definition
	ini->initFromINI( upgrade, upgrade->getFieldParse() );

}

