// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/displaystring /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
/*
 * Adapted from Electronic Arts' GPL-3.0 GeneralsMD GadgetListBox.cpp.
 * BFME-specific behavior and layout are witnessed in the retail body.
 *
 * GadgetListBoxInput: RVA 0x004B8940, 3495 bytes. The matched
 * GadgetListBoxRemoveMultiSelect (0x004BB890) installs ILT 0x0003C281,
 * which jumps here. Code ends at 0x004B95BC (last ret 0x004B95BB).
 * The two switch pointer tables (12 and 9 entries) and selector maps
 * extend through 0x004B96E7, where int3 padding begins. All 21 pointer
 * destinations were resolved from COFF labels and compared with retail.
 *
 * Rva004B7DC0: 215 bytes through ret 0x004B7E96 and then int3. Called
 * directly by the text-search arm. Its original name is not established.
 * Its final jump is adjustDisplay(GameWindow*, bool) at 0x004B7B20.
 *
 * Local static helper bodies are retained for VC7.1's private register
 * conventions. All six reproduce their separately witnessed retail
 * bodies: 4B69D0/273, 4B6B60/44, 4B6BA0/63, 4B7D50/80,
 * 4B7DC0/215 and 4B85F0/153. Existing helper ledger ownership is retained.
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
struct Rva004B8940Row
{
    int listHeight;
    int height;
    ListEntryCell *cell;
};
// BFME user data: extra flags +0x0F..+0x13 and fields +0x30/+0x48
// are absent from the ZH declaration; their names remain address-derived.
struct Rva004B8940List
{
    short listLength, columns;
    int *columnWidthPercentage;
    bool autoScroll, autoPurge, scrollBar, multiSelect;
    bool forceSelect, scrollIfAtEnd, audioFeedback, m_byte0f;
    bool m_byte10, m_byte11, m_byte12, m_byte13;
    int *columnWidth;
    Rva004B8940Row *listData;
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
extern unsigned int Rva00EF3640DoubleClickTime;
void adjustDisplay(GameWindow *, int, bool);
void adjustDisplay(GameWindow *, bool);

template <> inline WideChar StringBase<WideChar>::getCharAt(int index) const
{
    return m_data ? m_data->data[index] : 0;
}
inline WideChar Rva004B8940FirstChar(const UnicodeString &s)
{
    return ((const StringBase<WideChar> *)&s)->getCharAt(0);
}

// Primary vtable VA 0x010F8B60 +0xC0 -> ILT 0x00045D4A ->
// RVA 0x0047D080: mov eax,[ecx+0x28]; ret. The ZH-derived header
// lacks this no-argument pointer getter; use only its witnessed ABI.
class Rva0047D080ManagerView
{
  public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot0A();
    virtual void slot0B();
    virtual void slot0C();
    virtual void slot0D();
    virtual void slot0E();
    virtual void slot0F();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot1A();
    virtual void slot1B();
    virtual void slot1C();
    virtual void slot1D();
    virtual void slot1E();
    virtual void slot1F();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot2A();
    virtual void slot2B();
    virtual void slot2C();
    virtual void slot2D();
    virtual void slot2E();
    virtual void slot2F();
    virtual GameWindow *rva0047D080();
};
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

    Rva004B8940List *lData = (Rva004B8940List *)window->winGetUserData();
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

__declspec(noinline) static Int getListboxTopEntry(ListboxData *list)
{
    Int entry;
    const Rva004B8940List *retail = reinterpret_cast<const Rva004B8940List *>(list);
    for (entry = 0;; entry++)
    {
        if (retail->listData[entry].listHeight > retail->displayPos)
            return entry;

        if (entry >= retail->endPos)
            return 0;
    }

    return 0;
}
static int getListboxBottomEntry(ListboxData *raw)
{
    Rva004B8940List *list = (Rva004B8940List *)raw;
    for (int entry = list->endPos - 1;; --entry)
    {
        if (entry < 0)
            return 0;
        if (list->listData[entry].listHeight == list->displayPos + list->displayHeight)
            return entry;
        if (list->listData[entry].listHeight < list->displayPos + list->displayHeight)
        {
            if (entry != list->endPos - 1)
                return entry + 1;
            return entry;
        }
    }
}

static void adjustDisplayByDelta(GameWindow *window, Int adjustment, Bool updateSlider)
{
    Rva004B8940List *list = (Rva004B8940List *)window->winGetUserData();

    list->displayPos += adjustment;
    if (list->displayPos > list->totalHeight - list->displayHeight + 1)
        list->displayPos = list->totalHeight - list->displayHeight + 1;
    if (list->displayPos < 0)
        list->displayPos = 0;

    adjustDisplay(window, updateSlider);
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
__declspec(noinline) static void Rva004B7DC0(GameWindow *window, int index, int mode)
{
    if (index < 0)
        return;
    Rva004B8940List *list = (Rva004B8940List *)window->winGetUserData();
    if (index >= list->endPos)
        return;
    Rva004B8940Row *rows = list->listData;
    Rva004B8940Row *row = &rows[index];
    int y;
    switch (mode)
    {
    case 1:
        y = row->listHeight - row->height;
        break;
    default:
        y = (2 * row->listHeight - list->displayHeight - row->height) / 2;
        break;
    }
    list->displayPos = 0;
    int entry = 0;
    while (list->listData[entry].listHeight - list->listData[entry].height < y)
        ++entry;
    while (entry > 0 && list->totalHeight < rows[entry - 1].listHeight - rows[entry - 1].height +
                                                list->displayHeight)
        --entry;
    list->displayPos = rows[entry].listHeight - rows[entry].height;
    if (rows[list->endPos - 1].listHeight < list->displayPos + list->displayHeight)
        list->totalHeight = list->displayPos + list->displayHeight;
    adjustDisplay(window, true);
}

WindowMsgHandledType GadgetListBoxInput(GameWindow *window, UnsignedInt msg, WindowMsgData mData1,
                                        WindowMsgData mData2)
{
    Rva004B8940List *list = (Rva004B8940List *)window->winGetUserData();
    WinInstanceData *instData = window->winGetInstanceData();

    switch (msg)
    {
    case GWM_CHAR: {

        switch (mData1)
        {
        case KEY_ENTER:
        case KEY_SPACE: {

            if (BitTest(mData2, KEY_STATE_UP))
                if (mData2 & KEY_STATE_CONTROL)
                    return MSG_IGNORED;
                else
                {
                    doAudioFeedback(window);

                    TheWindowManager->winSendSystemMsg(window->winGetOwner(), 0x4015,
                                                       (WindowMsgData)window, list->selectPos);
                    return MSG_HANDLED;
                } // end if

            break;

        } // end enter or space
        case KEY_DOWN: {

            if (BitTest(mData2, KEY_STATE_DOWN))
            {

                if (list->m_byte10)
                {
                    int delta = 20;
                    if (window->winGetFont())
                        delta = window->winGetFont()->height;
                    adjustDisplayByDelta(window, delta, true);
                    break;
                }

                if (list->selectPos == -1)
                {
                    list->selectPos = 0;
                    adjustDisplay(window, 0, TRUE);
                }
                else if (list->selectPos < list->endPos - 1)
                {

                    list->selectPos++;

                    while (1)
                    {
                        Int cellBottom = list->listData[list->selectPos].listHeight;
                        Int cellTop = cellBottom - list->listData[list->selectPos].height;
                        Int displayTop = list->displayPos;
                        Int displayBottom =
                            list->displayPos + list->displayHeight - 1; // account for the border

                        if (cellTop < displayTop)
                        {
                            adjustDisplay(window, -1, TRUE);
                        }
                        else if (cellBottom < displayBottom)
                        {
                            adjustDisplay(window, 0, TRUE);
                            break;
                        }
                        else
                        {
                            adjustDisplay(window, 1, TRUE);
                        }
                    }
                }

                list->m_at48 = -1;
                TheWindowManager->winSendSystemMsg(window->winGetOwner(), 0x4014,
                                                   (WindowMsgData)window, list->selectPos);
                return MSG_HANDLED;
            } // end if

            break;

        } // end key down
        case KEY_PGDN:
            if (mData2 & KEY_STATE_DOWN)
            {
                if (list->m_byte10)
                {
                    list->displayPos += list->displayHeight;
                    adjustDisplayByDelta(window, 0, true);
                    break;
                }
                if (list->selectPos == -1)
                {
                    list->selectPos = 0;
                    adjustDisplay(window, 0, true);
                }
                else
                {
                    list->selectPos += getListboxBottomEntry((ListboxData *)list) -
                                       getListboxTopEntry((ListboxData *)list);
                    if (list->selectPos >= list->endPos)
                        list->selectPos = list->endPos - 1;
                    while (1)
                    {
                        Int cellBottom = list->listData[list->selectPos].listHeight;
                        Int cellTop = cellBottom - list->listData[list->selectPos].height;
                        Int displayTop = list->displayPos;
                        Int displayBottom =
                            list->displayPos + list->displayHeight - 1; // account for the border

                        if (cellTop < displayTop)
                        {
                            adjustDisplay(window, -1, TRUE);
                        }
                        else if (cellBottom < displayBottom)
                        {
                            adjustDisplay(window, 0, TRUE);
                            break;
                        }
                        else
                        {
                            adjustDisplay(window, 1, TRUE);
                        }
                    }
                }
                list->m_at48 = -1;
                TheWindowManager->winSendSystemMsg(window->winGetOwner(), 0x4014,
                                                   (WindowMsgData)window, list->selectPos);
                return MSG_HANDLED;
            }
            break;
        case KEY_END:
            if (mData2 & KEY_STATE_DOWN)
            {
                if (list->m_byte10)
                {
                    list->displayPos = list->totalHeight - list->displayHeight;
                    adjustDisplayByDelta(window, 0, true);
                    break;
                }
                list->selectPos = list->endPos - 1;
                while (1)
                {
                    Int cellBottom = list->listData[list->selectPos].listHeight;
                    Int cellTop = cellBottom - list->listData[list->selectPos].height;
                    Int displayTop = list->displayPos;
                    Int displayBottom =
                        list->displayPos + list->displayHeight - 1; // account for the border

                    if (cellTop < displayTop)
                    {
                        adjustDisplay(window, -1, TRUE);
                    }
                    else if (cellBottom < displayBottom)
                    {
                        adjustDisplay(window, 0, TRUE);
                        break;
                    }
                    else
                    {
                        adjustDisplay(window, 1, TRUE);
                    }
                }
                list->m_at48 = -1;
                TheWindowManager->winSendSystemMsg(window->winGetOwner(), 0x4014,
                                                   (WindowMsgData)window, list->selectPos);
                return MSG_HANDLED;
            }
            break;
        case KEY_UP: {

            if (BitTest(mData2, KEY_STATE_DOWN))
            {

                if (list->m_byte10)
                {
                    int delta = -20;
                    if (window->winGetFont())
                        delta = -window->winGetFont()->height;
                    adjustDisplayByDelta(window, delta, true);
                    break;
                }
                if (list->selectPos == -1)
                {
                    list->selectPos = 0;
                    adjustDisplay(window, 0, TRUE);
                }
                else if (list->selectPos > 0)
                {

                    list->selectPos--;

                    while (1)
                    {
                        if (list->listData[list->selectPos].listHeight -
                                list->listData[list->selectPos].height <
                            list->displayPos)
                        {
                            list->displayPos = list->listData[list->selectPos].listHeight + 1;
                            adjustDisplay(window, -1, TRUE);
                        }
                        else if (list->listData[list->selectPos].listHeight >
                                 list->displayPos + list->displayHeight)
                        {
                            list->displayPos =
                                list->listData[list->selectPos].listHeight - list->displayHeight;
                            adjustDisplay(window, 1, TRUE);
                        }
                        else
                        {
                            adjustDisplay(window, 0, TRUE);
                            break;
                        }
                    }
                }

                list->m_at48 = -1;
                TheWindowManager->winSendSystemMsg(window->winGetOwner(), 0x4014,
                                                   (WindowMsgData)window, list->selectPos);
                return MSG_HANDLED;
            }

            break;

        } // end key up
        case KEY_HOME:
            if (mData2 & KEY_STATE_DOWN)
            {
                if (list->m_byte10)
                {
                    list->displayPos = 0;
                    adjustDisplayByDelta(window, 0, true);
                    break;
                }
                list->selectPos = 0;
                while (1)
                {
                    if (list->listData[list->selectPos].listHeight -
                            list->listData[list->selectPos].height <
                        list->displayPos)
                    {
                        list->displayPos = list->listData[list->selectPos].listHeight + 1;
                        adjustDisplay(window, -1, TRUE);
                    }
                    else if (list->listData[list->selectPos].listHeight >
                             list->displayPos + list->displayHeight)
                    {
                        list->displayPos =
                            list->listData[list->selectPos].listHeight - list->displayHeight;
                        adjustDisplay(window, 1, TRUE);
                    }
                    else
                    {
                        adjustDisplay(window, 0, TRUE);
                        break;
                    }
                }
                list->m_at48 = -1;
                TheWindowManager->winSendSystemMsg(window->winGetOwner(), 0x4014,
                                                   (WindowMsgData)window, list->selectPos);
                return MSG_HANDLED;
            }
            break;
        case KEY_PGUP:
            if (mData2 & KEY_STATE_DOWN)
            {
                if (list->m_byte10)
                {
                    list->displayPos -= list->displayHeight;
                    adjustDisplayByDelta(window, 0, true);
                    break;
                }
                if (list->selectPos == -1)
                {
                    list->selectPos = 0;
                    adjustDisplay(window, 0, true);
                }
                else
                {
                    list->selectPos += getListboxTopEntry((ListboxData *)list) -
                                       getListboxBottomEntry((ListboxData *)list);
                    if (list->selectPos < 0)
                        list->selectPos = 0;
                    while (1)
                    {
                        Int cellBottom = list->listData[list->selectPos].listHeight;
                        Int cellTop = cellBottom - list->listData[list->selectPos].height;
                        Int displayTop = list->displayPos;
                        Int displayBottom =
                            list->displayPos + list->displayHeight - 1; // account for the border

                        if (cellTop < displayTop)
                        {
                            adjustDisplay(window, -1, TRUE);
                        }
                        else if (cellBottom < displayBottom)
                        {
                            adjustDisplay(window, 0, TRUE);
                            break;
                        }
                        else
                        {
                            adjustDisplay(window, 1, TRUE);
                        }
                    }
                }
                list->m_at48 = -1;
                TheWindowManager->winSendSystemMsg(window->winGetOwner(), 0x4014,
                                                   (WindowMsgData)window, list->selectPos);
                return MSG_HANDLED;
            }
            break;
        case KEY_TAB:
            if (mData2 & KEY_STATE_DOWN)
            {
                if (*(unsigned short *)((char *)TheKeyboard + 8) & 0x10)
                    TheWindowManager->winPrevTab(window);
                else
                    TheWindowManager->winNextTab(window);
            }
            break;
        default: {
            Bool foundIt = false;
            if (BitTest(mData2, KEY_STATE_DOWN))
            {
                if (list->m_byte10)
                    return MSG_IGNORED;
                Int position = list->selectPos;
                for (Int i = 0; i < list->endPos; ++i)
                {
                    ++position;
                    if (position >= list->endPos)
                        position = 0;

                    ListEntryCell *cell = NULL;
                    for (Int j = 0; j < list->columns; ++j)
                    {
                        cell = &list->listData[position].cell[j];
                        if (cell && cell->cellType == LISTBOX_TEXT && cell->data)
                        {
                            break;
                        }
                    }
                    if (!cell || cell->cellType != LISTBOX_TEXT)
                        continue;
                    DisplayString *dString = (DisplayString *)cell->data;
                    if (!dString)
                        continue;
                    for (j = 0; j < TheKeyboard->MAX_KEY_STATES; ++j)
                    {
                        if (Rva004B8940FirstChar(dString->getText()) ==
                            TheKeyboard->getPrintableKey(mData1, j))
                        {
                            list->selectPos = position;
                            Rva004B7DC0(window, position, 0);
                            list->m_at48 = -1;
                            TheWindowManager->winSendSystemMsg(window->winGetOwner(), 0x4014,
                                                               (WindowMsgData)window,
                                                               list->selectPos);
                            foundIt = TRUE;
                            break;
                        }
                    }
                    if (foundIt)
                    {
                        doAudioFeedback(window);
                        break;
                    }
                }
            }

            if (!foundIt)
                return MSG_IGNORED;
        }

        } // end switch( mData1 )

        break;

    } // end case char
    case GWM_WHEEL_DOWN: {
        if (list->m_byte10)
        {
            int delta = 20;
            if (window->winGetFont())
                delta = window->winGetFont()->height;
            adjustDisplayByDelta(window, delta, true);
            break;
        }
        if (list->endPos <= 0)
            break;

        if (list->listData[list->endPos - 1].listHeight > list->displayHeight + list->displayPos)
            adjustDisplay(window, 1, TRUE);

        break;

    } // end wheel down
    case GWM_WHEEL_UP: {
        if (list->m_byte10)
        {
            int delta = -20;
            if (window->winGetFont())
                delta = -window->winGetFont()->height;
            adjustDisplayByDelta(window, delta, true);
            break;
        }
        if (list->endPos <= 0)
            break;

        adjustDisplay(window, -1, TRUE);
        break;

    } // end wheel up
    case GWM_LEFT_UP: {
        if (list->m_byte0f)
            break;
        TheWindowManager->winSetFocus(window);
        Int mousex = mData1 & 0xFFFF;
        Int mousey = mData1 >> 16;
        Int x, y, i;
        Int oldPos = list->selectPos;

        window->winGetScreenPosition(&x, &y);
        if (instData->getTextLength())
            y += TheWindowManager->winFontHeight(instData->getFont()) + 1;

        list->selectPos = -2;

        for (i = 0;; i++)
        {

            if (i > 0)
                if (list->listData[i - 1].listHeight > (list->displayPos + list->displayHeight))
                {
                    list->selectPos = -1;
                    break;
                }

            if (i == list->endPos)
            {
                list->selectPos = -1;
                break;
            }

            if (list->listData[i].listHeight > (mousey - y + list->displayPos))
                break;
        }

        if ((i == oldPos) && (list->forceSelect == FALSE))
        {
            list->selectPos = -1;
        }

        if ((list->selectPos == -2) && (i < list->endPos))
        {
            list->selectPos = i;
        }

        if ((list->selectPos < 0) && (list->forceSelect))
        {
            list->selectPos = oldPos;
        }
        int relativeX = mousex - x;
        list->m_at48 = -1;
        if (relativeX > 1)
        {
            for (int column = 0; column < list->columns; ++column)
            {
                if (list->columnWidth[column] > relativeX)
                {
                    list->m_at48 = column;
                    break;
                }
                relativeX -= list->columnWidth[column];
            }
        }
        if (list->doubleClickTime + Rva00EF3640DoubleClickTime > timeGetTime() &&
            (i == oldPos || (oldPos == -1 && (i >= 0 && i < list->endPos))))
        {
            int temp;
            list->doubleClickTime = 0;
            if (oldPos == -1)
                temp = i;
            else
                temp = oldPos;
            TheWindowManager->winSendSystemMsg(window->winGetOwner(), 0x4015, (WindowMsgData)window,
                                               temp);
        }
        list->doubleClickTime = timeGetTime();
        TheWindowManager->winSendSystemMsg(window->winGetOwner(), 0x4014, (WindowMsgData)window,
                                           list->selectPos);

        break;

    } // end left click, left up
    case GWM_RIGHT_DOWN:
        doAudioFeedback(window);
        break; // if we're in game, we want to eat this message because we're right clicking on a
               // listbox
    case GWM_RIGHT_UP: {
        TheWindowManager->winSetFocus(window);
        Int pos;
        Int mousex = mData1 & 0xFFFF;
        Int mousey = mData1 >> 16;
        Int x, y, i;
        RightClickStruct rc;

        window->winGetScreenPosition(&x, &y);
        if (instData->getTextLength())
            y += TheWindowManager->winFontHeight(instData->getFont()) + 1;

        pos = -2;

        for (i = 0;; i++)
        {
            if (i > 0)
                if (list->listData[i - 1].listHeight > (list->displayPos + list->displayHeight))
                {
                    pos = -1;
                    break;
                }

            if (i == list->endPos)
            {
                pos = -1;
                break;
            }

            if (list->listData[i].listHeight > (mousey - y + list->displayPos))
                break;
        }

        if (pos == -2)
            pos = i;

        rc.pos = pos;
        rc.mouseX = mousex;
        rc.mouseY = mousey;
        TheWindowManager->winSendSystemMsg(window->winGetOwner(), 0x4016, (WindowMsgData)window,
                                           (WindowMsgData)&rc);
        break;

    } // end right up, right click
    case GWM_MOUSE_ENTERING: {

        if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
        {

            BitSet(instData->m_state, WIN_STATE_HILITED);
            TheWindowManager->winSendSystemMsg(window->winGetOwner(), GBM_MOUSE_ENTERING,
                                               (WindowMsgData)window, 0);

        } // end if

        break;

    } //  end mouse entering
    case GWM_MOUSE_LEAVING: {

        if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
        {

            BitClear(instData->m_state, WIN_STATE_HILITED);
            TheWindowManager->winSendSystemMsg(window->winGetOwner(), GBM_MOUSE_LEAVING,
                                               (WindowMsgData)window, 0);
        } // end if

        break;

    } // end mouse leaving
    case 24: {
        GameWindow *capture = ((Rva0047D080ManagerView *)TheWindowManager)->rva0047D080();
        if (capture && capture != window && !capture->winIsChild(window))
            return MSG_IGNORED;
        if (list->m_byte12)
        {
            int column;
            getListboxEntryBasedOnCoord(window, mData1 & 0xffff, mData1 >> 16, list->m_at30,
                                        column);
            TheWindowManager->winSendSystemMsg(window->winGetOwner(), 24, (WindowMsgData)window,
                                               mData1);
        }
        break;
    }
    case GWM_LEFT_DRAG:

        if (BitTest(instData->getStyle(), GWS_MOUSE_TRACK))
            TheWindowManager->winSendSystemMsg(window->winGetOwner(), GGM_LEFT_DRAG,
                                               (WindowMsgData)window, 0);
        break;
    case GWM_LEFT_DOWN:
        doAudioFeedback(window);
        return MSG_HANDLED;
    default:
        return MSG_IGNORED;

    } // end switch msg

    return MSG_HANDLED;
}
