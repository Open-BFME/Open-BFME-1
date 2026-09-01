// Open-BFME5 conversions.

char __cdecl bfmeCheckVHJ();
void __cdecl bfmeRecordVHJ(int n);

class BfmeMsgVHJ
{
public:
	virtual void bfmeSlot00VHJ();
	virtual void bfmeSlot04VHJ();
	virtual void bfmeSlot08VHJ();
	virtual void bfmeSlot0CVHJ();
	virtual void bfmeSlot10VHJ();
	virtual void bfmeSlot14VHJ();
	virtual void bfmeSlot18VHJ();
	virtual void bfmeSlot1CVHJ();
	virtual void bfmeSlot20VHJ();
	virtual void bfmeSlot24VHJ();
	virtual void bfmeSlot28VHJ();
	virtual void bfmeSlot2CVHJ();
	virtual void bfmeSlot30VHJ();
	virtual void bfmeSlot34VHJ();
	virtual class BfmeMsgVHJ *bfmeSlot38VHJ(const char *t);
	virtual void bfmeSlot3CVHJ();
	virtual void bfmeSlot40VHJ();
	virtual void bfmeSlot44VHJ();
	virtual void bfmeSlot48VHJ();
	virtual void bfmeSlot4cVHJ(int n);
	virtual void bfmeSlot50VHJ();
	virtual void bfmeSlot54VHJ();
	virtual void bfmeSlot58VHJ();
	virtual void bfmeSlot5CVHJ();
	virtual void bfmeSlot60VHJ();
	virtual void bfmeSlot64VHJ();
	virtual void bfmeSlot68VHJ();
	virtual void bfmeSlot6CVHJ();
};

class BfmeLogVHJ
{
public:
	virtual void bfmeOwn00VHJ();
	virtual void bfmeOwn04VHJ();
	virtual void bfmeOwn08VHJ();
	virtual void bfmeOwn0CVHJ();
	virtual void bfmeOwn10VHJ();
	virtual void bfmeOwn14VHJ();
	virtual void bfmeOwn18VHJ();
	virtual void bfmeOwn1CVHJ();
	virtual void bfmeOwn20VHJ();
	virtual void bfmeOwn24VHJ();
	virtual void bfmeOwn28VHJ();
	virtual void bfmeOwn2CVHJ();
	virtual void bfmeOwn30VHJ();
	virtual void bfmeOwn34VHJ();
	virtual void bfmeOwn38VHJ();
	virtual void bfmeOwn3CVHJ();
	virtual void bfmeOwn40VHJ();
	virtual void bfmeOwn44VHJ();
	virtual void bfmeOwn48VHJ();
	virtual void bfmeOwn4CVHJ();
	virtual void bfmeOwn50VHJ();
	virtual void bfmeOwn54VHJ();
	virtual void bfmeOwn58VHJ();
	virtual void bfmeOwn5CVHJ();
	virtual void bfmeOwn60VHJ();
	virtual void bfmeOwn64VHJ();
	virtual void bfmeOwn68VHJ();
	virtual class BfmeMsgVHJ *bfmeOwn6cVHJ(int a, int b);
};

extern BfmeLogVHJ *g_bfmeLogVHJ;

struct BfmeCsVHM
{
	char m_bfmePad[24];
};

__declspec(dllimport) unsigned long __stdcall bfmeWaitVHM(void *h, unsigned long ms);
__declspec(dllimport) void __stdcall bfmeEnterVHM(BfmeCsVHM *cs);
__declspec(dllimport) void __stdcall bfmeLeaveVHM(BfmeCsVHM *cs);

int __cdecl bfmeGetIdVHM();

extern void *g_bfmeEventVHM;
extern BfmeCsVHM g_bfmeCsVHM;
extern volatile int g_bfmeOwnerVHM;
extern volatile int g_bfmeDepthVHM;

void __cdecl bfmeLockVHM()
{
	if (bfmeWaitVHM(g_bfmeEventVHM, 20000) == 0x102)
	{
		if (bfmeCheckVHJ())
		{
			bfmeRecordVHJ(1);
			g_bfmeLogVHJ->bfmeOwn60VHJ();
			g_bfmeLogVHJ->bfmeOwn6cVHJ(0, 0)->bfmeSlot38VHJ("A thread held onto DirectX for more than 20000msec.")->bfmeSlot4cVHJ(2);
		}
	}
	bfmeEnterVHM(&g_bfmeCsVHM);
	g_bfmeOwnerVHM = bfmeGetIdVHM();
	g_bfmeDepthVHM = g_bfmeDepthVHM + 1;
	bfmeLeaveVHM(&g_bfmeCsVHM);
}
