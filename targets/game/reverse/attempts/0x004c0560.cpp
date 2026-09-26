// ?d_004c0560@@YAXXZ
// partial score=0.37 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/radar /Iinputs/reference/shims/mouselayout /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// BFME's callback adds slider-track handling and a common context-click tail to the Zero Hour twin.

#define ASCIISTRING_H
#define __PLACEMENT_VEC_NEW_INLINE
#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef unsigned int UnsignedInt;
typedef int Int;
typedef unsigned short WideChar;
typedef bool Bool;
#ifndef NULL
#define NULL 0
#endif

inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
template <> inline const char *StringBase<char>::str() const
{
    return m_data ? m_data->data : "";
}

typedef unsigned int WindowMsgData;
enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
enum GadgetGameMessage
{
    GBM_MOUSE_ENTERING = 0x4006,
    GBM_MOUSE_LEAVING = 0x4007,
    GBM_SELECTED = 0x4008,
    GBM_SELECTED_RIGHT = 0x4009,
    GSM_SLIDER_TRACK = 0x400B,
    GEM_EDIT_DONE = 0x4030
};
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum CBCommandStatus { CBC_COMMAND_NOT_USED = 0, CBC_COMMAND_USED = 1 };
enum { GWM_CREATE = 1 };

class UnicodeString
{
public:
    static UnicodeString TheEmptyString;
    UnicodeString( const UnicodeString &source )
    {
        ((StringBase<WideChar> *)this)->StringBase<WideChar>::StringBase(
            *(const StringBase<WideChar> *)&source );
    }
    ~UnicodeString();
    const WideChar *str() const
    {
        return m_text ? (const WideChar *)((const char *)m_text + 8) : (const WideChar *)L"";
    }
private:
    void *m_text;
};

class GameWindow
{
public:
    int winGetWindowId();
};
class CommandButton;
class NameKeyGenerator
{
public:
    NameKeyType nameToKey( const char *name );
    NameKeyType nameToKey( const AsciiString &name ) { return nameToKey( name.str() ); }
};
#define TheNameKeyGenerator (*(NameKeyGenerator **)0x012ED600)
inline NameKeyType NAMEKEY( const char *name ) { return TheNameKeyGenerator->nameToKey( name ); }

class ControlBar
{
public:
    CBCommandStatus processCommandTransitionUI( GameWindow *control, GadgetGameMessage gadgetMessage );
    CBCommandStatus processContextSensitiveButtonClick( GameWindow *button, GadgetGameMessage gadgetMessage );
    const CommandButton *findCommandButton( const AsciiString &name );
    void togglePurchaseScience();
    void toggleControlBarStage();
};
#define TheControlBar (*(ControlBar **)0x012F33F8)

class GameLogic
{
public:
    bool isInMultiplayerGame();
};
#define TheGameLogic (*(GameLogic **)0x012F0898)

class Player
{
public:
    bool isPlayerActive();
};
class PlayerList
{
public:
    Player *getLocalPlayer();
};
#define ThePlayerList (*(PlayerList **)0x012ED748)

class GameWindowManager;
class InGameUI;
#define TheWindowManager (*(GameWindowManager **)0x012F1B40)
#define TheInGameUI (*(InGameUI **)0x012F148C)

class LanguageFilter
{
public:
    void filterLine( UnicodeString &line );
};
#define TheLanguageFilter (*(LanguageFilter **)0x012F1570)

class GameMessage
{
public:
    typedef int Type;
    void appendWideCharArgument( const WideChar &character );
};
class Rva004C0560MessageStream
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot0A() = 0;
    virtual void slot0B() = 0;
    virtual void slot0C() = 0;
    virtual GameMessage *appendMessage( GameMessage::Type type ) = 0;
};
#define TheMessageStream (*(Rva004C0560MessageStream **)0x012ED5EC)

struct ScriptEngine
{
    unsigned char m_unreconstructed_00[0x17080];
    Int m_endGameTimer;
    Bool isGameEnding() const { return m_endGameTimer >= 0; }
};
extern ScriptEngine *TheScriptEngine;

UnicodeString GadgetTextEntryGetText( GameWindow *textEntry );
void GadgetTextEntrySetText( GameWindow *textEntry, UnicodeString text );
void HideSaveLoadMenu( void );
void rva00569D80( void );

