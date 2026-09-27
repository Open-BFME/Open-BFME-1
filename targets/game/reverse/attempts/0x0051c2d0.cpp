// ?init@BfmeGameLoadingScreen@@UAEXPAVGameInfo@@@Z
// partial score=0.633 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// partial score=0.63 date=2026-09-27
// BfmeGameLoadingScreen::init, retail 0x0051C2D0. The owner is proved by vtable 0x01106070.
// The target's direct calls and the member offsets are retained as address-derived evidence.

typedef bool Bool;
typedef unsigned short WideChar;
typedef unsigned int UnsignedInt;
typedef int NameKeyType;

template <class T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
	friend class Rva0046FBB0SideIndex;

protected:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	void releaseBuffer();
	void set(const StringBase<T> &other);
	void set(const T *text, int length);

public:
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class UnicodeString;

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString(const UnicodeString &other);
	~AsciiString() { releaseBuffer(); }
	void format(AsciiString format, ...);
	Bool isEmpty() const
	{
		return m_data == 0 || *(const unsigned short *)((const char *)m_data + 4) == 0;
	}
	const char *data() const
	{
		return m_data == 0 ? 0 : (const char *)m_data + 8;
	}
	AsciiString &operator=(const char *text)
	{
		StringBase<char>::set(text, (int)6);
		return *this;
	}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
	~UnicodeString() { releaseBuffer(); }
	UnicodeString &operator=(const UnicodeString &other)
	{
		StringBase<WideChar>::set(other);
		return *this;
	}
};

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

class WindowManager
{
public:
	void bfme_setAptText(const AsciiString &name, const AsciiString &text);
	void bfme_setAptText(const AsciiString &name, const UnicodeString &text);
};

class BfmeThingBIF
{
public:
	void bfmeGoBIF(void *what, void *out);
};

extern ImageCollection *TheMappedImageCollection;
extern WindowManager *g_theWindowManager;
extern BfmeThingBIF *Rva00579160TheManager;

class GameSlot
{
public:
	Bool isOccupied() const;
	Bool isAI() const;
	UnicodeString getName() const;
	UnicodeString getApparentPlayerTemplateDisplayName() const;

	char m_unknown00[4];
	int m_state;
	int m_accepted;
	char m_pad0c[8];
	int m_playerTemplate;
	int m_teamNumber;
};

class GameInfo
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual int getLocalSlotNum() const;
	GameSlot *getSlot(int slot);
};

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class GameSpyStagingRoom
{
public:
	char m_pad[0x43c];
	Bool m_isBusy;
	char m_pad43d[3];
	int m_gameType;
};

extern GameSpyStagingRoom *TheGameSpyGame;

class GameSpyPlayerData
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void *getRankData();
	int m_type;
	char m_pad0c[8];
	int m_profileID;
};

