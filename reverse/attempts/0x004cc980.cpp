// ?StartPressed@@YAX_N@Z
// partial score=0.78 date=2026-09-19
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseunicode /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned short WCHAR;
typedef bool Bool;

enum { MAX_SLOTS = 8, PLAYERTEMPLATE_OBSERVER = -2 };
#define TRUE true
#define FALSE false

#include <set>

template <typename T> struct BfmeStartStringData
{
	Int m_refCount;
	UnsignedShort m_length;
	UnsignedShort m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase(void) : m_data(0) {}
	StringBase(const StringBase<T> &other);
	StringBase(const T *text);
	~StringBase(void) { releaseBuffer(); }
	void releaseBuffer(void);

	BfmeStartStringData<T> *m_data;
};

class BFMERetailAsciiString
{
public:
	void releaseBuffer(void);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString(void)
	{
		((BFMERetailAsciiString *)this)->releaseBuffer();
	}
	const char *str(void) const
	{
		void *data = *(void *const *)this;
		return data ? (const char *)data + 8 : (const char *)0x0107388B;
	}
	Int getLength(void) const
	{
		void *data = *(void *const *)this;
		return data ? *(const UnsignedShort *)((const char *)data + 4) : 0;
	}
};

class UnicodeString : private StringBase<WCHAR>
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString(void) : StringBase<WCHAR>() {}
	UnicodeString(const WCHAR *text) : StringBase<WCHAR>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<WCHAR>(other) {}
	~UnicodeString(void) {}
	const WCHAR *str(void) const
	{
		void *data = *(void *const *)this;
		return data ? (const WCHAR *)((const char *)data + 8)
				: (const WCHAR *)0x0107388C;
	}
	void format(UnicodeString format, ...);
};

class GameWindow;
class GameSlotConnectInfo;

enum SlotState { SLOT_OPEN = 0, SLOT_CLOSED = 1 };

class GameSlot
{
public:
	Bool isOccupied(void) const;
	Bool isHuman(void) const;
	Bool isOpen(void) const;
	UnicodeString getName(void) const;
	void setState(SlotState state,
		UnicodeString name = UnicodeString::TheEmptyString,
		GameSlotConnectInfo *info = 0);

	Bool isAccepted(void) const { return m_accepted; }
	Bool hasMap(void) const { return m_hasMap; }
	void setAccept(void) { m_accepted = true; }
	Int getStartPos(void) const { return m_startPos; }
	Int getPlayerTemplate(void) const { return m_playerTemplate; }
	Int getTeamNumber(void) const { return m_teamNumber; }

private:
	void *m_vtable;
	UnsignedByte m_unmodelled[4];
	Bool m_accepted;
	Bool m_hasMap;
	UnsignedByte m_padding[6];
	Int m_startPos;
	Int m_playerTemplate;
	Int m_teamNumber;
};

class LANGameSlot : public GameSlot {};

class GameInfo
{
public:
	GameSlot *getSlot(Int slot);
	AsciiString getMap(void) const;
};

class LANGameInfo : public GameInfo
{
public:
	LANGameSlot *getLANSlot(Int slot);
};

class MapMetaData
{
public:
	UnsignedByte m_prefix[0x20];
	Int m_numPlayers;
	Bool m_isMultiplayer;
	Bool m_isScenarioMP;
	Bool m_isOfficial;
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

class GameTextInterface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
};

class MultiplayerSettings
{
public:
	Int getStartCountdownTimerSeconds(void) const
	{
		return *(const Int *)((const char *)this + 0x10);
	}
};

class GlobalData
{
public:
	UnsignedByte m_prefix[0xB0C];
	Int m_netMinPlayers;
};

class LANAPI
{
public:
	enum { LANCHAT_SYSTEM = 2 };
};

extern LANAPI *TheLAN;
extern GlobalData *TheWritableGlobalData;
extern MapCache *TheMapCache;
extern GameTextInterface *TheGameText;
extern MultiplayerSettings *TheMultiplayerSettings;
extern GameWindow *listboxChatWindowLanGame;
extern Int chatSystemColor;

