// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	int winEnable(bool enable);
	void bfmeClose(bool close);
};

class BfmeTransitionMD
{
public:
	void bfmeDetach(GameWindow *window);
};

extern BfmeTransitionMD *g_bfmeTransitionMD;
void bfmeTransitionFinished(void);

class Gen_00588D10
{
public:
	void bfmeFinish(void);

private:
	char m_bfme00[0x1A0];
	bool m_bfmeActive;
	char m_bfme1A1[3];
	GameWindow *m_bfmeWindow;
};

// ?bfmeFinish@Gen_00588D10@@QAEXXZ
void Gen_00588D10::bfmeFinish(void)
{
	if (!m_bfmeActive)
		return;

	if (m_bfmeWindow)
	{
		if (g_bfmeTransitionMD)
			g_bfmeTransitionMD->bfmeDetach(m_bfmeWindow);
		m_bfmeWindow->winEnable(false);
		m_bfmeWindow->bfmeClose(true);
	}

	bfmeTransitionFinished();
	m_bfmeActive = false;
}
