// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/iniexception /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The AnimationSoundClientBehaviorGlobalSetting block -- BFME-only, one global
// tuning value for the AnimationSoundClientBehavior module, and a block that
// refuses to be overridden from a map.ini.
//
// The refusal is the message-carrying throw BFME uses in place of Zero Hour's
// bare INI_INVALID_DATA, and its text is verbatim from the image.
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/INIException.h"

// BFME keeps m_loadType at INI+0x08; Zero Hour's header puts it at +0x2010
// because of the 8KB read buffer BFME does not have (docs/ini_loading.md).
static INILoadType retailLoadType( const INI *ini )
{
	struct RetailINI { char m_pad[ 0x08 ]; INILoadType m_loadType; };
	return reinterpret_cast<const RetailINI *>( ini )->m_loadType;
}

struct AnimationSoundClientBehaviorGlobalSetting
{
	Real m_minMicrophoneDistanceToDirty;	// 0x00  MinMicrophoneDistanceToDirty

	static const FieldParse m_fieldParseTable[];
};

// The single instance the block parses into, at 0x012B4D44. Nothing in the image
// names it; the class name is the block keyword.
extern AnimationSoundClientBehaviorGlobalSetting TheAnimationSoundClientBehaviorGlobalSetting;

void parseAnimationSoundClientBehaviorGlobalSetting( INI *ini )
{
	if( retailLoadType( ini ) == INI_LOAD_CREATE_OVERRIDES )
		throw INIException( 3, "Cannot override AnimationSoundClientBehaviorGlobalSetting in map.ini" );

	ini->initFromINI( &TheAnimationSoundClientBehaviorGlobalSetting,
										AnimationSoundClientBehaviorGlobalSetting::m_fieldParseTable );
}
