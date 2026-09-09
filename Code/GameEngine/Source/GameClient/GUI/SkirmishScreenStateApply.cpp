// cl: /O2 /DNDEBUG /MD /EHsc

class AsciiString
{
public:
	void *m_data;
	~AsciiString();
};

class GameWindow
{
public:
	int winEnable(bool enable);
	int winHide(bool hide);
	int winSetEnabledColor(int index, int color);
	int winBringToTop();
};

class GameInfo
{
public:
	AsciiString getMap() const;
};

class MpGameSetup
{
public:
	void populateMapType();
	void populateGameType();
};

class Gen_00525EE0
{
public:
	void bfmeSetMap(const AsciiString &mapName);
};

class MapCache
{
public:
	void updateCache();
};

void EnableSlotListUpdates(bool enabled);

class SkirmishScreenOwner
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual bool bfmeShouldRestore() = 0;
	virtual void slot13() = 0;
	virtual void bfmeSetVisible(bool visible) = 0;
	virtual void bfmeRestore() = 0;
};

class SkirmishScreenStateMember28
{
public:
	unsigned char m_padding[0x39];
	bool m_flag39;
	unsigned char m_tail[6];
};

class SkirmishScreenState
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;

	bool shouldRefresh();
	void refreshPlayerSlot(int index);
	void refreshPlayerTypeControl(int index);
	void refreshPlayerTeamControl(int index);
	void refreshPlayerFactionControl(int index, bool preserveSelection);
	void bfmeFlush11();
	bool apply(void *gameInfo, int force);

private:
	SkirmishScreenOwner *m_owner;
	GameInfo *m_game;
	void *m_secondaryGame;
	bool m_flag10;
	bool m_flag11;
	bool m_flag12;
	bool m_flag13;
	bool m_flag14;
	bool m_flag15;
	bool m_flag16;
	bool m_flag17;
	bool m_visible;
	unsigned char m_padding19[3];
	int m_value1c;
	int m_value20;
	int m_value24;
	SkirmishScreenStateMember28 m_member28;
	GameWindow *m_first[8];
	GameWindow *m_elements[8];
	GameWindow *m_second[8];
	GameWindow *m_third[8];
	GameWindow *m_fourth[8];
	unsigned char m_member10c[0x20];
	int m_field128;
};

extern MapCache *TheMapCache;

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

// Apply the current Skirmish game record to the APT controls.
// ?apply@SkirmishScreenState@@QAE_NPAXH@Z
bool SkirmishScreenState::apply(void *gameInfo, int force)
{
	if (!shouldRefresh())
		return false;

	if (!gameInfo)
		return false;

	m_game = (GameInfo *)gameInfo;
	m_flag16 = true;
	m_secondaryGame = 0;
	m_value24 = force;
	((MpGameSetup *)this)->populateMapType();
	((MpGameSetup *)this)->populateGameType();
	bool restore = m_owner->bfmeShouldRestore();
	_ReadWriteBarrier();

	for (int index = 7; index >= 0; --index)
	{
		refreshPlayerTypeControl(index);
		refreshPlayerSlot(index);
		refreshPlayerTeamControl(index);
		refreshPlayerFactionControl(index, false);
		m_first[index]->winEnable(restore);
		m_elements[index]->winEnable(false);
		m_third[index]->winEnable(false);
		m_second[index]->winEnable(false);
		if (m_fourth[index])
		{
			if (index != 0)
				m_fourth[index]->winHide(true);
			else
				m_fourth[index]->winSetEnabledColor(0, *(int *)0x012BA0D8);
		}
		m_first[index]->winBringToTop();
		m_elements[index]->winBringToTop();
		m_third[index]->winBringToTop();
		m_second[index]->winBringToTop();
	}

	if (TheMapCache)
		TheMapCache->updateCache();
	if (restore)
		bfmeFlush11();

	m_member28.m_flag39 = true;
	((Gen_00525EE0 *)this)->bfmeSetMap(m_game->getMap());
	EnableSlotListUpdates(true);

	m_flag16 = false;
	m_flag11 = false;
	m_field128 = 0;
	m_flag15 = true;
	m_flag10 = true;
	m_flag12 = true;
	m_flag13 = true;
	m_flag14 = true;
	return true;
}
