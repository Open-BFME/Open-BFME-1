// cl: /O2 /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0x005280A0 (570 bytes, thiscall, returns bool), called through its
// ILT from the still-dumped 0x00527930.
//
// The multiplayer setup screen's game-start countdown. Its labels are the Zero
// Hour LAN ones ("LAN:HostCanceledGame", "LAN:HostCanceledGameBecausePlayerLeave",
// "LAN:GameStartTimerSingular"/"Plural"; compare LANAPI::OnGameStartTimer in
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameNetwork/LANAPICallbacks.cpp),
// but the state lives on the setup receiver and messages go through its owner.
// The receiver shares MpGameSetup's owner at +4 and calls the matched
// MpGameSetup::bfmeCountReadyPlayers on itself; the class and member names keep
// the address token because the owning class is not proven.

#include "string_base.h"

template <typename T> inline StringBase<T>::StringBase() : m_data(0) {}
template <typename T> inline StringBase<T>::~StringBase() { releaseBuffer(); }

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}

	void __cdecl format(UnicodeString fmt, ...);
};

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class Rva005280A0Owner
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(const UnicodeString &text, int kind) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual bool slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(bool on) = 0;
	virtual void slot15(void) = 0;
};

class MpGameSetup
{
public:
	unsigned short bfmeCountReadyPlayers(void);
};

// Retail 0x00527930 behind ILT 0x00031327: thiscall, one stack word, bool in AL.
class Rva00527930Setup
{
public:
	bool rva00527930(bool arg);
};

class Rva005280A0Setup
{
public:
	bool updateGameStartTimer(void);

private:
	unsigned char m_vtable[4];
	Rva005280A0Owner *m_owner;
	unsigned char m_unmodelled08[0x0F];
	bool m_timerArmed17;
	bool m_starting18;
	unsigned char m_unmodelled19[3];
	int m_deadline1C;
	int m_secondsShown20;
	unsigned char m_unmodelled24[0x104];
	int m_requiredReady128;
};

// ?updateGameStartTimer@Rva005280A0Setup@@QAE_NXZ
bool Rva005280A0Setup::updateGameStartTimer(void)
{
	// Retail 0x012B77AF: referenced by this function only. A function-local
	// static reproduces its scheduling, which an extern global does not.
	static bool s_flag012B77AF;

	if (!m_timerArmed17)
	{
		if (m_deadline1C)
			m_owner->slot02(TheGameText->fetch("LAN:HostCanceledGame"), 2);
		else if (!s_flag012B77AF)
			m_owner->slot02(TheGameText->fetch("LAN:HostCanceledGameBecausePlayerLeave"), 2);

		if (m_starting18)
		{
			m_starting18 = false;
			m_owner->slot14(false);
			if (m_owner->slot12())
				m_owner->slot15();
		}
		s_flag012B77AF = true;
		m_secondsShown20 = 0;
		m_deadline1C = 0;
		return false;
	}

	int remaining = m_deadline1C - timeGetTime();
	if (remaining > 0)
	{
		if (m_starting18)
			return true;

		int seconds = remaining / 1000;
		if (seconds < m_secondsShown20)
		{
			if (seconds > 0)
			{
				UnicodeString text;
				text.format(TheGameText->fetch(seconds == 1 ? "LAN:GameStartTimerSingular" : "LAN:GameStartTimerPlural"), seconds);
				m_owner->slot02(text, 2);
			}
			m_secondsShown20 = seconds;
		}

		if (m_starting18 && ((MpGameSetup *)this)->bfmeCountReadyPlayers() < m_requiredReady128)
		{
			m_deadline1C = 0;
			m_secondsShown20 = 0;
		}
		return true;
	}

	if (!m_starting18)
	{
		m_owner->slot14(true);
		m_starting18 = true;
		s_flag012B77AF = true;
		m_deadline1C = timeGetTime() + 5000;
		return true;
	}

	s_flag012B77AF = true;
	m_timerArmed17 = false;
	if (((MpGameSetup *)this)->bfmeCountReadyPlayers() < m_requiredReady128)
	{
		s_flag012B77AF = false;
		m_deadline1C = 0;
		m_secondsShown20 = 0;
		return true;
	}
	return ((Rva00527930Setup *)this)->rva00527930(false);
}
