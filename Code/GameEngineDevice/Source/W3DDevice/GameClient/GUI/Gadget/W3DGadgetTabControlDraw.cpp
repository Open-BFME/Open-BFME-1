// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: BFME ABI slice for the retail W3DGadgetTabControlDraw body.
//
// The vendored ZH GameWindow header is four bytes short before m_instData.
// This callback therefore uses a TU-local window view whose draw-data arrays
// begin at the BFME offsets (+0x48, +0xB4 and +0x120).  The callback also
// contains the BFME default-draw dispatch at +0x1E8/+0x218; calling the ZH
// W3DGameWinDefaultDraw would produce a call and the wrong frame instead.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;
typedef float Real;
typedef int Color;

class Image;
class GameWindow;
class WinInstanceData;

struct ICoord2D
{
	Int x;
	Int y;
};

struct BfmeWinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

class GameWindow
{
public:
	Int winGetScreenPosition( Int *x, Int *y );
	Int winGetSize( Int *width, Int *height );
	UnsignedInt winGetStatus( void );
	void winDrawBorder( void );
	void *winGetUserData( void );

	Color winGetEnabledColor( Int index )
	{
		return m_enabledDrawData[ index ].color;
	}
	Color winGetEnabledBorderColor( Int index )
	{
		return m_enabledDrawData[ index ].borderColor;
	}
	Color winGetDisabledColor( Int index )
	{
		return m_disabledDrawData[ index ].color;
	}
	Color winGetDisabledBorderColor( Int index )
	{
		return m_disabledDrawData[ index ].borderColor;
	}
	Color winGetHiliteColor( Int index )
	{
		return m_hiliteDrawData[ index ].color;
	}
	Color winGetHiliteBorderColor( Int index )
	{
		return m_hiliteDrawData[ index ].borderColor;
	}

private:
	unsigned char m_unreconstructed_00[ 0x48 ];
	BfmeWinDrawData m_enabledDrawData[ 9 ];
	BfmeWinDrawData m_disabledDrawData[ 9 ];
	BfmeWinDrawData m_hiliteDrawData[ 9 ];
};

class BfmeGameWindowDrawSub
{
public:
	virtual void unused( void );
	virtual void draw( GameWindow *window, WinInstanceData *instData );
};

typedef void (__cdecl *BfmeGameWinDrawFunc)( GameWindow *, WinInstanceData * );

class BfmeGameWindowDispatch
{
public:
	unsigned char m_unreconstructed_00[ 0x1e8 ];
	BfmeGameWinDrawFunc m_draw;
	unsigned char m_unreconstructed_1ec[ 0x218 - 0x1ec ];
	BfmeGameWindowDrawSub m_drawSub;
};

static inline void bfmeTabControlDefaultDraw( GameWindow *window,
		WinInstanceData *instData )
{
	BfmeGameWindowDispatch *dispatch = (BfmeGameWindowDispatch *)window;

	if( dispatch->m_draw )
	{
		dispatch->m_draw( window, instData );
	}
	else
	{
		dispatch->m_drawSub.draw( window, instData );
	}
}

class GameWindowManager
{
public:
	virtual void unused00( void );
	virtual void unused01( void );
	virtual void unused02( void );
	virtual void unused03( void );
	virtual void unused04( void );
	virtual void unused05( void );
	virtual void unused06( void );
	virtual void unused07( void );
	virtual void unused08( void );
	virtual void unused09( void );
	virtual void unused10( void );
	virtual void unused11( void );
	virtual void unused12( void );
	virtual void unused13( void );
	virtual void unused14( void );
	virtual void unused15( void );
	virtual void unused16( void );
	virtual void unused17( void );
	virtual void unused18( void );
	virtual void unused19( void );
	virtual void unused20( void );
	virtual void unused21( void );
	virtual void unused22( void );
	virtual void unused23( void );
	virtual void unused24( void );
	virtual void unused25( void );
	virtual void unused26( void );
	virtual void unused27( void );
	virtual void unused28( void );
	virtual void unused29( void );
	virtual void unused30( void );
	virtual void unused31( void );
	virtual void unused32( void );
	virtual void unused33( void );
	virtual void unused34( void );
	virtual void unused35( void );
	virtual void unused36( void );
	virtual void unused37( void );
	virtual void unused38( void );
	virtual void unused39( void );
	virtual void unused40( void );
	virtual void unused41( void );
	virtual void unused42( void );
	virtual void unused43( void );
	virtual void unused44( void );
	virtual void unused45( void );
	virtual void unused46( void );
	virtual void unused47( void );
	virtual void unused48( void );
	virtual void unused49( void );
	virtual void unused50( void );
	virtual void unused51( void );
	virtual void unused52( void );
	virtual void unused53( void );
	virtual void unused54( void );
	virtual void unused55( void );
	virtual void unused56( void );
	virtual void unused57( void );
	virtual void unused58( void );
	virtual void unused59( void );
	virtual void unused60( void );
	virtual void unused61( void );
	virtual void winFillRect( Color color, Real width, Int startX, Int startY,
		Int endX, Int endY );
	virtual void winOpenRect( Color color, Real width, Int startX, Int startY,
		Int endX, Int endY );
};

