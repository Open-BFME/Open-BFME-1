// Twenty 35-byte __cdecl niladic statics, all byte-identical except for one
// string-literal address:
//
//     mov eax,[TheWideCall] / mov ecx,[TheWideRunner]
//     push 0 x6 / push offset "..." / push eax / call REL32 / ret
//
// WHAT THE BYTES SHOW.  Eight arguments go on the stack and NOTHING pops them
// before `ret`, so the callee cleans: a __thiscall member with eight stack
// arguments (`ret 0x20` at 0x004675F0, reached through the incremental-link
// thunk at 0x00015235).  Its receiver is a global pointer variable read with
// `mov ecx,[abs]`; the first argument is a SECOND global pointer variable read
// with `mov eax,[abs]`; the second argument is a string literal; the remaining
// six are literal zero.
//
// Both globals and the callee are the SAME in all twenty members.  THE ONLY
// VARYING FIELD IS THE STRING, and it is a DIR32 site -- so it is not merely
// masked, it is independently verified against the binary by the gate's
// string-ref pass.  The strings are UI event names: ShowCommandInterface,
// HideCommandInterface, ShowRankInterface, ... SampleHelpBoxTextWidth.
//
// The zero arguments are spelled `int` because `push 0` cannot distinguish an
// int, a bool, a char or a null pointer at this width; `int` asserts the least
// structure of those.
//
// IDENTITY IS NOT RECOVERED.  The class names, the member name and the two
// global names are inventions; only the string literals are retail's own.

class WideCall;

class WideRunner
{
public:
	void run( WideCall *target, const char *name, int a, int b, int c, int d, int e, int f );
};

extern WideCall *TheWideCall;
extern WideRunner *TheWideRunner;

#define WIDE_RUN_NAMED( NAME, TEXT )                                      	class Rva##NAME                                                       	{                                                                     	public:                                                               		static void go();                                                 	};                                                                    	void Rva##NAME::go()                                                  	{                                                                     		TheWideRunner->run( TheWideCall, TEXT, 0, 0, 0, 0, 0, 0 );         	}

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
