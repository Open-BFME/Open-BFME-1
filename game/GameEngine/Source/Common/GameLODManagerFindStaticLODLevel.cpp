// ?findStaticLODLevel@GameLODManager@@QAE?AW4StaticGameLODLevel@@XZ
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// Zero Hour twin: Common/GameLOD.cpp:445. BFME extent is 948 bytes,
// ending RET at 0007E4A3. The former OptionPreferences identity is wrong.
// Native headers retained; address-qualified views carry BFME-only offsets.
// Key construction must precede the level-name load, which must precede
// map lookup. Resolution lives through write(), exactly as retail cleanup.
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include "Lib/BaseType.h"
#include "Common/AsciiString.h"
struct FieldParse;
#include "Common/GameLOD.h"
#include "Common/UserPreferences.h"
extern "C" unsigned int __cdecl strlen(const char*);
#pragma intrinsic(strlen)
inline AsciiString::~AsciiString(){((StringBase<char>*)this)->~StringBase<char>();}
inline AsciiString &AsciiString::operator=(const char *s){((StringBase<char>*)this)->set(s,s?strlen(s):0);return *this;}
extern void j_0003e6da();
extern void j_0001391c();
class __single_inheritance Rva0007E0F0Calls{};
template<> __forceinline AsciiString &std::map<AsciiString,AsciiString>::operator[](const AsciiString &key){
 typedef AsciiString &(Rva0007E0F0Calls::*F)(const AsciiString&);
 union{void(*p)();F f;}u;u.p=j_0003e6da;
 return (((Rva0007E0F0Calls*)this)->*u.f)(key);
}
static const char *StaticGameLODNames[]={"VeryLow","Low","Medium","High","UltraHigh","Custom"};
#define PROFILE_ERROR_LIMIT 0.94f
struct Rva0007E0F0Preset {Int m_cpuType,m_mhz;Real m_cpuPerfIndex;Int m_videoType,m_memory,pad14,m_xResolution,m_yResolution;};
// Address-qualified BFME storage view, not a second GameLODManager declaration.
struct Rva0007E0F0Layout {
 char pad000[0x180];Rva0007E0F0Preset m_lodPresets[5][32];char pad1580[0x140];
 Int m_currentStaticLOD,m_currentDynamicLOD;char pad16c8[0x28];
 Int m_numLevelPresets[4],pad1700,pad1704;StaticGameLODLevel m_idealDetailLevel;
 Int pad170c,m_videoChipType,m_cpuType,m_numRAM,m_cpuFreq;
};
struct Rva0007E0F0GlobalView{char prefix[0x2c];Int x2c,y30;};
class GlobalData;extern GlobalData *TheWritableGlobalData;
struct BfmeOSVersionInfo{unsigned long dwOSVersionInfoSize,dwMajorVersion,dwMinorVersion,dwBuildNumber,dwPlatformId,szCSDVersion[32];};
extern "C" __declspec(dllimport) int __stdcall GetVersionExA(BfmeOSVersionInfo*);
extern "C" void *__cdecl memset(void*,int,unsigned int);
typedef char CheckRvaView[sizeof(Rva0007E0F0Layout)==0x1720?1:-1];
typedef char CheckOptionPreferences[sizeof(OptionPreferences)==20?1:-1];
StaticGameLODLevel GameLODManager::findStaticLODLevel(void)
{
	Rva0007E0F0Layout *view=(Rva0007E0F0Layout*)this;
	//Check if we have never done the test on current system
	if (view->m_idealDetailLevel == STATIC_GAME_LOD_UNKNOWN)
	{
		//search all our presets for matching hardware
		// Retail's immediate here is 0, not Zero Hour's 1: BFME
		// added VERY_LOW below LOW and made it the "nothing matched" answer, which
		// is also the name the preference below then stores (StaticGameLODNames[0]).
		view->m_idealDetailLevel = (StaticGameLODLevel)0;

		//get system configuration - only need video chip type, got rest in ::init().
		((void (__cdecl *)(Int*,Int*,Int*,Int*,Real*,Real*,Real*))j_0001391c)(&view->m_videoChipType,0,0,0,0,0,0);
		if (view->m_videoChipType == DC_UNKNOWN)
			view->m_videoChipType = 1;	//presume it's at least GeForce2 level

		Int numMBRam=view->m_numRAM/(1024*1024);
		Int xres=800;
		Int yres=600;

		for (Int i=3; i >= 1; i--)
		{
			Rva0007E0F0Preset *preset=&view->m_lodPresets[i][0];
			for (Int j=0; j<view->m_numLevelPresets[i]; j++)
			{
				if (	view->m_cpuType == preset->m_cpuType &&
						((Real)view->m_cpuFreq/(Real)preset->m_mhz >= PROFILE_ERROR_LIMIT) &&	//make sure we're within 5% or higher
						view->m_videoChipType >= preset->m_videoType &&
						((Real)numMBRam/(Real)preset->m_memory >= PROFILE_ERROR_LIMIT)
					)
				{	view->m_idealDetailLevel = (StaticGameLODLevel)i;
					xres = preset->m_xResolution;
					yres = preset->m_yResolution;
					break;
				}

				preset++;	//skip to next preset
			}
			if (view->m_idealDetailLevel >= i)
				break;	//we already found a higher level than the remaining presets so no need to keep searching.
		}

		//Windows 2000 measured a notch faster than retail's preset table claims.
		BfmeOSVersionInfo osvi;
		memset(&osvi, 0, sizeof(osvi));
		osvi.dwOSVersionInfoSize = sizeof(osvi);
		if (	GetVersionExA(&osvi) &&
			osvi.dwPlatformId == 2 &&
			osvi.dwMajorVersion == 5 &&
			osvi.dwMinorVersion == 0 &&
			view->m_idealDetailLevel >= 1 &&
			view->m_idealDetailLevel <= (StaticGameLODLevel)4)
		{
			view->m_idealDetailLevel = (StaticGameLODLevel)(view->m_idealDetailLevel - 1);
		}

		//Save ideal detail level for future usage
		OptionPreferences optionPref;
		{ AsciiString key("IdealStaticGameLOD"); const char *levelName=StaticGameLODNames[view->m_idealDetailLevel]; optionPref[key] = levelName; }
		if (view->m_currentStaticLOD == STATIC_GAME_LOD_UNKNOWN)	//save for future usage.
			{ AsciiString key("StaticGameLOD"); const char *levelName=StaticGameLODNames[view->m_idealDetailLevel]; optionPref[key] = levelName; }
		if (view->m_currentDynamicLOD == STATIC_GAME_LOD_UNKNOWN)
			{ AsciiString key("FixedStaticGameLOD"); const char *levelName=StaticGameLODNames[view->m_idealDetailLevel]; optionPref[key] = levelName; }

		// Retail's `if` guards only the two GlobalData stores: its `je` lands on the
		// resolution string's own zero-init, so the preference is written either way.
		if (TheWritableGlobalData)
		{
			((Rva0007E0F0GlobalView*)TheWritableGlobalData)->x2c = xres;
			((Rva0007E0F0GlobalView*)TheWritableGlobalData)->y30 = yres;
		}
			AsciiString resolution;
			resolution.format(AsciiString("%d %d"), xres, yres);
			optionPref["Resolution"] = resolution;
		optionPref.write();
	}

	return view->m_idealDetailLevel;
}
