// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// readable body of ?getCachedStats@GameSpyMiscPreferences@@QAE?AVAsciiString@@XZ: Code/GameEngine/Source/Common/UserPreferences.cpp

// Forwards to a virtual getter that returns an AsciiString by value.
//
// Two temporaries again, built right to left: the default is copy-constructed
// from a global AsciiString first, then the key from its literal. The hidden
// return-slot pointer is fetched from the caller's frame and pushed last, and
// the function returns it in eax.
//
// The getter is virtual slot 6 at +0x18, one below the setter its sibling
// setCachedStats reaches at +0x1C, which is a useful cross-check that both
// numbers are right.
#include "PreRTS.h"
#include "Common/AsciiString.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameSpyMiscPreferences.h
class GameSpyMiscPreferences
{
public:
	virtual void _bfme_slot0( void ) = 0;
	virtual void _bfme_slot1( void ) = 0;
	virtual void _bfme_slot2( void ) = 0;
	virtual void _bfme_slot3( void ) = 0;
	virtual void _bfme_slot4( void ) = 0;
	virtual void _bfme_slot5( void ) = 0;
	virtual AsciiString getPref( AsciiString key, AsciiString defaultValue ) = 0;	// slot 6, +0x18

	AsciiString getCachedStats( void );
};

// ?getCachedStats@GameSpyMiscPreferences@@QAE?AVAsciiString@@XZ
AsciiString GameSpyMiscPreferences::getCachedStats( void )
{
	return getPref( "CachedStats", AsciiString::TheEmptyString );
}
