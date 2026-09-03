// cl: /DNDEBUG /MD /EHsc
// readable body of ?enableLetterBox@W3DDisplay@@UAEX_N@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

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

private:
	unsigned char m_retailPad[0xd0];
	bool m_letterBoxEnabled;
	unsigned char m_alignmentPad[3];
	unsigned long m_letterBoxFadeStartTime;
};

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
