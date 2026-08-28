// cl: /DNDEBUG /MD /EHs-c-

// FILE: KeyboardOptionsMenuShutdown.cpp //////////////////////////////////////
//
// KeyboardOptionsMenuShutdown, retail 0x004C9060.
//
// No port of KeyboardOptionsMenu.cpp exists under Code/.  The body is Zero
// Hour's two lines and compiles to thirty bytes.
//
// Six byte-identical copies of these thirty bytes sit in the image -- one per
// menu compiland, since the linker did not fold them -- so the bytes cannot
// say which file this one is.  What does: 0x004C9060 sits 0x230 below
// 0x004C9290 and 0x330 below 0x004C9390, both of which push
// "KeyboardOptionsMenu.wnd:ButtonBack" and "KEYBOARD:Shift+" and so belong to
// that compiland.  The obvious neighbour was wrong and is worth recording:
// DownloadMenuShutdown, the nearest already-landed one, is at 0x004C76F0 and is
// 64 bytes, which is what ruled the obvious neighbour out.
//

// The other four are placed by the same ordering fact, which turned out to be
// exact rather than approximate: in each of these files the Shutdown callback
// sits 0x150 below the Init, and each Init is independently identified by the
// .wnd literal it pushes.
//
//   0x004F03D0 + 0x150 = 0x004F0520  "WOLCustomScoreScreen.wnd:..."
//   0x00504CC0 + 0x150 = 0x00504E10  "WOLMessageWindow.wnd:..."
//   0x00504F70 + 0x150 = 0x005050C0  "WOLQMScoreScreen.wnd:..."
//   0x0050ACC0 + 0x150 = 0x0050AE10  "WOLStatusMenu.wnd:..."
//
// Four for four, and Zero Hour spells all four bodies as the same two lines.
//
// The sixth copy, 0x004FEFE0, has nothing 0x150 above it that pushes a literal,
// and the ordering fact could not place it.  The FunctionLexicon table does:
// retail wires every .wnd callback by name through a (const char *, function,
// 0) triple in .data, and the triple at 0x012A9CC8 names "WOLLocaleSelectShutdown"
// against the ILT thunk at 0x0041500F, which jumps to 0x004FEFE0.  That is the
// binary naming the body itself, not an inference from adjacency.
// WindowLayout::hide is virtual in BFME at vtable slot 0x10 -- the fifth file
// today to say so -- and Shell::shutdownComplete takes a second argument the
// reference does not have; retail passes FALSE.
//
///////////////////////////////////////////////////////////////////////////////

typedef bool Bool;

class WindowLayout;

// Five-slot shim: only the last of these is claimed, and only its offset.
class BfmeVirtualHideLayout
{
public:
	virtual void slot0() = 0;
	virtual void slot4() = 0;
	virtual void slot8() = 0;
	virtual void slotC() = 0;
	virtual void hide( Bool immediate ) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	void shutdownComplete( WindowLayout *layout, Bool impending );
};

extern Shell *TheShell;

void KeyboardOptionsMenuShutdown( WindowLayout *layout, void *userData )
{
		// hide menu
	((BfmeVirtualHideLayout *)layout)->hide( true );

	// our shutdown is complete
	TheShell->shutdownComplete( layout, false );
}

void WOLCustomScoreScreenShutdown( WindowLayout *layout, void *userData )
{
	// hide menu
	((BfmeVirtualHideLayout *)layout)->hide( true );

	// our shutdown is complete
	TheShell->shutdownComplete( layout, false );
}

void WOLMessageWindowShutdown( WindowLayout *layout, void *userData )
{
	// hide menu
	((BfmeVirtualHideLayout *)layout)->hide( true );

	// our shutdown is complete
	TheShell->shutdownComplete( layout, false );
}

void WOLQMScoreScreenShutdown( WindowLayout *layout, void *userData )
{
	// hide menu
	((BfmeVirtualHideLayout *)layout)->hide( true );

	// our shutdown is complete
	TheShell->shutdownComplete( layout, false );
}

void WOLLocaleSelectShutdown( WindowLayout *layout, void *userData )
{
	// hide menu
	((BfmeVirtualHideLayout *)layout)->hide( true );

	// our shutdown is complete
	TheShell->shutdownComplete( layout, false );
}

void WOLStatusMenuShutdown( WindowLayout *layout, void *userData )
{
	// hide menu
	((BfmeVirtualHideLayout *)layout)->hide( true );

	// our shutdown is complete
	TheShell->shutdownComplete( layout, false );
}
