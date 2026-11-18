// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Include
// Evidence: targets/game/reverse/identity_evidence/004b4010-input-and-private-helper.md and 004b42f0-system.md
#include "ascii_string.h"
#include "unicode_string.h"
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::UnicodeString(const UnicodeString &that)
{
    ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that);
}
inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &that)
{
    ((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&that);
    return *this;
}

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
enum GameWindowMessage
{
    GWM_LEFT_DOWN = 5, GWM_LEFT_UP = 6, GWM_LEFT_DRAG = 8,
    GWM_RIGHT_UP = 14, GWM_WHEEL_UP = 19, GWM_WHEEL_DOWN = 20,
    GWM_CHAR = 21
};
enum { KEY_TAB = 15, KEY_STATE_DOWN = 2, GWS_MOUSE_TRACK = 0x400, GGM_LEFT_DRAG = 0x4000 };
#include "Lib/Coord3D.h"
#include "../../../../../Libraries/Include/Lib/ICoord2D.h"

// The complete constructor and destructor own the opaque event storage.
class AudioEventRTS
{
public:
    AudioEventRTS(const AsciiString &eventName, int timeOfDay);
    virtual void slot00();
    // Retail uses the ledger's direct complete-destructor spelling.
    ~AudioEventRTS();
private:
    unsigned char m_storage[0x6C];
};

typedef char AudioEventRTSSize[(sizeof(AudioEventRTS) == 0x70) ? 1 : -1];

class GameFont;
class WinInstanceData
{
public:
    unsigned char m_head[8];
    unsigned int m_state;
    unsigned int m_style;
    unsigned char m_middle[0x184-0x10];
    GameFont *m_font;
    // ?getStyle@WinInstanceData@@QAEIXZ absent-from-retail
    unsigned int getStyle() { return m_style; }
    // ?getFont@WinInstanceData@@QAEPAVGameFont@@XZ absent-from-retail
    GameFont *getFont() { return m_font; }
    void setText(UnicodeString text);
};
struct Rva004B42F0Image
{
    unsigned char m_head[0x24];
    ICoord2D m_imageSize;
};
class GameWindow
{
public:
    WinInstanceData *winGetInstanceData();
    void *winGetUserData();
    GameWindow *winGetOwner();
    bool winIsHidden();
    int winHide(bool hide);
    int winGetSize(int *width, int *height);
    int winSetSize(int width, int height);
    int winSetPosition(int x, int y);
    int winGetWindowId();
    int winEnable(bool enable);
    unsigned int winGetStatus();
    unsigned char m_pad00[0x48];
    Rva004B42F0Image *m_ptr48;
};
struct ComboBoxData
{
    bool isEditable;
    unsigned char m_pad01[3];
    int maxDisplay;
    unsigned char m_pad08[0x14];
    bool dontHide;
    unsigned char m_pad1d[3];
    int entryCount;
    GameWindow *dropDownButton;
    GameWindow *editBox;
    GameWindow *listBox;
};
struct ListboxData
{
    short listLength;
    short columns;
    unsigned char m_pad04[0x0e];
    bool m_flag12, m_flag13;
    unsigned char m_pad14[4];
    void *listData;
    GameWindow *upButton, *downButton, *slider;
    unsigned char m_pad28[8];
    int m_int30;
    int selectPos;
};
class GameWindowManager
{
public:
    virtual void slot000();
    virtual void slot004();
    virtual void slot008();
    virtual void slot00C();
    virtual void slot010();
    virtual void slot014();
    virtual void slot018();
    virtual void slot01C();
    virtual void slot020();
    virtual void slot024();
    virtual void slot028();
    virtual void slot02C();
    virtual void slot030();
    virtual void slot034();
    virtual void slot038();
    virtual void slot03C();
    virtual void slot040();
    virtual void slot044();
    virtual void slot048();
    virtual void slot04C();
    virtual void slot050();
    virtual void slot054();
    virtual void slot058();
    virtual void slot05C();
    virtual void slot060();
    virtual void slot064();
    virtual void slot068();
    virtual void slot06C();
    virtual void slot070();
    virtual void slot074();
    virtual void slot078();
    virtual void slot07C();
    virtual void slot080();
    virtual void slot084();
    virtual void slot088();
    virtual void slot08C();
    virtual void slot090();
    virtual void winNextTab(GameWindow *window);
    virtual void winPrevTab(GameWindow *window);
    virtual void slot09C();
    virtual void slot0A0();
    virtual void slot0A4();
    virtual void slot0A8();
    virtual void slot0AC();
    virtual void slot0B0();
    virtual void slot0B4();
    virtual void slot0B8();
    virtual void winSetLoneWindow(GameWindow *window);
    virtual GameWindow *rva0047D080();
    virtual void slot0C4();
    virtual void slot0C8();
    virtual void slot0CC();
    virtual void slot0D0();
    virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2);
    virtual WindowMsgHandledType winSendInputMsg(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2);
    virtual void slot0DC();
    virtual void slot0E0();
    virtual void slot0E4();
    virtual void slot0E8();
    virtual void slot0EC();
    virtual void slot0F0();
    virtual void slot0F4();
    virtual void slot0F8();
    virtual void slot0FC();
    virtual void slot100();
    virtual void slot104();
    virtual void slot108();
    virtual int winFontHeight(GameFont *font);
};
extern GameWindowManager *TheWindowManager;
class Keyboard
{
    unsigned char m_head[8];
    int m_modifiers;
public:
    // ?getModifierFlags@Keyboard@@QAEHXZ absent-from-retail
    int getModifierFlags() { return m_modifiers; }
};
extern Keyboard *TheKeyboard;
class AudioManager
{
public:
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
    virtual unsigned int addAudioEvent(const AudioEventRTS *event);
};
extern AudioManager *TheAudio;
typedef AudioManager Rva004B42F0AudioClient;
// Both source spellings use the recorded AudioManager singleton.
#define TheAudioClientUpdate TheAudio
void bfmeGo1017Y(int a, int b, int c);
void HideListBox(GameWindow *window);
inline GameWindow *GadgetComboBoxGetEditBox(GameWindow *window)
{
    ComboBoxData *data = (ComboBoxData *)window->winGetUserData();
    return data && data->editBox ? data->editBox : 0;
}
inline GameWindow *GadgetComboBoxGetListBox(GameWindow *window)
{
    ComboBoxData *data = (ComboBoxData *)window->winGetUserData();
    return data && data->listBox ? data->listBox : 0;
}
// ?Rva004B3E30@@YAXPAVGameWindow@@@Z
static __declspec(noinline) void Rva004B3E30(GameWindow *window)
{
    if (!window) return;
    ComboBoxData *comboData = (ComboBoxData *)window->winGetUserData();
    comboData->dontHide = false;
    ComboBoxData *componentData = (ComboBoxData *)window->winGetUserData();
    GameWindow *listBox = componentData ? componentData->listBox : 0;
    if (!listBox) return;
    if (listBox->winIsHidden())
    {
        TheWindowManager->winSetLoneWindow(window);
        if (comboData->entryCount <= 1) return;
        listBox->winHide(false);
        ICoord2D winSize;
        window->winGetSize(&winSize.x, &winSize.y);
        WinInstanceData *listInstData = listBox->winGetInstanceData();
        ListboxData *listData = (ListboxData *)listBox->winGetUserData();
        listData->m_flag12 = true;
        listData->m_flag13 = true;
        listData->m_int30 = listData->selectPos;
        int multiplier;
        int listX;
        if (comboData->entryCount <= comboData->maxDisplay)
        {
            multiplier = comboData->entryCount;
            listX = winSize.x;
            if (listData->upButton) listData->upButton->winHide(true);
            if (listData->downButton) listData->downButton->winHide(true);
            if (listData->slider) listData->slider->winHide(true);
        }
        else
        {
            multiplier = comboData->maxDisplay;
            listX = winSize.x;
            if (listData->upButton) listData->upButton->winHide(false);
            if (listData->downButton) listData->downButton->winHide(false);
            if (listData->slider) listData->slider->winHide(false);
        }
        ICoord2D newSize;
        newSize.y = (TheWindowManager->winFontHeight(listInstData->getFont()) + 2) * multiplier + 4;
        window->winSetSize(winSize.x, winSize.y + newSize.y);
        listBox->winSetPosition(0, winSize.y);
        listBox->winSetSize(listX, newSize.y);
    }
    else
    {
        HideListBox(window);
        TheWindowManager->winSetLoneWindow(0);
    }
}

