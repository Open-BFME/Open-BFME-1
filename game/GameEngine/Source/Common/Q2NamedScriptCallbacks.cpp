// Eight 38-byte __cdecl functions that each fire one named script callback
// with one string argument through a pair of globals:
//
//   mov eax,[<OWNER GLOBAL>] / mov ecx,[<TARGET GLOBAL>]
//   push 0 / push 0 / push 0 / push 0
//   push <ARGUMENT STRING> / push 1 / push <CALLBACK NAME> / push eax
//   call <REL32> / ret
//
// WHAT THE BYTES SHOW.  ecx is loaded from a global and never from a
// parameter, and the function itself takes none, so these are free functions
// calling a __thiscall member on a global instance.  Nothing cleans the stack
// after the call and the function ends in a bare `ret`, so the callee pops all
// eight arguments itself.  Both globals are dereferenced -- `mov eax,[abs]`,
// not `lea` -- so both hold pointers.
//
// THE TWO STRINGS ARE REAL AND READ OUT OF RETAIL, not guessed: the pushed
// addresses land in .rdata on "SetSelectAllHeroesButtonState",
// "SetMovieButtonState", "FadePalantirButtons" and "SetObserverStuffState" as
// callback names, and "_up", "_unused", "_show", "_hide", "0" and "1" as the
// argument.  The build's string-reference check verifies those contents
// against the target, so they are evidence and not decoration.  Every row uses
// the same two globals and the same callee; the callback name and the argument
// string are the whole axis.
//
// WHAT THE BYTES DO NOT DECIDE.  The `1` between the two strings is an
// int-width literal (`6a 01`); bool, an enumerator and a char would push the
// same.  The four trailing zeros are equally int, pointer or enumerator; they
// are void pointers here.  Nothing says the callee takes exactly this
// signature rather than a longer one with defaulted tail arguments -- only
// that eight dwords go across.  18 of the 38 bytes are concrete; the two
// global addresses, the two string addresses and the call displacement come
// from the target.
//
// The wrapper names remain address-derived. The shared target is spelled with
// its matched ledger name, BfmeLevelAN::bfmeBuildAN at 0x004675F0.

class BfmeLevelAN
{
public:
	char *bfmeBuildAN( unsigned int p1, int p2, int p3, int p4,
		int p5, int p6, int p7, int p8 );
};

// retail 0x012F19E8: the one global definition is
// WindowManager *g_rva012F19E8WindowManager (GUI/WindowManager.cpp).  The
// TU-local view below is what the callee at 0x004675F0 is called through.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;		///< retail 0x012F19E8
// Retail's dispatch-owner global at 0x012B7D80 is the AptPalantir window index,
// `int g_aptPalantirWindow` (defined in
// GUI/GUICallbacks/Apt/AptPalantir.cpp).  The canonical int is cast to the
// callee's `void *owner` at the use; the load is `mov eax,[abs]` either way.
extern int g_aptPalantirWindow;					///< retail 0x012B7D80

static __forceinline void *q2ScriptOwner()
{
	return (void *)g_aptPalantirWindow;
}

static __forceinline BfmeLevelAN *q2ScriptTarget()
{
	return (BfmeLevelAN *)g_rva012F19E8WindowManager;
}

#define Q2_NAMED_SCRIPT_CALLBACK( NAME, CALLBACK, ARGUMENT )              \
	void NAME()                                                           \
	{                                                                     \
		q2ScriptTarget()->bfmeBuildAN( (unsigned int)q2ScriptOwner(), (int)CALLBACK, \
									1, (int)ARGUMENT, 0, 0, 0, 0 );          \
	}

Q2_NAMED_SCRIPT_CALLBACK( Rva00564DE0, "SetSelectAllHeroesButtonState", "_up" )
Q2_NAMED_SCRIPT_CALLBACK( Rva00564E10, "SetSelectAllHeroesButtonState", "_unused" )
Q2_NAMED_SCRIPT_CALLBACK( Rva00564E40, "SetMovieButtonState", "_show" )
Q2_NAMED_SCRIPT_CALLBACK( Rva00564E70, "SetMovieButtonState", "_hide" )
Q2_NAMED_SCRIPT_CALLBACK( Rva00564EA0, "FadePalantirButtons", "0" )
Q2_NAMED_SCRIPT_CALLBACK( Rva00564ED0, "FadePalantirButtons", "1" )
Q2_NAMED_SCRIPT_CALLBACK( Rva00564F00, "SetObserverStuffState", "_show" )
Q2_NAMED_SCRIPT_CALLBACK( Rva00564F30, "SetObserverStuffState", "_hide" )
