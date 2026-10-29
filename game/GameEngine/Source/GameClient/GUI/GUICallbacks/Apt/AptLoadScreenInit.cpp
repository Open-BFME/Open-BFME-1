// ?init@AptLoadScreen@@UAEXPAVGameInfo@@@Z
// Retail 0x0051C2D0 (2702 bytes): slot +8 of the load-screen vtable 0x01106070,
// the GameLogic::getLoadScreen screen's init(GameInfo *) override.  The
// gen-dump row ?d_0051c2d0@@YAXXZ carried these same 2702 bytes from
// game/gen_asm/d_0051b7e0.asm, so this is a rename to a real body and not a
// new match.
//
// Identity: vtable VA 0x01106070 routes slot +8 through ILT 0x00042CA3 to this
// body; the already matched constructor ??0LoadScreen0051BF30@@QAE@I@Z at
// 0x0051BF30 installs the same table and the parked destructor at 0x0051B7E0
// installs it too (build/0051c2d0-retry/025-vtable-loadscreen.log).
// EA's own tree names it: targets/game/reverse/ea_evidence.csv records
// 0x0051C2D0 -> AptLoadScreen::init (chain+direct, strong) and the sibling
// constructor's address -> AptLoadScreen::AptLoadScreen, both under
// GameEngine/Source/GameClient/Gui/GUICallbacks/Apt/AptLoadScreen.cpp, so this
// TU takes EA's class name rather than inventing one.
//
// The body is byte-identical to retail outside relocation slots: the probe
// measures ours=2702 retail=2702 relocs=177 and "EXACT (modulo relocation
// slots)"; the compiled unwind metadata matches all 27 retail predecessor
// states (build/0051c2d0-retry/062-reviewed-unwind.log).  Evidence and the
// trial log: targets/game/reverse/identity_evidence/0x0051c2d0-init-retry.md.
//
// The player record is three native AsciiStrings followed by ten dwords,
// measured by the complete out-of-line constructor/assignment/destructor trio
// at 0x004F1120/0x00630D60/0x004F10B0; the object has no virtual prefix.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

typedef bool Bool;
typedef unsigned short WideChar;
typedef unsigned int UnsignedInt;
enum NameKeyType { NAMEKEY_INVALID = 0 };

#include "ascii_string.h"
#include "unicode_string.h"
#include <string.h>
#pragma intrinsic(strlen)

template <> inline bool StringBase<char>::isEmpty() const
{
	return m_data == 0 || m_data->length == 0;
}

// ??4AsciiString@@QAEAAV0@PBD@Z
inline AsciiString &AsciiString::operator=(const char *text)
{
	StringBase<char>::set(text, strlen(text));
	return *this;
}

inline UnicodeString::UnicodeString()
{
	*(void **)this = 0;
}

inline UnicodeString::UnicodeString(const wchar_t *text)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase((const unsigned short *)text);
}

inline UnicodeString::UnicodeString(const UnicodeString &other)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&other);
}

inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}

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
// Retail 0x012F19E8 is ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A
// (data_rows.csv, GUI/WindowManager.cpp); g_theWindowManager was only a pin.
extern WindowManager *g_rva012F19E8WindowManager;
#define g_theWindowManager g_rva012F19E8WindowManager
// Retail 0x012F19E8 is ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A (data_rows.csv,
// GUI/WindowManager.cpp); Rva00579160TheManager was only a pin.
extern WindowManager *g_rva012F19E8WindowManager;
#define Rva00579160TheManager ( *(BfmeThingBIF **)&g_rva012F19E8WindowManager )

class GameSlot
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void *getRankData();
	int getPlayerTemplate() const { return m_playerTemplate; }
	int getTeamNumber() const { return m_teamNumber; }
	Bool isOccupied() const;
	Bool isAI() const;
	UnicodeString getName() const;
	UnicodeString getApparentPlayerTemplateDisplayName() const;

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
	AsciiString m_name;
	AsciiString m_type;
	AsciiString m_pad0c;
	int m_unmodelled0c[2];
	int m_profileID;
	int m_unmodelled18[7];
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
	virtual GameSpyPlayerData *getPlayer(const char *name);
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
	virtual Bool didPlayerPreorder(int profileID) const;
};

extern GameSpyInfoInterface *TheGameSpyInfo;
struct Rva00579160Current;
extern Rva00579160Current *Rva00579160TheCurrent;
extern const unsigned short BFMEEmptyString;
extern const char Rva006A16B0Empty;

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

extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;

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

// Retail 0x012F0898 is ?TheGameLogic@@3PAVGameLogic@@A (data_rows.csv,
// GameLogic.cpp); TheBfmeGameLogic was only a pin nothing defines.
extern GameLogic *TheGameLogic;
#define TheBfmeGameLogic TheGameLogic

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
private:
	char m_data[0x10];
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
	char m_data[4];
};

// The matched lifetime source emits the canonical virtual destructor.
// Its object-symbol alias binds this direct call and the unwind cleanup.
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int objectID);
	virtual void slot00();
	virtual ~AudioEventRTS();
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
	virtual unsigned int addAudioEvent(const AudioEventRTS *event);
#define AUDIO_SLOT(n) virtual void audio2_##n();
	AUDIO_SLOT(18) AUDIO_SLOT(19) AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22)
	AUDIO_SLOT(23) AUDIO_SLOT(24) AUDIO_SLOT(25) AUDIO_SLOT(26)
#undef AUDIO_SLOT
	virtual void stopMusic(int a, int b, int c);
};

// Retail 0x012ED668 is ?TheAudio@@3PAVAudioManager@@A (data_rows.csv,
// Common/Audio/GameAudio.cpp); TheAudioClientUpdate was only a pin.
class AudioManager;
extern AudioManager *TheAudio;
#define TheAudioClientUpdate ( *(AudioClient **)&TheAudio )
extern UnicodeString Rva0051BA90RankOrUnavailableText(int rank);

class AptLoadScreen
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void init(GameInfo *game);
	virtual void slot0c();
	virtual void slot10(int slot, int percentage);

private:
	char m_head[0x54];
	GameInfo *m_game;
	int m_unknown5c;
	int m_playerLookup[8];
	int m_playerSlots[8];
};

