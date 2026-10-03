// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Address-derived: 0.853 difflib match to the landed
// ??1W3DTerrainVisualBase@@UAE@XZ (game/GameEngineDevice/Source/W3DDevice/
// GameClient/W3DTerrainVisualBaseDestructor.cpp). Same two-vtable-install
// shape (own vtable at +0, a second base's vtable at +0x218, a string
// member released via releaseBuffer), but this body's second base has a
// real out-of-line destructor (called through ILT thunk 0x00021FC1, whose
// only target 0x00464E20 is the matched S4Owner destructor) instead of a
// plain vtable-constant reset, and the chain finishes with an explicit call
// to GameWindow's own destructor (ILT thunk 0x0002C98F, whose only target
// 0x00479CD0 is the matched protected complete destructor
// ??1GameWindow@@MAE@XZ) rather than a Snapshot-style literal vtable store
// -- GameWindow is this class's primary (offset-0) base.
// Installs vtables 0x010F711C (own) and 0x010F7118 (second base). Symbol
// name taken from the lane brief's pin ??1_bfme_AptGameWindow@@UAE@XZ; real
// field layout beyond the two known offsets (+0x218 second base, +0x24C
// filename string) is unmodelled padding. Both base-dtor names below follow
// the matched constructor's own spelling (game/GameEngine/Source/GameClient/
// GUI/BfmeAptGameWindowConstructor.cpp installs ??_7S4Owner@@6B@ at +0x218
// before overwriting it with the derived view of the same base), so the two
// base-dtor references in the unwind chain resolve to bodies the tree owns.

class GameWindow
{
	// Retail's base destructor here is the PROTECTED GameWindow one, called
	// through ILT 0x0002C98F: ?j_0002c98f@@YAXXZ is the unique-dtor thunk
	// whose target 0x00479CD0 is the matched complete destructor
	// ??1GameWindow@@MAE@XZ (game/GameEngine/Source/GameClient/GUI/
	// GameWindowDestructorThunk.cpp, the only definition of that name).
	// A protected virtual destructor mangles MAE@XZ, so declaring it public
	// would emit ?UAE@XZ and leave the base-dtor call unresolved. The
	// derived destructor may still call it: this is a GameWindow subobject.
protected:
	virtual ~GameWindow();

private:
	unsigned char m_pad[ 0x218 - 4 ];
};

// The second base is S4Owner: retail's base-dtor call goes through ILT
// 0x00021FC1, whose sole target is the matched S4Owner destructor
// ??1S4Owner@@UAE@XZ at 0x00464E20
// (game/GameEngine/Source/Common/S4OwnerDestructor.cpp) - the only
// definition of that mangled name in the tree. The four vector members it
// drains live past this class's modelled padding and are not touched here.
class S4Owner
{
public:
	virtual ~S4Owner();

private:
	unsigned char m_pad[ 0x24C - 0x218 - 4 ];
};

#include "ascii_string.h"

class _bfme_AptGameWindow : public GameWindow, public S4Owner
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	AsciiString m_filenameString;
};

// ??1_bfme_AptGameWindow@@UAE@XZ
_bfme_AptGameWindow::~_bfme_AptGameWindow()
{
}
