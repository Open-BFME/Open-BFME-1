// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "PreRTS.h"
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"

extern UnicodeString getUnicodeDateBuffer( SYSTEMTIME timeValue );

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SkirmishBattleHonors.h
class SkirmishBattleHonors
{
public:
	virtual void _bfme_slot0( void ) = 0;
	virtual void _bfme_slot1( void ) = 0;
	virtual void _bfme_slot2( void ) = 0;
	virtual void _bfme_slot3( void ) = 0;
	virtual void _bfme_slot4( void ) = 0;
	virtual void _bfme_slot5( void ) = 0;
	virtual AsciiString getAsciiString( AsciiString key, AsciiString defaultValue ) = 0;
	virtual void setAsciiString( AsciiString key, AsciiString value ) = 0;

	AsciiString getProfileCreatedDate( void );
	void setProfileCreatedDate( void );
};

AsciiString SkirmishBattleHonors::getProfileCreatedDate( void )
{
	return getAsciiString( "ProfileCreatedDate", AsciiString::TheEmptyString );
}

void SkirmishBattleHonors::setProfileCreatedDate( void )
{
	SYSTEMTIME timeValue;
	GetLocalTime( &timeValue );

	UnicodeString displayDate = getUnicodeDateBuffer( timeValue );
	AsciiString profileDate;
	profileDate.translate( displayDate );
	setAsciiString( "ProfileCreatedDate", profileDate );
}
