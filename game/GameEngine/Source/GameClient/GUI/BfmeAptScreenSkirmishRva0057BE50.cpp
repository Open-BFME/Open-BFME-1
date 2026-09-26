// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc /G5 /Iinputs/reference/shims/stringinline

#include <new>
#include "StringInline.h"
extern void b_0009e650();
extern void b_0009d020();



typedef int Int;
typedef unsigned int UnsignedInt;

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

enum
{
	PLAYERTEMPLATE_RANDOM = -1,
	PLAYERTEMPLATE_OBSERVER = -2,
	PLAYERTEMPLATE_MIN = PLAYERTEMPLATE_OBSERVER
};

struct GameSlotConnectInfo
{
	unsigned int m_nat;
	unsigned short m_port;
};

class GameSlot
{
public:
	GameSlot();
	__forceinline ~GameSlot() {}
	GameSlot(const GameSlot &other);
	void reset();
	void setState(SlotState state,
		UnicodeString name,
		const GameSlotConnectInfo *connectInfo);
	void setColor(Int color) { m_color = color; }
	void setPlayerTemplate(Int playerTemplate)
	{
		m_playerTemplate = playerTemplate;
		if (playerTemplate <= PLAYERTEMPLATE_MIN)
			m_startPos = -1;
	}

private:
	void *m_vtable;
	Int m_state;
	unsigned char m_accepted;
	unsigned char m_hasMap;
	unsigned char m_isMuted;
	unsigned char m_padding0b;
public:
	Int m_color;
	Int m_startPos;
	Int m_playerTemplate;
private:
	Int m_teamNumber;
	Int m_originalColor;
	Int m_originalStartPos;
	Int m_originalPlayerTemplate;
public:
	UnicodeString m_name;
private:
	AsciiString m_unmodelled2c;
	UnsignedInt m_ip;
	unsigned char m_unmodelled34[0x10];
};



extern void j_0001f4a6();
class GameInfo
{
public:
	virtual Int _bfme_gi_slot0();
	virtual Int _bfme_gi_slot1();
	virtual void reset();
	virtual void startGame(Int gameID);
	void endGame();
	void leaveGame();
	void clearSlotList();
	GameSlot *getSlot(Int index);
	void enterGame();
	void setSlot(Int index, GameSlot slot);
	void setMap(AsciiString mapName);
	void setMapCRC(UnsignedInt mapCRC);
	void setMapSize(UnsignedInt mapSize);
	void setSeed(Int seed)
	{
		typedef void (GameInfo::*Method)(Int);
		union
		{
			Method method;
			void (*entry)();
		} call;
		call.entry = j_0001f4a6;
		(this->*call.method)(seed);
	}
	AsciiString getMap() const;

private:
	void *m_unmodelled04;
	void *m_unmodelled08;
public:
	bool m_inGame;
private:
	unsigned char m_unmodelled0d[3];
	unsigned char m_unmodelled10[0x24];
public:
	UnsignedInt m_slotData34;
	UnsignedInt m_slotData38;
private:
	unsigned char m_unmodelled3c[0x10];
	Int m_seed;
	unsigned char m_unmodelled50[8];
};

class Snapshot
{
public:
	virtual ~Snapshot();
};

class Rva00003409Open2SlotOwner : public GameInfo, public Snapshot
{
public:
	Rva00003409Open2SlotOwner();
	virtual ~Rva00003409Open2SlotOwner();

private:
	virtual void crc(void *);
	virtual void xfer(void *);
	virtual void loadPostProcess();
	GameSlot m_slots[8];
};

struct Rva00579160Current : public GameInfo
{
};
extern Rva00579160Current *Rva00579160TheCurrent;

class SkirmishPreferences
{
public:
	virtual ~SkirmishPreferences();
	virtual void slot1();
	virtual bool load();
	virtual bool write();
	UnicodeString getUserName();


private:
	unsigned char m_unmodelled04[0x14];
};
class SkirmishRetailCallView
{
public:
	__forceinline Int colorResult()
	{
		typedef Int (SkirmishRetailCallView::*Method)();
		union
		{
			Method method;
			void (*entry)();
		} call;
		call.entry = b_0009e650;
		return (this->*call.method)();
	}

	__forceinline Int factionResult()
	{
		typedef Int (SkirmishRetailCallView::*Method)();
		union
		{
			Method method;
			void (*entry)();
		} call;
		call.entry = b_0009d020;
		return (this->*call.method)();
	}
};

class SkirmishBattleHonors
{
public:
	virtual ~SkirmishBattleHonors();
	virtual void slot1();
	virtual bool load();
	virtual bool write();
	Int getWins(AsciiString name) const;
	Int rva0009c6f0() const;

private:
	unsigned char m_unmodelled04[0x38];
};

class Rva0009E830Prefs
{
public:
	AsciiString getPreferredMap();
};

class Rva0000BAD7Owner
{
public:
	AsciiString getSlotList();
};

class PlayerTemplate
{
private:
	unsigned char m_unmodelled00[8];

public:
	AsciiString m_displayName;
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(Int index) const;
};
extern PlayerTemplateStore *ThePlayerTemplateStore;

class MapMetaData
{
private:
	unsigned char m_unmodelled00[0x28];

public:
	UnsignedInt m_filesize;
	UnsignedInt m_CRC;
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};
extern MapCache *TheMapCache;

