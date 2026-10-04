// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: BFME's own CommandLine.cpp option handlers.
//
// Every body here is an `Int parseXxx(char *args[], int num)` of the shape the
// Zero Hour CommandLine.cpp uses, and the already-matched rows in
// game/GameEngine/Source/Common/CommandLine.cpp (parseXRes, parseFullVersion,
// parseFPUPreserve) sit in the same run of addresses. The Zero Hour source
// cannot claim these, though: BFME's GlobalData is a different object, so the
// ZH header puts m_windowed at +0x20 where retail stores +0x29, and the ZH
// translation unit misses on member offsets alone. So GlobalData is rebuilt
// here from the offsets retail actually writes.
//
// One of those offset pairs is pinned by numbers rather than by shape: the pair
// (m_useFpsLimit at +0x1E, m_framesPerSecondLimit at +0x24) is written FALSE and
// 0x7530 = 30000 together, which is ZH parseNoFPSLimit verbatim.
//
// TheCommandLineFlags at [0x012A6FA0] is a BFME addition with no ZH counterpart:
// a bitmask of which switches were seen, OR-ed with one bit per handler.
//
// A handler takes EA's name where tools/ea_flagtable.py reads it from the
// CommandLineParam tables: retail's own (0x00EA6F40) pairs a flag with a body,
// BFME1 WorldBuilder's (0x00FBB788) pairs it with a body of identical effects,
// and Zero Hour's table pairs that flag with the name
// (targets/game/reverse/identity_evidence/00ea6f40-commandline-params.md).
// The rest are address-derived: their rows are Rva-prefixed and each carries
// the ZH handler it matches in shape where there is one.
//
// Every offset below is one retail store; no name moves one. The named members
// are the offsets retail's own INI field table at 0x00C77018 gives a key to,
// joined to the upstream member that key writes -- so the offset is BFME's and
// only the vocabulary is Zero Hour's. That table independently reproduces the
// three offsets this file had already pinned by hand from the stores
// (m_useFpsLimit +0x1E, m_framesPerSecondLimit +0x24, m_windowed +0x29), which
// is what makes it safe to read the rest of it. A key BFME added and Zero Hour
// has no member for stays an offset name, with the key in its comment.

typedef int Int;
typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) int __cdecl atoi(const char *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_unreconstructed_00[0x1E];
	bool m_useFpsLimit;									///< retail this+0x1E
	unsigned char m_unreconstructed_1F[0x20 - 0x1F];
	bool m_dumpAssetUsage;								///< retail this+0x20, INI key DumpAssetUsage
	unsigned char m_unreconstructed_21[0x24 - 0x21];
	Int m_framesPerSecondLimit;							///< retail this+0x24
	unsigned char m_unreconstructed_28[1];
	bool m_windowed;									///< retail this+0x29
	bool m_flag2A;										///< retail this+0x2A, INI key SkipMapUnroll
	unsigned char m_unreconstructed_2B[0x30 - 0x2B];
	Int m_yResolution;										///< retail this+0x30
	unsigned char m_unreconstructed_34[0x64 - 0x34];
	bool m_useShadowVolumes;										///< retail this+0x64
	bool m_useShadowDecals;										///< retail this+0x65
	unsigned char m_unreconstructed_66[0xA6C - 0x66];
	bool m_audioOn;										///< retail this+0xA6C
	bool m_musicOn;										///< retail this+0xA6D
	bool m_soundsOn;										///< retail this+0xA6E
	bool m_sounds3DOn;										///< retail this+0xA6F
	bool m_speechOn;										///< retail this+0xA70
	bool m_flagA71;										///< retail this+0xA71, INI key AmbientStreamsOn
	unsigned char m_unreconstructed_A72[0xA84 - 0xA72];
	Int m_valueA84;										///< retail this+0xA84
	unsigned char m_unreconstructed_A88[0xA8F - 0xA88];
	bool m_flagA8F;										///< retail this+0xA8F, INI key ShowTooltips
	bool m_flagA90;										///< retail this+0xA90
	bool m_flagA91;										///< retail this+0xA91
	unsigned char m_unreconstructed_A92[0xA95 - 0xA92];
	bool m_flagA95;										///< retail this+0xA95
	unsigned char m_unreconstructed_A96[0xAB0 - 0xA96];
	Int m_fixedSeed;										///< retail this+0xAB0
	unsigned char m_unreconstructed_AB4[0xB0C - 0xAB4];
	Int m_valueB0C;										///< retail this+0xB0C
	unsigned char m_unreconstructed_B10[0xBB4 - 0xB10];
	bool m_shellMapOn;										///< retail this+0xBB4
	bool m_flagBB5;										///< retail this+0xBB5, INI key ShellMapOffByCommandArgument
	unsigned char m_unreconstructed_BB6[0xBC4 - 0xBB6];
	bool m_flagBC4;										///< retail this+0xBC4
	unsigned char m_unreconstructed_BC5[0xCCC - 0xBC5];
	Int m_playStats;										///< retail this+0xCCC
	unsigned char m_unreconstructed_CD0[0xDCD - 0xCD0];
	bool m_flagDCD;										///< retail this+0xDCD
	unsigned char m_unreconstructed_DCE[0x11FC - 0xDCE];
	bool m_flag11FC;									///< retail this+0x11FC
};

