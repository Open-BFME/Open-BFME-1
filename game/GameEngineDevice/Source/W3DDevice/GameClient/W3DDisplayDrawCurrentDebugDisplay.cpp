// cl: /O2 /Ob0 /EHsc

class DebugDisplayInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void reset();
};

typedef void DebugDisplayCallback(DebugDisplayInterface *, void *, void *);

class W3DDisplay
{
public:
	virtual void slot00();
	void drawDisplayStrings();
	void drawDebugStats();
	void drawThirdDebugDisplay();

	protected:
	void drawCurrentDebugDisplay();

private:
	char m_padding04[0x24];
	DebugDisplayInterface *m_debugDisplay;
	DebugDisplayCallback *m_debugDisplayCallback;
	void *m_debugDisplayUserData;
};

#pragma comment(linker, "/alternatename:?drawThirdDebugDisplay@W3DDisplay@@QAEXXZ=?d_006e8800@@YAXXZ")

void W3DDisplay::drawCurrentDebugDisplay()
{
	if (m_debugDisplayCallback ==
		reinterpret_cast<DebugDisplayCallback *>(0x0042f9f0))
	{
		drawDisplayStrings();
		return;
	}

	if (m_debugDisplayCallback ==
		reinterpret_cast<DebugDisplayCallback *>(0x0043413f))
	{
		drawDebugStats();
		return;
	}

	if (m_debugDisplayCallback ==
		reinterpret_cast<DebugDisplayCallback *>(0x0040d779))
	{
		drawThirdDebugDisplay();
		return;
	}

	if (m_debugDisplay != 0 && m_debugDisplayCallback != 0)
	{
		m_debugDisplay->reset();
		m_debugDisplayCallback(m_debugDisplay, m_debugDisplayUserData, 0);
	}
}
