// ?rva005280A0@MpGameSetup@@QAE_NXZ
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Igame/GameEngine/Source/GameClient
//
// Retail 0x005280A0, 570 B (RET at +0x239, INT3 after). MpGameSetup's
// start-countdown tick: it calls the matched countReadyPlayers (0x00524A70,
// ILT 0x0002ED9D) and rva00527930(bool) (0x00527930, ILT 0x00031327) on this.
// Layout: m_owner +0x04, m_pending +0x17, m_backgroundVisible +0x18 (as in
// MpGameSetup.cpp), deadline +0x1C, last shown seconds +0x20 and required
// ready count +0x128 (bank evidence, re_attempts.log 0x005280A0).
//
// The byte flag at 0x012B77AF is read and written only by this body (all
// five retail references to it lie inside 0x005280A0..0x005282DA), so it is
// a file static here; as a static VC7.1 schedules its store after the
// `mov ecx,esi` receiver copy at +0x1E0, which an extern or volatile global
// does not (docs/shape_levers.md, global store schedule).

#include "ascii_string.h"
#include "game_window.h"
#include "Common/UnicodeString.h"

class GameTextInterface
{
public:
	virtual void slot0(void) = 0;
	virtual void slot1(void) = 0;
	virtual void slot2(void) = 0;
	virtual void slot3(void) = 0;
	virtual void slot4(void) = 0;
	virtual void slot5(void) = 0;
	virtual void slot6(void) = 0;
	virtual void slot7(void) = 0;
	virtual void slot8(void) = 0;
	virtual void slot9(void) = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

class Rva005280A0OwnerView
{
public:
	virtual void slot0(void) = 0;
	virtual void slot1(void) = 0;
	virtual void slot2(const UnicodeString &value, int kind) = 0;
	virtual void slot3(void) = 0;
	virtual void slot4(void) = 0;
	virtual void slot5(void) = 0;
	virtual void slot6(void) = 0;
	virtual void slot7(void) = 0;
	virtual void slot8(void) = 0;
	virtual void slot9(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual bool slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(bool visible) = 0;
	virtual void slot15(void) = 0;
};

class MpGameSetup
{
public:
	unsigned short countReadyPlayers(void);
	bool rva00527930(bool arg);
	bool rva005280A0(void);

private:
	unsigned char m_unmodelled[4];
	Rva005280A0OwnerView *m_owner;
	unsigned char m_unmodelled08[0x0F];
	bool m_pending;
	bool m_backgroundVisible;
	unsigned char m_unmodelled19[3];
	int m_field1C;
	int m_field20;
	unsigned char m_unmodelled24[0x104];
	int m_field128;
};

static bool s_rva005280A0Flag;

extern int (__cdecl *g_bfmeNowVNH)(void);

bool MpGameSetup::rva005280A0(void)
{
	if (!m_pending)
	{
		if (m_field1C != 0)
		{
			m_owner->slot2(
				TheGameText->fetch("LAN:HostCanceledGame"), 2);
		}
		else if (!s_rva005280A0Flag)
		{
			m_owner->slot2(
				TheGameText->fetch("LAN:HostCanceledGameBecausePlayerLeave"), 2);
		}

		if (m_backgroundVisible)
		{
			m_backgroundVisible = false;
			m_owner->slot14(false);
			if (m_owner->slot12())
				m_owner->slot15();
		}

		s_rva005280A0Flag = true;
		m_field20 = 0;
		m_field1C = 0;
		return false;
	}

	int (__cdecl *nowFunction)(void) = g_bfmeNowVNH;
	int remaining = m_field1C - nowFunction();
	if (remaining > 0)
	{
		if (m_backgroundVisible)
			goto returnTrue;

		int seconds = remaining / 1000;
		if (seconds < m_field20)
		{
			if (seconds > 0)
			{
				UnicodeString text;
				const char *format = seconds == 1
					? "LAN:GameStartTimerSingular"
					: "LAN:GameStartTimerPlural";
				text.format(TheGameText->fetch(format), seconds);
				m_owner->slot2(text, 2);
			}
			m_field20 = seconds;
		}

		if (m_backgroundVisible)
		{
			if (countReadyPlayers() < m_field128)
			{
				m_field1C = 0;
				m_field20 = 0;
				goto returnTrue;
			}
		}
		goto returnTrue;
	}

	if (!m_backgroundVisible)
	{
		m_owner->slot14(true);
		m_backgroundVisible = true;
		s_rva005280A0Flag = true;
		m_field1C = nowFunction() + 5000;
		return true;
	}

	register MpGameSetup *setup = this;
	s_rva005280A0Flag = true;
	m_pending = false;
	if (setup->countReadyPlayers() < m_field128)
	{
		s_rva005280A0Flag = false;
		m_field1C = 0;
		m_field20 = 0;
		goto returnTrue;
	}

	return rva00527930(false);

returnTrue:
	return true;
}
