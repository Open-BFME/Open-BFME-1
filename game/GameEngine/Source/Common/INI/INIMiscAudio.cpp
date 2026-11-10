// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/gameaudio /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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
// The field table (retail VA 0x01083310) is defined below.
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/GameAudio.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MiscAudio.h
class MiscAudio
{
public:
	static const FieldParse m_fieldParseTable[];
};

// Retail .rdata VA 0x01083310: the 32-entry table, every field an AudioEventRTS
// parsed through ILT 0x00009E94 (body INI::parseAudioEventRTS at 0x000BBB60).
// Tokens and offsets read from the image.
extern "C" void __identifier("?j_00009e94@@YAXXZ")(INI *, void *, void *, const void *);
const FieldParse MiscAudio::m_fieldParseTable[] =
{
	{ "RadarNotifyHarvesterUnderAttackSound", __identifier("?j_00009e94@@YAXXZ"), 0, 0x0 },
	{ "RadarNotifyStructureUnderAttackSound", __identifier("?j_00009e94@@YAXXZ"), 0, 0x70 },
	{ "RadarNotifyInfiltrationSound", __identifier("?j_00009e94@@YAXXZ"), 0, 0xE0 },
	{ "RadarNotifyOnlineSound", __identifier("?j_00009e94@@YAXXZ"), 0, 0x150 },
	{ "RadarNotifyOfflineSound", __identifier("?j_00009e94@@YAXXZ"), 0, 0x1C0 },
	{ "DefectorTimerTickSound", __identifier("?j_00009e94@@YAXXZ"), 0, 0x230 },
	{ "DefectorTimerDingSound", __identifier("?j_00009e94@@YAXXZ"), 0, 0x2A0 },
	{ "AllCheerSound", __identifier("?j_00009e94@@YAXXZ"), 0, 0x310 },
	{ "BattleCrySound", __identifier("?j_00009e94@@YAXXZ"), 0, 0x380 },
	{ "NoCanDoSound", __identifier("?j_00009e94@@YAXXZ"), 0, 0x3F0 },
	{ "StealthDiscoveredSound", __identifier("?j_00009e94@@YAXXZ"), 0, 0x460 },
	{ "StealthNeutralizedSound", __identifier("?j_00009e94@@YAXXZ"), 0, 0x4D0 },
	{ "MoneyDepositSound", __identifier("?j_00009e94@@YAXXZ"), 0, 0x540 },
	{ "MoneyWithdrawSound", __identifier("?j_00009e94@@YAXXZ"), 0, 0x5B0 },
	{ "BuildingDisabled", __identifier("?j_00009e94@@YAXXZ"), 0, 0x620 },
	{ "BuildingReenabled", __identifier("?j_00009e94@@YAXXZ"), 0, 0x690 },
	{ "VehicleDisabled", __identifier("?j_00009e94@@YAXXZ"), 0, 0x700 },
	{ "VehicleReenabled", __identifier("?j_00009e94@@YAXXZ"), 0, 0x770 },
	{ "SplatterVehiclePilotsBrain", __identifier("?j_00009e94@@YAXXZ"), 0, 0x7E0 },
	{ "CrateHeal", __identifier("?j_00009e94@@YAXXZ"), 0, 0x850 },
	{ "CrateShroud", __identifier("?j_00009e94@@YAXXZ"), 0, 0x8C0 },
	{ "CrateSalvage", __identifier("?j_00009e94@@YAXXZ"), 0, 0x930 },
	{ "CrateFreeUnit", __identifier("?j_00009e94@@YAXXZ"), 0, 0x9A0 },
	{ "CrateMoney", __identifier("?j_00009e94@@YAXXZ"), 0, 0xA10 },
	{ "UnitPromoted", __identifier("?j_00009e94@@YAXXZ"), 0, 0xA80 },
	{ "RepairSparks", __identifier("?j_00009e94@@YAXXZ"), 0, 0xAF0 },
	{ "EnterCloseCombat", __identifier("?j_00009e94@@YAXXZ"), 0, 0xB60 },
	{ "ExitCloseCombat", __identifier("?j_00009e94@@YAXXZ"), 0, 0xBD0 },
	{ "IncomingChatNotification", __identifier("?j_00009e94@@YAXXZ"), 0, 0xC40 },
	{ "EnabledHotKeyPressed", __identifier("?j_00009e94@@YAXXZ"), 0, 0xCB0 },
	{ "DisabledHotKeyPressed", __identifier("?j_00009e94@@YAXXZ"), 0, 0xD20 },
	{ "LowLODShellMusic", __identifier("?j_00009e94@@YAXXZ"), 0, 0xD90 },
	{ 0, 0, 0, 0 }
};

// ?parseMiscAudio@INI@@SAXPAV1@@Z
void INI::parseMiscAudio( INI *ini )
{
	ini->initFromINI( TheAudio->friend_getMiscAudio(), MiscAudio::m_fieldParseTable );
}
