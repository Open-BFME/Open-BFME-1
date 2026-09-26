// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringbaseunicode /ICode/Libraries/Source/WWVegas/WWLib
// ControlBar::setControlCommand(GameWindow *, const CommandButton *), retail
// 0x0049EDE0, 603 bytes -- the GameWindow overload the AsciiString overload
// (ControlBar_setControlCommand_Thunk.cpp, 0x0049F0E0) forwards to.
//
// Zero Hour twin: GeneralsMD ControlBar.cpp setControlCommand. BFME keeps its
// skeleton (check-like option, button image, text, user data, border,
// hot key, alt sound) and changes it:
//   - the "is a push button" test is GameWindow vtable slot 8 (+0x20; retail
//     vtable 0x010F7778, body 0x00477DD0 compares the input callback at
//     +0x1E0 with GadgetPushButtonInput's ILT 0x00011F54), and a NULL
//     command button no longer returns early;
//   - a button with an image clears its text; one without clears enabled
//     images 0, 5 and 6 and shows the translated command name unless the
//     name starts with "NonCommand_";
//   - the tooltip callback is set unconditionally, the button is recorded
//     back into the command button (+0xA4), ShowProductionCount (+0x150,
//     FieldParse table 0x00CFA3B8) gates a call to 0x004BBF20, the alt sound is
//     "GUIControlButtonClick", and a second window callback (+0x1F0) is
//     installed last.
// The by-value UnicodeString arguments are built in place with the
// StringBase<unsigned short> copy constructor (0x00888400), which is what
// reference/shims/stringbaseunicode spells; retail inlines StringBase<char>'s
// str()/isEmpty()/isNotEmpty() against the 8-byte WWLib header.

#include <string.h>
#include "ascii_string.h"
#include "Common/UnicodeString.h"

template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template <> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
template <> inline bool StringBase<char>::isNotEmpty() const { return m_data != 0 && m_data->length != 0; }

class Image;
class WinInstanceData;
class GameWindow;

typedef void (*GameWinTooltipFunc)(GameWindow *, WinInstanceData *, unsigned int);
typedef void (*Rva00478ED0Callback)(GameWindow *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
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
	virtual bool isRva00477DD0() const;			///< slot 8, vtable +0x20

	int winSetEnabledImage(int index, const Image *image);	///< 0x00478FE0
	int winSetTooltipFunc(GameWinTooltipFunc tooltip);	///< 0x00478EB0
	void rva00478ED0(Rva00478ED0Callback callback);		///< 0x00478ED0, stores +0x1F0
};

