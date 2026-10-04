// Open-BFME5 conversions.

// Every helper this file reaches is called through retail's own
// incremental-link thunk, which the ledger owns as ?j_<rva>@@YAXXZ; retail
// carries no body name for the callees, so the thunks are the only identities
// the image proves. The thiscall is spelled as a one-argument __fastcall so
// the object pointer still lands in ECX.
extern void j_00020c84();
extern void j_0000a754();
extern void j_0003fbf7();
extern void j_0000e570();

typedef void (__fastcall *VoidOn)(void *object);
typedef void *(__fastcall *GoalOf)(void *object);

// Retail's global at 0x012F1024 is EA's LivingWorldCampaignManager singleton,
// defined once in GameEngine/Source/GameLogic/LivingWorld/
// LivingWorldCampaignManager.cpp; this reference carries that canonical type
// and the call casts at the one use.
class LivingWorldCampaignManager;

extern LivingWorldCampaignManager *TheLivingWorldCampaignManager;

class BfmeB1003
{
public:
	void bfmeGo1003B(char a, char b);

	char m_bfmePad[0x80];
	char m_bfmeOn;
};

void BfmeB1003::bfmeGo1003B(char a, char b)
{
	if (m_bfmeOn) {
		((VoidOn)j_00020c84)((void *)TheLivingWorldCampaignManager);
		((VoidOn)j_0000a754)(this);
	}

	if (!a && !b)
		((VoidOn)j_0003fbf7)(this);
}

class BfmeSink1003
{
public:
	virtual void bfmeVS01003();
	virtual void bfmeVS11003();
	virtual void bfmeVS21003();
	virtual void bfmeVS31003();
	virtual int bfmeRun1003();
	virtual void bfmeVS51003();
	virtual void bfmeVS61003();
	virtual void bfmeVS71003();
	virtual void bfmeVS81003();
	virtual void bfmeVS91003();
	virtual void bfmeVS101003();
	virtual void bfmeVS111003();
	virtual void bfmeVS121003();
	virtual void bfmeVS131003();
	virtual void bfmeSet1003(void *g);
};

class BfmeC1003
{
public:
	int bfmeGo1003C();

	char m_bfmePad[0x1c];
	void *m_bfmeHold;
	char m_bfmePad2[4];
	BfmeSink1003 *m_bfmeSink;
};

int BfmeC1003::bfmeGo1003C()
{
	if (!m_bfmeSink)
		return -2;

	void *g = ((GoalOf)j_0000e570)(m_bfmeHold);

	if (g && g != ((GoalOf)j_0000e570)(m_bfmeSink))
		m_bfmeSink->bfmeSet1003(g);

	return m_bfmeSink->bfmeRun1003();
}