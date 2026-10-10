class BfmeHostXP;

class Gen_004674E0
{
public:
	void bfmePop(int id);
};

// Retail global 0x012F19E8. EA's own name for this pointer; see
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp for the definition.
// The pop helper has an address-derived owner; the hide call uses the
// authored WindowManager name and signature.
class WindowManager
{
public:
	bool hideAptWindow(int id);
};
extern WindowManager *g_rva012F19E8WindowManager;

// Retail global 0x012F4B58 is EA's shell singleton, defined once under the
// canonical spelling (Shell *TheShell).
class WindowLayout;
class Shell
{
public:
	void shutdownComplete(WindowLayout *layout, bool impendingPush);
};

extern Shell *TheShell;

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
		((Gen_004674E0 *)g_rva012F19E8WindowManager)->bfmePop(m_bfme24XP->m_bfme250XP);
		g_rva012F19E8WindowManager->hideAptWindow(m_bfme24XP->m_bfme250XP);
		m_bfme28XP = 0;
	}

	TheShell->shutdownComplete(reinterpret_cast<WindowLayout *>(this), false);
}