extern GlobalData *TheWritableGlobalData;				///< retail [0x012ED5C8]
extern UnsignedInt TheCommandLineFlags;					///< retail [0x012A6FA0]

bool ScriptDebugMessagesDisabled = false;								///< retail [0x012ED4D8]
bool g_flag12ED4D9 = false;								///< retail [0x012ED4D9]
bool g_flag12ED4DA = false;								///< retail [0x012ED4DA]
bool ignoreCRCMismatches = false;								///< retail [0x012ED4E8]
extern bool g_flag12D6DA8;								///< retail [0x012D6DA8]

// ?Rva00060910_parse@@YAHQAPADH@Z
Int Rva00060910_parse(char *args[], int num)
{
	if (TheWritableGlobalData)
	{
		TheWritableGlobalData->m_shellMapOn = false;
		TheWritableGlobalData->m_flagBB5 = true;
		TheWritableGlobalData->m_flagBC4 = false;
		TheWritableGlobalData->m_flag11FC = true;
	}
	return 1;
}

// ?Rva00060980_parse@@YAHQAPADH@Z
Int Rva00060980_parse(char *args[], int num)
{
	g_flag12ED4D9 = false;
	return 1;
}

// ?Rva000609A0_parse@@YAHQAPADH@Z
Int Rva000609A0_parse(char *args[], int num)
{
	if (TheWritableGlobalData)
	{
		TheWritableGlobalData->m_flag2A = true;
	}
	return 1;
}

// ?Rva00060A00_parse@@YAHQAPADH@Z
Int Rva00060A00_parse(char *args[], int num)
{
	TheCommandLineFlags |= 4;
	if (TheWritableGlobalData)
	{
		TheWritableGlobalData->m_musicOn = false;
	}
	return 1;
}

// ?parseNoAudio@@YAHQAPADH@Z -- retail table entry "-noaudio" (0x00EA6F50) ->
// ILT 0x00019CEF -> 0x00060A60; ZH pairs "-noaudio" with parseNoAudio, and the
// stores follow ZH's order.
Int parseNoAudio(char *args[], int num)
{
	TheCommandLineFlags |= 2;
	if (TheWritableGlobalData)
	{
		TheWritableGlobalData->m_audioOn = false;
		TheWritableGlobalData->m_speechOn = false;
		TheWritableGlobalData->m_soundsOn = false;
		TheWritableGlobalData->m_sounds3DOn = false;
		TheWritableGlobalData->m_musicOn = false;
		TheWritableGlobalData->m_flagA71 = false;
	}
	return 1;
}

// ?Rva00060B20_parseNoWin@@YAHQAPADH@Z
Int Rva00060B20_parseNoWin(char *args[], int num)
{
	if (TheWritableGlobalData)
	{
		TheWritableGlobalData->m_windowed = false;
	}
	return 1;
}

// ?Rva00060B90_parse@@YAHQAPADH@Z -- ZH parseNoShadows shape
Int Rva00060B90_parse(char *args[], int num)
{
	if (TheWritableGlobalData)
	{
		TheWritableGlobalData->m_useShadowVolumes = false;
		TheWritableGlobalData->m_useShadowDecals = false;
	}
	return 1;
}

