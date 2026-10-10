// stlport
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

extern "C" void __identifier("?getMap@GameInfo@@QBE?AVAsciiString@@XZ")();
extern "C" void __identifier("?compare@?$StringBase@D@@QBEHABV1@@Z")();
extern "C" void __identifier("?releaseBuffer@?$StringBase@D@@AAEXXZ")();

struct AsciiStringStorage
{
	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	AsciiString getMap(void) const;
	void setMap(AsciiString mapName);
};

class Gen00525EE0Owner
{
public:
	virtual void bfmeSlot0(void) = 0;
	virtual void bfmeSlot1(void) = 0;
	virtual void bfmeSlot2(void) = 0;
	virtual void bfmeSlot3(void) = 0;
	virtual void bfmeSlot4(void) = 0;
	virtual void bfmeSlot5(void) = 0;
	virtual void bfmeSlot6(void) = 0;
	virtual void bfmeSlot7(void) = 0;
	virtual void bfmeMapChanged(const AsciiString *mapName) = 0;
	virtual bool bfmeContains(GameInfo *game) = 0;
};

class MpGameSetup
{
public:
	void bfmeRefresh(void);
	void bfmeSetMap(const AsciiString &mapName);
private:
	unsigned char m_unmodelled[4];
	Gen00525EE0Owner *m_owner;
	GameInfo *m_first;
	GameInfo *m_second;
	bool m_flag10;
	unsigned char m_unmodelled11[1];
	bool m_flag12;
	bool m_flag13;
	bool m_flag14;
	bool m_flag15;
};

// Update the active game's map only when its name changed and mark every
// dependent presentation field dirty.
// ?bfmeSetMap@MpGameSetup@@QAEXABVAsciiString@@@Z
void MpGameSetup::bfmeSetMap(const AsciiString &mapName)
{
	if (m_first && !m_owner->bfmeContains(m_first))
		m_first = 0;
	if (m_second && !m_owner->bfmeContains(m_second))
		m_second = 0;

	if (m_first)
	{
		AsciiStringStorage current;
		// The native nontrivial return ABI takes a hidden output pointer and
		// returns that pointer in EAX; retail cleans its one stack slot.
		union { void (*raw)(); AsciiString *(GameInfo::*member)(AsciiString *) const; } getMap;
		getMap.raw = __identifier("?getMap@GameInfo@@QBE?AVAsciiString@@XZ");
		union { void (*raw)(); int (StringBase<char>::*member)(const StringBase<char> &) const; } compare;
		compare.raw = __identifier("?compare@?$StringBase@D@@QBEHABV1@@Z");
		bool changed = (reinterpret_cast<const StringBase<char> *>(&mapName)->*compare.member)(
			*reinterpret_cast<const StringBase<char> *>((m_first->*getMap.member)(
				reinterpret_cast<AsciiString *>(&current)))) != 0;
		union { void (*raw)(); void (StringBase<char>::*member)(); } release;
		release.raw = __identifier("?releaseBuffer@?$StringBase@D@@AAEXXZ");
		(reinterpret_cast<StringBase<char> *>(&current)->*release.member)();
		if (changed)
		{
			m_first->setMap(mapName);
			m_owner->bfmeMapChanged(&mapName);
		}
	}
	bfmeRefresh();
	m_flag15 = true;
	m_flag14 = true;
	m_flag10 = true;
	m_flag12 = true;
	m_flag13 = true;
}