extern Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
	Int color, Int row, Int column, Bool overwrite = true);
extern void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, Int item,
	Bool dontHide = false);
extern void LANEnableStartButton(Bool enabled);

#define TheGlobalData TheWritableGlobalData

// The BFME callsite passes the GameInfo object, not an AsciiString map name.
Bool WouldMapTransfer(GameInfo *game);
#pragma comment(linker, "/alternatename:?WouldMapTransfer@@YA_NPAVGameInfo@@@Z=?j_000393fb@@YAXXZ")

// BFME's LANAPI table is not the Zero Hour table exposed by LANAPI.h.  The
// body reaches the witnessed entries at slots 14, 18, 19, 35, 46, 48, and
// 55; keeping the intervening slots opaque preserves those call offsets.
class BfmeStartLANAPI
{
public:
	virtual void slot00(void) = 0; virtual void slot01(void) = 0;
	virtual void slot02(void) = 0; virtual void slot03(void) = 0;
	virtual void slot04(void) = 0; virtual void slot05(void) = 0;
	virtual void slot06(void) = 0; virtual void slot07(void) = 0;
	virtual void slot08(void) = 0; virtual void slot09(void) = 0;
	virtual void slot10(void) = 0; virtual void slot11(void) = 0;
	virtual void slot12(void) = 0; virtual void slot13(void) = 0;
	virtual void RequestAccept(void) = 0;
	virtual void slot15(void) = 0; virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void RequestGameStart(void) = 0;
	virtual void RequestGameStartTimer(Int seconds) = 0;
	virtual void slot20(void) = 0; virtual void slot21(void) = 0;
	virtual void slot22(void) = 0; virtual void slot23(void) = 0;
	virtual void slot24(void) = 0; virtual void slot25(void) = 0;
	virtual void slot26(void) = 0; virtual void slot27(void) = 0;
	virtual void slot28(void) = 0; virtual void slot29(void) = 0;
	virtual void slot30(void) = 0; virtual void slot31(void) = 0;
	virtual void slot32(void) = 0; virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void OnChat(UnicodeString player, UnsignedInt ip,
		UnicodeString message, Int chatType) = 0;
	virtual void slot36(void) = 0; virtual void slot37(void) = 0;
	virtual void slot38(void) = 0; virtual void slot39(void) = 0;
	virtual void slot40(void) = 0; virtual void slot41(void) = 0;
	virtual void slot42(void) = 0; virtual void slot43(void) = 0;
	virtual void slot44(void) = 0; virtual void slot45(void) = 0;
	virtual Bool AmIHost(void) = 0;
	virtual void slot47(void) = 0;
	virtual LANGameInfo *GetMyGame(void) = 0;
	virtual void slot49(void) = 0; virtual void slot50(void) = 0;
	virtual void slot51(void) = 0; virtual void slot52(void) = 0;
	virtual void slot53(void) = 0; virtual void slot54(void) = 0;
	virtual UnsignedInt GetLocalIP(void) = 0;
};

// The BFME GlobalData witness used by this body places netMinPlayers at
// +0xB0C; the vendored declaration places the similarly named field at a ZH
// offset and is not an identity/layout witness for this retail body.
struct BfmeStartGlobalData
{
	unsigned char m_unmodelled[0xB0C];
	Int m_netMinPlayers;
};

// The map-cache record has one extra Boolean in BFME, so the official flag is
// at +0x26 rather than the vendored MapMetaData offset +0x25.  Its string
// payload uses BFME's inline StringBase representation at each retail call.
struct BfmeStartMapMetaData
{
	void *m_displayName;
	void *m_description;
	unsigned char m_unmodelled[24];
	Int m_numPlayers;
	Bool m_isMultiplayer;
	Bool m_isScenarioMP;
	Bool m_isOfficial;
};

static __forceinline const char *BfmeStartAsciiString(
	const AsciiString &string)
{
	void *data = *(void *const *)&string;
	return data ? (const char *)data + 8 : (const char *)0x0107388B;
}