extern GameWindowManager *TheWindowManager;

struct TabControlData
{
	Int tabOrientation;
	Int tabEdge;
	Int tabWidth;
	Int tabHeight;
	Int tabCount;
	GameWindow *subPanes[ 8 ];
	Bool subPaneDisabled[ 8 ];
	Int paneBorder;
	Int activeTab;
	Int tabsLeftLimit;
	Int tabsRightLimit;
	Int tabsTopLimit;
	Int tabsBottomLimit;
};

enum
{
	WIN_STATUS_BORDER = 0x00001000,
	WIN_STATUS_SEE_THRU = 0x00010000,
	WIN_COLOR_UNDEFINED = 0x00ffffff,
	TP_TOP_SIDE = 3,
	TP_BOTTOM_SIDE = 6
};

inline Int BitTest( UnsignedInt bits, UnsignedInt mask )
{
	return ( bits & mask ) != 0;
}

#define WIN_DRAW_LINE_WIDTH 1.0f

#define BFME_DRAW_TAB( NUMBER, INDEX ) \
	if( tabData->tabCount >= NUMBER ) \
	{ \
		if( tabData->subPaneDisabled[ INDEX ] ) \
		{ \
			color = tabControl->winGetDisabledColor( NUMBER ); \
			border = tabControl->winGetDisabledBorderColor( NUMBER ); \
		} \
		else if( tabData->activeTab == INDEX ) \
		{ \
			color = tabControl->winGetHiliteColor( NUMBER ); \
			border = tabControl->winGetHiliteBorderColor( NUMBER ); \
		} \
		else \
		{ \
			color = tabControl->winGetEnabledColor( NUMBER ); \
			border = tabControl->winGetEnabledBorderColor( NUMBER ); \
		} \
		if( border != WIN_COLOR_UNDEFINED ) \
		{ \
			TheWindowManager->winOpenRect( border, WIN_DRAW_LINE_WIDTH, \
				tabX, tabY, tabX + tabWidth, tabY + tabHeight ); \
		} \
		if( color != WIN_COLOR_UNDEFINED ) \
		{ \
			TheWindowManager->winFillRect( color, WIN_DRAW_LINE_WIDTH, \
				tabX + 1, tabY + 1, tabX + tabWidth - 1, tabY + tabHeight - 1 ); \
		} \
	} \
	tabX += tabDeltaX; \
	tabY += tabDeltaY;

// ?W3DGadgetTabControlDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
void W3DGadgetTabControlDraw( GameWindow *tabControl,
	WinInstanceData *instData )
{
	ICoord2D origin, size;

	tabControl->winGetScreenPosition( &origin.x, &origin.y );
	tabControl->winGetSize( &size.x, &size.y );

	bfmeTabControlDefaultDraw( tabControl, instData );

	if( BitTest( tabControl->winGetStatus(), WIN_STATUS_BORDER ) == 1 &&
		!BitTest( tabControl->winGetStatus(), WIN_STATUS_SEE_THRU ) )
	{
		tabControl->winDrawBorder();
	}

	TabControlData *tabData = (TabControlData *)tabControl->winGetUserData();

	Int tabX, tabY, tabWidth, tabHeight, tabDeltaX, tabDeltaY;
	tabX = origin.x + tabData->tabsLeftLimit;
	tabY = origin.y + tabData->tabsTopLimit;
	tabWidth = tabData->tabWidth;
	tabHeight = tabData->tabHeight;
	if( ( tabData->tabEdge == TP_TOP_SIDE ) ||
		( tabData->tabEdge == TP_BOTTOM_SIDE ) )
	{
		tabDeltaX = tabWidth;
		tabDeltaY = 0;
	}
	else
	{
		tabDeltaX = 0;
		tabDeltaY = tabHeight;
	}

	Color color, border;

	BFME_DRAW_TAB( 1, 0 )
	BFME_DRAW_TAB( 2, 1 )
	BFME_DRAW_TAB( 3, 2 )
	BFME_DRAW_TAB( 4, 3 )
	BFME_DRAW_TAB( 5, 4 )
	BFME_DRAW_TAB( 6, 5 )
	BFME_DRAW_TAB( 7, 6 )
	BFME_DRAW_TAB( 8, 7 )
}

#undef BFME_DRAW_TAB
