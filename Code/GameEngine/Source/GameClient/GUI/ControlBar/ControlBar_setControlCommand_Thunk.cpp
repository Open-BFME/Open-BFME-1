// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Open-BFME5: ControlBar::setControlCommand (the AsciiString overload),
// retail 0x0049F0E0, zh_sweep packet 0049f0e0.
//
// The Zero Hour body unchanged -- look the child window up by name under the
// given parent, and if it exists forward to the GameWindow overload. One byte
// separated it from retail when compiled against the vendored AsciiString:
// str() reaches the characters at m_data+8, not m_data+4. BFME's
// AsciiStringData carries one extra 4-byte field ahead of the text, the same
// drift Win32LocalFileSystem.cpp and W3DDisplayString.cpp already record.
//
// It gets its own TU rather than an include-path swap in ControlBar.cpp: that
// file has 55 other matched rows compiled against the 4-byte header, and the
// shim is per-translation-unit.
//
// winGetWindowFromId is vtable +0xDC on TheWindowManager, slot 55, matching
// ControlBar_getStarImage_Thunk.cpp. nameToKey and the GameWindow overload of
// setControlCommand are direct calls, ILT 0x0003ADD7 and 0x00015DA7.

typedef int Int;
typedef bool Bool;

class GameWindow;
class CommandButton;

enum NameKeyType { NAMEKEY_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);			///< ILT thunk at 0x0003ADD7
};

extern NameKeyGenerator *TheNameKeyGenerator;			///< retail [0x012ED600]

// BFME's string data header is 8 bytes, so the characters begin at m_data+8.
struct AsciiStringData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	const char *str(void) const
	{
		return m_data ? (const char *)((const unsigned char *)m_data + 8) : "";
	}

private:
	AsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void unused1();
	virtual void unused2();
	virtual void unused3();
	virtual void unused4();
	virtual void unused5();
	virtual void unused6();
	virtual void unused7();
	virtual void unused8();
	virtual void unused9();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();
	virtual void unused55();

	virtual GameWindow *winGetWindowFromId(GameWindow *window, NameKeyType id);	///< vtable +0xDC
};

extern GameWindowManager *TheWindowManager;				///< retail [0x012F1B40]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void setControlCommand(GameWindow *button, const CommandButton *commandButton);	///< ILT 0x00015DA7

protected:
	void setControlCommand(const AsciiString &buttonWindowName, GameWindow *parent,
												 const CommandButton *commandButton);
};

// ?setControlCommand@ControlBar@@IAEXABVAsciiString@@PAVGameWindow@@PBVCommandButton@@@Z
void ControlBar::setControlCommand( const AsciiString& buttonWindowName, GameWindow *parent,
																		const CommandButton *commandButton )
{
	NameKeyType winID = TheNameKeyGenerator->nameToKey( buttonWindowName.str() );
	GameWindow *win = TheWindowManager->winGetWindowFromId( parent, winID );

	if( win == 0 )
	{
		return;
	}

	setControlCommand( win, commandButton );
}
