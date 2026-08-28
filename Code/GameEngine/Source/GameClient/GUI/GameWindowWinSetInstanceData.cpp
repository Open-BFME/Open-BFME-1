// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source
// readable body of ?winSetInstanceData@GameWindow@@QAEHPAVWinInstanceData@@@Z: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// BFME's GameWindow instance-data member begins at +0x30; the vendored ZH
// declaration places it at +0x2c.  Retail also uses the BFME DisplayString
// vtable slot at +0x0c for getTextLength/getTooltipTextLength.  This narrow
// ABI slice keeps those proven facts local to the recovered body.

#include "Common/UnicodeString.h"

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual UnicodeString getText(void);
	virtual void unusedDisplayStringSlot0(void);
	virtual void unusedDisplayStringSlot1(void);
	virtual Int getTextLength(void);
};

class GameWindow;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	virtual ~WinInstanceData(void);

	UnicodeString getText(void)
	{
		if (m_text)
			return m_text->getText();
		return UnicodeString::TheEmptyString;
	}
	Int getTextLength(void)
	{
		if (m_text)
			return m_text->getTextLength();
		return 0;
	}
	UnicodeString getTooltipText(void)
	{
		if (m_tooltip)
			return m_tooltip->getText();
		return UnicodeString::TheEmptyString;
	}
	Int getTooltipTextLength(void)
	{
		if (m_tooltip)
			return m_tooltip->getTextLength();
		return 0;
	}
	void setText(UnicodeString text);
	void setTooltipText(UnicodeString text);

	unsigned char m_bfmePrefix[0x198];
	DisplayString *m_text;
	DisplayString *m_tooltip;
	void *m_videoBuffer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winSetInstanceData(WinInstanceData *data);

	unsigned char m_bfmePrefix[0x30];
	WinInstanceData m_instData;
};

Int GameWindow::winSetInstanceData(WinInstanceData *data)
{
	DisplayString *text, *tooltipText;

	text = m_instData.m_text;
	tooltipText = m_instData.m_tooltip;

	m_instData = *data;

	m_instData.m_text = text;
	m_instData.m_tooltip = tooltipText;
	m_instData.m_videoBuffer = NULL;

	if (data->getTextLength())
		m_instData.setText(data->getText());
	if (data->getTooltipTextLength())
		m_instData.setTooltipText(data->getTooltipText());

	return 0;
}
