// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source
// readable body of ?winSetInstanceData@GameWindow@@QAEHPAVWinInstanceData@@@Z: game/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// BFME's GameWindow instance-data member begins at +0x30; the vendored ZH
// declaration places it at +0x2c.  Retail also uses the BFME DisplayString
// vtable slot at +0x0c for getTextLength/getTooltipTextLength.  This narrow
// ABI slice keeps those proven facts local to the recovered body.

// Zero Hour's UnicodeString::releaseBuffer has no retail body: retail's
// inlined destructors call StringBase<unsigned short>::releaseBuffer
// (0x008881D0, StringBase.cpp).  The header's declaration and its inline
// callers are renamed to a TU-local inline that calls that body by name.
#include "Lib/BaseType.h"
#include "Common/Debug.h"
#include "Common/Errors.h"
#define releaseBuffer() bfmeReleaseWideBuffer()
#include "Common/UnicodeString.h"
#undef releaseBuffer
extern "C" void __identifier("?releaseBuffer@?$StringBase@G@@AAEXXZ")(void);
// ?bfmeReleaseWideBuffer@UnicodeString@@IAEXXZ absent-from-retail
inline void UnicodeString::bfmeReleaseWideBuffer()
{
	typedef void (UnicodeString::*ReleaseCall)();
	union { void (*raw)(); ReleaseCall member; } call;
	call.raw = __identifier("?releaseBuffer@?$StringBase@G@@AAEXXZ");
	(this->*call.member)();
}

typedef int Int;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual UnicodeString getText(void);
	virtual void unusedDisplayStringSlot0(void);
	virtual void unusedDisplayStringSlot1(void);
	virtual Int getTextLength(void);
};

class GameWindow;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	virtual ~WinInstanceData(void);

	// retail 0x00478780 (WinInstanceDataAssignment.cpp); this view must not
	// generate its own copy from the byte-array layout.
	WinInstanceData &operator=(const WinInstanceData &);

	UnicodeString getText(void);
	Int getTextLength(void)
	{
		if (m_text)
			return m_text->getTextLength();
		return 0;
	}
	UnicodeString getTooltipText(void);
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
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