class GameSpyInfoInterface
{
public:
#define GSI_SLOT(n) virtual void gsi_##n();
	GSI_SLOT(00) GSI_SLOT(01) GSI_SLOT(02) GSI_SLOT(03) GSI_SLOT(04)
	GSI_SLOT(05) GSI_SLOT(06) GSI_SLOT(07) GSI_SLOT(08) GSI_SLOT(09)
	GSI_SLOT(10) GSI_SLOT(11) GSI_SLOT(12) GSI_SLOT(13) GSI_SLOT(14)
	GSI_SLOT(15) GSI_SLOT(16) GSI_SLOT(17) GSI_SLOT(18)
#undef GSI_SLOT
	GameSpyPlayerData *getPlayer(const char *name);
#define GSI_SLOT(n) virtual void gsi2_##n();
	GSI_SLOT(20) GSI_SLOT(21) GSI_SLOT(22) GSI_SLOT(23) GSI_SLOT(24)
	GSI_SLOT(25) GSI_SLOT(26) GSI_SLOT(27) GSI_SLOT(28) GSI_SLOT(29)
	GSI_SLOT(30) GSI_SLOT(31) GSI_SLOT(32) GSI_SLOT(33) GSI_SLOT(34)
	GSI_SLOT(35) GSI_SLOT(36) GSI_SLOT(37) GSI_SLOT(38) GSI_SLOT(39)
	GSI_SLOT(40) GSI_SLOT(41) GSI_SLOT(42) GSI_SLOT(43) GSI_SLOT(44)
	GSI_SLOT(45) GSI_SLOT(46) GSI_SLOT(47) GSI_SLOT(48) GSI_SLOT(49)
	GSI_SLOT(50) GSI_SLOT(51) GSI_SLOT(52) GSI_SLOT(53) GSI_SLOT(54)
	GSI_SLOT(55) GSI_SLOT(56) GSI_SLOT(57) GSI_SLOT(58) GSI_SLOT(59)
	GSI_SLOT(60) GSI_SLOT(61) GSI_SLOT(62) GSI_SLOT(63) GSI_SLOT(64)
	GSI_SLOT(65) GSI_SLOT(66) GSI_SLOT(67) GSI_SLOT(68) GSI_SLOT(69)
	GSI_SLOT(70) GSI_SLOT(71) GSI_SLOT(72) GSI_SLOT(73) GSI_SLOT(74)
	GSI_SLOT(75) GSI_SLOT(76) GSI_SLOT(77) GSI_SLOT(78) GSI_SLOT(79)
	GSI_SLOT(80) GSI_SLOT(81) GSI_SLOT(82) GSI_SLOT(83) GSI_SLOT(84)
	GSI_SLOT(85) GSI_SLOT(86) GSI_SLOT(87);
#undef GSI_SLOT
	Bool didPlayerPreorder(int profileID) const;
};

extern GameSpyInfoInterface *TheGameSpyInfo;
extern void *Rva00579160TheCurrent;

class PSPlayerStats
{
public:
	~PSPlayerStats();
	int id;
	char m_data[0x1c0];
};

class GameSpyPSMessageQueueInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual PSPlayerStats findPlayerStatsByID(int profileID);
};

extern GameSpyPSMessageQueueInterface *g_bfmeQueueEUG;

class PlayerTemplate
{
public:
	char m_pad[0xb8];
	AsciiString m_loadScreenMusic;
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(int index) const;
	const PlayerTemplate *findPlayerTemplate(NameKeyType key) const;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameLogic
{
public:
	void initTimeOutValues();
};

extern GameLogic *TheBfmeGameLogic;

class Rva004D8EE0
{
public:
	Rva004D8EE0();
private:
	int m_values[10];
};

class Rva0046FBB0SideIndex
{
public:
	static int get(StringBase<char> side);
};

extern int __cdecl bfmeBandChecked(int value);
extern int __cdecl Rva0046F910(int rank, AsciiString *side);
extern void j_00022976();

class UserPreferences
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
};

class SkirmishBattleHonors : public UserPreferences
{
public:
	SkirmishBattleHonors(UnicodeString userName);
	virtual ~SkirmishBattleHonors();
	int getRankDisplay(AsciiString name) const;
private:
	Rva004D8EE0 m_values;
};

class SkirmishPreferences : public UserPreferences
{
public:
	SkirmishPreferences();
	virtual ~SkirmishPreferences();
	virtual void slot18();
	virtual void slot1c();
	UnicodeString getUserName();
private:
	char m_data[0x14];
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int objectID);
	virtual void slot00();
	~AudioEventRTS();
	void setIsLogicalAudio(Bool value);
private:
	char m_data[0x6c];
};

class AudioClient
{
public:
#define AUDIO_SLOT(n) virtual void audio_##n();
	AUDIO_SLOT(00) AUDIO_SLOT(01) AUDIO_SLOT(02) AUDIO_SLOT(03) AUDIO_SLOT(04)
	AUDIO_SLOT(05) AUDIO_SLOT(06) AUDIO_SLOT(07) AUDIO_SLOT(08) AUDIO_SLOT(09)
	AUDIO_SLOT(10) AUDIO_SLOT(11) AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14)
	AUDIO_SLOT(15) AUDIO_SLOT(16)
#undef AUDIO_SLOT
	virtual void addAudioEvent(const AudioEventRTS *event);
