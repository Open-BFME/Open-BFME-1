// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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
