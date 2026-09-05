// cl: /DNDEBUG /MD /GX-
// BFME GameLogic::setGamePaused(bool paused, int pauseMode, bool affectMouse)
// retail 0x00383490 size 300. ZH twin is 2-arg; BFME grew a middle Int.

class BfmeInGameUI_setInputEnabled
{
public:
	bool getInputEnabled() const { return m_inputEnabled && m_inputAllowed; }
	void setEngineInputEnabled(bool enabled);

private:
	unsigned char m_unreconstructed_00[0x0D];
	unsigned char m_inputEnabled;
	unsigned char m_inputAllowed;
};

class Mouse
{
public:
	void _bfme_setEngineVisibility(bool visible);
};

class Win32Mouse
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void setCursor(int cursor);

	bool isCursorVisible();
};

class BfmeAudioPause
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void pauseAudio(unsigned int which, int a, int b);
	virtual void resumeAudio(unsigned int which, int a, int b);
};

#define TheInGameUI (*(BfmeInGameUI_setInputEnabled **)0x012F148C)
#define TheMouse (*(Win32Mouse **)0x012F4C5C)
#define TheMouseVis (*(Mouse **)0x012F4C5C)
#define TheAudio (*(BfmeAudioPause **)0x012ED668)

class BfmeGameLogicPause
{
public:
	void setGamePaused(bool paused, int pauseMode, bool affectMouse);

private:
	unsigned char m_unreconstructed_00[0x11C];
	bool m_gamePaused;
	unsigned char m_pad_11d;
	bool m_inputEnabledMemory;
	bool m_mouseVisibleMemory;
};

void BfmeGameLogicPause::setGamePaused(bool paused, int pauseMode, bool affectMouse)
{
	if (paused == (bool)m_gamePaused)
		return;

	int mode = pauseMode;
	int audToAffect = (mode != 1);
	m_gamePaused = paused;
	audToAffect += 0x1E;
	audToAffect |= 0x20;

	if (paused)
	{
		m_inputEnabledMemory = TheInGameUI->getInputEnabled();
		m_mouseVisibleMemory = TheMouse->isCursorVisible();
		if (affectMouse)
		{
			TheMouseVis->_bfme_setEngineVisibility(true);
			TheMouse->setCursor(2);
		}
		if (m_inputEnabledMemory)
			TheInGameUI->setEngineInputEnabled(false);
		if (mode != 2)
		{
			TheAudio->pauseAudio(audToAffect, 3, 0);
			TheAudio->pauseAudio(audToAffect, 4, 1);
		}
	}
	else
	{
		if (affectMouse)
			TheMouseVis->_bfme_setEngineVisibility(m_mouseVisibleMemory);
		if (m_inputEnabledMemory)
			TheInGameUI->setEngineInputEnabled(true);
		if (mode != 2)
		{
			TheAudio->resumeAudio(audToAffect, 3, 0);
			TheAudio->resumeAudio(audToAffect, 4, 1);
		}
	}
}