// ?init@AptLoadScreen@@UAEXPAVGameInfo@@@Z
// Evidence: targets/game/reverse/identity_evidence/0x0051c2d0-init-retry.md
void AptLoadScreen::init(GameInfo *game)
{
	if (game == 0)
		return;
	m_game = game;
	int netSlot = 0;
	AsciiString playerNameKey;
	AsciiString teamName;
	AsciiString levelKey;
	const Image *fellowshipImage;
	{
		AsciiString imageName("Aptfellowship_clup");
		fellowshipImage = TheMappedImageCollection->findImageByName(imageName);
	}
	Bool online = TheGameSpyGame != 0 && TheGameSpyGame->m_isBusy;
	for (int index = 0; index <= 7; ++index)
	{
		AsciiString key;
		key.format("LoadingScreen::Rank%d", index);
		g_theWindowManager->bfme_setAptText(key, UnicodeString(L" "));
	}
	int slotIndex;
	for (slotIndex = 0; slotIndex < 8; ++slotIndex)
	{
		GameSlot *slot = m_game->getSlot(slotIndex);
		if (slot == 0 || !slot->isOccupied())
			continue;
		if (netSlot == 8)
			break;
		playerNameKey.format("LoadingScreen::PlayerName%d", netSlot);
		g_theWindowManager->bfme_setAptText(playerNameKey, slot->getName());
		playerNameKey.format("LoadingScreen::TeamNumber%d", netSlot);
		if (slot->isAI() && slot->getTeamNumber() == -1)
			teamName = "Team:0";
		else
			teamName.format("Team:%d", slot->getTeamNumber() + 1);
		g_theWindowManager->bfme_setAptText(playerNameKey, TheGameText->fetch(teamName));
		playerNameKey.format("LoadingScreen::ArmyName%d", netSlot);
		UnicodeString armyName = slot->getApparentPlayerTemplateDisplayName();
		g_theWindowManager->bfme_setAptText(playerNameKey, armyName);
		Bool isPreorder = false;
		int rankImage = 0;
		AsciiString side = armyName;
		Rva004D8EE0 rankValues;
		if (slot->isAI() && (Rva00579160TheCurrent != 0 || TheGameSpyInfo != 0) && !online)
		{
			switch (slot->m_state)
			{
			case 2: rankImage = Rva0046F910(1, &side); break;
			case 3: rankImage = Rva0046F910(5, &side); break;
			case 4: rankImage = Rva0046F910(9, &side); break;
			}
		}
		else if (TheGameSpyInfo != 0)
		{
			if (!online)
			{
				AsciiString lookupName = slot->getName();
				GameSpyPlayerData *player = TheGameSpyInfo->getPlayer(lookupName.str());
				if (player)
				{
					isPreorder = TheGameSpyInfo->didPlayerPreorder(player->m_profileID);
					PSPlayerStats stats = TheGameSpyPSMessageQueue->findPlayerStatsByID(player->m_profileID);
					if (!stats.id)
					{
						AsciiString imageName("AptRankIcon0");
						rankImage = (int)TheMappedImageCollection->findImageByName(imageName);
					}
					else
					{
						int sideIndex = ((int (__cdecl *)(AsciiString))Rva0046FBB0SideIndex::get)(side);
						if (sideIndex == 4)
						{
							AsciiString imageName("AptRankIcon0");
							rankImage = (int)TheMappedImageCollection->findImageByName(imageName);
						}
						else
						{
							int points = ((int (__cdecl *)(PSPlayerStats *, int))j_00022976)(&stats, sideIndex);
							rankImage = Rva0046F910(bfmeBandChecked(points), &side);
						}
					}
				}
				else
				{
					AsciiString imageName("AptRankIcon0");
					rankImage = (int)TheMappedImageCollection->findImageByName(imageName);
				}
			}
			else
			{
				void *rankData = slot->getRankData();
				int rank = TheGameSpyGame->m_gameType == 2 ? *(int *)((char *)rankData + 0x6c) : *(int *)((char *)rankData + 0x68);
				UnicodeString rankText = Rva0051BA90RankOrUnavailableText(rank);
				AsciiString rankKey;
				rankKey.format("LoadingScreen::Rank%d", slotIndex);
				g_theWindowManager->bfme_setAptText(rankKey, UnicodeString(rankText));
			}
		}
		else if (Rva00579160TheCurrent)
		{
			const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(slot->getPlayerTemplate());
			if (pt)
			{
				SkirmishPreferences prefs;
				SkirmishBattleHonors honors(prefs.getUserName());
				rankImage = honors.getRankDisplay(*(const AsciiString *)((const char *)pt + 8));
			}
		}
		levelKey.format("UIClip/Level/%d", netSlot);
		Rva00579160TheManager->bfmeGoBIF(&levelKey, (void *)rankImage);
		levelKey.format("UIClip/Fellowship/%d", netSlot);
		Rva00579160TheManager->bfmeGoBIF(&levelKey, isPreorder ? (void *)fellowshipImage : 0);
		m_playerSlots[slotIndex] = netSlot;
		m_playerLookup[netSlot] = slotIndex;
		++netSlot;
		slot10(slotIndex, 0);
	}
	for (; netSlot < 8; ++netSlot)
	{
		playerNameKey.format("LoadingScreen::PlayerName%d", netSlot);
		g_theWindowManager->bfme_setAptText(playerNameKey, AsciiString(" "));
		playerNameKey.format("LoadingScreen::TeamNumber%d", netSlot);
		g_theWindowManager->bfme_setAptText(playerNameKey, AsciiString(" "));
		playerNameKey.format("LoadingScreen::ArmyName%d", netSlot);
		g_theWindowManager->bfme_setAptText(playerNameKey, AsciiString(" "));
		levelKey.format("UIClip/Level/%d", slotIndex);
		Rva00579160TheManager->bfmeGoBIF(&levelKey, 0);
		levelKey.format("UIClip/Fellowship/%d", slotIndex);
		Rva00579160TheManager->bfmeGoBIF(&levelKey, 0);
	}
	GameSlot *slot = game->getSlot(game->getLocalSlotNum());
	if (slot)
	{
		const PlayerTemplate *pt;
		if (slot->getPlayerTemplate() >= 0)
			pt = ThePlayerTemplateStore->getNthPlayerTemplate(slot->getPlayerTemplate());
		else
			pt = ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey("FactionObserver"));
		AsciiString music = pt->m_loadScreenMusic;
		if (!music.isEmpty())
		{
			TheAudioClientUpdate->stopMusic(2, 1, 0);
			AudioEventRTS event(music, 2);
			event.setIsLogicalAudio(1);
			TheAudioClientUpdate->addAudioEvent(&event);
			TheAudioClientUpdate->audio_05();
		}
	}
	TheBfmeGameLogic->initTimeOutValues();
}
