// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// readable body of ?setCachedStats@GameSpyMiscPreferences@@QAEXVAsciiString@@@Z: Code/GameEngine/Source/Common/UserPreferences.cpp

// Forwards to a virtual setter with two by-value AsciiStrings.
//
// Both are temporaries, and their construction order is the argument evaluation
// order: right to left, so the copy of the parameter is built first and the key
// from the literal second. Each gets its own unwind state, 0 then 1, and after
// the call the state drops back so the parameter itself can be released -- a
// by-value class parameter is destroyed by the callee.
//
// The setter is virtual slot 7, reached at +0x1C.
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
	virtual void _bfme_slot6( void ) = 0;
	virtual void setPref( AsciiString key, AsciiString value ) = 0;	// slot 7, +0x1C

	void setCachedStats( AsciiString stats );
};

// ?setCachedStats@GameSpyMiscPreferences@@QAEXVAsciiString@@@Z
void GameSpyMiscPreferences::setCachedStats( AsciiString stats )
{
	setPref( "CachedStats", stats );
}
