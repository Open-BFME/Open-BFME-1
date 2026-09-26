// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/gameaudio /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// INI::parseMiscAudio -- the "MiscAudio" block, one global set of interface and
// notification sounds. The block table binds the keyword to 0x000C25B0, and the
// body is a single forward:
//
//     ini->initFromINI( TheAudio->friend_getMiscAudio(), MiscAudio::m_fieldParseTable );
//
// which is exactly Zero Hour's, so the only BFME-specific part is where
// friend_getMiscAudio sits in the AudioManager vtable -- slot 75, where Zero Hour
// does not have it as a virtual at all. inputs/reference/shims/gameaudio carries that.
//
// The field table is declared but not defined here. Its address is a DIR32 slot,
// which the verifier fills in from the target, so the 32 entries retail's table
// at 0x01083310 holds are recorded in docs/ini_schema.md rather than duplicated
// as an approximation.
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/GameAudio.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MiscAudio.h
class MiscAudio
{
public:
	static const FieldParse m_fieldParseTable[];
};

// ?parseMiscAudio@INI@@SAXPAV1@@Z
void INI::parseMiscAudio( INI *ini )
{
	ini->initFromINI( TheAudio->friend_getMiscAudio(), MiscAudio::m_fieldParseTable );
}
