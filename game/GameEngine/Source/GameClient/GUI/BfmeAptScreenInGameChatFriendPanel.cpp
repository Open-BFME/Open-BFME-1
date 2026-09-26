// cl: /DNDEBUG /MD

// FILE: BfmeAptScreenInGameChatFriendPanel.cpp
// A BfmeAptScreenInGameChat method that records a mode at +0x26C and then
// drives one of the two gadget hooks the constructor at 0x005160E0 builds.
//
// The owner is that constructor's class: it fixes the object at 0x2A4 bytes
// with InGameChatSlot m_firstControl at +0x270 and m_secondControl at +0x280,
// and this body reads +0x278 and +0x288, which are the eight-byte mark of
// each of those two slots.  Both are passed to GadgetTextEntrySetText, so
// they hold GameWindow pointers.
//
// Mode 0 sends 'addFriend' through the APT CallChild entry and clears the
// first text entry.  Mode 1 sends 'removeFriend' and clears the second.
//
// The two windows are read through inline accessors rather than directly.
// Reading the members produces the same instructions with ecx and edx where
// retail uses eax; the accessors put eax back.

typedef bool Bool;
typedef int Int;

class GameWindow;

template <class T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	static UnicodeString TheEmptyString;
};

void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );

// The body at 0x004675F0 this reaches through ILT 0x00015235 is the APT
// function invoker: it formats /_level%d and hands the named function its
// five string arguments.
class WindowManager
{
public:
	void *_bfme_callAptFunction( unsigned int level, const char *functionName,
		Int argCount, const char *a0, const char *a1, const char *a2,
		const char *a3, const char *a4 );
};

extern WindowManager *g_theWindowManager;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
#define WINDOW_MANAGER_SLOT(n) virtual void slot##n() = 0
	WINDOW_MANAGER_SLOT(00); WINDOW_MANAGER_SLOT(01); WINDOW_MANAGER_SLOT(02);
	WINDOW_MANAGER_SLOT(03); WINDOW_MANAGER_SLOT(04); WINDOW_MANAGER_SLOT(05);
	WINDOW_MANAGER_SLOT(06); WINDOW_MANAGER_SLOT(07); WINDOW_MANAGER_SLOT(08);
	WINDOW_MANAGER_SLOT(09); WINDOW_MANAGER_SLOT(10); WINDOW_MANAGER_SLOT(11);
	WINDOW_MANAGER_SLOT(12); WINDOW_MANAGER_SLOT(13); WINDOW_MANAGER_SLOT(14);
	WINDOW_MANAGER_SLOT(15); WINDOW_MANAGER_SLOT(16); WINDOW_MANAGER_SLOT(17);
	WINDOW_MANAGER_SLOT(18); WINDOW_MANAGER_SLOT(19); WINDOW_MANAGER_SLOT(20);
	WINDOW_MANAGER_SLOT(21); WINDOW_MANAGER_SLOT(22); WINDOW_MANAGER_SLOT(23);
	WINDOW_MANAGER_SLOT(24); WINDOW_MANAGER_SLOT(25); WINDOW_MANAGER_SLOT(26);
	WINDOW_MANAGER_SLOT(27); WINDOW_MANAGER_SLOT(28); WINDOW_MANAGER_SLOT(29);
	WINDOW_MANAGER_SLOT(30); WINDOW_MANAGER_SLOT(31); WINDOW_MANAGER_SLOT(32);
	WINDOW_MANAGER_SLOT(33); WINDOW_MANAGER_SLOT(34); WINDOW_MANAGER_SLOT(35);
	WINDOW_MANAGER_SLOT(36); WINDOW_MANAGER_SLOT(37); WINDOW_MANAGER_SLOT(38);
	WINDOW_MANAGER_SLOT(39); WINDOW_MANAGER_SLOT(40); WINDOW_MANAGER_SLOT(41);
	WINDOW_MANAGER_SLOT(42); WINDOW_MANAGER_SLOT(43);
#undef WINDOW_MANAGER_SLOT
	virtual void slot44( GameWindow *window ) = 0;
};

extern GameWindowManager *TheWindowManager;

// Layout witnessed by game/GameEngine/Source/GameClient/GUI/
// BfmeAptScreenInGameChatConstructor.cpp at 0x005160E0.
class BfmeAptScreenInGameChat
{
public:
	void rva00512050( Int mode );
	GameWindow *firstWindow() { return m_firstWindow; }
	GameWindow *secondWindow() { return m_secondWindow; }

private:
	unsigned char m_unmodelled000[ 0x250 ];
	unsigned int m_field250;
	unsigned char m_unmodelled254[ 0x26c - 0x254 ];
	Int m_field26C;
	unsigned char m_unmodelled270[ 8 ];
	GameWindow *m_firstWindow;
	unsigned char m_unmodelled27C[ 0xc ];
	GameWindow *m_secondWindow;
};

// @?rva00512050@BfmeAptScreenInGameChat@@QAEXH@Z 0x00512050
void BfmeAptScreenInGameChat::rva00512050( Int mode )
{
	m_field26C = mode;

	switch ( mode )
	{
	case 0:
		g_theWindowManager->_bfme_callAptFunction(
			m_field250, "CallChild", 1, "addFriend", 0, 0, 0, 0 );
		GadgetTextEntrySetText( firstWindow(), UnicodeString::TheEmptyString );
		TheWindowManager->slot44( firstWindow() );
		break;

	case 1:
		g_theWindowManager->_bfme_callAptFunction(
			m_field250, "CallChild", 1, "removeFriend", 0, 0, 0, 0 );
		GadgetTextEntrySetText( secondWindow(), UnicodeString::TheEmptyString );
		TheWindowManager->slot44( secondWindow() );
		break;
	}
}
