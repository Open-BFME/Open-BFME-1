// Seven one-line wrappers that forward a bool to a named entry point on a
// global object, choosing between two string literals.
//
// WHAT THE BYTES SHOW.
//
//     mov al,[esp+4] / test al,al          // one BYTE parameter
//     eax = <literal A>; if ( al == 0 ) eax = <literal B>
//     ecx = *<global P>                    // receiver loaded from a global
//     push 0 x4 / push eax / eax = *<global Q> / push 1 / push <name literal>
//     push eax / call <one shared target> / ret
//
// No stack cleanup after the call and a receiver in ecx make the target a
// __thiscall member taking EIGHT stack arguments, and the argument order that
// falls out of the pushes is (Q, <name>, 1, <chosen literal>, 0, 0, 0, 0).  All
// seven reach the SAME target and load the SAME two globals.
//
// THE LITERALS ARE REAL AND VERIFIED.  The name strings are
// "EnablePlayerMagicButton", "HighlightPlayerMagicButton",
// "SetPlayerButtonsState", "MoveHelpBox", "SetPlayerPowerCapState",
// "SetResourceIconState" and "FlashObjectivesButton"; the chosen pairs are
// "1"/"0", "_ring"/"_evenstar" and "_show"/"_hide".  Each was read at the
// address its DIR32 points at, and the full build re-checks every one of them
// byte-for-byte against that address, so unlike the rest of the DIR32 operands
// here these ARE evidence.
//
// TWO AXES.  The name literal, distinct in all seven, and the chosen pair,
// which repeats: "1"/"0" three times, "_ring"/"_evenstar" twice, "_show"/"_hide"
// twice.  Because the pair repeats while the name does not, the two are
// independent and neither is standing in for the other.
//
// The wrapper names and globals remain address-derived. The shared target is
// spelled with its matched ledger name, BfmeLevelAN::bfmeBuildAN, while the
// literals identify these wrappers as a UI-script dispatch layer.
//
// WHAT THE BYTES CANNOT DECIDE.  The types of the eight arguments beyond their
// width; the third argument is the constant 1 and the last four are 0 in every
// one of the seven, so nothing distinguishes an int from a pointer there.

class BfmeLevelAN
{
	public:
	char *bfmeBuildAN( unsigned int p1, int p2, int p3, int p4,
		int p5, int p6, int p7, int p8 );
};

// Retail global 0x012F19E8, canonical name and pointee type; the TU-local
// view below is what these bodies call through.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;
// Retail's dispatch-receiver global at 0x012B7D80 is the AptPalantir window
// index, `int g_aptPalantirWindow` (defined in
// GUI/GUICallbacks/Apt/AptPalantir.cpp).  The TU-local Q3ScriptMovie view is
// only a dispatch-target type here, so the canonical int is cast to it at the
// use; the load is `mov eax,[abs]` either way.
extern int g_aptPalantirWindow;

static inline unsigned int q3ScriptMovie()
{
	return (unsigned int)g_aptPalantirWindow;
}

static inline BfmeLevelAN *q3Dispatcher()
{
	return (BfmeLevelAN *)g_rva012F19E8WindowManager;
}

#define BFME_SCRIPT_TOGGLE( NAME, ENTRY, WHEN_TRUE, WHEN_FALSE )              \
	void NAME( bool on )                                                      \
	{                                                                         \
		q3Dispatcher()->bfmeBuildAN( q3ScriptMovie(), (int)ENTRY, 1,            \
			(int)( on ? WHEN_TRUE : WHEN_FALSE ), 0, 0, 0, 0 );                  \
	}

BFME_SCRIPT_TOGGLE( Rva005642F0, "EnablePlayerMagicButton", "1", "0" )
BFME_SCRIPT_TOGGLE( Rva00564340, "HighlightPlayerMagicButton", "1", "0" )
BFME_SCRIPT_TOGGLE( Rva00564750, "SetPlayerButtonsState", "_ring", "_evenstar" )
BFME_SCRIPT_TOGGLE( Rva00564A70, "MoveHelpBox", "1", "0" )
BFME_SCRIPT_TOGGLE( Rva00564B00, "SetPlayerPowerCapState", "_ring", "_evenstar" )
BFME_SCRIPT_TOGGLE( Rva00564C70, "SetResourceIconState", "_show", "_hide" )
BFME_SCRIPT_TOGGLE( Rva00564F60, "FlashObjectivesButton", "_show", "_hide" )
