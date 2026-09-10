// cl: /DNDEBUG /MD /EHsc
// BFME ControlBar mode transition at retail RVA 0x0049E5A0.

#include <string.h>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

class GameMessage
{
public:
	void appendBooleanArgument(Bool value);
};

class MessageStream
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0;
	virtual void slot0C() = 0; virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0; virtual void slot20() = 0;
	virtual void slot24() = 0; virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual GameMessage *appendMessage(UnsignedInt type) = 0;
};

class InGameUI
{
public:
	#define UI_SLOT(n) virtual void slot##n() = 0;
	UI_SLOT(00) UI_SLOT(04) UI_SLOT(08) UI_SLOT(0C) UI_SLOT(10) UI_SLOT(14)
	UI_SLOT(18) UI_SLOT(1C) UI_SLOT(20) UI_SLOT(24) UI_SLOT(28) UI_SLOT(2C)
	UI_SLOT(30) UI_SLOT(34) UI_SLOT(38) UI_SLOT(3C) UI_SLOT(40) UI_SLOT(44)
	UI_SLOT(48) UI_SLOT(4C) UI_SLOT(50) UI_SLOT(54) UI_SLOT(58) UI_SLOT(5C)
	UI_SLOT(60) UI_SLOT(64) UI_SLOT(68) UI_SLOT(6C) UI_SLOT(70) UI_SLOT(74)
	UI_SLOT(78) UI_SLOT(7C) UI_SLOT(80) UI_SLOT(84) UI_SLOT(88) UI_SLOT(8C)
	UI_SLOT(90) UI_SLOT(94) UI_SLOT(98) UI_SLOT(9C) UI_SLOT(A0) UI_SLOT(A4)
	UI_SLOT(A8) UI_SLOT(AC) UI_SLOT(B0) UI_SLOT(B4) UI_SLOT(B8) UI_SLOT(BC)
	UI_SLOT(C0) UI_SLOT(C4) UI_SLOT(C8) UI_SLOT(CC) UI_SLOT(D0) UI_SLOT(D4)
	UI_SLOT(D8) UI_SLOT(DC) UI_SLOT(E0) UI_SLOT(E4)
	virtual void deselectAllDrawables() = 0;
	#undef UI_SLOT
};

class Gen_00609320
{
public:
	unsigned char m_pad00[8];
	unsigned char m_modeFlag;
};

class GlobalData
{
public:
	unsigned char m_pad00[0xA9D];
	unsigned char m_modeFlag;
};

extern MessageStream *TheMessageStream;
extern InGameUI *TheInGameUI;
extern Gen_00609320 *g_bfmeStateDF;
extern GlobalData *TheWritableGlobalData;

class ControlBar
{
public:
	Int Rva0049E5A0();
	void update();

private:
	unsigned char m_pad00[0x100];
	void *m_commandWindows[20];
	void *m_modeWindows[20];
	void *m_defaultWindows[20];
	unsigned char m_pad1F0[0x2EC - 0x1F0];
	Int m_mode;
};

Int ControlBar::Rva0049E5A0()
{
	switch (m_mode)
	{
	case 0:
		m_mode = 1;
		break;
	case 1:
		if (g_bfmeStateDF != 0 && g_bfmeStateDF->m_modeFlag != 0)
			m_mode = 0;
		else
			m_mode = TheWritableGlobalData->m_modeFlag ? 2 : 0;
		break;
	case 2:
		m_mode = 0;
		break;
	}

	GameMessage *message = TheMessageStream->appendMessage(0x3EB);
	message->appendBooleanArgument(true);
	TheInGameUI->deselectAllDrawables();

	if (m_mode >= 0)
	{
		if (m_mode > 1)
		{
			if (m_mode == 2)
			memcpy(m_commandWindows, m_modeWindows, 0x50);
		}
		else
			memcpy(m_commandWindows, m_defaultWindows, 0x50);
	}

	update();
	return m_mode;
}
