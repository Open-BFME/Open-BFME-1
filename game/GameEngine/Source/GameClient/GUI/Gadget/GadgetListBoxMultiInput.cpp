// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/displaystring /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
/* Native multi-selection list input, RVA004B9A50.
 * Adapted from Electronic Arts GPL-3.0 GeneralsMD GadgetListBox.cpp.
 * Full972B:908 instruction bytes,11 switch destinations and20 selector bytes.
 * AddMultiSelect at004BB800 installs ILT000356E8, which jumps to this body.
 * Retained private helper definitions reproduce their existing retail bodies:
 * coordinate lookup004B69D0/273B, removeSelection004B6BF0/50B,
 * and audio feedback004B85F0/153B. Existing helper ownership is retained.
 * BFME input flags at+0F/+12 and state at+30/+48 keep address-derived names.
 * All37 relocations strictly resolve;13 local table references independently
 * reproduce retail, including both table-base instructions. No assembly/pins.
 */
#include <windows.h>
#include <mmsystem.h>
#include <ctype.h>
#include <string.h>
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"
#include "Common/Language.h"
#include "Common/Debug.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetSlider.h"
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/Keyboard.h"
#include "string_base.h"
inline UnicodeString::UnicodeString(const UnicodeString &stringSrc)
{
    ((StringBase<WideChar> *)this)
        ->StringBase<WideChar>::StringBase(*(const StringBase<WideChar> *)&stringSrc);
}
// BFME strings share StringBase's 8-byte buffer header and release routine.
inline AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}
inline void UnicodeString::releaseBuffer()
{
    ((StringBase<WideChar> *)this)->releaseBuffer();
}
// The ZH row stride agrees, but BFME reads a 32-bit height at +4.
struct Rva004B9A50Row
{
    int listHeight;
    int height;
    ListEntryCell *cell;
};
// BFME user data: extra flags +0x0F..+0x13 and fields +0x30/+0x48
// are absent from the ZH declaration; their names remain address-derived.
struct Rva004B9A50List
{
    short listLength, columns;
    int *columnWidthPercentage;
    bool autoScroll, autoPurge, scrollBar, multiSelect;
    bool forceSelect, scrollIfAtEnd, audioFeedback, m_byte0f;
    bool m_byte10, m_byte11, m_byte12, m_byte13;
    int *columnWidth;
    Rva004B9A50Row *listData;
    GameWindow *upButton, *downButton, *slider;
    int totalHeight;
    short endPos, insertPos;
    int m_at30;
    int selectPos;
    int *selections;
    short displayHeight;
    unsigned int doubleClickTime;
    short displayPos;
    int m_at48;
};
void adjustDisplay(GameWindow *, int, bool);
// Same BFME ABI as the landed doAudioFeedback_Thunk.cpp: 0x70 bytes,
// ObjectID constructor argument and non-virtual destructor spelling.
class AudioEventRTS
{
  public:
    AudioEventRTS(const AsciiString &eventName, ObjectID ownerID);
    ~AudioEventRTS();
  private:
    unsigned char m_unreconstructed_04[0x70];
};
class AudioManager
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
    virtual unsigned int addAudioEvent(const AudioEventRTS *eventToAdd);
};
extern AudioManager *TheAudio; ///< retail [0x012ED668]
__declspec(noinline) static void doAudioFeedback(GameWindow *window)
{
    if (!window)
        return;
    Rva004B9A50List *lData = (Rva004B9A50List *)window->winGetUserData();
    if (!lData)
        return;
    if (lData->audioFeedback)
    {
        AudioEventRTS buttonClick("GUIComboBoxClick", (ObjectID)2);
        if (TheAudio)
        {
            TheAudio->addAudioEvent(&buttonClick);
        }
    }
}
static Int getListboxEntryBasedOnCoord(GameWindow *window, Int x, Int y, Int &row, Int &column)
{
    Int pos;
    Int winx, winy, i;
    WinInstanceData *instData = window->winGetInstanceData();
    ListboxData *list = (ListboxData *)window->winGetUserData();
    window->winGetScreenPosition(&winx, &winy);
    if (instData->getTextLength())
        winy += TheWindowManager->winFontHeight(instData->getFont()) + 1;
    pos = -2;
    for (i = 0;; i++)
    {
        if (i > 0)
            if ((*(ListEntryRow **)((char *)list + 0x18))[i - 1].listHeight >
                (*(Short *)((char *)list + 0x3C) + *(Short *)((char *)list + 0x44)))
            {
                pos = -1;
                break;
            }
        if (i == *(Short *)((char *)list + 0x2C))
        {
            pos = -1;
            break;
        }
        if ((*(ListEntryRow **)((char *)list + 0x18))[i].listHeight >
            (y - winy + *(Short *)((char *)list + 0x44)))
            break;
    }
    column = -1;
    if (pos == -2)
    {
        pos = i;
        Int total = 0;
        for (i = 0; i < list->columns; i++)
        {
            total += (*(Int **)((char *)list + 0x14))[i];
            if (x - winx < total)
            {
                column = i;
                break;
            }
        }
    }
    row = pos;
    return pos;
}
__declspec(noinline) static void removeSelection( ListboxData *list, Int i )
{
	memcpy( &(*(Int **)((char *)list + 0x38))[i],
						&(*(Int **)((char *)list + 0x38))[(i+1)],
						((list->listLength - i) * sizeof(Int)) );
	// put -1 at end of list just for safety
	(*(Int **)((char *)list + 0x38))[(list->listLength - 1)] = -1;
}
WindowMsgHandledType GadgetListBoxMultiInput( GameWindow *window, UnsignedInt msg,
															WindowMsgData mData1, WindowMsgData mData2 )
{
	Rva004B9A50List *list = (Rva004B9A50List *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();
	switch( msg )
	{
		case GWM_CHAR:
		{
			switch( mData1 )
			{
				case KEY_TAB:
					if( BitTest( mData2, KEY_STATE_DOWN ) )
						window->winNextTab();
					break;
				default:
					return MSG_IGNORED;
			}
			break;
		}
		case GWM_LEFT_UP:
		{
			if (list->m_byte0f) break;
            TheWindowManager->winSetFocus( window );
			Int selectPos = -2;
			Int mousey = mData1 >> 16;
			Int x, y, i;
			Bool removed = FALSE;
			window->winGetScreenPosition( &x, &y );
			if( instData->getTextLength() )
				y += TheWindowManager->winFontHeight( instData->getFont() ) + 1;
			for( i = 0; ; i++ )
			{
				if( i > 0 )
					if( list->listData[ i - 1 ].listHeight >
							(list->displayPos + list->displayHeight ) )
					{
						selectPos = -1;
						break;
					}
				if( i == list->endPos )
				{
					selectPos = -1;
					break;
				}
				if( list->listData[i].listHeight > (mousey - y + list->displayPos) )
					break;
			}
			if( selectPos == -2 )
				selectPos = i;
			i = 0;
			while( list->selections[i] >= 0 )
			{
				if( list->selections[i] == selectPos )
				{
					removeSelection( (ListboxData *)list, i );
					removed = TRUE;
					break;
				}
				i++;
			}
			if( removed == FALSE )
			{
				list->selections[ i] = selectPos;
				list->selections[ i + 1 ] = -1;
			}
			list->m_at48 = -1;
            TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																					0x4014,
																					(WindowMsgData)window,
																					selectPos );
			break;
		}
		case GWM_RIGHT_UP:
		{
			TheWindowManager->winSetFocus( window );
			Int pos;
			Int mousex = mData1 & 0xFFFF;
			Int mousey = mData1 >> 16;
			Int x, y, i;
			RightClickStruct rc;
			window->winGetScreenPosition( &x, &y );
			if( instData->getTextLength() )
				y += TheWindowManager->winFontHeight( instData->getFont() ) + 1;
			pos = -2;
			for( i=0; ; i++ )
			{
				if( i > 0 )
					if( list->listData[ i - 1 ].listHeight >
							(list->displayPos + list->displayHeight ) )
					{
						pos = -1;
						break;
					}
				if( i == list->endPos )
				{
					pos = -1;
					break;
				}
				if( list->listData[i].listHeight > (mousey - y + list->displayPos) )
					break;
			}
			if( pos == -2 )
				pos = i;
			rc.pos = pos;
			rc.mouseX = mousex;
			rc.mouseY = mousey;
			TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																					0x4016,
																					(WindowMsgData)window,
																					(WindowMsgData)&rc );
			break;
		}
		case GWM_WHEEL_DOWN:
			if( list->downButton )
			{
				if( list->displayPos + list->displayHeight <= list->totalHeight )
					adjustDisplay( window, 1, TRUE );
			}
			break;
		case GWM_WHEEL_UP:
			if( list->upButton )
			{
				if( list->displayPos > 0 )
					adjustDisplay( window, -1, TRUE );
			}
			break;
		case GWM_MOUSE_ENTERING:
		{
			if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) )
			{
				BitSet( instData->m_state, WIN_STATE_HILITED );
				TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																						GBM_MOUSE_ENTERING,
																						(WindowMsgData)window,
																						0 );
			}
			break;
		}
		case GWM_MOUSE_LEAVING:
		{
			if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK ))
			{
				BitClear( instData->m_state, WIN_STATE_HILITED );
				TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																						GBM_MOUSE_LEAVING,
																						(WindowMsgData)window,
																						0 );
			}
			break;
		}
		case 24:
        {
            if (list->m_byte12)
            {
                Int column;
                getListboxEntryBasedOnCoord(window, mData1 & 0xffff, mData1 >> 16,
                                            list->m_at30, column);
                TheWindowManager->winSendSystemMsg(window->winGetOwner(), 24,
                                                    (WindowMsgData)window, mData1);
            }
            break;
        }
        case GWM_LEFT_DRAG:
			if (BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) )
				TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																						GGM_LEFT_DRAG,
																						(WindowMsgData)window,
																						0 );
			break;
		case GWM_LEFT_DOWN:
			doAudioFeedback(window);
			return MSG_HANDLED;
		default:
			return MSG_IGNORED;
	}
	return MSG_HANDLED;
}
