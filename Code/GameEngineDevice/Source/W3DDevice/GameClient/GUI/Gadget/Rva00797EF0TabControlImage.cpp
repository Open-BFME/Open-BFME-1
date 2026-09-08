// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME ABI reconstruction of the image-backed tab-control draw callback at
// retail RVA 0x00797EF0.  The tab-data offsets and the callback dispatch are
// the BFME layouts; no generated body is included here.

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

	const Image *winGetEnabledImage( Int index )
	{
		return m_enabledDrawData[ index ].image;
	}
	const Image *winGetDisabledImage( Int index )
	{
		return m_disabledDrawData[ index ].image;
	}
	const Image *winGetHiliteImage( Int index )
	{
		return m_hiliteDrawData[ index ].image;
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
		dispatch->m_draw( window, instData );
	else
		dispatch->m_drawSub.draw( window, instData );
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
	virtual void winDrawImage( const Image *image, Int startX, Int startY,
		Int endX, Int endY, Color color = 0xFFFFFFFF );
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
	TP_TOP_SIDE = 3,
	TP_BOTTOM_SIDE = 6,
	WIN_STATUS_BORDER = 0x00001000,
	WIN_STATUS_SEE_THRU = 0x00010000
};

#define BFME_DRAW_TAB_IMAGE( NUMBER, INDEX ) \
	if( tabData->tabCount >= NUMBER ) \
	{ \
		if( tabData->subPaneDisabled[ INDEX ] ) \
			image = tabControl->winGetDisabledImage( INDEX + 1 ); \
		else if( tabData->activeTab == INDEX ) \
			image = tabControl->winGetHiliteImage( INDEX + 1 ); \
		else \
			image = tabControl->winGetEnabledImage( INDEX + 1 ); \
		if( image != 0 ) \
			TheWindowManager->winDrawImage( image, tabX, tabY, \
				tabX + tabWidth, tabY + tabHeight, -1 ); \
	} \
	tabX += tabDeltaX; \
	tabY += tabDeltaY;

void W3DGadgetTabControlImageDraw( GameWindow *tabControl,
		WinInstanceData *instData )
{
	ICoord2D origin, size;
	tabControl->winGetScreenPosition( &origin.x, &origin.y );
	tabControl->winGetSize( &size.x, &size.y );
	(void)size;

	bfmeTabControlDefaultDraw( tabControl, instData );
	if( ( tabControl->winGetStatus() & WIN_STATUS_BORDER ) != 0 &&
		( tabControl->winGetStatus() & WIN_STATUS_SEE_THRU ) == 0 )
		tabControl->winDrawBorder();

	TabControlData *tabData = (TabControlData *)tabControl->winGetUserData();
	Int tabX = origin.x + tabData->tabsLeftLimit;
	Int tabY = origin.y + tabData->tabsTopLimit;
	Int tabWidth = tabData->tabWidth;
	Int tabHeight = tabData->tabHeight;
	Int tabDeltaX;
	Int tabDeltaY;
	if( tabData->tabEdge == TP_TOP_SIDE || tabData->tabEdge == TP_BOTTOM_SIDE )
	{
		tabDeltaX = tabWidth;
		tabDeltaY = 0;
	}
	else
	{
		tabDeltaX = 0;
		tabDeltaY = tabHeight;
	}

	const Image *image = 0;
	BFME_DRAW_TAB_IMAGE( 1, 0 )
	BFME_DRAW_TAB_IMAGE( 2, 1 )
	BFME_DRAW_TAB_IMAGE( 3, 2 )
	BFME_DRAW_TAB_IMAGE( 4, 3 )
	BFME_DRAW_TAB_IMAGE( 5, 4 )
	BFME_DRAW_TAB_IMAGE( 6, 5 )
	BFME_DRAW_TAB_IMAGE( 7, 6 )
	BFME_DRAW_TAB_IMAGE( 8, 7 )
}