#include "../../../../Include/Common/ScalarTypes.h"



typedef unsigned int WindowMsgData;
typedef int Color;
enum { FALSE = 0, TRUE = 1, WIN_STATE_HILITED = 2, GWM_INPUT_FOCUS = 0x17,
    GCM_UPDATE_TEXT = 0x402d, GCM_SELECTED = 0x4025, GGM_FOCUS_CHANGE = 0x4003 };
struct ListEntryRow;
struct Rva004B42F0EntryData { unsigned char m_head[0x16]; bool m_flag16; };
UnicodeString GadgetTextEntryGetText(GameWindow *window);
void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);
void GadgetTextEntrySetTextColor(GameWindow *window, int color);
void GadgetListBoxSetSelected(GameWindow *window, int index);
void GadgetListBoxGetSelected(GameWindow *window, int *index);
void GadgetListBoxSetItemData(GameWindow *window, void *data, int row, int column = 0);
void *GadgetListBoxGetItemData(GameWindow *window, int row, int column);
UnicodeString GadgetListBoxGetTextAndColor(GameWindow *window, int *color, int row, int column);
void GadgetListBoxReset(GameWindow *window);
void GadgetListBoxSetListLength(GameWindow *window, int length);
int GadgetListBoxAddEntryText(GameWindow *window, UnicodeString text, int color, int row, int column, bool overwrite);

