// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "PreRTS.h"
#include "Common/UserPreferences.h"

class SkirmishBattleHonors : public UserPreferences
{
public:
	virtual Bool write( void );
};

class GameSlot
{
public:
	Int getColor( void ) const
	{
		return *( (const Int *)((const char *)this + 0x0c) );
	}

	Int getPlayerTemplate( void ) const
	{
		return *( (const Int *)((const char *)this + 0x14) );
	}
};

class GameInfo
{
public:
	const GameSlot *getConstSlot( Int slotNum ) const;
	AsciiString getMap( void ) const;
};

extern GameInfo *TheSkirmishGameInfo;

Bool SkirmishBattleHonors::write( void )
{
	if( TheSkirmishGameInfo )
	{
		AsciiString tmp;

		tmp.format( "%d", TheSkirmishGameInfo->getConstSlot( 0 )->getColor() );
		( *this )["Color"] = tmp;

		tmp.format( "%d", TheSkirmishGameInfo->getConstSlot( 0 )->getPlayerTemplate() );
		( *this )["PlayerTemplate"] = tmp;

		( *this )["Map"] = TheSkirmishGameInfo->getMap();
	}

	return UserPreferences::write();
}
