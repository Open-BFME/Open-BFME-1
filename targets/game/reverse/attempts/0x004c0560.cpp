// ?ControlBarSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// partial score=0.438 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// ControlBarSystem, retail 0x004C0560 (1459 B). Home: game/GameEngine/Source/GameClient/GUI/GUICallbacks/.
// IDENTITY PROVEN: FunctionLexicon entry at VA 0x012A9648 pairs literal "ControlBarSystem"
// (VA 0x010873F0) with ILT 0x004080E4 -> 0x004C0560, the same proof as LeftHUDInput (0x012A98E8).
// String model: WWLib ascii_string/unicode_string as in ControlBarVisibility.cpp. Real extern globals.
// Control flow read from retail: no common tail; slider-track tests 8 ids then
// processContextSensitiveButtonClick decides HANDLED/IGNORED; BFME HideSaveLoadMenu/rva00569D80.
// Residue (probe 1457/1459 B, shape 0.926): retail msg=ebp, zero=ebx (prologue/CREATE/EDIT),
// -1=esi (statics only); ours msg=ebx, -1=ebp, no zero register. Retail also caches TheGameLogic
// in edi across the else-chain and skips its reload after isInMultiplayerGame (callee memory
// effects known) but not after isPlayerActive; a visible noinline isInMultiplayerGame body gives
// that knowledge but also ecx-preservation knowledge retail lacks (1447 B, shape 0.928).
#include "ascii_string.h"
#include "unicode_string.h"

template <> inline const char *StringBase<char>::str() const {
    return m_data ? m_data->data : "";
}
template <> inline const unsigned short *StringBase<unsigned short>::str() const {
    return m_data ? m_data->data : (const unsigned short *)L"";
}
template <> inline StringBase<unsigned short>::~StringBase() { releaseBuffer(); }
inline UnicodeString::UnicodeString(const UnicodeString& s) {
    ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&s);
}
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::~StringBase(); }

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef unsigned short WideChar;
typedef unsigned int WindowMsgData;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
enum { GWM_CREATE = 1 };
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
enum CBCommandStatus { CBC_COMMAND_NOT_USED = 0, CBC_COMMAND_USED };

class GameWindow
{
public:
    Int winGetWindowId( void );
};

class CommandButton;

class NameKeyGenerator
{
public:
    NameKeyType nameToKey( const char *name );
    NameKeyType nameToKey( const AsciiString &name ) { return nameToKey( name.str() ); }
};
extern NameKeyGenerator *TheNameKeyGenerator;
inline NameKeyType NAMEKEY( const char *name ) { return TheNameKeyGenerator->nameToKey( name ); }

WindowMsgHandledType ControlBarSystem( GameWindow *window, UnsignedInt msg,
                                       WindowMsgData mData1, WindowMsgData mData2 );

class ControlBar
{
public:
    CBCommandStatus processContextSensitiveButtonClick( GameWindow *button, GadgetGameMessage gadgetMessage );
    const CommandButton *findCommandButton( const AsciiString &name );
    void togglePurchaseScience( void );
    void toggleControlBarStage( void );
protected:
    CBCommandStatus processCommandTransitionUI( GameWindow *control, GadgetGameMessage gadgetMessage );
    friend WindowMsgHandledType ControlBarSystem( GameWindow *, UnsignedInt, WindowMsgData, WindowMsgData );
};
extern ControlBar *TheControlBar;

class GameLogic
{
public:
    Bool isInMultiplayerGame( void );
};
extern GameLogic *TheGameLogic;

class Player
{
public:
    Bool isPlayerActive( void ) const;
};

class PlayerList
{
public:
    Player *getLocalPlayer( void ) { return m_local; }
private:
    Int m_unmodelled[3];
    Player *m_local;
};
extern PlayerList *ThePlayerList;

class ScriptEngine
{
public:
    Bool isGameEnding( void ) { return m_endGameTimer >= 0; }
private:
    unsigned char m_unreconstructed_00[0x17080];
    Int m_endGameTimer;
};
extern ScriptEngine *TheScriptEngine;

class LanguageFilter
{
public:
    void filterLine( UnicodeString &line );
};
extern LanguageFilter *TheLanguageFilter;

class GameMessage
{
public:
    enum Type { MSG_REMOVE_BEACON = 0x444, MSG_SET_BEACON_TEXT = 0x445 };
    void appendWideCharArgument( const WideChar &character );
};

class MessageStream
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
    virtual void slot0C();
    virtual GameMessage *appendMessage( GameMessage::Type type );
};
extern MessageStream *TheMessageStream;