bool ParseAsciiStringToGameInfo(GameInfo *game, AsciiString options, bool includeSlots);
extern "C" __declspec(dllimport) unsigned long __stdcall GetTickCount(void);

class BfmeAptScreenSkirmish
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual bool rva0057BE50();
	void _bfme_updateProfileDisplay();

private:
	unsigned char m_unmodelled00[0x3a8];
	SkirmishPreferences m_preferences;
	SkirmishBattleHonors m_honors;
};

bool BfmeAptScreenSkirmish::rva0057BE50()
{
	register Int zero = 0;
	if (Rva00579160TheCurrent == 0)
	{
		Rva00579160TheCurrent =
			(Rva00579160Current *)new Rva00003409Open2SlotOwner();
	}
	else if (Rva00579160TheCurrent->m_inGame)
	{
		Rva00579160TheCurrent->endGame();
	}

	Rva00579160TheCurrent->leaveGame();
	Rva00579160TheCurrent->clearSlotList();
	Rva00579160TheCurrent->reset();

	GameSlot *slot0 = Rva00579160TheCurrent->getSlot(zero);
	Rva00579160TheCurrent->m_slotData34 = *(UnsignedInt *)((char *)slot0 + 0x30);
	Rva00579160TheCurrent->m_slotData38 = *(UnsignedInt *)((char *)slot0 + 0x34);
	Rva00579160TheCurrent->enterGame();


	GameSlot slot;
	{
		UnicodeString userName = m_preferences.getUserName();
		slot.m_name = userName;
	}
	{
		GameSlotConnectInfo connectInfo;
		connectInfo.m_nat = 0;
		connectInfo.m_port = 0;
		slot.setState(SLOT_PLAYER, m_preferences.getUserName(), &connectInfo);
	}
	SkirmishRetailCallView *retailCalls = (SkirmishRetailCallView *)&m_honors;
	slot.setColor(retailCalls->colorResult());
	slot.setPlayerTemplate(retailCalls->factionResult());
	Rva00579160TheCurrent->setSlot(zero, slot);

	if (slot.m_playerTemplate != PLAYERTEMPLATE_RANDOM &&
		slot.m_playerTemplate != PLAYERTEMPLATE_OBSERVER)
	{
		AsciiString playerName =
			ThePlayerTemplateStore->getNthPlayerTemplate(slot.m_playerTemplate)->m_displayName;
		if (m_honors.getWins(playerName) > 10)
		{
			GameSlotConnectInfo connectInfo;
			connectInfo.m_nat = 0;
			connectInfo.m_port = 0;
			slot.setState(SLOT_BRUTAL_AI, UnicodeString::TheEmptyString, &connectInfo);
		}
		else if (m_honors.getWins(playerName) > 5)
		{
			GameSlotConnectInfo connectInfo;
			connectInfo.m_nat = 0;
			connectInfo.m_port = 0;
			slot.setState(SLOT_MED_AI, UnicodeString::TheEmptyString, &connectInfo);
		}
		else
		{
			GameSlotConnectInfo connectInfo;
			connectInfo.m_nat = 0;
			connectInfo.m_port = 0;
			slot.setState(SLOT_EASY_AI, UnicodeString::TheEmptyString, &connectInfo);
		}
		Rva00579160TheCurrent->setSlot(1, slot);
	}
	else
	{
		if (m_honors.rva0009c6f0() > 40)
		{
			GameSlotConnectInfo fallbackConnectInfo;
			fallbackConnectInfo.m_nat = 0;
			fallbackConnectInfo.m_port = 0;
			slot.setState(SLOT_BRUTAL_AI, UnicodeString::TheEmptyString, &fallbackConnectInfo);
		}
		else if (m_honors.rva0009c6f0() > 20)
		{
			GameSlotConnectInfo fallbackConnectInfo;
			fallbackConnectInfo.m_nat = 0;
			fallbackConnectInfo.m_port = 0;
			slot.setState(SLOT_MED_AI, UnicodeString::TheEmptyString, &fallbackConnectInfo);
		}
		else
		{
			GameSlotConnectInfo fallbackConnectInfo;
			fallbackConnectInfo.m_nat = 0;
			fallbackConnectInfo.m_port = 0;
			slot.setState(SLOT_EASY_AI, UnicodeString::TheEmptyString, &fallbackConnectInfo);
		}
		Rva00579160TheCurrent->setSlot(1, slot);
	}
	ParseAsciiStringToGameInfo(Rva00579160TheCurrent,
		((Rva0000BAD7Owner *)&m_honors)->getSlotList(), true);
	Rva00579160TheCurrent->setSeed(GetTickCount());
	Rva00579160TheCurrent->setMap(
		((Rva0009E830Prefs *)&m_honors)->getPreferredMap());

	const MapMetaData *map = TheMapCache->findMap(Rva00579160TheCurrent->getMap());
	if (!map)
	{
		Rva00579160TheCurrent->setMapCRC(zero);
		Rva00579160TheCurrent->setMapSize(zero);
	}
	else
	{
		Rva00579160TheCurrent->setMapCRC(map->m_CRC);
		Rva00579160TheCurrent->setMapSize(map->m_filesize);
	}

	_bfme_updateProfileDisplay();
	return true;
}
