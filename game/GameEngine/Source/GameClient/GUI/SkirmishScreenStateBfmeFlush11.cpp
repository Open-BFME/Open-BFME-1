// cl: /O2 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

class WinInstanceData;

class UserPreferences
{
public:
	bool getBool(AsciiString key, bool defaultValue) const;
};

class GameInfo
{
public:
	AsciiString getMap() const;
};

class GameWindow
{
public:
	int winSetTooltipFunc(void (*tooltip)(GameWindow *, WinInstanceData *, unsigned int));
};

// Defined in SkirmishMapSelectMenu.cpp (0x00524730).
void mapListTooltipFunc(GameWindow *window, WinInstanceData *instData, unsigned int mouse);

class SkirmishScreenOwner
{
public:
	virtual void slot00() = 0;
	virtual UserPreferences *slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual bool slot24(GameInfo *game) = 0;
};

class SkirmishScreenState
{
public:
	void bfmeFlush11();
	void rva0052A2E0(int flags);
	void rva00528370(const AsciiString &mapName);

private:
	unsigned char m_unmodelled00[4];
	SkirmishScreenOwner *m_owner;
	GameInfo *m_first;
	GameInfo *m_second;
	bool m_flag10;
	bool m_flag11;
	bool m_flag12;
	bool m_flag13;
	bool m_flag14;
	bool m_flag15;
	bool m_flag16;
	bool m_flag17;
	bool m_flag18;
	unsigned char m_unmodelled19[3];
	int m_value1c;
	int m_value20;
	int m_value24;
	unsigned char m_unmodelled28[0xe0];
	GameWindow *m_window108;
};

// Revalidate both cached game records; for a surviving first record pass the
// preference-derived flags and its map to the two list helpers, then install
// mapListTooltipFunc when UseMapListTooltips is set.
// ?bfmeFlush11@SkirmishScreenState@@QAEXXZ
void SkirmishScreenState::bfmeFlush11()
{
	if (m_first && !m_owner->slot24(m_first))
		m_first = 0;

	if (m_second && !m_owner->slot24(m_second))
		m_second = 0;

	if (m_first)
	{
		bool useMapListTooltips = m_owner->slot04()->getBool("UseMapListTooltips", false);
		bool useSystemMapDir = m_owner->slot04()->getBool("UseSystemMapDir", true);

		int flags;
		if (useSystemMapDir || !(m_value24 & 1))
		{
			flags = 8;
			if (useSystemMapDir)
				flags |= 1;
		}
		else
			flags = 0;
		if (!useSystemMapDir)
			flags |= 2;
		flags |= 0x10;
		rva0052A2E0(flags);
		rva00528370(m_first->getMap());

		m_flag12 = true;
		if (m_window108 && useMapListTooltips)
			m_window108->winSetTooltipFunc(mapListTooltipFunc);
	}
}
