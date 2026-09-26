class BfmeHostXP;

struct Rva00579160Manager
{
	void bfmeDetachXP(int id);
	void bfmeCloseXP(int id);
};

extern Rva00579160Manager *Rva00579160TheManager;

class Shell40D9
{
public:
	void bfmeDoneXP(BfmeHostXP *layout, int flag);
};

extern Shell40D9 *TheShell;

class BfmeWinXP
{
public:
	virtual void bfmeVW0() = 0;
	virtual void bfmeVW1() = 0;
	virtual void bfmeVW2() = 0;
	virtual void bfmeVW3() = 0;
	virtual void bfmeVW4() = 0;
	virtual void bfmeVW5() = 0;
	virtual void bfmeVW6() = 0;
	virtual void bfmeVW7() = 0;
	virtual void bfmeVW8() = 0;
	virtual void bfmeVW9() = 0;
	virtual void bfmeVW10() = 0;
	virtual void bfmeVW11() = 0;
	virtual void bfmeVW12() = 0;
	virtual void bfmeShutXP() = 0;

	unsigned char m_bfmeHeadXP[0x24c];
	int m_bfme250XP;
};

class BfmeHostXP
{
public:
	void bfmeCloseAllXP(int unused);

	virtual void bfmeVH0() = 0;
	virtual void bfmeVH1() = 0;
	virtual void bfmeVH2() = 0;
	virtual void bfmeVH3() = 0;
	virtual void bfmeHideXP(int on) = 0;

	unsigned char m_bfmeHeadXP[0x20];
	BfmeWinXP *m_bfme24XP;
	char m_bfme28XP;
};

void BfmeHostXP::bfmeCloseAllXP(int unused)
{
	if (m_bfme24XP == 0)
		return;

	bfmeHideXP(1);
	m_bfme24XP->bfmeShutXP();

	if (m_bfme28XP)
	{
		Rva00579160TheManager->bfmeDetachXP(m_bfme24XP->m_bfme250XP);
		Rva00579160TheManager->bfmeCloseXP(m_bfme24XP->m_bfme250XP);
		m_bfme28XP = 0;
	}

	TheShell->bfmeDoneXP(this, 0);
}
