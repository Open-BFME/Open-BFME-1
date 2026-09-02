// stlport
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class AsciiStringCompareShim
{
public:
	int compare(const AsciiString &other) const;
};

struct AsciiStringStorage
{
	void *m_data;
};

class AsciiStringDtorShim
{
public:
	void destroy(void);
};

class GameInfo
{
public:
	AsciiString getMap(void) const;
	void setMap(AsciiString mapName);
};

class GameInfoMapShim
{
public:
	AsciiString *getMapTo(AsciiString *result) const;
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

class Gen_00525EE0
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
// ?bfmeSetMap@Gen_00525EE0@@QAEXABVAsciiString@@@Z
void Gen_00525EE0::bfmeSetMap(const AsciiString &mapName)
{
	if (m_first && !m_owner->bfmeContains(m_first))
		m_first = 0;
	if (m_second && !m_owner->bfmeContains(m_second))
		m_second = 0;

	if (m_first)
	{
		AsciiStringStorage current;
		bool changed = reinterpret_cast<const AsciiStringCompareShim *>(&mapName)->compare(
			*reinterpret_cast<const GameInfoMapShim *>(m_first)->getMapTo(
				reinterpret_cast<AsciiString *>(&current))) != 0;
		reinterpret_cast<AsciiStringDtorShim *>(&current)->destroy();
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
