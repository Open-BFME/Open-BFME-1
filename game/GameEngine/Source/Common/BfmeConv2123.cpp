struct Rva00367E30Logic
{
	void bfmeStopAAV(int a, int b);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

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

class Shell40D9
{
public:
	void bfmeShowAAV();
	void bfmeGoAAV(bool a);

	unsigned char m_bfmeHeadAAV[0x50];
	unsigned char m_bfme50AAV;
};

extern Shell40D9 *TheShell;

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

	TheBfmeGameLogic->bfmeStopAAV(0, 0);
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
	TheShell->bfmeShowAAV();
	TheShell->bfmeGoAAV(true);

	g_bfmeDoneAAV = 1;
}
