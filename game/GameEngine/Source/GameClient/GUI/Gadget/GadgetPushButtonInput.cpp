// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// BFME GadgetPushButtonInput (RVA 0x004BBFC0), ported from the ZH
// GameClient/GUI/Gadget/GadgetPushButton.cpp twin. The message cases and
// dispatch callbacks establish identity; retail adds repeat timing and Shift-Tab.
// WinInstanceData offsets are layout-witnessed. AudioEventRTS occupies 0x70
// bytes in both retail stack scopes (constructor 0xB2CC0 / destructor 0xB31F0).
// Unknown button-data members and global aliases retain this caller's RVA.
// The final 0x3c bytes are the compiler switch tables, not executable code;
// the complete extent ends at 0x004BC564 before alignment padding.
#include "ascii_string.h"
typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;
typedef bool Bool;
enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
#define FALSE false
#define BitTest(a,b) ((a)&(b))
#define BitSet(a,b) ((a)|=(b))
#define BitClear(a,b) ((a)&=~(b))
class GameWindow;
class WinInstanceData {
public:
 unsigned int rva004BBFC0_00, m_id, m_state, m_style, m_status;
 GameWindow *m_owner;
 unsigned int getStyle() {return m_style;}
 unsigned int getState() {return m_state;}
 GameWindow *getOwner() {return m_owner;}
};
class GameWindow {
public:
 WinInstanceData *winGetInstanceData();
 void *winGetUserData();
 GameWindow *winGetParent();
 unsigned int winGetStyle();
 unsigned int winGetStatus();
};
class GameWindowManager { public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2C();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3C();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4C();
 virtual void slot50();
 virtual void slot54();
 virtual void slot58();
 virtual void slot5C();
 virtual void slot60();
 virtual void slot64();
 virtual void slot68();
 virtual void slot6C();
 virtual void slot70();
 virtual void slot74();
 virtual void slot78();
 virtual void slot7C();
 virtual void slot80();
 virtual void slot84();
 virtual void slot88();
 virtual void slot8C();
 virtual void slot90();
 virtual void winNextTab(GameWindow*);
 virtual void winPrevTab(GameWindow*);
 virtual void slot9C();
 virtual void slotA0();
 virtual void slotA4();
 virtual void slotA8();
 virtual void slotAC();
 virtual void slotB0();
 virtual void slotB4();
 virtual void slotB8();
 virtual void slotBC();
 virtual void slotC0();
 virtual void slotC4();
 virtual void slotC8();
 virtual void slotCC();
 virtual void slotD0();
 virtual WindowMsgHandledType winSendSystemMsg(GameWindow*,unsigned int,unsigned int,unsigned int);
};
extern GameWindowManager *TheWindowManager;
class AudioEventRTS { public:
 AudioEventRTS(const AsciiString&,int);
 ~AudioEventRTS();
 void setEventName(AsciiString);
 unsigned char rva004BBFC0_storage[112];
};
struct Rva000B21A0Object { void setValue(unsigned int); };
class Rva004BBFC0Audio { public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2C();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3C();
 virtual void slot40();
 virtual void addAudioEvent(AudioEventRTS*);
};
class AudioManager;
extern AudioManager *TheAudio;
extern const AsciiString rva004BBFC0_emptyString;
struct Rva004BBFC0Keyboard { unsigned int rva00[2]; unsigned int m_modifiers; };
class Keyboard;
extern Keyboard *TheKeyboard;
struct Rva004BBFC0PushButtonData { unsigned char rva00[0x1c]; AsciiString rva1c; unsigned int rva20; int rva24; };
extern unsigned long rva004BBFC0_lastRepeat;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
enum {
 GWM_LEFT_DOWN=5, GWM_LEFT_UP=6, GWM_LEFT_DRAG=8, GWM_RIGHT_DOWN=13, GWM_RIGHT_UP=14,
 GWM_MOUSE_ENTERING=17,GWM_MOUSE_LEAVING=18,GWM_CHAR=21,GWM_TICK=24,
 GBM_SELECTED=0x4008,GBM_SELECTED_RIGHT=0x4009,GBM_MOUSE_ENTERING=0x4006,GBM_MOUSE_LEAVING=0x4007,GGM_LEFT_DRAG=0x4000,
 GWS_MOUSE_TRACK=0x400,GWS_HORZ_SLIDER=0x10, WIN_STATE_HILITED=2,WIN_STATE_SELECTED=4,
 WIN_STATUS_CHECK_LIKE=0x80000,WIN_STATUS_RIGHT_CLICK=0x20000,WIN_STATUS_ON_MOUSE_DOWN=0x02000000,
 KEY_ENTER=28,KEY_SPACE=57,KEY_TAB=15,KEY_STATE_UP=1,KEY_STATE_DOWN=2
};
static Bool buttonTriggersOnMouseDown(GameWindow *window)
{
	// Buttons with the on down status set trigger on mouse down. jba. [8/6/2003]
	Bool onDown = BitTest( window->winGetStatus(), WIN_STATUS_ON_MOUSE_DOWN);

	// Checkboxes always trigger on mouse down. jba [8/6/2003]
	if (BitTest( window->winGetStatus(), WIN_STATUS_CHECK_LIKE )) {
		onDown = true;
	}
	return onDown;
}