static __forceinline const unsigned short *BfmeStartUnicodeString(
	const UnicodeString &string)
{
	void *data = *(void *const *)&string;
	return data ? (const unsigned short *)((const char *)data + 8)
				: (const unsigned short *)0x0107388C;
}

// Identity is established by the two exact callers through ILT 0x00040AF7:
// the LAN menu update passes FALSE and the selected-button path passes TRUE.
// Their slot/map/team validation and LAN start path prove this BFME
// StartPressed(Bool) variant; the parameterless ZH helper is a different body.

void StartPressed( Bool showNetworkAction )
{
	LANGameInfo *myGame = ((BfmeStartLANAPI *)TheLAN)->GetMyGame();

	Bool isReady = true;
	Bool allHaveMap = true;
	if (!myGame)
		return;
	myGame->getLANSlot(0)->setAccept();

	Int numUsers = 0;
	Int numHumans = 0;

	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		GameSlot *slot = myGame->getSlot(i);
		if (slot && slot->isOccupied() && slot->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
		{
			if (slot->isHuman())
				numHumans++;
			numUsers++;
		}
	}

	const MapMetaData *md = TheMapCache->findMap( myGame->getMap() );
	if (!md || md->m_numPlayers < numUsers)
	{
	if (((BfmeStartLANAPI *)TheLAN)->AmIHost() && showNetworkAction)
		{
			UnicodeString text;
			text.format(TheGameText->fetch("LAN:TooManyPlayers"), (md) ? md->m_numPlayers : 0);
			((BfmeStartLANAPI *)TheLAN)->OnChat(UnicodeString(L"SYSTEM"),
				((BfmeStartLANAPI *)TheLAN)->GetLocalIP(), text,
				LANAPI::LANCHAT_SYSTEM);
		}
		return;
	}

	if (((BfmeStartGlobalData *)TheGlobalData)->m_netMinPlayers && !numHumans)
	{
		if (((BfmeStartLANAPI *)TheLAN)->AmIHost() && showNetworkAction)
		{
			UnicodeString text = TheGameText->fetch("GUI:NeedHumanPlayers");
			((BfmeStartLANAPI *)TheLAN)->OnChat(UnicodeString(L"SYSTEM"),
				((BfmeStartLANAPI *)TheLAN)->GetLocalIP(), text,
				LANAPI::LANCHAT_SYSTEM);
		}
		return;
	}

	if (numUsers < ((BfmeStartGlobalData *)TheGlobalData)->m_netMinPlayers)
	{
		if (((BfmeStartLANAPI *)TheLAN)->AmIHost() && showNetworkAction)
		{
			UnicodeString text;
			text.format(TheGameText->fetch("LAN:NeedMorePlayers"), numUsers);
			((BfmeStartLANAPI *)TheLAN)->OnChat(UnicodeString(L"SYSTEM"),
				((BfmeStartLANAPI *)TheLAN)->GetLocalIP(), text,
				LANAPI::LANCHAT_SYSTEM);
		}
		return;
	}

	Int numRandom = 0;
	std::set<Int> teams;
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		GameSlot *slot = myGame->getSlot(i);
		if (slot && slot->isOccupied() && slot->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
		{
			if (slot->getTeamNumber() >= 0)
				teams.insert(slot->getTeamNumber());
			else
				++numRandom;
		}
	}
	if (numRandom + teams.size() < ((BfmeStartGlobalData *)TheGlobalData)->m_netMinPlayers)
	{
		if (((BfmeStartLANAPI *)TheLAN)->AmIHost() && showNetworkAction)
		{
			UnicodeString text;
			text.format(TheGameText->fetch("LAN:NeedMoreTeams"));
			((BfmeStartLANAPI *)TheLAN)->OnChat(UnicodeString(L"SYSTEM"),
				((BfmeStartLANAPI *)TheLAN)->GetLocalIP(), text,
				LANAPI::LANCHAT_SYSTEM);
		}
		return;
	}

	if (((const BfmeStartMapMetaData *)md)->m_isScenarioMP)
	{
		Int occupiedStartingPositions = 0;
		for (Int i = 0; i < MAX_SLOTS; ++i)
		{
			GameSlot *slot = myGame->getSlot(i);
			if (slot && slot->isOccupied() && slot->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
			{
				if (slot->getStartPos() < 0)
				{
					UnicodeString text;
					text.format(TheGameText->fetch("GUI:AllPlayersMustSelectStartPosition"));
					((BfmeStartLANAPI *)TheLAN)->OnChat(UnicodeString(L"SYSTEM"),
						((BfmeStartLANAPI *)TheLAN)->GetLocalIP(), text,
						LANAPI::LANCHAT_SYSTEM);
					return;
				}
				++occupiedStartingPositions;
			}
		}
		if (occupiedStartingPositions < md->m_numPlayers)
		{
			UnicodeString text;
			text.format(TheGameText->fetch("GUI:AllPlayerPositionsMustBeOccupied"));
			((BfmeStartLANAPI *)TheLAN)->OnChat(UnicodeString(L"SYSTEM"),
				((BfmeStartLANAPI *)TheLAN)->GetLocalIP(), text,
				LANAPI::LANCHAT_SYSTEM);
			return;
		}
	}

	if (numRandom + teams.size() < 2)
	{
		UnicodeString text;
		text.format(TheGameText->fetch("GUI:SandboxMode"));
		((BfmeStartLANAPI *)TheLAN)->OnChat(UnicodeString(L"SYSTEM"),
			((BfmeStartLANAPI *)TheLAN)->GetLocalIP(), text,
			LANAPI::LANCHAT_SYSTEM);
	}

	UnicodeString mapDisplayName;
	const MapMetaData *mapData = TheMapCache->findMap( myGame->getMap() );
	Bool willTransfer = TRUE;
	if (mapData)
	{
		const BfmeStartMapMetaData *bfmeMapData =
			(const BfmeStartMapMetaData *)mapData;
		mapDisplayName.format(UnicodeString(L"%ls"),
			BfmeStartUnicodeString(*(const UnicodeString *)&bfmeMapData->m_displayName));
		willTransfer = !bfmeMapData->m_isOfficial;
	}
	else
	{
		mapDisplayName.format(UnicodeString(L"%hs"),
			BfmeStartAsciiString(myGame->getMap()));
		willTransfer = WouldMapTransfer(
			myGame);
	}

	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		LANGameSlot *slot = myGame->getLANSlot(i);
		if (slot->isHuman() && !slot->isAccepted())
		{
			isReady = false;
			if (!willTransfer && !slot->hasMap())
			{
				UnicodeString msg;
				msg.format(TheGameText->fetch("GUI:PlayerNoMap"),
					BfmeStartUnicodeString(slot->getName()),
					BfmeStartUnicodeString(mapDisplayName));
				GadgetListBoxAddEntryText(listboxChatWindowLanGame, msg, chatSystemColor, -1, 1);
				allHaveMap = false;
			}
		}
		slot->isHuman();
	}

	if (isReady)
	{
		for (Int i = 0; i < MAX_SLOTS; ++i)
		{
		LANGameSlot *slot = myGame->getLANSlot(i);
			if (slot && slot->isOpen())
			{
				slot->setState(SLOT_CLOSED);
				GadgetComboBoxSetSelectedPos(
					reinterpret_cast<GameWindow *(*)[MAX_SLOTS]>(0x012F3C24)[0][i],
					SLOT_CLOSED);
			}
		}
		Int seconds = TheMultiplayerSettings->getStartCountdownTimerSeconds();
		if (seconds)
			((BfmeStartLANAPI *)TheLAN)->RequestGameStartTimer(seconds);
		else
			((BfmeStartLANAPI *)TheLAN)->RequestGameStart();
		LANEnableStartButton(false);
	}
	else if (allHaveMap && showNetworkAction)
	{
		GadgetListBoxAddEntryText(listboxChatWindowLanGame,
			TheGameText->fetch("GUI:NotifiedStartIntent"), chatSystemColor, -1, 1);
		((BfmeStartLANAPI *)TheLAN)->RequestAccept();
	}
}
