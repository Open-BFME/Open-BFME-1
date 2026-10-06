// cl: /DNDEBUG /MD /GX- /O2 /Ob2

typedef bool Bool;

struct QuitMenu
{
	char m_bfmeHead[0x254];
	Bool m_hidden;
	char m_bfmeGap[0x25C - 0x255];
	int m_field25C;
};

class Shell
{
public:
	char m_bfmeHead[0x50];
	Bool m_isShellActive;
};

class WindowManager;

// Retail calls ILT 000290D2 -> the existing Rva00465B80::apply provider.
// Preserve its declaration from TinyByteFieldSetters.cpp. This byte setter
// establishes the +1AC write, not the manager's original semantic class.
class Rva00465B80
{
public:
	void apply();
	char m_lead[0x1AC];
	char m_flag;
};

class VictoryConditionsInterface
{
public:
	virtual void bfme00() = 0;
	virtual void bfme01() = 0;
	virtual void bfme02() = 0;
	virtual void bfme03() = 0;
	virtual void bfme04() = 0;
	virtual void bfme05() = 0;
	virtual void bfme06() = 0;
	virtual void bfme07() = 0;
	virtual void bfme08() = 0;
	virtual void bfme09() = 0;
	virtual void bfme10() = 0;
	virtual void bfme11() = 0;
	virtual void bfme12() = 0;
	virtual Bool isLocalAlliedVictory() = 0;
};

class GameMessage
{
public:
	void appendBooleanArgument(Bool value);
};

class MessageStream
{
public:
	virtual void bfme00() = 0;
	virtual void bfme01() = 0;
	virtual void bfme02() = 0;
	virtual void bfme03() = 0;
	virtual void bfme04() = 0;
	virtual void bfme05() = 0;
	virtual void bfme06() = 0;
	virtual void bfme07() = 0;
	virtual void bfme08() = 0;
	virtual void bfme09() = 0;
	virtual void bfme10() = 0;
	virtual void bfme11() = 0;
	virtual void bfme12() = 0;
	virtual GameMessage *appendMessage(unsigned int type) = 0;
};

class InGameUI
{
public:
	char m_bfmeHead[0x12BE];
	Bool m_clientQuiet;
};

class BfmeAptScreenQuitMenu;
extern BfmeAptScreenQuitMenu *g_obj12F4B40;
extern Shell *TheShell;
extern WindowManager *g_rva012F19E8WindowManager;	// retail 0x012F19E8
extern VictoryConditionsInterface *TheVictoryConditions;
extern MessageStream *TheMessageStream;
extern InGameUI *TheInGameUI;

// ?surrenderQuitMenu@@YAXXZ
void surrenderQuitMenu()
{
	QuitMenu *menu = static_cast<QuitMenu *>(reinterpret_cast<void * &>(g_obj12F4B40));
	if (menu && !menu->m_hidden)
	{
		menu->m_hidden = true;
		static_cast<QuitMenu *>(reinterpret_cast<void * &>(g_obj12F4B40))->m_field25C = 0;
		TheShell->m_isShellActive = true;
		reinterpret_cast<Rva00465B80 *>(g_rva012F19E8WindowManager)->apply();
	}

	if (TheVictoryConditions->isLocalAlliedVictory())
		return;

	GameMessage *message = TheMessageStream->appendMessage(0x447);
	message->appendBooleanArgument(false);
	TheInGameUI->m_clientQuiet = true;
}
