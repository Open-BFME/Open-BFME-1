// ?winProcessMouseEvent@GameWindowManager@@UAE?AW4WinInputReturnCode@@W4GameWindowMessage@@PAUICoord2D@@PAX@Z
// partial score=0.3 date=2026-09-26
// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/gamewindowlist /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// BFME GameWindow layout and virtual tooltip slots.
#include "PreRTS.h"
#include "GameClient/Mouse.h"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef int Int;
typedef float Real;
typedef bool Bool;

class DisplayString {
public:
  virtual ~DisplayString() = 0;
  virtual void setText(UnicodeString) = 0;
  virtual UnicodeString getText() = 0;
  virtual Int getTextLength() = 0;
};

enum WinInputReturnCode { WIN_INPUT_NOT_USED = 0, WIN_INPUT_USED = 1 };
enum WindowMsgHandledType { MSG_IGNORED = 0, MSG_HANDLED = 1 };
enum GameWindowMessage {
  GWM_NONE = 0, GWM_CREATE, GWM_DESTROY, GWM_ACTIVATE, GWM_ENABLE,
  GWM_LEFT_DOWN, GWM_LEFT_UP, GWM_LEFT_DOUBLE, GWM_LEFT_DRAG,
  GWM_MIDDLE_DOWN, GWM_MIDDLE_UP, GWM_MIDDLE_DOUBLE, GWM_MIDDLE_DRAG,
  GWM_RIGHT_DOWN, GWM_RIGHT_UP, GWM_RIGHT_DOUBLE, GWM_RIGHT_DRAG,
  GWM_MOUSE_ENTERING, GWM_MOUSE_LEAVING, GWM_MOUSE_WHEEL_UP,
  GWM_MOUSE_WHEEL_DOWN, GWM_CHAR, GWM_SCRIPT_CREATE, GWM_INPUT_FOCUS,
  GWM_MOUSE_POS, GWM_IME_CHAR, GWM_IME_STRING
};

enum {
  WIN_STATUS_ACTIVE = 0x00000001,
  WIN_STATUS_TOGGLE = 0x00000002,
  WIN_STATUS_DRAGABLE = 0x00000004,
  WIN_STATUS_ENABLED = 0x00000008,
  WIN_STATUS_HIDDEN = 0x00000010,
  WIN_STATUS_ABOVE = 0x00000020,
  WIN_STATUS_BELOW = 0x00000040,
  WIN_STATUS_NO_INPUT = 0x00000200,
  GWS_COMBO_BOX = 0x00008000
};

class GameWindow;

class WinInstanceData {
public:
  UnsignedInt m_id;
  UnsignedInt m_state;
  UnsignedInt m_style;
  UnsignedInt m_status;
  void *m_owner;
  UnsignedByte m_padding[0x184];
  Int m_tooltipDelay;
  DisplayString *m_text;
  DisplayString *m_tooltip;
  UnsignedByte m_tail[8];

  UnsignedInt getStyle() const { return m_style; }
  Int getTooltipTextLength() const {
    return m_tooltip ? m_tooltip->getTextLength() : 0;
  }
  UnicodeString getTooltipText() const;
};

class TooltipProxy {
public:
  operator Bool() const;
  void operator()(GameWindow *, WinInstanceData *, UnsignedInt) const;
};

class GameWindow {
public:
  virtual void v00() = 0;
  virtual void v01() = 0;
  virtual void v02() = 0;
  virtual void v03() = 0;
  virtual void invokeTooltip(WinInstanceData *, UnsignedInt) = 0;
  virtual void v05() = 0;
  virtual void v06() = 0;
  virtual void v07() = 0;
  virtual void v08() = 0;
  virtual Bool hasTooltip() = 0;

  UnsignedInt m_bfmeAnchor;
  UnsignedInt m_status;
  ICoord2D m_size;
  IRegion2D m_region;
  Int m_cursorX;
  Int m_cursorY;
  void *m_userData;
  WinInstanceData m_instData;
  void *m_inputData;
  void *m_bfmeInputExtra;
  void *m_input;
  void *m_extra;
  void *m_inputCallback;
  void *m_systemCallback;
  void *m_drawCallback;
  TooltipProxy m_tooltip;
  void *m_callbackExtra;
  UnsignedInt m_callbackExtra2;
  GameWindow *m_next;
  GameWindow *m_prev;
  GameWindow *m_parent;
  GameWindow *m_child;