class Rva004C0560InGameUI
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot0A() = 0;
    virtual void slot0B() = 0;
    virtual void slot0C() = 0;
    virtual void slot0D() = 0;
    virtual void slot0E() = 0;
    virtual void slot0F() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot1A() = 0;
    virtual void slot1B() = 0;
    virtual void slot1C() = 0;
    virtual void slot1D() = 0;
    virtual void slot1E() = 0;
    virtual void slot1F() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void slot25() = 0;
    virtual void slot26() = 0;
    virtual void slot27() = 0;
    virtual void slot28() = 0;
    virtual void slot29() = 0;
    virtual void slot2A() = 0;
    virtual void slot2B() = 0;
    virtual void slot2C() = 0;
    virtual void slot2D() = 0;
    virtual void setGUICommand( const CommandButton *command ) = 0;
    virtual const CommandButton *getGUICommand() = 0;
    virtual void slot30() = 0;
    virtual void slot31() = 0;
    virtual void slot32() = 0;
    virtual void slot33() = 0;
    virtual void slot34() = 0;
    virtual void slot35() = 0;
    virtual void slot36() = 0;
    virtual void slot37() = 0;
    virtual void slot38() = 0;
    virtual void slot39() = 0;
    virtual void slot3A() = 0;
    virtual void slot3B() = 0;
    virtual int getSelectCount() = 0;
    virtual void slot3D() = 0;
    virtual void slot3E() = 0;
    virtual void slot3F() = 0;
    virtual void slot40() = 0;
    virtual void slot41() = 0;
    virtual void slot42() = 0;
    virtual void slot43() = 0;
    virtual void slot44() = 0;
    virtual void slot45() = 0;
    virtual void slot46() = 0;
    virtual void slot47() = 0;
    virtual void slot48() = 0;
    virtual void slot49() = 0;
    virtual void slot4A() = 0;
    virtual void slot4B() = 0;
    virtual void slot4C() = 0;
    virtual void slot4D() = 0;
    virtual void slot4E() = 0;
    virtual void slot4F() = 0;
    virtual void slot50() = 0;
    virtual void slot51() = 0;
    virtual void slot52() = 0;
    virtual void slot53() = 0;
    virtual void slot54() = 0;
    virtual void slot55() = 0;
    virtual void slot56() = 0;
    virtual void slot57() = 0;
    virtual void slot58() = 0;
    virtual void slot59() = 0;
    virtual void slot5A() = 0;
    virtual void slot5B() = 0;
    virtual void slot5C() = 0;
    virtual void slot5D() = 0;
    virtual void slot5E() = 0;
    virtual void slot5F() = 0;
    virtual void slot60() = 0;
    virtual void selectNextIdleWorker() = 0;
};

class Rva004C0560WindowManager
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot0A() = 0;
    virtual void slot0B() = 0;
    virtual void slot0C() = 0;
    virtual void slot0D() = 0;
    virtual void slot0E() = 0;
    virtual void slot0F() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot1A() = 0;
    virtual void slot1B() = 0;
    virtual void slot1C() = 0;
    virtual void slot1D() = 0;
    virtual void slot1E() = 0;
    virtual void slot1F() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void slot25() = 0;
    virtual void slot26() = 0;
    virtual void slot27() = 0;
    virtual void slot28() = 0;
    virtual void slot29() = 0;
    virtual void slot2A() = 0;
    virtual void slot2B() = 0;
    virtual void slot2C() = 0;
    virtual void slot2D() = 0;
    virtual void slot2E() = 0;
    virtual void slot2F() = 0;
    virtual void slot30() = 0;
    virtual void slot31() = 0;
    virtual void slot32() = 0;
    virtual void slot33() = 0;
    virtual void slot34() = 0;
    virtual void slot35() = 0;
    virtual void slot36() = 0;
    virtual GameWindow *winGetWindowFromId( GameWindow *parent, int id ) = 0;
};