class GameWindowManager
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
    virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
    virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
    virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
    virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual void slot1F();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28(); virtual void slot29(); virtual void slot2A(); virtual void slot2B();
    virtual void slot2C(); virtual void slot2D(); virtual void slot2E(); virtual void slot2F();
    virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
    virtual void slot34(); virtual void slot35(); virtual void slot36();
    virtual GameWindow *winGetWindowFromId( GameWindow *window, Int id );
};
extern GameWindowManager *TheWindowManager;

class InGameUI
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
    virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
    virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
    virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
    virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual void slot1F();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28(); virtual void slot29(); virtual void slot2A(); virtual void slot2B();
    virtual void slot2C(); virtual void slot2D();
    virtual void setGUICommand( const CommandButton *command );
    virtual void slot2F();
    virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
    virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
    virtual void slot38(); virtual void slot39(); virtual void slot3A(); virtual void slot3B();
    virtual Int getSelectCount( void );
    virtual void slot3D(); virtual void slot3E(); virtual void slot3F();
    virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
    virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
    virtual void slot48(); virtual void slot49(); virtual void slot4A(); virtual void slot4B();
    virtual void slot4C(); virtual void slot4D(); virtual void slot4E(); virtual void slot4F();
    virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
    virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57();
    virtual void slot58(); virtual void slot59(); virtual void slot5A(); virtual void slot5B();
    virtual void slot5C(); virtual void slot5D(); virtual void slot5E(); virtual void slot5F();
    virtual void slot60();
    virtual void selectNextIdleWorker( void );
};
extern InGameUI *TheInGameUI;

UnicodeString GadgetTextEntryGetText( GameWindow *textentry );
void GadgetTextEntrySetText( GameWindow *textentry, UnicodeString text );
void HideSaveLoadMenu( void );
// UnicodeString::TheEmptyString; the WWLib UnicodeString model has no static member.
extern const UnicodeString Rva01336E54EmptyUnicode;
void rva00569D80( void );

WindowMsgHandledType ControlBarSystem( GameWindow *window, UnsignedInt msg,
                                       WindowMsgData mData1, WindowMsgData mData2 )
{
    static NameKeyType buttonCommunicator = NAMEKEY_INVALID;
    if( TheScriptEngine && TheScriptEngine->isGameEnding() )
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
                if( TheControlBar->processContextSensitiveButtonClick( control, (GadgetGameMessage)msg ) == CBC_COMMAND_NOT_USED )
                    return MSG_IGNORED;
                break;
            }

            if( controlID == buttonCommunicator )
            {
            }
            else if( controlID == beaconPlacementButtonID && TheGameLogic->isInMultiplayerGame() &&
                ThePlayerList->getLocalPlayer()->isPlayerActive() )
            {
                const CommandButton *commandButton = TheControlBar->findCommandButton( AsciiString("Command_PlaceBeacon") );
                TheInGameUI->setGUICommand( commandButton );
            }
            else if( controlID == beaconDeleteButtonID && TheGameLogic->isInMultiplayerGame() )
            {
                TheMessageStream->appendMessage( GameMessage::MSG_REMOVE_BEACON );
            }
            else if( controlID == beaconClearTextButtonID && TheGameLogic->isInMultiplayerGame() )
            {
                static NameKeyType textID = NAMEKEY("ControlBar.wnd:EditBeaconText");
                GameWindow *win = TheWindowManager->winGetWindowFromId( 0, textID );
                if( win )
                {
                    GadgetTextEntrySetText( win, Rva01336E54EmptyUnicode );
                }
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
                TheInGameUI->selectNextIdleWorker();
            }
            else
            {
                TheControlBar->processContextSensitiveButtonClick( control, (GadgetGameMessage)msg );
            }
            break;
        }

        case GEM_EDIT_DONE:
        {
            GameWindow *control = (GameWindow *)mData1;
            Int controlID = control->winGetWindowId();
            static NameKeyType textID = NAMEKEY("ControlBar.wnd:EditBeaconText");
            if( controlID == textID )
            {
                if( TheInGameUI->getSelectCount() == 1 )
                {
                    GameMessage *msg = TheMessageStream->appendMessage( GameMessage::MSG_SET_BEACON_TEXT );
                    UnicodeString newText = GadgetTextEntryGetText( control );
                    TheLanguageFilter->filterLine( newText );
                    const WideChar *c = (const WideChar *)newText.str();
                    while( c && *c )
                    {
                        msg->appendWideCharArgument( *c++ );
                    }
                    msg->appendWideCharArgument( L'\0' );
                }
            }
            break;
        }

        default:
            return MSG_IGNORED;
    }

    return MSG_HANDLED;
}
