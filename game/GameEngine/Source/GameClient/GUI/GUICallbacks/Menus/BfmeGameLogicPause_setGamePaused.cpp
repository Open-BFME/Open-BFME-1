// cl: /DNDEBUG /MD /GX-
// BFME GameLogic::setGamePaused(bool paused, int pauseMode, bool affectMouse)
// retail 0x00383490 size 300. ZH twin is 2-arg; BFME grew a middle Int.
//
// `BfmeGameLogicPause` is a TU-local call view, NOT a retail class: this body's
// ecx is TheGameLogic (0x012F0898) and it stores to GameLogic+0x11C, the byte
// mods/features/039-replayctl documents as the pause flag, so the retail class
// is GameLogic. The consequence is a grep trap -- `?setGamePaused@GameLogic@@`
// matches no ledger row, so a modder searching for it lands on
// GameLogic.cpp:7322, whose two-argument (Bool, Bool) body is Zero Hour's and
// is NOT what retail runs. That body is marked present-unmatched and has no
// byte evidence; this 300-byte one does. The middle argument here is a dword
// mode tested against 1 and 2, not ZH's Bool pauseMusic.

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
};

// Same declaration as the existing owner in R2PairedGuardTests.cpp. Retail's
// call at 0x003834EF goes through ILT 0x00023FA6 to the complete 29-byte body
// at 0x005A44B0. It receives this in ECX, takes no stack arguments and returns
// with bare RET. Both exits define all of EAX: 1 when the bytes at +0x4DA1
// and +0x4DA2 are nonzero, otherwise 0. Keep that owner's 32-bit int return ABI.
class Rva005A44B0
{
public:
	char m_leading[0x4DA1];
	bool m_first;
	bool m_second;
	int test();
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

class InGameUI;
class AudioManager;
extern InGameUI *TheInGameUI;
extern Mouse *TheMouse;
extern AudioManager *TheAudio;

#define TheInGameUI ((BfmeInGameUI_setInputEnabled *)TheInGameUI)
#define TheMouse ((Win32Mouse *)TheMouse)
#define TheMouseVis ((Mouse *)TheMouse)
#define TheAudio ((BfmeAudioPause *)TheAudio)

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
		// Retail stores only AL at 0x003834F4, without an Int-to-bool test.
		// The proven 0/1 range is already a valid one-byte MSVC bool object
		// representation, so write that byte through its unsigned-char view.
		reinterpret_cast<unsigned char &>(m_mouseVisibleMemory) =
			static_cast<unsigned char>(reinterpret_cast<Rva005A44B0 *>(TheMouse)->test());
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
