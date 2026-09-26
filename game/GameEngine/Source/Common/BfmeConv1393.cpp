// Open-BFME5 conversions.

void __cdecl W3DRadarResetLock();
char __cdecl bfmeUnlockVJR();

class BfmeThingVJR
{
public:
	virtual void bfmeV000VJR();
	virtual void bfmeV004VJR();
	virtual void bfmeV008VJR();
	virtual void bfmeV00CVJR();
	virtual void bfmeV010VJR();
	virtual void bfmeV014VJR();
	virtual void bfmeV018VJR();
	virtual void bfmeV01CVJR();
	virtual void bfmeV020VJR();
	virtual void bfmeV024VJR();
	virtual void bfmeV028VJR();
	virtual void bfmeV02CVJR();
	virtual void bfmeV030VJR();
	virtual void bfmeV034VJR();
	virtual void bfmeV038VJR();
	virtual void bfmeV03CVJR();
	virtual void bfmeV040VJR();
	virtual void bfmeV044VJR();
	virtual void bfmeV048VJR();
	virtual void bfmeV04CVJR();
	virtual void bfmeV050VJR();
	virtual void bfmeV054VJR();
	virtual void bfmeV058VJR();
	virtual void bfmeV05CVJR();
	virtual void bfmeV060VJR();
	virtual void bfmeV064VJR();
	virtual void bfmeV068VJR();
	virtual void bfmeV06CVJR();
	virtual void bfmeV070VJR();
	virtual void bfmeV074VJR();
	virtual void bfmeV078VJR();
	virtual void bfmeV07CVJR();
	virtual void bfmeV080VJR();
	virtual void bfmeV084VJR();
	virtual void bfmeV088VJR();
	virtual void bfmeV08CVJR();
	virtual void bfmeV090VJR();
	virtual void bfmeV094VJR();
	virtual void bfmeV098VJR();
	virtual void bfmeV09CVJR();
	virtual void bfmeV0A0VJR();
	virtual void bfmeV0A4VJR();
	virtual void bfmeV0A8VJR();
	virtual void bfmeV0ACVJR();
	virtual void bfmeV0B0VJR();
	virtual void bfmeV0B4VJR();
	virtual void bfmeV0B8VJR();
	virtual void bfmeV0BCVJR();
	virtual void bfmeV0C0VJR();
	virtual void bfmeV0C4VJR();
	virtual void bfmeV0C8VJR();
	virtual void bfmeV0CCVJR();
	virtual void bfmeV0D0VJR();
	virtual void bfmeV0D4VJR();
	virtual void bfmeV0D8VJR();
	virtual void bfmeV0DCVJR();
	virtual void bfmeV0E0VJR();
	virtual void bfmeV0E4VJR();
	virtual void bfmeV0E8VJR();
	virtual void bfmeV0ECVJR();
	virtual void bfmeV0F0VJR();
	virtual void bfmeV0F4VJR();
	virtual void bfmeV0F8VJR();
	virtual void bfmeV0FCVJR();
	virtual void bfmeV100VJR();
	virtual void bfmeV104VJR();
	virtual void bfmeV108VJR();
	virtual void bfmeV10CVJR();
	virtual void bfmeV110VJR();
	virtual void bfmeV114VJR();
	virtual void bfmeV118VJR();
	virtual void bfmeV11CVJR();
	virtual void bfmeV120VJR();
	virtual void bfmeV124VJR();
	virtual void bfmeV128VJR();
	virtual void bfmeV12CVJR();
	virtual void bfmeV130VJR();
	virtual void bfmeV134VJR();
	virtual void bfmeV138VJR();
	virtual void bfmeV13CVJR();
	virtual void bfmeV140VJR();
	virtual void bfmeV144VJR();
	virtual void bfmeV148VJR();
	virtual void bfmeV14CVJR();
	virtual void bfmeV150VJR();
	virtual void bfmeV154VJR();
	virtual void bfmeV158VJR();
	virtual void bfmeV15CVJR();
	virtual void bfmeV160VJR();
	virtual void bfmeV164VJR(int n);
	int bfmeGoVJR(int force);
	char m_bfmePad[0x38];
	int m_bfme3c;
	int m_bfme40;
};

int BfmeThingVJR::bfmeGoVJR(int force)
{
	if (force || (m_bfme3c == 0 && m_bfme40 == 0))
	{
		W3DRadarResetLock();
		bfmeV164VJR(3);
		bfmeUnlockVJR();
	}
	return 0;
}

void __cdecl bfmeDelArrVJS(void *p);

extern int g_bfmeVftAVJS[];
extern int g_bfmeVftBVJS[];

class BfmeThingVJS
{
public:
	void bfmeClearVJS();
	void *m_bfmeVfptr;
	int m_bfme04;
	int m_bfme08;
	void *m_bfme0c;
	int m_bfme10;
	void *m_bfme14;
	void *m_bfme18;
};

void BfmeThingVJS::bfmeClearVJS()
{
	m_bfmeVfptr = g_bfmeVftAVJS;
	m_bfme08 = 0;
	if (m_bfme0c)
	{
		bfmeDelArrVJS(m_bfme0c);
		m_bfme0c = 0;
	}
	m_bfme10 = 0;
	if (m_bfme14)
	{
		bfmeDelArrVJS(m_bfme14);
		m_bfme14 = 0;
	}
	m_bfmeVfptr = g_bfmeVftBVJS;
	if (m_bfme18)
		m_bfme18 = 0;
}
