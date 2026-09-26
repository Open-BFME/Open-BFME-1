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
// IDENTITY IS NOT RECOVERED for the function names, the globals or the callee:
// those are address-derived, and the callee pin is additive.  What the literals
// DO say is that this is a UI-script dispatch layer -- the names read as
// entry points and the pairs as movie-clip labels and flag strings -- but the
// bytes do not name the class, so nothing here asserts one.
//
// WHAT THE BYTES CANNOT DECIDE.  The types of the eight arguments beyond their
// width; the third argument is the constant 1 and the last four are 0 in every
// one of the seven, so nothing distinguishes an int from a pointer there.

struct Q3ScriptMovie;

struct Q3ScriptDispatcher
{
	void invoke( Q3ScriptMovie *movie, const char *name, int argc,
		const char *arg0, void *a1, void *a2, void *a3, void *a4 );
};

extern Q3ScriptDispatcher *g_q3ScriptDispatcher;
extern Q3ScriptMovie *g_q3ScriptMovie;

#define BFME_SCRIPT_TOGGLE( NAME, ENTRY, WHEN_TRUE, WHEN_FALSE )              \
	void NAME( bool on )                                                      \
	{                                                                         \
		g_q3ScriptDispatcher->invoke( g_q3ScriptMovie, ENTRY, 1,              \
			on ? WHEN_TRUE : WHEN_FALSE, 0, 0, 0, 0 );                        \
	}

BFME_SCRIPT_TOGGLE( Rva005642F0, "EnablePlayerMagicButton", "1", "0" )
BFME_SCRIPT_TOGGLE( Rva00564340, "HighlightPlayerMagicButton", "1", "0" )
BFME_SCRIPT_TOGGLE( Rva00564750, "SetPlayerButtonsState", "_ring", "_evenstar" )
BFME_SCRIPT_TOGGLE( Rva00564A70, "MoveHelpBox", "1", "0" )
BFME_SCRIPT_TOGGLE( Rva00564B00, "SetPlayerPowerCapState", "_ring", "_evenstar" )
BFME_SCRIPT_TOGGLE( Rva00564C70, "SetResourceIconState", "_show", "_hide" )
BFME_SCRIPT_TOGGLE( Rva00564F60, "FlashObjectivesButton", "_show", "_hide" )