  GameWindow *winPointInChild(Int, Int, Bool = FALSE, Bool = FALSE);
  GameWindow *winPointInAnyChild(Int, Int, Bool, Bool = FALSE);
  Bool winPointInWindow(Int, Int);
  GameWindow *winGetParent();
  Bool winIsChild(GameWindow *);
  Int winGetPosition(Int *, Int *);
  Int winGetSize(Int *, Int *);
  Int winSetPosition(Int, Int);
  WinInstanceData *winGetInstanceData();
};

static GameWindow *tooltipOwner(const TooltipProxy *proxy) {
  return (GameWindow *)((UnsignedByte *)proxy - 0x1ec);
}

TooltipProxy::operator Bool() const { return tooltipOwner(this)->hasTooltip(); }
void TooltipProxy::operator()(GameWindow *, WinInstanceData *data, UnsignedInt coords) const {
  tooltipOwner(this)->invokeTooltip(data, coords);
}

class ModalWindow {
public:
  virtual ~ModalWindow() = 0;
  GameWindow *window;
};

class Display {
public:
  virtual void d00() = 0; virtual void d01() = 0; virtual void d02() = 0;
  virtual void d03() = 0; virtual void d04() = 0; virtual void d05() = 0;
  virtual void d06() = 0; virtual void d07() = 0; virtual void d08() = 0;
  virtual void d09() = 0; virtual void d10() = 0;
  virtual Int getWidth();
  virtual Int getHeight();
};
extern Display *TheDisplay;

#define DECL_MANAGER_SLOT(n) virtual void slot##n();
class GameWindowManager {
public:
  DECL_MANAGER_SLOT(00) DECL_MANAGER_SLOT(01) DECL_MANAGER_SLOT(02)
  DECL_MANAGER_SLOT(03) DECL_MANAGER_SLOT(04) DECL_MANAGER_SLOT(05)
  DECL_MANAGER_SLOT(06) DECL_MANAGER_SLOT(07) DECL_MANAGER_SLOT(08)
  DECL_MANAGER_SLOT(09) DECL_MANAGER_SLOT(10) DECL_MANAGER_SLOT(11)
  DECL_MANAGER_SLOT(12) DECL_MANAGER_SLOT(13) DECL_MANAGER_SLOT(14)
  DECL_MANAGER_SLOT(15) DECL_MANAGER_SLOT(16) DECL_MANAGER_SLOT(17)
  DECL_MANAGER_SLOT(18) DECL_MANAGER_SLOT(19) DECL_MANAGER_SLOT(20)
  DECL_MANAGER_SLOT(21) DECL_MANAGER_SLOT(22) DECL_MANAGER_SLOT(23)
  DECL_MANAGER_SLOT(24) DECL_MANAGER_SLOT(25) DECL_MANAGER_SLOT(26)
  DECL_MANAGER_SLOT(27) DECL_MANAGER_SLOT(28) DECL_MANAGER_SLOT(29)
  DECL_MANAGER_SLOT(30) DECL_MANAGER_SLOT(31) DECL_MANAGER_SLOT(32)
  DECL_MANAGER_SLOT(33) DECL_MANAGER_SLOT(34) DECL_MANAGER_SLOT(35)
  DECL_MANAGER_SLOT(36) DECL_MANAGER_SLOT(37) DECL_MANAGER_SLOT(38)
  DECL_MANAGER_SLOT(39) DECL_MANAGER_SLOT(40)
  virtual WinInputReturnCode winProcessMouseEvent(GameWindowMessage, ICoord2D *, void *);
  DECL_MANAGER_SLOT(42)
  virtual GameWindow *winGetFocus();
  virtual void winSetFocus(GameWindow *);
  virtual void winSetGrabWindow(GameWindow *);
  virtual GameWindow *winGetGrabWindow();
  virtual void winSetLoneWindow(GameWindow *);
  DECL_MANAGER_SLOT(48)
  DECL_MANAGER_SLOT(49)
  virtual Bool isHidden(GameWindow *);
  DECL_MANAGER_SLOT(51)
  DECL_MANAGER_SLOT(52)
  virtual WindowMsgHandledType winSendSystemMsg(GameWindow *, UnsignedInt, UnsignedInt, UnsignedInt);
  virtual WindowMsgHandledType winSendInputMsg(GameWindow *, UnsignedInt, UnsignedInt, UnsignedInt);

