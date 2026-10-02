struct Rva00367E30Logic
{
	void bfmeStopAAV(int a, int b);
};

class GameLogic;
extern GameLogic *TheGameLogic;

// TU-local method view of the retail global at 0x012F0898; the global itself is
// declared with its real type (GameLogic *) so the linked build has one symbol.
static inline Rva00367E30Logic *theBfmeGameLogic()
{
	return (Rva00367E30Logic *)TheGameLogic;
}

class ScriptEngine
{
public:
	void bfmeResetAAV(int a);
};

extern ScriptEngine *TheScriptEngine;

class BfmeMsgAAV
{
public:
	void bfmeAppendAAV(int a);
};

class MessageStream
{
public:
	virtual void bfmeSlot0AAV();
	virtual void bfmeSlot1AAV();
	virtual void bfmeSlot2AAV();
	virtual void bfmeSlot3AAV();
	virtual void bfmeSlot4AAV();
	virtual void bfmeSlot5AAV();
	virtual void bfmeSlot6AAV();
	virtual void bfmeSlot7AAV();
	virtual void bfmeSlot8AAV();
	virtual void bfmeSlot9AAV();
	virtual void bfmeSlot10AAV();
	virtual void bfmeSlot11AAV();
	virtual void bfmeSlot12AAV();
	virtual BfmeMsgAAV *bfmeNewMsgAAV(int kind);
};

extern MessageStream *TheMessageStream;

// Retail global 0x012F4B58 is EA's shell singleton, defined once under the
// canonical spelling (Shell *TheShell).
class Shell
{
public:
	unsigned char m_bfmeHeadAAV[0x50];
	unsigned char m_bfme50AAV;
};

// bfmeShowAAV (ILT 0x00006AAA) and bfmeGoAAV (ILT 0x000428ED) are pinned
// under the Shell40D9 spelling, so the calls go through that view; the casts
// are pointer-size neutral.
class Shell40D9
{
public:
	void bfmeShowAAV();
	void bfmeGoAAV(bool a);
};

extern Shell *TheShell;

extern unsigned char g_bfmeDirtyYH;
extern int g_bfmeArgAAV;
extern unsigned char g_bfmeFlagAAV;
extern void *g_bfmePtrAAV;
extern unsigned char g_bfmeDoneAAV;

void bfmeClearAAV(int a);
void bfmeAltAAV(void);

void bfmeShutdownAAV(void);

void bfmeShutdownAAV(void)
{
	g_bfmeDirtyYH = 0;

	theBfmeGameLogic()->bfmeStopAAV(0, 0);
	TheScriptEngine->bfmeResetAAV(g_bfmeArgAAV);

	if (g_bfmeFlagAAV == 0 && g_bfmePtrAAV != 0)
	{
		bfmeAltAAV();
	}
	else
	{
		bfmeClearAAV(0);

		BfmeMsgAAV *m = TheMessageStream->bfmeNewMsgAAV(0x1e);

		m->bfmeAppendAAV(0);
		m->bfmeAppendAAV(g_bfmeArgAAV);
		m->bfmeAppendAAV(0);
	}

	TheShell->m_bfme50AAV = 1;
	((Shell40D9 *)TheShell)->bfmeShowAAV();
	((Shell40D9 *)TheShell)->bfmeGoAAV(true);

	g_bfmeDoneAAV = 1;
}