WindowMsgHandledType ControlBarSystem( GameWindow *window, UnsignedInt msg,
                                       WindowMsgData mData1, WindowMsgData mData2 )
{
    static NameKeyType buttonCommunicator = NAMEKEY_INVALID;
    if( TheScriptEngine && TheScriptEngine->m_endGameTimer >= 0 )
        return MSG_IGNORED;

    switch( msg )
    {
        case GWM_CREATE:
        {
            buttonCommunicator = TheNameKeyGenerator->nameToKey( AsciiString("ControlBar.wnd:PopupCommunicator") );
            break;
        }

        case GBM_MOUSE_ENTERING:
        case GBM_MOUSE_LEAVING:
        {
            GameWindow *control = (GameWindow *)mData1;
            TheControlBar->processCommandTransitionUI( control, (GadgetGameMessage)msg );
            break;
        }

        case GBM_SELECTED:
        case GBM_SELECTED_RIGHT:
        case GSM_SLIDER_TRACK:
        {
            GameWindow *control = (GameWindow *)mData1;
            static NameKeyType beaconPlacementButtonID = NAMEKEY("ControlBar.wnd:ButtonPlaceBeacon");
            static NameKeyType beaconDeleteButtonID = NAMEKEY("ControlBar.wnd:ButtonDeleteBeacon");
            static NameKeyType beaconClearTextButtonID = NAMEKEY("ControlBar.wnd:ButtonClearBeaconText");
            static NameKeyType beaconGeneralButtonID = NAMEKEY("ControlBar.wnd:ButtonGeneral");
            static NameKeyType buttonLargeID = NAMEKEY("ControlBar.wnd:ButtonLarge");
            static NameKeyType buttonOptions = NAMEKEY("ControlBar.wnd:ButtonOptions");
            static NameKeyType buttonIdleWorker = NAMEKEY("ControlBar.wnd:ButtonIdleWorker");

            Int controlID = control->winGetWindowId();
            if( msg == GSM_SLIDER_TRACK )
            {
                if( controlID == buttonCommunicator || controlID == beaconPlacementButtonID ||
                    controlID == beaconDeleteButtonID || controlID == beaconGeneralButtonID ||
                    controlID == beaconClearTextButtonID || controlID == buttonLargeID ||
                    controlID == buttonOptions || controlID == buttonIdleWorker )
                    break;

            }

            if( controlID == buttonCommunicator )
                break;

            if( controlID == beaconPlacementButtonID && TheGameLogic->isInMultiplayerGame() &&
                ThePlayerList->getLocalPlayer()->isPlayerActive() )
            {
                const CommandButton *commandButton = TheControlBar->findCommandButton( AsciiString("Command_PlaceBeacon") );
                ((Rva004C0560InGameUI *)TheInGameUI)->setGUICommand( commandButton );
            }
            else if( controlID == beaconDeleteButtonID && TheGameLogic->isInMultiplayerGame() )
            {
                TheMessageStream->appendMessage( (GameMessage::Type)0x444 );
            }
            else if( controlID == beaconClearTextButtonID && TheGameLogic->isInMultiplayerGame() )
            {
                static NameKeyType textID = NAMEKEY("ControlBar.wnd:EditBeaconText");
                GameWindow *win = ((Rva004C0560WindowManager *)TheWindowManager)->winGetWindowFromId( NULL, textID );
                if( win )
                    GadgetTextEntrySetText( win, UnicodeString::TheEmptyString );
            }
            else if( controlID == beaconGeneralButtonID )
            {
                HideSaveLoadMenu();
                TheControlBar->togglePurchaseScience();
            }
            else if( controlID == buttonLargeID )
            {
                TheControlBar->toggleControlBarStage();
            }
            else if( controlID == buttonOptions )
            {
                rva00569D80();
            }
            else if( controlID == buttonIdleWorker )
            {
                HideSaveLoadMenu();
                ((Rva004C0560InGameUI *)TheInGameUI)->selectNextIdleWorker();
            }
            else
            {
                if( TheControlBar->processContextSensitiveButtonClick( control, (GadgetGameMessage)msg ) )
                    break;
                return MSG_IGNORED;
            }
            break;
        }

        case GEM_EDIT_DONE:
        {
            GameWindow *control = (GameWindow *)mData1;
            Int controlID = control->winGetWindowId();
            static NameKeyType textID = NAMEKEY("ControlBar.wnd:EditBeaconText");
            if( controlID == textID && ((Rva004C0560InGameUI *)TheInGameUI)->getSelectCount() == 1 )
            {
                GameMessage *message = TheMessageStream->appendMessage( (GameMessage::Type)0x445 );
                UnicodeString newText = GadgetTextEntryGetText( control );
                TheLanguageFilter->filterLine( newText );
                const WideChar *c = newText.str();
                while( c && *c )
                    message->appendWideCharArgument( *c++ );
                message->appendWideCharArgument( (WideChar)L'\0' );
            }
            break;
        }

        default:
            return MSG_IGNORED;

    }

    TheControlBar->processContextSensitiveButtonClick( (GameWindow *)mData1, (GadgetGameMessage)msg );
    return MSG_HANDLED;
}
