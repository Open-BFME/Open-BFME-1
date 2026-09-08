// ?bfmeNotifyABJ@@YGXPAXH_N@Z
// partial score=0.95 date=2026-09-09
struct BfmeVec3ABJ
{
	int m_bfmeXABJ;
	int m_bfmeYABJ;
	int m_bfmeZABJ;
};

class BfmeSinkABJ
{
public:
	void bfmeEmitABJ(BfmeVec3ABJ *v, int a, int b);
};

struct BfmeOwnerABJ
{
	unsigned char m_bfmeHeadABJ[0x20];
	BfmeSinkABJ m_bfme20ABJ;
};

struct BfmeThingABJ
{
	unsigned char m_bfmeHeadTABJ[0x38];
	int m_bfme38ABJ;
	int m_bfme3CABJ;
	int m_bfme40ABJ;
	unsigned char m_bfmeGapABJ[0x204 - 0x44];
	BfmeOwnerABJ *m_bfme204ABJ;
};

class ScriptEngine
{
public:
	virtual void bfmeSlot0ABJ();
	virtual void bfmeSlot1ABJ();
	virtual void bfmeSlot2ABJ();
	virtual void bfmeSlot3ABJ();
	virtual void bfmeSlot4ABJ();
	virtual void bfmeSlot5ABJ();
	virtual void bfmeSlot6ABJ();
	virtual void bfmeSlot7ABJ();
	virtual void bfmeSlot8ABJ();
	virtual void bfmeSlot9ABJ();
	virtual void bfmeSlot10ABJ();
	virtual void bfmeSlot11ABJ();
	virtual void bfmeSlot12ABJ();
	virtual void bfmeSlot13ABJ();
	virtual void bfmeSlot14ABJ();
	virtual void bfmeSlot15ABJ();
	virtual void bfmeSlot16ABJ();
	virtual void bfmeSlot17ABJ();
	virtual void bfmeSlot18ABJ();
	virtual void bfmeSlot19ABJ();
	virtual void bfmeSlot20ABJ();
	virtual void bfmeSlot21ABJ();
	virtual void bfmeSlot22ABJ();
	virtual void bfmeSlot23ABJ();
	virtual void bfmeSlot24ABJ();
	virtual void bfmeSlot25ABJ();
	virtual struct BfmeThingABJ *bfmeLookupABJ(void *key);

	void bfmeReportABJ(BfmeThingABJ *t, int n);
};

extern ScriptEngine *TheScriptEngine;

void __stdcall bfmeNotifyABJ(void *key, int n, bool scaled);

void __stdcall bfmeNotifyABJ(void *key, int n, bool scaled)
{
	BfmeThingABJ *t = TheScriptEngine->bfmeLookupABJ(key);

	if (t == 0)
		return;

	BfmeOwnerABJ *o = t->m_bfme204ABJ;

	if (o == 0)
		return;

	int x = t->m_bfme38ABJ;
	int y = t->m_bfme3CABJ;
	BfmeVec3ABJ v;

	v.m_bfmeXABJ = x;
	v.m_bfmeYABJ = y;
	v.m_bfmeZABJ = t->m_bfme40ABJ;

	o->m_bfme20ABJ.bfmeEmitABJ(&v, 0, 1);

	if (scaled)
		TheScriptEngine->bfmeReportABJ(t, n * 5);
	else
		TheScriptEngine->bfmeReportABJ(t, n);
}