#define AUDIO_SLOT(n) virtual void audio2_##n();
	AUDIO_SLOT(18) AUDIO_SLOT(19) AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22)
	AUDIO_SLOT(23) AUDIO_SLOT(24) AUDIO_SLOT(25) AUDIO_SLOT(26)
#undef AUDIO_SLOT
	virtual void stopMusic(int a, int b, int c);
};

extern AudioClient *TheAudioClientUpdate;
extern UnicodeString Rva0051BA90RankOrUnavailableText(int rank);

class BfmeGameLoadingScreen
{
public:
	virtual void init(GameInfo *game);

private:
	char m_head[0x58];
	GameInfo *m_game;
	int m_unknown5c;
	int m_playerLookup[8];
	int m_playerSlots[8];
};

void BfmeGameLoadingScreen::init(GameInfo *game)
{
	if (game == 0)
		return;
	m_game = game;

	const Image *fellowshipImage;
	{
		AsciiString imageName("Aptfellowship_clup");
		fellowshipImage = TheMappedImageCollection->findImageByName(imageName);
	}

	Bool online = TheGameSpyGame != 0 && TheGameSpyGame->m_isBusy;
	for (int index = 0; index < 8; ++index)
	{
		AsciiString key;
		key.format(AsciiString("LoadingScreen::Rank%d"), index);
		UnicodeString blank((const WideChar *)0x01084C34);
		g_theWindowManager->bfme_setAptText(key, blank);
	}

	int netSlot = 0;
	for (int slotIndex = 0; slotIndex < 8; ++slotIndex)
	{
		GameSlot *slot = game->getSlot(slotIndex);
		if (slot == 0 || !slot->isOccupied())
			continue;
		if (netSlot == 8)
			break;

		{
			AsciiString playerNameKey;
			playerNameKey.format(AsciiString("LoadingScreen::PlayerName%d"), netSlot);
			UnicodeString playerName = slot->getName();
			g_theWindowManager->bfme_setAptText(playerNameKey, playerName);
		}

		{
			AsciiString teamKey;
			teamKey.format(AsciiString("LoadingScreen::TeamNumber%d"), netSlot);
			AsciiString teamName;
			if (slot->isAI() && slot->m_teamNumber == -1)
				teamName = "Team:0";
			else
				teamName.format(AsciiString("Team:%d"), slot->m_teamNumber + 1);
			UnicodeString teamText = TheGameText->fetch(teamName);
			g_theWindowManager->bfme_setAptText(teamKey, teamText);
		}

		UnicodeString armyName = slot->getApparentPlayerTemplateDisplayName();
		{
			AsciiString armyKey;
			armyKey.format(AsciiString("LoadingScreen::ArmyName%d"), netSlot);
			g_theWindowManager->bfme_setAptText(armyKey, armyName);
		}

		AsciiString side = armyName;
		Rva004D8EE0 rankValues;
		Bool isAI = slot->isAI();
		int rankImage = 0;
		Bool isPreorder = 0;
		GameSpyPlayerData *player = 0;
		if (isAI)
		{
			if (Rva00579160TheCurrent != 0 && TheGameSpyInfo != 0 && !online)
			{
				if (slot->m_state == 2)
					rankImage = Rva0046F910(9, &side);
				else if (slot->m_state == 3)
					rankImage = Rva0046F910(5, &side);
				else if (slot->m_state == 4)
					rankImage = Rva0046F910(1, &side);
			}
		}
		else if (TheGameSpyInfo != 0 && !online)
		{
			{
				UnicodeString lookupUnicode = slot->getName();
				AsciiString lookupName = lookupUnicode;
				const char *lookupText = lookupName.data();
				if (lookupText == 0)
					lookupText = (const char *)0x0107388B;
				player = TheGameSpyInfo->getPlayer(lookupText);
			}
			if (player == 0)
			{
				AsciiString imageName("AptRankIcon0");
				rankImage = (int)TheMappedImageCollection->findImageByName(imageName);
			}
			else
			{
				isPreorder = TheGameSpyInfo->didPlayerPreorder(player->m_profileID);
				PSPlayerStats stats = g_bfmeQueueEUG->findPlayerStatsByID(player->m_profileID);
			if (stats.id == 0)
			{
				AsciiString imageName("AptRankIcon0");
				rankImage = (int)TheMappedImageCollection->findImageByName(imageName);
			}
			else
			{
				AsciiString sideCopy = side;
				int sideIndex = Rva0046FBB0SideIndex::get(
					*(StringBase<char> *)&sideCopy);
				if (sideIndex == 4)
				{
					AsciiString imageName("AptRankIcon0");
					rankImage = (int)TheMappedImageCollection->findImageByName(imageName);
				}
				else
				{
					int points = ((int (__cdecl *)(PSPlayerStats *, int))j_00022976)(
						&stats, sideIndex);
					int rank = bfmeBandChecked(points);
					rankImage = Rva0046F910(rank, &side);
				}
			}
				void *rankData = player->getRankData();
				GameSpyStagingRoom *gameSpyGame = TheGameSpyGame;
				int rank = gameSpyGame && gameSpyGame->m_gameType == 2 ?
					*(int *)((char *)rankData + 0x6c) : *(int *)((char *)rankData + 0x68);
				{
					UnicodeString rankText = Rva0051BA90RankOrUnavailableText(rank);
					AsciiString rankKey;
					rankKey.format(AsciiString("LoadingScreen::Rank%d"), netSlot);
					g_theWindowManager->bfme_setAptText(rankKey, rankText);
				}
			}
		}

		if (rankImage == 0 && TheGameSpyInfo == 0)
		{
			const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(
				slot->m_playerTemplate);
			if (pt != 0)
			{
				SkirmishPreferences prefs;
				UnicodeString userName = prefs.getUserName();
				SkirmishBattleHonors honors(userName);
				rankImage = honors.getRankDisplay(side);
			}
		}

		AsciiString levelKey;
		levelKey.format(AsciiString("UIClip/Level/%d"), netSlot);
		Rva00579160TheManager->bfmeGoBIF(&levelKey, (void *)rankImage);
		AsciiString fellowshipKey;
		fellowshipKey.format(AsciiString("UIClip/Fellowship/%d"), netSlot);
		Rva00579160TheManager->bfmeGoBIF(&fellowshipKey,
			isPreorder ? (void *)rankImage : 0);

		m_playerLookup[slotIndex] = netSlot;
		m_playerSlots[netSlot] = slotIndex;
		++netSlot;
	}

	for (; netSlot < 8; ++netSlot)
	{
		AsciiString key;
		key.format(AsciiString("LoadingScreen::PlayerName%d"), netSlot);
		AsciiString blank((const char *)0x0108ED1C);
		g_theWindowManager->bfme_setAptText(key, blank);
		key.format(AsciiString("LoadingScreen::TeamNumber%d"), netSlot);
		g_theWindowManager->bfme_setAptText(key, blank);
		key.format(AsciiString("LoadingScreen::ArmyName%d"), netSlot);
		g_theWindowManager->bfme_setAptText(key, blank);
		key.format(AsciiString("UIClip/Level/%d"), netSlot);
		Rva00579160TheManager->bfmeGoBIF(&key, 0);
		key.format(AsciiString("UIClip/Fellowship/%d"), netSlot);
		Rva00579160TheManager->bfmeGoBIF(&key, 0);
	}

	int localSlot = game->getLocalSlotNum();
	GameSlot *slot = game->getSlot(localSlot);
	if (slot != 0)
	{
		const PlayerTemplate *pt;
		if (slot->m_playerTemplate >= 0)
			pt = ThePlayerTemplateStore->getNthPlayerTemplate(slot->m_playerTemplate);
		else
		{
			NameKeyType key = TheNameKeyGenerator->nameToKey("FactionObserver");
			pt = ThePlayerTemplateStore->findPlayerTemplate(key);
		}
		if (pt != 0 && !pt->m_loadScreenMusic.isEmpty())
		{
			TheAudioClientUpdate->stopMusic(2, 1, 0);
			AudioEventRTS event(pt->m_loadScreenMusic, 2);
			event.setIsLogicalAudio(1);
			TheAudioClientUpdate->addAudioEvent(&event);
			TheAudioClientUpdate->audio_05();
		}
	}
	TheBfmeGameLogic->initTimeOutValues();
}