  UnsignedByte m_base[4];
  GameWindow *m_windowList;
  GameWindow *m_windowTail;
  GameWindow *m_destroyList;
  GameWindow *m_currMouseRgn;
  GameWindow *m_mouseCaptor;
  GameWindow *m_keyboardFocus;
  ModalWindow *m_modalHead;
  GameWindow *m_grabWindow;
  GameWindow *m_loneWindow;
  UnsignedByte m_tail[8];
  void *m_cursorBitmap;
  UnsignedInt m_captureFlags;
};
#undef DECL_MANAGER_SLOT

#define SHORTTOLONG(a, b) ((Int)(((UnsignedShort)(a) << 16) | (UnsignedShort)(b)))
static Bool sendMousePosMessages = TRUE;

// ?winProcessMouseEvent@GameWindowManager@@UAE?AW4WinInputReturnCode@@W4GameWindowMessage@@PAUICoord2D@@PAX@Z
// partial score=0.52 date=2026-09-10
WinInputReturnCode GameWindowManager::winProcessMouseEvent( GameWindowMessage msg,
																														ICoord2D *mousePos,
																														void *data )
{
	WinInputReturnCode returnCode = WIN_INPUT_NOT_USED;
	Bool objectTooltip = FALSE;
	UnsignedInt packedMouseCoords;
	GameWindow *window = NULL;
	GameWindow *toolTipWindow = NULL;
	GameWindow *childWindow;
	Int dx, dy;
	Bool clearGrabWindow = FALSE;

	// pack mouse coords into one entity for message passing
	packedMouseCoords = SHORTTOLONG( mousePos->y, mousePos->x );

	// clear tooltip ... it will be reset if necessary
	TheMouse->setCursorTooltip( UnicodeString::TheEmptyString );

	// Check for mouse capture
	if( m_mouseCaptor )
	{

		// no window grabbed as of yet
		m_grabWindow = NULL;

		// what what window within the captured window are we in
		window = m_mouseCaptor->winPointInChild( mousePos->x, mousePos->y );

		//
		// send buttons, drags, wheels to the windows, we don't continually
		// send mouse positions
		//
		if( sendMousePosMessages == TRUE || msg != GWM_MOUSE_POS )
		{
			GameWindow *win = window;

			if( win )
			{
				while( win != NULL )
				{

					if( winSendInputMsg( win, msg, packedMouseCoords, 0 ) == MSG_HANDLED )
					{

						// if used clear the event
						returnCode = WIN_INPUT_USED;
						break;

					}

					// if we just tested mouseCaptor don't go any higher in the chain
					if( win == m_mouseCaptor )
						break;

					win = win->winGetParent();

				}  // end while

			}  // end if
			else
			{

				// if used clear the event
				if(	winSendInputMsg( m_mouseCaptor, msg, packedMouseCoords, 0 ) == MSG_HANDLED )
					returnCode = WIN_INPUT_USED;

			}  // end else

		}  // end if

	}  // end if, mouse captor window present
	else
	{

		if( m_grabWindow )
		{
			GameWindow *parent;

			switch( msg )
			{

				// --------------------------------------------------------------------
				case GWM_LEFT_UP:
				{
					//Play a beep sound if the window is disabled.
					m_grabWindow->winPointInChild( mousePos->x, mousePos->y, FALSE, TRUE );

					BitClear( m_grabWindow->m_status, WIN_STATUS_ACTIVE );
					if( m_grabWindow->winPointInWindow( mousePos->x, mousePos->y ) )
						winSendInputMsg( m_grabWindow, GWM_LEFT_UP, packedMouseCoords, 0 );
					else if( BitTest( m_grabWindow->m_status, WIN_STATUS_DRAGABLE ))
					{
						winSendInputMsg( m_grabWindow, GWM_LEFT_UP, packedMouseCoords, 0 );
					}

					clearGrabWindow = TRUE;
					break;

				}  // end left up

				// --------------------------------------------------------------------
				case MOUSE_EVENT_NONE:
				case GWM_LEFT_DRAG:
				{

					if( BitTest( m_grabWindow->m_status, WIN_STATUS_DRAGABLE ) )
					{
						ICoord2D *mouseDelta = (ICoord2D *)data;
						dx = mouseDelta->x;
						dy = mouseDelta->y;

						// Clip window to parent
						if( m_grabWindow->winGetParent() )
						{

							parent = m_grabWindow->winGetParent();

							if( m_grabWindow->m_region.lo.x + dx < 0 )
								dx = 0 - m_grabWindow->m_region.lo.x;
							else if( m_grabWindow->m_region.hi.x + dx > parent->m_size.x )
								dx = parent->m_size.x - m_grabWindow->m_region.hi.x;

							if( m_grabWindow->m_region.lo.y + dy < 0 )
								dy = 0 - m_grabWindow->m_region.lo.y;
							else if( m_grabWindow->m_region.hi.y + dy > parent->m_size.y )
								dy = parent->m_size.y - m_grabWindow->m_region.hi.y;
						}

						// Move the window, but keep it completely visible within screen boundaries
						IRegion2D newRegion;
						ICoord2D grabSize;

						m_grabWindow->winGetPosition( &newRegion.lo.x, &newRegion.lo.y );
						m_grabWindow->winGetSize( &grabSize.x, &grabSize.y );

						newRegion.lo.x += dx;
						newRegion.lo.y += dy;
						if( newRegion.lo.x < 0 )
							newRegion.lo.x = 0;
						if( newRegion.lo.y < 0 )
							newRegion.lo.y = 0;
						
						newRegion.hi.x = newRegion.lo.x + grabSize.x;
						newRegion.hi.y = newRegion.lo.y + grabSize.y;
						if( newRegion.hi.x > (Int)TheDisplay->getWidth() )
							newRegion.hi.x = (Int)TheDisplay->getWidth();
						if( newRegion.hi.y > (Int)TheDisplay->getHeight() )
							newRegion.hi.y = (Int)TheDisplay->getHeight();
						
						newRegion.lo.x = newRegion.hi.x - grabSize.x;
						newRegion.lo.y = newRegion.hi.y - grabSize.y;

						m_grabWindow->winSetPosition( newRegion.lo.x, newRegion.lo.y );

					}  // end if, draggable window

					// Send mouse drag message
					winSendInputMsg( m_grabWindow, msg, packedMouseCoords, 0 );
					break;

				}  // end mouse event none or left drag

			}  // end switch

			// mark event handled
			returnCode = WIN_INPUT_USED;

		}  // end if, m_grabWindow
		else
		{

			if( m_modalHead && m_modalHead->window )
			{
				window = m_modalHead->window->winPointInChild( mousePos->x, mousePos->y );
			}
			else
			{
			
				/**@todo Colin, there are 3 cases here that are nearly identical code,
				break them up into functions with parameters */

				// search for top-level window which contains pointer
				GameWindow *belowWindow = NULL;
				GameWindow *normalWindow = NULL;
				for( window = m_windowList; window; window = window->m_next )
				{
					if( !BitTest( window->m_status, WIN_STATUS_HIDDEN ) &&
							window->m_callbackExtra2 == m_captureFlags &&
							mousePos->x >= window->m_region.lo.x &&
							mousePos->x <= window->m_region.hi.x &&
							mousePos->y >= window->m_region.lo.y &&
							mousePos->y <= window->m_region.hi.y )
					{
						if( BitTest( window->m_status, WIN_STATUS_ABOVE ) )
							break;
						if( BitTest( window->m_status, WIN_STATUS_BELOW ) )
						{
							if( belowWindow == NULL )
								belowWindow = window;
						}
						else if( normalWindow == NULL )
							normalWindow = window;
					}
				}
				if( window == NULL )
					window = normalWindow ? normalWindow : belowWindow;
				if( window )
				{
					childWindow = window->winPointInAnyChild( mousePos->x, mousePos->y, TRUE, TRUE );
					if( toolTipWindow == NULL )
					{
						if( childWindow->m_tooltip ||
								childWindow->m_instData.getTooltipTextLength() )
						{
							toolTipWindow = childWindow;
						}
					}
					window = window->winPointInChild( mousePos->x, mousePos->y );
				}

			}  // end else, no modal head

			if( window )
				if( BitTest( window->m_status, WIN_STATUS_NO_INPUT ) )
				{
					if(window->winGetParent() && BitTest( window->winGetParent()->winGetInstanceData()->getStyle(), GWS_COMBO_BOX ))
						window = window->winGetParent();
					else
						window = NULL;
				}

			if( window )
			{
				GameWindow *tempWin;

				//
				// only send messages for button states, wheel states, we do not
				// continually send messages for mouse positions
				//
				if( sendMousePosMessages == TRUE || msg != GWM_MOUSE_POS )
				{

					tempWin = window;
	
					// Give everyone a chance to do something with the clicks
					GameWindow *oldLoneWindow = m_loneWindow;
					while( winSendInputMsg( tempWin, msg, packedMouseCoords, 0 ) == MSG_IGNORED )
					{

						tempWin = tempWin->m_parent;
						if( tempWin == NULL )
							break;

					}  // end while

						
					// First check to see if m_loneWindow is set if so, close the window
					if( m_loneWindow && m_loneWindow == oldLoneWindow 
					&&( msg == GWM_LEFT_UP || msg == GWM_MIDDLE_UP || msg == GWM_RIGHT_UP || tempWin))
					{
						if(!m_loneWindow->winIsChild(tempWin))
							winSetLoneWindow( NULL );
						/*
								ComboBoxData *cData = (ComboBoxData *)m_comboBoxOpen->winGetUserData();
															// verify that the window that ate the message wasn't one of our own
															if(cData->dropDownButton != tempWin &&
																cData->editBox != tempWin &&
																cData->listBox != tempWin &&
																cData->listboxData->upButton != tempWin &&
																cData->listboxData->downButton != tempWin &&
																cData->listboxData->slider != tempWin &&
																cData->listboxData->slider != tempWin->winGetParent())
																	winSetOpenComboBoxWindow( NULL );*/
								
					}
					if( tempWin )
					{
					
						//
						// Someone cares, if this is a left button down event
						// it should get "grabbed"
						/// @todo should allow for left handed mouse configs here?
						//
						if( msg == GWM_LEFT_DOWN )
						{

//						if( tempWin != windowList ) 
//							WinActivate( tempWin );
							m_grabWindow = tempWin;

						}  // end if

						// event is used
						returnCode = WIN_INPUT_USED;

					}  // end if, tempWin

				}  // end if

			}  // end if( window ) 

			if( toolTipWindow == NULL )
			{

				if( isHidden( window ) == FALSE )
					toolTipWindow = window;

			}  // end if

			// if tooltips are on set them into the window
			Bool tooltipsOn = TRUE;
			if( tooltipsOn )
			{
//				if( toolTipWindow && toolTipWindow->winGetParent() && BitTest( toolTipWindow->winGetParent()->winGetInstanceData()->getStyle(), GWS_COMBO_BOX ))
//					toolTipWindow = toolTipWindow->winGetParent();
				if( toolTipWindow )
				{
					// do we have a callback to call for the tooltip
					if( toolTipWindow->m_tooltip )
						toolTipWindow->m_tooltip( toolTipWindow, 
																			&toolTipWindow->m_instData, 
																			packedMouseCoords );

					// else, do we have a normal tooltip to set
					else if( toolTipWindow->m_instData.getTooltipTextLength() )
						TheMouse->setCursorTooltip( toolTipWindow->m_instData.getTooltipText(), toolTipWindow->m_instData.m_tooltipDelay );

				}  // end if
				else
				{

					//
					// not pointing at a window... perhaps we are pointing at a valid
					// tooltip-able object in the game world ... let's set a flag so 
					// during the object testing we can set the tooltip, we can do
					// whatever we like now that we know no other tooltip was set from
					// a window
					//
					objectTooltip = TRUE;

				}  // end else

			}  // end if

		}  // end if grabWindow not present

	}  // end else (mouseCaptor) 

	//
	// check if new current window is different from the last
	// but only if both windows fall within the mouseCaptor if one exists
	//
	if( (m_grabWindow == NULL) && (window != m_currMouseRgn) )
	{
		if( m_mouseCaptor )
		{
			if( m_mouseCaptor->winIsChild( m_currMouseRgn ) )
				winSendInputMsg( m_currMouseRgn, GWM_MOUSE_LEAVING, packedMouseCoords, 0 );
		}
		else if( m_currMouseRgn )
			winSendInputMsg( m_currMouseRgn, GWM_MOUSE_LEAVING, packedMouseCoords, 0 );

		if( window )
			winSendInputMsg( window, GWM_MOUSE_ENTERING, packedMouseCoords, 0 );

		m_currMouseRgn = window;

	}  // end if

	// clear grabWindow if necessary
	if( clearGrabWindow == TRUE )
	{

		m_grabWindow = NULL;
		clearGrabWindow = FALSE;

	}  // end if

	return returnCode;

}  // end winProcessMouseEvent