// ?parseYRes@@YAHQAPADH@Z -- retail table entry "-yres" (0x00EA6F60) -> ILT
// 0x00026CC4 -> 0x00060C10; ZH pairs "-yres" with parseYRes. +0x30 is the
// YResolution of retail's INI field table.
Int parseYRes(char *args[], int num)
{
	if (TheWritableGlobalData && num > 1)
	{
		TheWritableGlobalData->m_yResolution = atoi(args[1]);
		return 2;
	}
	return 1;
}

// ?Rva00060CA0_parse@@YAHQAPADH@Z -- ZH parseScriptDebug shape
Int Rva00060CA0_parse(char *args[], int num)
{
	if (TheWritableGlobalData)
	{
		TheWritableGlobalData->m_flagA90 = true;
		TheWritableGlobalData->m_flagA95 = true;
	}
	return 1;
}

// ?Rva00060CD0_parse@@YAHQAPADH@Z
Int Rva00060CD0_parse(char *args[], int num)
{
	if (TheWritableGlobalData)
	{
		TheWritableGlobalData->m_flagA90 = true;
		TheWritableGlobalData->m_flagA95 = true;
		g_flag12ED4DA = true;
	}
	return 1;
}

// ?Rva00060D00_parse@@YAHQAPADH@Z
Int Rva00060D00_parse(char *args[], int num)
{
	if (TheWritableGlobalData)
	{
		TheWritableGlobalData->m_flagA90 = true;
		TheWritableGlobalData->m_flagA95 = true;
		g_flag12ED4DA = true;
		ScriptDebugMessagesDisabled = true;
	}
	return 1;
}

// ?Rva00060D40_parse@@YAHQAPADH@Z -- ZH parseParticleEdit shape
Int Rva00060D40_parse(char *args[], int num)
{
	if (TheWritableGlobalData)
	{
		TheWritableGlobalData->m_flagA91 = true;
		TheWritableGlobalData->m_flagA95 = true;
		TheWritableGlobalData->m_windowed = true;
	}
	return 1;
}

// ?Rva00060EE0_parse@@YAHQAPADH@Z
Int Rva00060EE0_parse(char *args[], int num)
{
	if (TheWritableGlobalData && num > 1)
	{
		TheWritableGlobalData->m_fixedSeed = atoi(args[1]);
	}
	return 2;
}

// ?parseNetMinPlayers@@YAHQAPADH@Z -- BFME1 WorldBuilder's table pairs
// "-netMinPlayers" with a +0xB0C atoi store; this is the only game body with
// that effect, and ZH pairs the flag with parseNetMinPlayers.
Int parseNetMinPlayers(char *args[], int num)
{
	if (TheWritableGlobalData && num > 1)
	{
		TheWritableGlobalData->m_valueB0C = atoi(args[1]);
	}
	return 2;
}

// ?Rva00060FA0_parse@@YAHQAPADH@Z
Int Rva00060FA0_parse(char *args[], int num)
{
	if (TheWritableGlobalData && num > 1)
	{
		TheWritableGlobalData->m_playStats = atoi(args[1]);
	}
	return 2;
}

// ?Rva00061020_parseNoFPSLimit@@YAHQAPADH@Z
Int Rva00061020_parseNoFPSLimit(char *args[], int num)
{
	if (TheWritableGlobalData)
	{
		TheWritableGlobalData->m_useFpsLimit = false;
		TheWritableGlobalData->m_framesPerSecondLimit = 30000;
	}
	return 1;
}

// ?Rva00061070_parse@@YAHQAPADH@Z -- ZH parseJumpToFrame shape
Int Rva00061070_parse(char *args[], int num)
{
	if (TheWritableGlobalData && num > 1)
	{
		TheWritableGlobalData->m_useFpsLimit = false;
		TheWritableGlobalData->m_framesPerSecondLimit = 30000;
		TheWritableGlobalData->m_valueA84 = atoi(args[1]);
		return 2;
	}
	return 1;
}

// ?Rva00061110_parse@@YAHQAPADH@Z
Int Rva00061110_parse(char *args[], int num)
{
	if (TheWritableGlobalData)
	{
		TheWritableGlobalData->m_flagDCD = true;
		TheWritableGlobalData->m_flagA8F = false;
		g_flag12D6DA8 = false;
	}
	return 1;
}

