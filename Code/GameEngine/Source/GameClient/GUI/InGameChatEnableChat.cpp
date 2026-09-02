// cl: /DNDEBUG /MD
//
// Retail 0x00511340: AptInGameChat enable/disable of the chat entry field and
// send button.  Movie at +0x250; a cached GameWindow at +0x260 is given focus
// when enabling.

class WindowManager
{
public:
	void unidentified_00015235( int movie, const char *function, int argumentCount,
		const void *argument1, const void *argument2, int unused1, int unused2,
		int unused3 );
};

class GameWindow;

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43();
	virtual void winSetFocus( GameWindow *window );
};

extern WindowManager *g_theWindowManager;
extern GameWindowManager *TheWindowManager;

class BfmeAptScreenInGameChat
{
public:
	void _bfme_enableChat( bool enable );

private:
	char m_head[ 0x250 ];
	int m_movie;
	char m_gap[ 0x0C ];
	GameWindow *m_entryWindow;
	char m_gap264[ 0x2C ];
	bool m_busy;
	bool m_enabled;
};

// ?_bfme_enableChat@BfmeAptScreenInGameChat@@QAEX_N@Z
void BfmeAptScreenInGameChat::_bfme_enableChat( bool enable )
{
	if( !m_busy && enable == m_enabled )
		return;

	m_busy = false;
	m_enabled = enable;

	const char *entry = enable ? "EnableChatEntryField" : "DisableChatEntryField";
	g_theWindowManager->unidentified_00015235(
		m_movie, entry, 0, 0, 0, 0, 0, 0 );

	const char *send = enable ? "EnableSendButton" : "DisableSendButton";
	g_theWindowManager->unidentified_00015235(
		m_movie, send, 0, 0, 0, 0, 0, 0 );

	if( m_entryWindow && enable )
		TheWindowManager->winSetFocus( m_entryWindow );
	else
		TheWindowManager->winSetFocus( (GameWindow *)this );
}