// ?GadgetComboBoxInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
WindowMsgHandledType GadgetComboBoxInput(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2)
{
    WinInstanceData *instData = window->winGetInstanceData();
    GameWindow *editBox = GadgetComboBoxGetEditBox(window);
    switch (msg)
    {
    case GWM_CHAR:
        switch (mData1)
        {
        case KEY_TAB:
            if (mData2 & KEY_STATE_DOWN)
            {
                if ((unsigned char)TheKeyboard->getModifierFlags() & 0x10)
                    TheWindowManager->winPrevTab(window);
                else
                    TheWindowManager->winNextTab(window);
            }
            break;
        default:
            return TheWindowManager->winSendInputMsg(editBox, GWM_CHAR, mData1, mData2);
        }
        break;
    case GWM_WHEEL_UP:
    case GWM_WHEEL_DOWN:
    case GWM_RIGHT_UP:
        break;
    case GWM_LEFT_UP:
        if (TheAudio)
        {
            AudioEventRTS buttonClick("GUIComboBoxClick", 2);
            TheAudio->addAudioEvent(&buttonClick);
        }
        // The complete static helper lets VC7.1 pass window in EBX.
        Rva004B3E30(window);
        bfmeGo1017Y(0, 1, 1);
        break;
    case GWM_LEFT_DRAG:
        if (instData->getStyle() & GWS_MOUSE_TRACK)
            TheWindowManager->winSendSystemMsg(window->winGetOwner(), GGM_LEFT_DRAG, (unsigned int)window, 0);
        break;
    case GWM_LEFT_DOWN:
        if (TheWindowManager->rva0047D080() == window) return MSG_IGNORED;
        break;
    default:
        return MSG_IGNORED;
    }
    return MSG_HANDLED;
}