// ?Rva000608C0_parse@@YAHQAPADH@Z
Int Rva000608C0_parse(char *args[], int num)
{
	TheCommandLineFlags |= 1;
	return 1;
}

// ?Rva00061430_parse@@YAHQAPADH@Z
Int Rva00061430_parse(char *args[], int num)
{
	ignoreCRCMismatches = true;
	TheCommandLineFlags |= 0x40000;
	return 1;
}

extern Int g_value12A6F30;								///< retail [0x012A6F30]
extern Int g_value12A6F34;								///< retail [0x012A6F34]
extern Int g_value12A6F38;								///< retail [0x012A6F38]
extern Int g_value12A6FA8;								///< retail [0x012A6FA8]
extern Int g_value12A6FB0;								///< retail [0x012A6FB0]
extern Int g_value12A6FB4;								///< retail [0x012A6FB4]
extern Int NET_CRC_INTERVAL;								///< retail [0x012A7040]

// ?Rva00061260_parse@@YAHQAPADH@Z
Int Rva00061260_parse(char *args[], int num)
{
	if (num > 1)
	{
		Int value = atoi(args[1]);
		g_value12A6F30 = value;
		TheCommandLineFlags |= 0x2000;
		g_value12A6FA8 = value;
	}
	return 2;
}

// ?Rva000612B0_parse@@YAHQAPADH@Z
Int Rva000612B0_parse(char *args[], int num)
{
	if (num > 1)
	{
		Int value = atoi(args[1]);
		g_value12A6F34 = value;
		TheCommandLineFlags |= 0x4000;
		g_value12A6FA8 = value;
	}
	return 2;
}

// ?Rva00061490_parse@@YAHQAPADH@Z
Int Rva00061490_parse(char *args[], int num)
{
	if (num > 1)
	{
		Int value = atoi(args[1]);
		NET_CRC_INTERVAL = value;
		TheCommandLineFlags |= 0x8000;
		g_value12A6FB0 = value;
	}
	return 2;
}

// ?Rva000613F0_parse@@YAHQAPADH@Z
Int Rva000613F0_parse(char *args[], int num)
{
	if (num > 1)
	{
		Int value = atoi(args[1]);
		if (value > 0)
		{
			g_value12A6F38 = value;
			g_value12A6FB4 = value;
		}
	}
	return 1;
}

// ?parseNoShellMap@@YAHQAPADH@Z -- retail table entry "-noshellmap"
// (0x00EA6F40) -> ILT 0x000428FC -> 0x00060880; ZH pairs "-noshellmap" with
// parseNoShellMap. Its two stores are the first two of Rva00060910_parse.
Int parseNoShellMap(char *args[], int num)
{
	if (TheWritableGlobalData)
	{
		TheWritableGlobalData->m_shellMapOn = false;
		TheWritableGlobalData->m_flagBB5 = true;
	}
	return 1;
}

// ?Rva00060970_parse@@YAHQAPADH@Z -- the set twin of Rva00060980_parse
Int Rva00060970_parse(char *args[], int num)
{
	g_flag12ED4D9 = true;
	return 1;
}

// ?parseWin@@YAHQAPADH@Z -- retail table entry "-win" (0x00EA6F68) -> ILT
// 0x00001F2D -> 0x000609C0; ZH pairs "-win" with parseWin. The set twin of
// Rva00060B20_parseNoWin.
Int parseWin(char *args[], int num)
{
	if (TheWritableGlobalData)
	{
		TheWritableGlobalData->m_windowed = true;
	}
	return 1;
}

// ?parseDumpAssetUsage@@YAHQAPADH@Z -- 0x00061050, the only retail body that
// stores TRUE to +0x20, the offset retail's INI field table entry
// "DumpAssetUsage" (0x00C770C8) writes; ZH parseDumpAssetUsage verbatim, and it
// sits between the parseNoFPSLimit and parseJumpToFrame shapes as in ZH. Its
// flag is debug-only in ZH's table, and retail's table has no entry for it.
Int parseDumpAssetUsage(char *args[], int num)
{
	if (TheWritableGlobalData)
	{
		TheWritableGlobalData->m_dumpAssetUsage = true;
	}
	return 1;
}
