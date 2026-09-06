// cl: /DNDEBUG /MD /EHsc
// readable body of ?enableLetterBox@W3DDisplay@@UAEX_N@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
// readable body of ?isLetterBoxFading@W3DDisplay@@UAE_NXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
// readable body of ?isLetterBoxed@W3DDisplay@@UAE_NXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
// readable body of ?toggleLetterBox@W3DDisplay@@UAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
//
// The four consecutive W3DDisplay vtable slots that drive the cinematic letter
// box. They read and write the same three members, so they need one declaration
// of the class rather than four that disagree about which of the three each one
// can see.
//
// The single layout below is the union of what the four bodies prove:
//   +0xD0  m_letterBoxFadeLevel     (isLetterBoxFading compares it to 0.0/1.0)
//   +0xD4  m_letterBoxEnabled       (all four read it)
//   +0xD8  m_letterBoxFadeStartTime (enableLetterBox and toggleLetterBox stamp it)
// The offsets are retail's, counted from the vtable pointer at +0x00; upstream
// supplies only the words.

typedef bool Bool;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

// The tactical view releases its zoom limit while the bars are in, so only the
// slot at +0x1C that the two setters call is spelled out.
class TacticalViewFadeShim
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void setZoomLimited(bool limited);
};

extern TacticalViewFadeShim *TheTacticalViewFadeShim;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
class W3DDisplay
{
public:
	virtual void enableLetterBox(bool enable);
	virtual Bool isLetterBoxFading();
	virtual Bool isLetterBoxed();
	virtual void toggleLetterBox();

private:
	unsigned char m_retailPad[0xcc];
	float m_letterBoxFadeLevel;
	bool m_letterBoxEnabled;
	unsigned char m_alignmentPad[3];
	unsigned long m_letterBoxFadeStartTime;
};

// ?enableLetterBox@W3DDisplay@@UAEX_N@Z
void W3DDisplay::enableLetterBox(bool enable)
{
	if (enable)
	{
		if (!m_letterBoxEnabled)
		{
			m_letterBoxEnabled = true;
			m_letterBoxFadeStartTime = timeGetTime();
			if (TheTacticalViewFadeShim)
				TheTacticalViewFadeShim->setZoomLimited(false);
		}
	}
	else if (m_letterBoxEnabled)
	{
		m_letterBoxEnabled = false;
		m_letterBoxFadeStartTime = timeGetTime();
		if (TheTacticalViewFadeShim)
			TheTacticalViewFadeShim->setZoomLimited(true);
	}
}

// ?isLetterBoxFading@W3DDisplay@@UAE_NXZ
Bool W3DDisplay::isLetterBoxFading()
{
	if (m_letterBoxEnabled && m_letterBoxFadeLevel != 1.0f)
		return 1;
	if (!m_letterBoxEnabled && m_letterBoxFadeLevel != 0.0f)
		return 1;
	return 0;
}

// ?isLetterBoxed@W3DDisplay@@UAE_NXZ
Bool W3DDisplay::isLetterBoxed()
{
	return m_letterBoxEnabled;
}

// ?toggleLetterBox@W3DDisplay@@UAEXXZ
void W3DDisplay::toggleLetterBox()
{
	m_letterBoxEnabled = !m_letterBoxEnabled;
	m_letterBoxFadeStartTime = timeGetTime();
	if (TheTacticalViewFadeShim)
		TheTacticalViewFadeShim->setZoomLimited(!m_letterBoxEnabled);
}