typedef ComboBoxData Rva004B42F0ComboData;
typedef ListboxData Rva004B42F0ListboxData;
// GadgetListBoxSystem ========================================================
/** Handle system messages for list box */
//=============================================================================
// ?GadgetComboBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
WindowMsgHandledType GadgetComboBoxSystem( GameWindow *window, UnsignedInt msg,
													WindowMsgData mData1, WindowMsgData mData2 )
{
//	ListboxData *list = (ListboxData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();
	Rva004B42F0ComboData *comboData = (Rva004B42F0ComboData *)window->winGetUserData();
	switch( msg )
	{
		// ------------------------------------------------------------------------
		case 0x4001:
		{
			instData->setText(*(UnicodeString*)mData1);
			break;
		}  // end set lavel
		// ------------------------------------------------------------------------
		case 0x4026:
		{
			if(comboData->editBox)
				*(UnicodeString*)mData2 = GadgetTextEntryGetText(comboData->editBox);
			break;
		} // end Get text
		// ------------------------------------------------------------------------
		case 0x4027:
		{
			if (comboData->editBox)
				GadgetTextEntrySetText(comboData->editBox,*(const UnicodeString*)mData1);
			break;
		}  // end set text
		case 0x4031:
		{
			TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																	GCM_UPDATE_TEXT,
																	(WindowMsgData)window,
																	0 );
			if (comboData->listBox)
			{
				GadgetListBoxSetSelected(comboData->listBox, -1);
				HideListBox(window);
			}
			break;
		}
		// ------------------------------------------------------------------------
		// if we get sent an edit done message from the text box, lets notify the parent
		case 0x4030:
		{
			if ((GameWindow *)mData1 == comboData->editBox)
			{
				HideListBox(window);
				TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																		GCM_SELECTED,
																		(WindowMsgData)window,
                                                                        (WindowMsgData)-1 );
                TheWindowManager->winNextTab(window);
			}
			break;
		}
		// ------------------------------------------------------------------------
		// Set the selection in the listbox, this will trigger the listbox selected message 
		// which will set the edit box.
		case 0x402C:
		{
			GameWindow *listBox = GadgetComboBoxGetListBox(window);
			if(listBox)
			{
				if( !listBox->winIsHidden() && mData2 == TRUE )
					comboData->dontHide = TRUE;
				GadgetListBoxSetSelected(listBox, (Int)mData1);
			}
			break;
		}
		// ------------------------------------------------------------------------
		// Get what the listbox has selected.
		case 0x402B:
		{
			if(comboData->listBox)
				GadgetListBoxGetSelected(comboData->listBox, (Int *)mData2);
			else
			{
				*(Int *)mData2 = -1;
			}
			break;
		} //case GCM_GET_SELECTION:
		// ------------------------------------------------------------------------
		// Set the User Data for the specified listbox element
		case 0x402A:
		{
			if(comboData->listBox)
			{
				GadgetListBoxSetItemData(comboData->listBox, (void *)mData2, (Int)mData1 );
			}
			break;
		}
		// ------------------------------------------------------------------------
		// Get the user Data for the specified listbox element
		case 0x4029:
		{
			if(comboData->listBox)
			{
				*(void **)mData2 = GadgetListBoxGetItemData(comboData->listBox, (Int) mData1, 0);
			}
			break;
		}
		// ------------------------------------------------------------------------
		// Pass onto the parent window the selection the listbox just made
		case 0x4014:
		{
				if((GameWindow *) mData1 == comboData->listBox)
				{
					if( comboData->dontHide == TRUE )
					{
						comboData->dontHide = FALSE;
					}
					else
						HideListBox(window);
					// Nothing was actually selected, so we just want to 
					if( mData2 == -1)
					{
						break;
					}
					//Grab the text that was selected
					UnicodeString tempUString;
					Color color;
					tempUString = GadgetListBoxGetTextAndColor( comboData->listBox, &color, mData2, 0 );
					GadgetTextEntrySetTextColor(comboData->editBox, color);
					GadgetTextEntrySetText(comboData->editBox, tempUString);
					TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																		GCM_SELECTED,
																		(WindowMsgData)window,
																		0 );
				}
			break;
		}
		// ------------------------------------------------------------------------
		case 0x4000:
		{
			break;
		}  // end left drag
		// ------------------------------------------------------------------------
		case 0x4024:
		{
			if ( comboData->listBox )
				GadgetListBoxReset(comboData->listBox);
			if ( comboData->editBox )
				GadgetTextEntrySetText(comboData->editBox, UnicodeString::TheEmptyString );
			comboData->entryCount = 0;
			//HideListBox(window);	
            comboData->dropDownButton->winEnable(false);
			break;
		}  // end delete all
        // ------------------------------------------------------------------------
        case 0x4023:
            break;  // end delete entry
		// ------------------------------------------------------------------------
		case 0x4005:
		{
			HideListBox(window);
			break;
		}  // end delete entry
		// ------------------------------------------------------------------------
		case 0x4022:
		{
			GameWindow *listBox = GadgetComboBoxGetListBox(window);
			Rva004B42F0ListboxData *listData = (Rva004B42F0ListboxData *)listBox->winGetUserData();
			Int addedIndex = -1;
			if( listBox )
			{
				//Increase our internal entry count
				comboData->entryCount++;
				//If we've exceeded the set listlength, resize it to twice the size
				if(comboData->entryCount >= listData->listLength)
					GadgetListBoxSetListLength(listBox,listData->listLength * 2);
				//Add the entry to the Listbox
				addedIndex = GadgetListBoxAddEntryText( listBox, *(UnicodeString*)mData1, mData2, -1, 0, true );
				// Now resize the list box
				ICoord2D winSize;
				ICoord2D newSize;
				ICoord2D editBoxSize;
				Int listX;
				Int multiplier;
				WinInstanceData *listInstData = listBox->winGetInstanceData();
				GameWindow *editBox = GadgetComboBoxGetEditBox(window);
				window->winGetSize(&winSize.x, &winSize.y);
				editBox->winGetSize(&editBoxSize.x, &editBoxSize.y);
				// If the listbox has less entries then the MaxDisplay, size it smaller
				if(comboData->entryCount <= comboData->maxDisplay)
				{
					multiplier = comboData->entryCount;
					listX = winSize.x + 16;
					if(listData->upButton)
						listData->upButton->winHide(TRUE);
					if(listData->downButton)
						listData->downButton->winHide(TRUE);
					if(listData->slider)
						listData->slider->winHide(TRUE);
				}
				else
				{
					//Else size it to the MaxDisplay Size
					listX = winSize.x;
					multiplier = comboData->maxDisplay;
					if(listData->upButton)
						listData->upButton->winHide(FALSE);
					if(listData->downButton)
						listData->downButton->winHide(FALSE);
					if(listData->slider)
						listData->slider->winHide(FALSE);
				}
				newSize.y = (TheWindowManager->winFontHeight(listInstData->getFont()) + 2) * multiplier + 4;
				listBox->winSetPosition(0, editBoxSize.y);
				listBox->winSetSize(listX , newSize.y);
                if (listBox->winGetStatus() & 8)
                    comboData->dropDownButton->winEnable(comboData->entryCount > 1);
			}
			return( (WindowMsgHandledType) addedIndex );
		}  // end add entry
        case 0x1c:
            if (mData1 && comboData->entryCount <= 1)
                comboData->dropDownButton->winEnable(false);
            break;
        case 0x4003:
        {
            GameWindow *editBox = GadgetComboBoxGetEditBox(window);
            if ((int)mData2 == editBox->winGetWindowId())
            {
                Rva004B42F0EntryData *entryData = (Rva004B42F0EntryData *)editBox->winGetUserData();
                if (mData1) entryData->m_flag16 = false;
                else entryData->m_flag16 = true;
            }
            break;
        }
		// ------------------------------------------------------------------------
		case 1:
			break;
		// ------------------------------------------------------------------------
		case 0x4004:
		{
			Int width = (Int)mData1;
			Int height = (Int)mData2;
			ICoord2D dropDownSize;
			// get needed window sizes
			comboData->dropDownButton->winGetSize( &dropDownSize.x, &dropDownSize.y );
			GameWindow *listBox = GadgetComboBoxGetListBox(window);
			if (listBox->winIsHidden())
			{
				if (listBox)
					listBox->winSetSize(width,height);
				if( comboData->dropDownButton )
				{
                    Rva004B42F0Image *image = comboData->dropDownButton->m_ptr48;
                    if (image)
                    {
                        dropDownSize.x = image->m_imageSize.x;
                        dropDownSize.y = image->m_imageSize.y;
                        float ratio = (float)height / dropDownSize.y;
                        dropDownSize.x = (int)(dropDownSize.x * ratio);
                        dropDownSize.y = (int)(dropDownSize.y * ratio);
                    }
                    comboData->dropDownButton->winSetPosition(width - dropDownSize.x, 0);
                    comboData->dropDownButton->winSetSize(dropDownSize.x, dropDownSize.y);
				}
				if( comboData->editBox )
				{
					comboData->editBox->winSetPosition(  0,  0 );
					comboData->editBox->winSetSize( width - dropDownSize.x, height );
				}
			}
			break;
		}  // end resized
		// ------------------------------------------------------------------------
		// ------------------------------------------------------------------------
		case 2:
		{
			if (TheWindowManager) TheWindowManager->winSetLoneWindow(0); // if we are transitioning screens, close all combo boxes
			if (comboData)
			{
				delete(comboData);
				comboData = 0;
			}
			break;
		}  // end destroy
		// ------------------------------------------------------------------------
		case 0x17:
		{
			// If we're losing focus
			if( mData1 == FALSE )
			{
				instData->m_state &= ~WIN_STATE_HILITED;
			}
			else
			{
				instData->m_state |= WIN_STATE_HILITED;
			}
			TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																					GGM_FOCUS_CHANGE,
																					mData1,
																					window->winGetWindowId() );
			Bool wantsFocus = FALSE;
			GameWindow *editBox = GadgetComboBoxGetEditBox(window);
			// we need to tell the text entry box to take the focus.
			TheWindowManager->winSendSystemMsg( editBox, GWM_INPUT_FOCUS, mData1, (WindowMsgData)&wantsFocus );
			*(Bool*)mData2 = TRUE;
			break;
		}  // end input focus
		case 0x4008:
        // See if the drop down button was selected
        if ((GameWindow *)mData1 == comboData->dropDownButton)
        {
            if (TheAudioClientUpdate)
            {
                AudioEventRTS buttonClick("GUIComboBoxClick", 2);
                TheAudioClientUpdate->addAudioEvent(&buttonClick);
            }
            Rva004B3E30(window);
        }
        break;
		default:
			return MSG_IGNORED;
	}  // end switch( msg )
	return MSG_HANDLED;
}  // end GadgetListBoxSystem
