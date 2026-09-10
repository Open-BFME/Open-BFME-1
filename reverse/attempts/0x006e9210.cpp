// ?renderLetterBox@W3DDisplay@@IAEXI@Z
// partial score=0.78 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// Retail body: 0x006E9210..0x006E944F (576 bytes), identified by the
// W3DDisplay::draw caller in W3DDisplay.cpp and the upstream declaration of
// W3DDisplay::renderLetterBox(UnsignedInt).  This TU keeps the old retail
// offsets local; it does not alter the shared W3DDisplay header.

typedef unsigned int UnsignedInt;
typedef int Int;

// The retail body dispatches through these three observed W3DDisplay vtable
// slots: reset at +0xB0, drawFillRect at +0xC0, and reset at +0xDC.  The
// unnamed slots are padding only, so no unsupported function identity is
// claimed for them.
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
	virtual void resetBeforeLetterBox();
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
	virtual void resetAfterLetterBox();

protected:
	void renderLetterBox(UnsignedInt currentTime);

private:
	unsigned char m_pad04[4];
	Int m_width;
	Int m_height;
	unsigned char m_pad10[0xc0];
	float m_letterBoxFadeLevel;
	bool m_letterBoxEnabled;
	unsigned char m_padD5[3];
	UnsignedInt m_letterBoxFadeStartTime;
};

#define LETTER_BOX_FADE_TIME 1000.0f

// ?renderLetterBox@W3DDisplay@@IAEXI@Z
void W3DDisplay::renderLetterBox(UnsignedInt currentTime)
{
	if (m_letterBoxEnabled)
	{
		if (m_letterBoxFadeLevel != 1.0f)
		{
			m_letterBoxFadeLevel = (currentTime - m_letterBoxFadeStartTime) / LETTER_BOX_FADE_TIME;
			if (m_letterBoxFadeLevel > 1.0f)
				m_letterBoxFadeLevel = 1.0f;
		}

		UnsignedInt lbcolor = (Int)(m_letterBoxFadeLevel * 255.0f) << 24;

		resetBeforeLetterBox();
		drawFillRect(0, 0, m_width, (m_height - (9.0f / 16.0f * m_width)) * 0.5f, lbcolor);
		resetAfterLetterBox();
		drawFillRect(0, m_height - (m_height - (9.0f / 16.0f * m_width)) * 0.5f, m_width, m_height, lbcolor);
		resetAfterLetterBox();
	}
	else
	{
		// Letter box is disabled, but may still be fading out.
		if (m_letterBoxFadeLevel != 0.0f)
		{
			m_letterBoxFadeLevel = 1.0f - (currentTime - m_letterBoxFadeStartTime) / LETTER_BOX_FADE_TIME;
			if (m_letterBoxFadeLevel < 0.0f)
				m_letterBoxFadeLevel = 0.0f;

			UnsignedInt lbcolor = (Int)(m_letterBoxFadeLevel * 255.0f) << 24;

			resetBeforeLetterBox();
			drawFillRect(0, 0, m_width, (m_height - (9.0f / 16.0f * m_width)) * 0.5f, lbcolor);
			resetAfterLetterBox();
		}
		else
		{
			m_letterBoxEnabled = false;
		}
	}
}
