// cl: /DNDEBUG /MD /EHsc
//
// BfmeAptScreenOnlineChat::_bfme_onBttnAccept, retail 0x00535090, 152 bytes.
// Retail 0x00536FB3 pushes the selector string
// "AptOnline::OnlineChat::OnBttnAccept" and loads this body's ILT thunk a few
// bytes later, which is what names it. The 152 bytes cover the 135-byte body,
// one alignment nop and the four-entry jump table that follows it.
//
// The dialog mode at this+0xA8 says which of the four add and remove text
// entries the accept button applies. Each branch hands the window out of its
// gadget slot to the matching handler. The screen then gives the chat entry
// focus back, clears the dialog mode and refreshes the three lists.

typedef int Int;

class GameWindow;

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

// The gadget slot BfmeAptScreenOnlineChatInitGadgets.cpp attaches each text
// entry to. Its window sits eight bytes in, the same place
// BfmeAptScreenInGameChatFriendPanel.cpp reads it.
class Gen_00479A60
{
public:
	GameWindow *window() { return m_window; }

private:
	unsigned char m_unmodelled000[ 8 ];
	GameWindow *m_window;
	unsigned char m_unmodelled00C[ 4 ];
};

void Rva00533EA0( GameWindow *listbox );

extern GameWindowManager *TheWindowManager;

// Layout witnessed by BfmeAptScreenOnlineChatInitGadgets.cpp at 0x00534A60.
class BfmeAptScreenOnlineChat
{
public:
	void _bfme_onBttnAccept( const char *name );
	void Rva0052E4C0( GameWindow *entry );
	void Rva0052E5B0( GameWindow *entry );
	void Rva0052E680( GameWindow *entry );
	void Rva0052E7B0( GameWindow *entry );
	void Rva005337E0( void );
	void Rva00534380( void );

private:
	unsigned char m_unmodelled000[ 0x44 ];
	GameWindow *m_friendsList;
	unsigned char m_unmodelled048[ 8 ];
	GameWindow *m_chatEntry;
	unsigned char m_unmodelled054[ 4 ];
	Gen_00479A60 m_addIgnoreSlot;
	Gen_00479A60 m_addFriendSlot;
	Gen_00479A60 m_removeIgnoreSlot;
	Gen_00479A60 m_removeFriendSlot;
	unsigned char m_unmodelled098[ 0xa8 - 0x98 ];
	Int m_dialogMode;
};

void BfmeAptScreenOnlineChat::_bfme_onBttnAccept( const char *name )
{
	(void)name;
	switch ( m_dialogMode )
	{
	case 0:
		Rva0052E4C0( m_addFriendSlot.window() );
		break;
	case 1:
		Rva0052E680( m_addIgnoreSlot.window() );
		break;
	case 2:
		Rva0052E5B0( m_removeFriendSlot.window() );
		break;
	case 3:
		Rva0052E7B0( m_removeIgnoreSlot.window() );
		break;
	}

	TheWindowManager->slot44( m_chatEntry );
	m_dialogMode = 4;
	Rva005337E0();
	Rva00533EA0( m_friendsList );
	Rva00534380();
}