// GadgetPushButtonInput ======================================================
/** Handle input for push button */
//=============================================================================
WindowMsgHandledType GadgetPushButtonInput( GameWindow *window, 
																						UnsignedInt msg,
																						WindowMsgData mData1, 
																						WindowMsgData mData2 )
{
	WinInstanceData *instData = window->winGetInstanceData();

	switch( msg ) 
	{

		// ------------------------------------------------------------------------
		case GWM_TICK:
        {
            if (BitTest(instData->m_state, WIN_STATE_SELECTED) && buttonTriggersOnMouseDown(window)) {
                Rva004BBFC0PushButtonData *pData=(Rva004BBFC0PushButtonData*)window->winGetUserData();
                if(pData->rva24) {
                    unsigned long now=timeGetTime();
                    if(now>rva004BBFC0_lastRepeat && now-rva004BBFC0_lastRepeat>(unsigned int)pData->rva24) {
                        TheWindowManager->winSendSystemMsg(instData->getOwner(),GBM_SELECTED,(WindowMsgData)window,0);
                        rva004BBFC0_lastRepeat=now;
                    }
                }
            }
            return MSG_IGNORED;
        }
        case GWM_MOUSE_ENTERING:
		{

			if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) ) 
			{
				BitSet( instData->m_state, WIN_STATE_HILITED );

				TheWindowManager->winSendSystemMsg( instData->getOwner(), 
																						GBM_MOUSE_ENTERING,
																						(WindowMsgData)window, 
																						mData1 );

				//TheWindowManager->winSetFocus( window );
			}
			if(window->winGetParent() && BitTest(window->winGetParent()->winGetStyle(),GWS_HORZ_SLIDER) )
			{
				WinInstanceData *instDataParent = window->winGetParent()->winGetInstanceData();
				BitSet(instDataParent->m_state, WIN_STATE_HILITED);
			}
			break;

		}  // end mouse entering

		// ------------------------------------------------------------------------
		case GWM_MOUSE_LEAVING:
		{

			if(BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) ) 
			{
				BitClear( instData->m_state, WIN_STATE_HILITED );
				TheWindowManager->winSendSystemMsg( instData->getOwner(), 
																						GBM_MOUSE_LEAVING,
																						(WindowMsgData)window, 
																						mData1 );
			}
		
			//
			// if this is not a check-like button, clear any selected state when the
			// move leaves the window area
			//
			if( BitTest( window->winGetStatus(), WIN_STATUS_CHECK_LIKE ) == FALSE )
				if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
					BitClear( instData->m_state, WIN_STATE_SELECTED );
			//TheWindowManager->winSetFocus( NULL );
			if(window->winGetParent() && BitTest(window->winGetParent()->winGetStyle(),GWS_HORZ_SLIDER) )
			{
				WinInstanceData *instDataParent = window->winGetParent()->winGetInstanceData();
				BitClear(instDataParent->m_state, WIN_STATE_HILITED);
			}
			break;

		}  // end mouse leaving

		// ------------------------------------------------------------------------
		case GWM_LEFT_DRAG:
		{

			TheWindowManager->winSendSystemMsg( instData->getOwner(), GGM_LEFT_DRAG,
																					(WindowMsgData)window, mData1 );
			break;

		}  // end left drag

		// ------------------------------------------------------------------------
		case GWM_LEFT_DOWN:
		{
			Rva004BBFC0PushButtonData *pData = (Rva004BBFC0PushButtonData *)window->winGetUserData();
			AudioEventRTS buttonClick(rva004BBFC0_emptyString,0);
            ((Rva000B21A0Object*)&buttonClick)->setValue(2);
			if(pData && pData->rva1c.isNotEmpty())
				buttonClick.setEventName(pData->rva1c);

			if( TheAudio )
			{
				((Rva004BBFC0Audio *)TheAudio)->addAudioEvent( &buttonClick );
			}  // end if

			//
			// for 'check-like' buttons we have "dual state", we flip the selected status
			// in that case instead of just turning it on like normal ... also note
			// that selected messages are sent immediately
			//
			if( BitTest( window->winGetStatus(), WIN_STATUS_CHECK_LIKE ) )
			{
				
				if( BitTest( instData->m_state, WIN_STATE_SELECTED ) )
					BitClear( instData->m_state, WIN_STATE_SELECTED );
				else
					BitSet( instData->m_state, WIN_STATE_SELECTED );


			}  // end if
			else
			{
				
				// just select as normal
				BitSet( instData->m_state, WIN_STATE_SELECTED );

			}  // end else

			if (buttonTriggersOnMouseDown(window)) {
				TheWindowManager->winSendSystemMsg( instData->getOwner(), GBM_SELECTED,
																						(WindowMsgData)window, mData1 );
                rva004BBFC0_lastRepeat=timeGetTime()+pData->rva24*2;
			}

			break;
		}  // end left down

		//-------------------------------------------------------------------------
		case GWM_LEFT_UP:
		{

			//
			// note check like selected messages aren't sent here ... they are sent
			// on the down press
			//
			if( BitTest( instData->getState(), WIN_STATE_SELECTED ) &&
					BitTest( window->winGetStatus(), WIN_STATUS_CHECK_LIKE ) == FALSE )
			{

				if (!buttonTriggersOnMouseDown(window)) {
					// If it didn't trigger on mouse down, trigger on the mouse up. jba  [8/6/2003]
					TheWindowManager->winSendSystemMsg( instData->getOwner(), GBM_SELECTED,
																							(WindowMsgData)window, mData1 );
				}

				BitClear( instData->m_state, WIN_STATE_SELECTED );

			}
			else
			{

				// this up click was not meant for this button
				return MSG_IGNORED;

			}

			break;

		}  // end left up or left click

		// ------------------------------------------------------------------------
		case GWM_RIGHT_DOWN:
		{
			Rva004BBFC0PushButtonData *pData = (Rva004BBFC0PushButtonData *)window->winGetUserData();
			AudioEventRTS buttonClick(rva004BBFC0_emptyString,0);
            ((Rva000B21A0Object*)&buttonClick)->setValue(2);
			if(pData && pData->rva1c.isNotEmpty())
				buttonClick.setEventName(pData->rva1c);
				

			if( BitTest( window->winGetStatus(), WIN_STATUS_RIGHT_CLICK ) )
			{
                if(TheAudio) ((Rva004BBFC0Audio *)TheAudio)->addAudioEvent(&buttonClick);
			//
			// for 'check-like' buttons we have "dual state", we flip the selected status
			// in that case instead of just turning it on like normal ... also note
			// that selected messages are sent immediately
			//
			if( BitTest( window->winGetStatus(), WIN_STATUS_CHECK_LIKE ) )
			{
				
				if( BitTest( instData->m_state, WIN_STATE_SELECTED ) )
					BitClear( instData->m_state, WIN_STATE_SELECTED );
				else
					BitSet( instData->m_state, WIN_STATE_SELECTED );


			}  // end if
			else
			{
				
				// just select as normal
				BitSet( instData->m_state, WIN_STATE_SELECTED );

			}  // end else

			if (buttonTriggersOnMouseDown(window)) {
				TheWindowManager->winSendSystemMsg( instData->getOwner(), GBM_SELECTED_RIGHT,
																						(WindowMsgData)window, mData1 );
                rva004BBFC0_lastRepeat=timeGetTime()+pData->rva24*2;
			}

			}
			else
			{
				// Else I don't care about right events
				return MSG_IGNORED;
			}
			break;
		}  // end right down

		//-------------------------------------------------------------------------
		case GWM_RIGHT_UP:
		{
			
			if( BitTest( window->winGetStatus(), WIN_STATUS_RIGHT_CLICK ) )
			{

				//
				// note check like selected messages aren't sent here ... they are sent
				// on the down press
				//
				if( BitTest( instData->getState(), WIN_STATE_SELECTED ) &&
						BitTest( window->winGetStatus(), WIN_STATUS_CHECK_LIKE ) == FALSE )
				{

					if (!buttonTriggersOnMouseDown(window))
                        TheWindowManager->winSendSystemMsg( instData->getOwner(), GBM_SELECTED_RIGHT,
																							(WindowMsgData)window, mData1 );

					BitClear( instData->m_state, WIN_STATE_SELECTED );

				}
				else
				{

					// this up click was not meant for this button
					return MSG_IGNORED;

				}

			}
			else
			{
				// Else I don't care about right events
				return MSG_IGNORED;
			}

			break;

		}  // end right up or right click

		// ------------------------------------------------------------------------
		case GWM_CHAR:
		{
			switch( mData1 )
			{
				// --------------------------------------------------------------------
				case KEY_ENTER:
				case KEY_SPACE:
				{

					if( BitTest( mData2, KEY_STATE_UP ) )
					{

						//
						// note check like selected messages aren't sent here ... they are sent
						// on the down press
						//
						if( BitTest( instData->getState(), WIN_STATE_SELECTED ) &&
								BitTest( window->winGetStatus(), WIN_STATUS_CHECK_LIKE ) == FALSE )
						{

							TheWindowManager->winSendSystemMsg( instData->getOwner(), GBM_SELECTED,
																									(WindowMsgData)window, 0 );

							BitClear( instData->m_state, WIN_STATE_SELECTED );

						}

					} 
					else
					{

						//
						// for 'check-like' buttons we have "dual state", we flip the selected status
						// in that case instead of just turning it on like normal ... also note
						// that selected messages are sent immediately
						//
						if( BitTest( window->winGetStatus(), WIN_STATUS_CHECK_LIKE ) )
						{
							
							if( BitTest( instData->m_state, WIN_STATE_SELECTED ) )
								BitClear( instData->m_state, WIN_STATE_SELECTED );
							else
								BitSet( instData->m_state, WIN_STATE_SELECTED );

							TheWindowManager->winSendSystemMsg( instData->getOwner(), GBM_SELECTED,
																									(WindowMsgData)window, mData1 );

						}  // end if
						else
						{
							
							// just select as normal
							BitSet( instData->m_state, WIN_STATE_SELECTED );

						}  // end else


					}  // end else

					break;

				}  // end handle enter and space button

				// --------------------------------------------------------------------
                case KEY_TAB:
                    if (BitTest(mData2,KEY_STATE_DOWN)) {
                        if(reinterpret_cast<Rva004BBFC0Keyboard *>(TheKeyboard)->m_modifiers & 0x10) TheWindowManager->winPrevTab(window);
                        else TheWindowManager->winNextTab(window);
                    }
                    break;
				default:
					return MSG_IGNORED;

			}  // end switch on char

			break;

		}  // end character message

		// ------------------------------------------------------------------------
		default:
			return MSG_IGNORED;

	}  // end switch( msg )

	return MSG_HANDLED;

}  // end GadgetPushButtonInput

