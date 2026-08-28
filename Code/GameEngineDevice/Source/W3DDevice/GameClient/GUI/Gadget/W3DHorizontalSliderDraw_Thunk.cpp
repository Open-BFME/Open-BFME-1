// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// W3DGadgetHorizontalSliderDraw, retail 0x00790D80 (227 bytes).
//
// Zero Hour's W3DHorizontalSlider.cpp body verbatim; the only thing that ever
// blocked it was layout.  BFME's WinInstanceData is four bytes longer than the vendored
// one, so the three GameWindow draw-data arrays sit at +0x48 (enabled),
// +0xB4 (disabled) and +0x120 (hilite) with twelve-byte entries
// { image, color, borderColor } -- retail reads [win+0x4C]/[win+0x50],
// [win+0xB8]/[win+0xBC] and [win+0x124]/[win+0x128], which pins all three
// bases and the entry stride at once.  The GadgetSliderGet*Color helpers are
// header inlines over index 0, which is why retail reads them directly.
//
// Local ABI-slice replica so no shared header moves.
//
// The one shape note: in the filled-back block the origin+1 value must reach
// the addition as a TEMPORARY, not as a re-read of start.x.  MSVC 7.1 picks the
// lea's SIB base from that distinction -- `end.x = start.x + size.x - 2' over a
// stored-then-re-read start.x compiles to lea esi,[ecx+eax-2] (size as base),
// while retail is lea esi,[eax+ecx-2] (start as base), which is what the
// temporary produces.  Source operand order, parenthesisation, re-association
// and statement order are all canonicalised away and do not reach it; this is
// the only lever.  end.y matches either way, which is what made the asymmetry
// look like allocation noise rather than a source-level fact.  Same fix as
// IMECandidateMainDraw 0x004C4AB0.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef int Color;

class Image;

enum { WIN_STATUS_ENABLED = 0x00000008 };
enum { WIN_STATE_HILITED = 0x00000002 };
enum { WIN_COLOR_UNDEFINED = 0x00FFFFFF };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
struct WinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	UnsignedInt getState(void) const { return m_state; }

private:
	unsigned char m_unreconstructed_00[0x08];
	UnsignedInt m_state;								///< retail this+0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);			///< ILT thunk at 0x0002F94B
	Int winGetSize(Int *width, Int *height);			///< ILT thunk at 0x00036EBC
	UnsignedInt winGetStatus(void);						///< ILT thunk at 0x00023DDA

	Color winGetEnabledColor(Int index) { return m_enabledDrawData[index].color; }
	Color winGetEnabledBorderColor(Int index) { return m_enabledDrawData[index].borderColor; }
	Color winGetDisabledColor(Int index) { return m_disabledDrawData[index].color; }
	Color winGetDisabledBorderColor(Int index) { return m_disabledDrawData[index].borderColor; }
	Color winGetHiliteColor(Int index) { return m_hiliteDrawData[index].color; }
	Color winGetHiliteBorderColor(Int index) { return m_hiliteDrawData[index].borderColor; }

private:
	unsigned char m_unreconstructed_00[0x48];
	WinDrawData m_enabledDrawData[9];					///< retail this+0x48
	WinDrawData m_disabledDrawData[9];					///< retail this+0xB4
	WinDrawData m_hiliteDrawData[9];					///< retail this+0x120
};

// Only the two rect calls are reconstructed; the slots ahead of them place them.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();
	virtual void unused55();
	virtual void unused56();
	virtual void unused57();
	virtual void unused58();
	virtual void unused59();
	virtual void unused60();
	virtual void unused61();

	virtual void winFillRect(Color color, Real width,
													 Int startX, Int startY,
													 Int endX, Int endY);		///< vtable +0xF8
	virtual void winOpenRect(Color color, Real width,
													 Int startX, Int startY,
													 Int endX, Int endY);		///< vtable +0xFC
};

extern GameWindowManager *TheWindowManager;				///< retail [0x012F1B40]

inline Int BitTest(UnsignedInt bits, UnsignedInt mask) { return (bits & mask) != 0; }


#define WIN_DRAW_LINE_WIDTH 1.0f

// GadgetSlider.h header inlines, all over draw-data index 0.
inline Color GadgetSliderGetEnabledColor( GameWindow *g ) { return g->winGetEnabledColor( 0 ); }
inline Color GadgetSliderGetEnabledBorderColor( GameWindow *g ) { return g->winGetEnabledBorderColor( 0 ); }
inline Color GadgetSliderGetDisabledColor( GameWindow *g ) { return g->winGetDisabledColor( 0 ); }
inline Color GadgetSliderGetDisabledBorderColor( GameWindow *g ) { return g->winGetDisabledBorderColor( 0 ); }
inline Color GadgetSliderGetHiliteColor( GameWindow *g ) { return g->winGetHiliteColor( 0 ); }
inline Color GadgetSliderGetHiliteBorderColor( GameWindow *g ) { return g->winGetHiliteBorderColor( 0 ); }

// ?W3DGadgetHorizontalSliderDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
void W3DGadgetHorizontalSliderDraw( GameWindow *window, WinInstanceData *instData )
{
	Color backBorder, backColor;
	ICoord2D origin, size, start, end;

	// get screen position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get the right colors
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == 0 )
	{

		backBorder		= GadgetSliderGetDisabledBorderColor( window );
		backColor			= GadgetSliderGetDisabledColor( window );

	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		backBorder		= GadgetSliderGetHiliteBorderColor( window );
		backColor			= GadgetSliderGetHiliteColor( window );

	}  // end else if, hilited
	else
	{

		backBorder		= GadgetSliderGetEnabledBorderColor( window );
		backColor			= GadgetSliderGetEnabledColor( window );

	}  // end else, enabled

	// draw background border and rect over whole control
	if( backBorder != WIN_COLOR_UNDEFINED )
	{

		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect( backBorder, WIN_DRAW_LINE_WIDTH,
																	 start.x, start.y, end.x, end.y );

	}  // end if
	if( backColor != WIN_COLOR_UNDEFINED )
	{

		Int sx = origin.x + 1, sy = origin.y + 1;
		start.x = sx;
		start.y = sy;
		end.x = sx + size.x - 2;
		end.y = sy + size.y - 2;
		TheWindowManager->winFillRect( backColor, WIN_DRAW_LINE_WIDTH,
																	 start.x, start.y, end.x, end.y );

	}  // end if

}  // end W3DGadgetHorizontalSliderDraw
