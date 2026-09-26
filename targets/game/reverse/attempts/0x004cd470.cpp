// ?d_004cd470@@YAXXZ
// partial score=0.87 date=2026-09-22
// EXTRACTED STASH: this is a fragment of the full TU
// Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanGameOptionsMenu.cpp
// (too large to stash whole -- 67KB). Contains ONLY the added facade class,
// macros, and the replacement LanGameOptionsMenuUpdate body for retail
// 0x004CD470; a future attempt must re-apply this into the full file,
// replacing the original two-line ZH-stub LanGameOptionsMenuUpdate.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc (matches the file's own flags)
// Open-BFME5: partial score~0.87 date=2026-09-22, retail 0x004CD470.
// BFME un-comments ZH's "TheLAN->update();" and adds an auto-fill countdown
// after it -- four more LANAPIInterface vtable slots this file has not
// named elsewhere (0x38, 0xb8 [called twice], 0xc0, 0xcc), spelled as a
// TU-local facade like BfmeVirtualLanApi above. The window whose status is
// tested at retail 0x012F3C08 has no proven name from this body alone.
// Shape: if no slot is open (0xcc && 0xb8[1st] && window && status&8, then
// scanning game->getSlot(1..7)->isOpen() finds none), call the still-dump
// carved neighbour at 0x004CC980 (thunk 0x00040af7) with 0; either way,
// falling through to a SECOND 0xb8 check, then getenv("_EA_RTS_HEADLESS")
// or TheWritableGlobalData+0xb88 gates a frame counter at 0x012F3D44 that
// triggers vtable slot 0x38 once it exceeds 30 (a headless/auto-start
// fallback timer) and resets to 0. Byte-exact in size (296B) and control
// flow (every branch target and the double bounds-check on the loop
// counter, docs/shape_levers.md's SIB-family redundant-check shape,
// reproduce retail's); 38 non-reloc bytes remain, ALL a single stable
// eax<->ecx register-choice residue around the this+0x012F3C08 window
// pointer and its winGetStatus() call (shape_search over 9 trials/register
// family levers found no alternative shape); tried a named local, a
// hoisted fetch, and different && groupings, none changed it.
class Rva004CD470VirtualLan
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00C() = 0;
	virtual void slot010() = 0;
	virtual void update() = 0;
	virtual void slot018() = 0;
	virtual void slot01C() = 0;
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02C() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038Call() = 0;
	virtual void slot03C() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual void slot04C() = 0;
	virtual void slot050() = 0;
	virtual void slot054() = 0;
	virtual void slot058() = 0;
	virtual void slot05C() = 0;
	virtual void slot060() = 0;
	virtual void slot064() = 0;
	virtual void slot068() = 0;
	virtual void slot06C() = 0;
	virtual void slot070() = 0;
	virtual void slot074() = 0;
	virtual void slot078() = 0;
	virtual void slot07C() = 0;
	virtual void slot080() = 0;
	virtual void slot084() = 0;
	virtual void slot088() = 0;
	virtual void slot08C() = 0;
	virtual void slot090() = 0;
	virtual void slot094() = 0;
	virtual void slot098() = 0;
	virtual void slot09C() = 0;
	virtual void slot0A0() = 0;
	virtual void slot0A4() = 0;
	virtual void slot0A8() = 0;
	virtual void slot0AC() = 0;
	virtual void slot0B0() = 0;
	virtual void slot0B4() = 0;
	virtual Bool slot0B8Call() = 0;
	virtual void slot0BC() = 0;
	virtual GameInfo *slot0C0Call() = 0;
	virtual void slot0C4() = 0;
	virtual void slot0C8() = 0;
	virtual Bool slot0CCCall() = 0;
};

#define g_rva012F3C08Window (*(GameWindow **)0x012F3C08)
#define g_rva012F3D44Counter (*(UnsignedInt *)0x012F3D44)

extern "C" __declspec(dllimport) char *getenv(const char *name);

// the opaque helper this file's own resetLanSession/carved neighbours reach
// through the same ILT thunk; the served body at 0x004CC980 is still a dump
extern void j_00040af7();

//-------------------------------------------------------------------------------------------------
/** Lan Game Options menu update method */
//-------------------------------------------------------------------------------------------------
void LanGameOptionsMenuUpdate( WindowLayout * layout, void *userData)
{
	if(LANisShuttingDown && TheShell->isAnimFinished() && TheTransitionHandler->isFinished())
		shutdownCompleteLanGameOptionsMenu(layout);

	((Rva004CD470VirtualLan *)TheLAN)->update();

	if (LANbuttonPushed)
		return;

	if (((Rva004CD470VirtualLan *)TheLAN)->slot0CCCall() &&
		((Rva004CD470VirtualLan *)TheLAN)->slot0B8Call() &&
		g_rva012F3C08Window &&
		g_rva012F3C08Window->winGetStatus() & 8)
	{
		GameInfo *game = ((Rva004CD470VirtualLan *)TheLAN)->slot0C0Call();
		if (game)
		{
			int i;
			for (i = 1; i < 8; ++i)
			{
				GameSlot *slot = game->getSlot(i);
				if (slot && slot->isOpen())
					break;
			}

			if (i != 8)
				goto secondCheck;

			typedef void (__cdecl *Rva004CD470Opaque40AF7)(int);
			((Rva004CD470Opaque40AF7)::j_00040af7)(0);
		}
