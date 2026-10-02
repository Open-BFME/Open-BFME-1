// Twenty 35-byte __cdecl niladic statics, all byte-identical except for one
// string-literal address:
//
//     mov eax,[g_aptPalantirWindow] / mov ecx,[g_rva012F19E8WindowManager]
//     push 0 x6 / push offset "..." / push eax / call REL32 / ret
//
// WHAT THE BYTES SHOW.  Eight dwords go on the stack and the callee cleans
// (`ret 0x20` at 0x004675F0, reached through the incremental-link thunk at
// 0x00015235).  The matched owner is BfmeLevelAN::bfmeBuildAN.  The local view
// below keeps its exact decorated name and dword-sized argument ABI; casts at
// the call preserve the pointer-sized values found in these wrappers.
//
// Both globals and the callee are the SAME in all twenty members.  THE ONLY
// VARYING FIELD IS THE STRING, and it is a DIR32 site -- so it is not merely
// masked, it is independently verified against the binary by the gate's
// string-ref pass.
//
// The zero arguments are spelled `int` because `push 0` cannot distinguish an
// int, a bool, a char or a null pointer at this width; `int` asserts the least
// structure of those.
//
class BfmeLevelAN
{
public:
	char *bfmeBuildAN( unsigned int level, int p2, int p3, int p4, int p5, int p6,
		int p7, int p8 );
};

// Retail's first-argument global at 0x012B7D80 is the AptPalantir window index,
// `int g_aptPalantirWindow` (defined in GUI/GUICallbacks/Apt/AptPalantir.cpp).
// This is the first dword passed by each wrapper.
extern int g_aptPalantirWindow;
// Retail's runner receiver global at 0x012F19E8 is EA's WindowManager singleton
// (defined in GameClient/GUI/WindowManager.cpp); the TU-local BfmeLevelAN view
// below is reached by casting the canonical global.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

#define WIDE_RUN_NAMED( NAME, TEXT )                                      	class Rva##NAME                                                       	{                                                                     	public:                                                               		static void go();                                                 	};                                                                    	void Rva##NAME::go()                                                  	{                                                                     		((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN( (unsigned int)g_aptPalantirWindow, (int)TEXT, 0, 0, 0, 0, 0, 0 );         	}

WIDE_RUN_NAMED( 00563DA0, "ShowCommandInterface" )
WIDE_RUN_NAMED( 00563DD0, "HideCommandInterface" )
WIDE_RUN_NAMED( 00563E00, "ShowRankInterface" )
WIDE_RUN_NAMED( 00563E30, "HideRankInterface" )
WIDE_RUN_NAMED( 00563E60, "ShowRankProgress" )
WIDE_RUN_NAMED( 00563E90, "HideRankProgress" )
WIDE_RUN_NAMED( 00563F50, "ShowCostModifierUpgradeInterface" )
WIDE_RUN_NAMED( 00563F80, "HideCostModifierUpgradeInterface" )
WIDE_RUN_NAMED( 00563FB0, "ShowRegionInterface" )
WIDE_RUN_NAMED( 00563FE0, "HideRegionInterface" )
WIDE_RUN_NAMED( 00564010, "ShowHeroSelectInterface" )
WIDE_RUN_NAMED( 00564040, "HideHeroSelectInterface" )
WIDE_RUN_NAMED( 005646D0, "OnLightPointsAdded" )
WIDE_RUN_NAMED( 005648B0, "RestartHeroSelectGui" )
WIDE_RUN_NAMED( 005648E0, "HideSpellBook" )
WIDE_RUN_NAMED( 00564910, "PlayCommandPointEffect" )
WIDE_RUN_NAMED( 00564940, "PlayPlayerSpellPointEffect" )
WIDE_RUN_NAMED( 00564970, "PlayPlayerLevelUpEffect" )
WIDE_RUN_NAMED( 00564A10, "HideHelpBox" )
WIDE_RUN_NAMED( 00564A40, "SampleHelpBoxTextWidth" )
