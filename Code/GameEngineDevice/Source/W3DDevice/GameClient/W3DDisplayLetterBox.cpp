// cl: /DNDEBUG /MD /EHsc
// readable body of ?enableLetterBox@W3DDisplay@@UAEX_N@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
// readable body of ?isLetterBoxFading@W3DDisplay@@UAE_NXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
// readable body of ?isLetterBoxed@W3DDisplay@@UAE_NXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
// readable body of ?toggleLetterBox@W3DDisplay@@UAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
//
// The renderer and four consecutive W3DDisplay vtable slots drive the cinematic letter
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
typedef unsigned int UnsignedInt;
typedef int Int;

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
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void rva006E9B70();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void drawFillRect(float x, float y, float width, float height, Int color);
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void rva006E9B80();
	virtual void enableLetterBox(bool enable);
	virtual Bool isLetterBoxFading();
	virtual Bool isLetterBoxed();
	virtual void toggleLetterBox();

protected:
	void renderLetterBox(UnsignedInt currentTime);

private:
	unsigned char m_retailPad04[4];
	UnsignedInt m_width;
	UnsignedInt m_height;
	unsigned char m_retailPad10[0xc0];
	float m_letterBoxFadeLevel;
	bool m_letterBoxEnabled;
	unsigned char m_alignmentPad[3];
	UnsignedInt m_letterBoxFadeStartTime;
};

// ?renderLetterBox@W3DDisplay@@IAEXI@Z
// Retail uses the W3DDisplay vtable's +0xB0 and +0xDC entries for the two
// Render2D state-reset wrappers.  The +0xC0 entry is the matched float
// coordinate drawFillRect overload.  The wrapper at +0xDC is kept
// address-derived because its Render2D target has no recovered source name.
void W3DDisplay::renderLetterBox(UnsignedInt currentTime)
{
	if (m_letterBoxEnabled)
	{
		if (m_letterBoxFadeLevel != 1.0f)
		{
			m_letterBoxFadeLevel = (currentTime - m_letterBoxFadeStartTime) / 1000.0f;
			if (m_letterBoxFadeLevel > 1.0f)
				m_letterBoxFadeLevel = 1.0f;
		}

		UnsignedInt lbcolor = (UnsignedInt)(Int)(m_letterBoxFadeLevel * 255.0f) << 24;

		float topHeight =
			(m_height - (9.0f / 16.0f * m_width)) * 0.5f;
		float width = m_width;
		rva006E9B70();
		drawFillRect(0, 0, width, topHeight, lbcolor);
		rva006E9B80();
		float bottomHeight = m_height;
		float bottomWidth = m_width;
		float bottom =
			m_height - (m_height - (9.0f / 16.0f * m_width)) * 0.5f;
		rva006E9B70();
		drawFillRect(0, bottom, bottomWidth, bottomHeight, lbcolor);
		rva006E9B80();
	}
	else
	{
		if (m_letterBoxFadeLevel != 0.0f)
		{
			m_letterBoxFadeLevel = 1.0f -
				(currentTime - m_letterBoxFadeStartTime) / 1000.0f;
			if (m_letterBoxFadeLevel < 0.0f)
				m_letterBoxFadeLevel = 0.0f;

			UnsignedInt lbcolor = (UnsignedInt)(Int)(m_letterBoxFadeLevel * 255.0f) << 24;

			float topHeight =
				(m_height - (9.0f / 16.0f * m_width)) * 0.5f;
			float width = m_width;
			rva006E9B70();
			drawFillRect(0, 0, width, topHeight, lbcolor);
			rva006E9B80();
		}
		else
		{
			m_letterBoxEnabled = false;
		}
	}
}

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
