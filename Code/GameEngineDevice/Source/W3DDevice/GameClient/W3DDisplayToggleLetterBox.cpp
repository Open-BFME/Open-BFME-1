// cl: /DNDEBUG /MD /EHsc

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

class W3DDisplay
{
public:
	virtual void toggleLetterBox();

private:
	unsigned char m_retailPad[0xd0];
	bool m_letterBoxEnabled;
	unsigned char m_alignmentPad[3];
	unsigned long m_letterBoxFadeStartTime;
};

void W3DDisplay::toggleLetterBox()
{
	m_letterBoxEnabled = !m_letterBoxEnabled;
	m_letterBoxFadeStartTime = timeGetTime();
	if (TheTacticalViewFadeShim)
		TheTacticalViewFadeShim->setZoomLimited(!m_letterBoxEnabled);
}