// CommandButton members: m_options/m_science from the CommandButton
// FieldParse table 0x00CFA3B8 (Options 0x18, Science 0x84,
// ShowProductionCount 0x150); m_name is the ZH member at +0xC.
struct Rva0049EDE0ScienceVec
{
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
	bool empty() const { return m_start == m_finish; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	char m_pad00[0x0C];
	AsciiString m_name;					///< +0x0C
	char m_pad10[0x18 - 0x10];
	unsigned int m_options;					///< +0x18
	char m_pad1C[0x84 - 0x1C];
	Rva0049EDE0ScienceVec m_science;			///< +0x84
	char m_pad90[0xA4 - 0x90];
	mutable GameWindow *m_unmodelledA4;			///< +0xA4
	char m_padA8[0x150 - 0xA8];
	bool m_showProductionCount;				///< +0x150
};

enum { CHECK_LIKE = 0x00000400 };

// Ledger names of the three CommandButton accessors retail calls.
class Gen_0049AFE0 { public: int bfmeCurrent() const; };		///< 0x0049AFE0 (button image)
class Rva0049AC30Object { public: int select(); };			///< 0x0049AC30 (border type)
struct Rva0049B010String : public AsciiString {};
class Rva0049B010Owner { public: const Rva0049B010String &Rva0049B010(); };	///< 0x0049B010 (text label)

class BfmeKeyAWB;
void bfmeGoAWB(BfmeKeyAWB *window);					///< 0x004BBF20

void GadgetButtonEnableCheckLike(GameWindow *g, bool makeCheckLike, bool initiallyChecked);
void GadgetButtonSetEnabledImage(GameWindow *g, const Image *image);
// ZH calls GadgetButtonSetText here; retail's target is the ledger's
// GadgetRadioSetText row (0x004BC6E0, inside the GadgetPushButton range).
void GadgetRadioSetText(GameWindow *g, UnicodeString text);
void GadgetButtonSetData(GameWindow *g, void *data);
void GadgetButtonSetAltSound(GameWindow *g, AsciiString altSound);

// 0x0049CA90: the tooltip ZH passes here; its body calls a TheControlBar method with the window.
void commandButtonTooltip(GameWindow *window, WinInstanceData *instData, unsigned int mouse);
void Rva004BCCE0(GameWindow *window);					///< 0x004BCCE0

enum CommandButtonMappedBorderType { COMMAND_BUTTON_BORDER_NONE = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/HotKey.h
class HotKeyManager
{
public:
	AsciiString searchHotKey(const AsciiString &label);
	void addHotKey(GameWindow *win, const AsciiString &key, bool commandKey);
};
extern HotKeyManager *TheHotKeyManager;		///< [0x012F4C7C], receiver of both HotKeyManager calls

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void setControlCommand(GameWindow *button, const CommandButton *commandButton);

private:
	void setCommandBarBorder(GameWindow *button, CommandButtonMappedBorderType type);
};

// ?setControlCommand@ControlBar@@QAEXPAVGameWindow@@PBVCommandButton@@@Z
void ControlBar::setControlCommand( GameWindow *button, const CommandButton *commandButton )
{
	if( !button->isRva00477DD0() )
		return;

	if( commandButton && (commandButton->m_options & CHECK_LIKE) )
		GadgetButtonEnableCheckLike( button, true, false );
	else
		GadgetButtonEnableCheckLike( button, false, false );

	if( commandButton && ((const Gen_0049AFE0 *)commandButton)->bfmeCurrent() )
	{
		GadgetRadioSetText( button, UnicodeString::TheEmptyString );
		GadgetButtonSetEnabledImage( button,
			(const Image *)((const Gen_0049AFE0 *)commandButton)->bfmeCurrent() );
	}
	else
	{
		button->winSetEnabledImage( 0, 0 );
		button->winSetEnabledImage( 5, 0 );
		button->winSetEnabledImage( 6, 0 );
		if( commandButton && strncmp( commandButton->m_name.str(), "NonCommand_", 11 ) != 0 )
		{
			UnicodeString text;
			text.translate( commandButton->m_name );
			GadgetRadioSetText( button, text );
		}
		else
			GadgetRadioSetText( button, UnicodeString::TheEmptyString );
	}

	GadgetButtonSetData( button, (void *)commandButton );
	if( commandButton == 0 )
		return;

	button->winSetTooltipFunc( commandButtonTooltip );
	if( ((Rva0049B010Owner *)commandButton)->Rva0049B010().isEmpty() && commandButton->m_science.empty() )
		GadgetRadioSetText( button, UnicodeString( L"" ) );

	commandButton->m_unmodelledA4 = button;
	setCommandBarBorder( button,
		(CommandButtonMappedBorderType)((Rva0049AC30Object *)commandButton)->select() );

	if( commandButton->m_showProductionCount )
		bfmeGoAWB( (BfmeKeyAWB *)button );

	if( TheHotKeyManager )
	{
		AsciiString hotKey = TheHotKeyManager->searchHotKey( ((Rva0049B010Owner *)commandButton)->Rva0049B010() );
		if( hotKey.isNotEmpty() )
			TheHotKeyManager->addHotKey( button, hotKey, false );
	}
	GadgetButtonSetAltSound( button, AsciiString( "GUIControlButtonClick" ) );
	button->rva00478ED0( Rva004BCCE0 );
}
