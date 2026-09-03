// cl: /DNDEBUG /MD /EHsc

// ControlBar::updateContextUnderConstruction, retail 0x004AF660, 48 bytes.
// Twin: ControlBarUnderConstruction.cpp. BFME inlines the under-construction
// flag as a byte test at Object+0x90 bit 2, and the construction percent as
// the Real at Object+0x220. m_displayedConstructPercent is at this+0x68.

typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Real getConstructionPercent(void) const
	{
		return *(const Real *)((const char *)this + 0x220);
	}

	bool testUnderConstruction(void) const
	{
		return (*(const unsigned char *)((const char *)this + 0x90) & 4) != 0;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	Object *getObject(void) { return m_object; }

private:
	char m_slice_pad[0xFC];
	Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void updateConstructionTextDisplay(Object *obj);

protected:
	void updateContextUnderConstruction(void);
	void evaluateContextUI(void);

	char m_slice_pad[0x5C];
	Drawable *m_currentSelectedDrawable;
	char m_slice_padB[0x68 - 0x60];
	Real m_displayedConstructPercent;
};

void ControlBar::updateContextUnderConstruction(void)
{
	Object *obj = m_currentSelectedDrawable->getObject();

	if (!obj->testUnderConstruction())
	{
		evaluateContextUI();
		return;
	}

	if (m_displayedConstructPercent != obj->getConstructionPercent())
		updateConstructionTextDisplay(obj);
}
