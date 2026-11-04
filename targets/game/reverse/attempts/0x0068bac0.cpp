// ?handleRequestGameLeave@LANAPI@@IAEXPAULANMessage@@ABUIPAddr@@_N@Z
// partial score=0.3754 date=2026-11-04
// ?handleRequestGameLeave@LANAPI@@IAEXPAULANMessage@@ABUIPAddr@@_N@Z
// partial date=2026-11-04 model=claude-opus-5-5
// cl: /DNDEBUG /MD /EHsc
//
// Fresh rewrite from the retail stream (ZH LANAPIhandlers.cpp twin on the BFME
// ABI; the name is the matched LANAPI::update caller's pin at 0x0068BAC0).
// 999/999 bytes, shape 0.974, 10 structural differences; see
// targets/game/reverse/attempt_support/0068bac0-handlerequestgameleave-20261104.md

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;
typedef bool Bool;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const WideChar *text);

extern const char g_bfmeEmptyAscii[];
extern const WideChar BFMEEmptyUnicodeString;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	void set(const StringBase<T> &other);

private:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() { releaseBuffer(); }

	const char *str() const { return m_data ? m_data->m_text : g_bfmeEmptyAscii; }
};

class UnicodeString : private StringBase<WideChar>
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
	~UnicodeString() { releaseBuffer(); }

	UnicodeString &operator=(const UnicodeString &other)
	{
		set(other);
		return *this;
	}

	const WideChar *str() const { return m_data ? m_data->m_text : &BFMEEmptyUnicodeString; }
	Int getLength() const { return m_data ? m_data->m_length : 0; }

	void translate(const AsciiString &text);

	__forceinline Int compare(const WideChar *text) const
	{
		Int otherLength = text ? wcslen(text) : 0;
		Int myLength = getLength();
		const WideChar *mine = str();
		Int count = myLength < otherLength ? myLength : otherLength;
		while (count > 0)
		{
			if (*mine != *text)
			{
				Int diff = *mine - *text;
				if (diff)
					return diff;
				break;
			}
			++mine;
			++text;
			--count;
		}
		return myLength - otherLength;
	}
};

struct IPAddr
{
	IPAddr() : m_ip(0), m_port(0) {}

	UnsignedInt m_ip;
	UnsignedShort m_port;
};

struct GameSlotConnectInfo
{
	GameSlotConnectInfo() : m_ip(0), m_port(0) {}

	UnsignedInt m_ip;
	UnsignedShort m_port;
};

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

#pragma pack(push, 1)
struct LANMessage
{
	Int LANMessageType;
	WideChar name[13];					// +0x04
	char userName[2];
	char hostName[2];
	union
	{
		struct
		{
			WideChar gameName[17];			// +0x22
		} GameToLeave;
	};
};
#pragma pack(pop)

class LANPlayer
{
public:
	LANPlayer() : m_lastHeard(0), m_next(0) {}

	void setName(const UnicodeString &name) { m_name = name; }
	void setLogin(const AsciiString &name) { m_login.translate(name); }
	void setHost(const AsciiString &name) { m_host.translate(name); }
	void setLastHeard(UnsignedInt lastHeard) { m_lastHeard = lastHeard; }
	void setIP(const IPAddr &address) { m_address = address; }

	UnicodeString m_name;					// +0x00
	UnicodeString m_login;					// +0x04
	UnicodeString m_host;					// +0x08
	UnsignedInt m_lastHeard;				// +0x0c
	LANPlayer *m_next;					// +0x10
	IPAddr m_address;					// +0x14
};

class GameSlot
{
public:
	void setState(SlotState state, UnicodeString name = UnicodeString::TheEmptyString,
		const GameSlotConnectInfo *connectInfo = &GameSlotConnectInfo());

	UnsignedByte m_bfmeBeforeAddress[0x30];
	IPAddr m_address;					// +0x30
	UnsignedByte m_bfmeAfterAddress[0x30];
};

class LANGameSlot : public GameSlot
{
public:
	LANGameSlot();
	LANGameSlot(const LANGameSlot &other);
	~LANGameSlot();
};

struct Rva0068D3E0Slot : public LANGameSlot
{
};

class Rva0068D3E0Arr
{
public:
	Rva0068D3E0Slot *at(Int index);
};

class LANGameInfo
{
public:
	virtual void _bfme_slot00(void) = 0;
	virtual void _bfme_slot01(void) = 0;
	virtual void _bfme_slot02(void) = 0;
	virtual void _bfme_slot03(void) = 0;
	virtual void _bfme_slot04(void) = 0;
	virtual void _bfme_slot05(void) = 0;
	virtual void resetAccepted(void) = 0;		// slot 6, vtable+0x18

	~LANGameInfo();

	Bool isGameInProgress(void) const { return m_inProgress != 0; }
	IPAddr *getIP(Int player) { return &m_LANSlot[player].m_address; }
	LANGameSlot *getLANSlot(Int player)
	{
		return (LANGameSlot *)((Rva0068D3E0Arr *)this)->at(player);
	}
	void setSlot(Int slotNum, LANGameSlot slotInfo);
	UnicodeString getName(void);
	LANGameInfo *getNext(void) { return m_next; }

	UnsignedByte m_bfmeBeforeInProgress[0x0d - 4];
	UnsignedByte m_inProgress;				// +0x0d
	UnsignedByte m_bfmeBeforeSlots[0x58 - 0x0e];
	LANGameSlot m_LANSlot[8];				// +0x58, 0x68 apart
	LANGameInfo *m_next;					// +0x398
};

class LANAPI
{
public:
	virtual void _bfme_slot00(void) = 0;
	virtual void _bfme_slot01(void) = 0;
	virtual void _bfme_slot02(void) = 0;
	virtual void _bfme_slot03(void) = 0;
	virtual void _bfme_slot04(void) = 0;
	virtual void _bfme_slot05(void) = 0;
	virtual void _bfme_slot06(void) = 0;
	virtual void _bfme_slot07(void) = 0;
	virtual void _bfme_slot08(void) = 0;
	virtual void _bfme_slot09(void) = 0;
	virtual void _bfme_slot10(void) = 0;
	virtual void _bfme_slot11(void) = 0;
	virtual void _bfme_slot12(void) = 0;
	virtual void _bfme_slot13(void) = 0;
	virtual void _bfme_slot14(void) = 0;
	virtual void _bfme_slot15(void) = 0;
	virtual void _bfme_slot16(void) = 0;
	virtual void _bfme_slot17(void) = 0;
	virtual void _bfme_slot18(void) = 0;
	virtual void _bfme_slot19(void) = 0;
	virtual void _bfme_slot20(void) = 0;
	virtual void requestSerializedGameInfo(Bool broadcast, const IPAddr &address) = 0;	// slot 21, +0x54
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual void _bfme_slot24(void) = 0;
	virtual void _bfme_slot25(void) = 0;
	virtual void _bfme_slot26(void) = 0;
	virtual void OnGameList(LANGameInfo *gameList) = 0;		// slot 27, +0x6C
	virtual void _bfme_slot28(void) = 0;
	virtual void _bfme_slot29(void) = 0;
	virtual void _bfme_slot30(void) = 0;
	virtual void OnHostLeave(void) = 0;				// slot 31, +0x7C
	virtual void OnPlayerLeave(UnicodeString player) = 0;		// slot 32, +0x80
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_slot34(void) = 0;
	virtual void _bfme_slot35(void) = 0;
	virtual void _bfme_slot36(void) = 0;
	virtual void _bfme_slot37(void) = 0;
	virtual void _bfme_slot38(void) = 0;
	virtual void _bfme_slot39(void) = 0;
	virtual void _bfme_slot40(void) = 0;
	virtual void _bfme_slot41(void) = 0;
	virtual void _bfme_slot42(void) = 0;
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual void _bfme_slot45(void) = 0;
	virtual Bool AmIHost(void) = 0;				// slot 46, +0xB8
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void _bfme_slot49(void) = 0;
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual LANPlayer *LookupPlayer(const IPAddr *address) = 0;	// slot 54, +0xD8
	virtual const IPAddr *getLocalAddress(void) = 0;		// slot 55, +0xDC

protected:
	void removeGame(LANGameInfo *game);
	void removePlayer(LANPlayer *player);
	void addPlayer(LANPlayer *player);
	void handleRequestGameLeave(LANMessage *msg, const IPAddr &senderIP, bool removeLobbyGame);

	UnsignedByte m_bfmeHeadA[0x0c - 4];
	LANGameInfo *m_games;					// +0x0c
	UnicodeString m_name;					// +0x10
	AsciiString m_userName;					// +0x14
	AsciiString m_hostName;					// +0x18
	UnsignedByte m_bfmeHeadB[0x3d - 0x1c];
	Bool m_inLobby;						// +0x3d
	UnsignedByte m_bfmeHeadC[2];
	LANGameInfo *m_currentGame;				// +0x40
};

// ?handleRequestGameLeave@LANAPI@@IAEXPAULANMessage@@ABUIPAddr@@_N@Z
void LANAPI::handleRequestGameLeave(LANMessage *msg, const IPAddr &senderIP, bool removeLobbyGame)
{
	if (!m_inLobby && m_currentGame && !m_currentGame->isGameInProgress())
	{
		int player;
		for (player = 0; player < 8; ++player)
		{
			IPAddr *slotIP = m_currentGame->getIP(player);
			if (slotIP->m_ip == senderIP.m_ip && slotIP->m_port == senderIP.m_port)
			{
				if (player == 0)
				{
					OnHostLeave();
					removeGame(m_currentGame);
					delete m_currentGame;
					m_currentGame = 0;

					LANPlayer *lanPlayer = LookupPlayer(getLocalAddress());
					if (!lanPlayer)
					{
						lanPlayer = new LANPlayer;
						lanPlayer->setIP(*getLocalAddress());
					}
					else
					{
						removePlayer(lanPlayer);
					}
					lanPlayer->setName(UnicodeString(m_name));
					lanPlayer->setHost(m_hostName.str());
					lanPlayer->setLogin(m_userName.str());
					lanPlayer->setLastHeard(timeGetTime());
					addPlayer(lanPlayer);
				}
				else
				{
					if (AmIHost())
					{
						LANGameSlot slot;
						slot.setState(SLOT_OPEN);
						m_currentGame->setSlot(player, slot);
					}
					OnPlayerLeave(UnicodeString(msg->name));
					((Rva0068D3E0Arr *)m_currentGame)->at(player)->setState(SLOT_OPEN);
					m_currentGame->resetAccepted();
					requestSerializedGameInfo(false, senderIP);
				}
				return;
			}
		}
	}
	else if (m_inLobby)
	{
		LANGameInfo *game = m_games;
		while (game)
		{
			if (game->getName().compare(msg->GameToLeave.gameName) == 0)
			{
				if (removeLobbyGame)
				{
					removeGame(game);
					if (game == m_currentGame)
						m_currentGame = 0;
					delete game;
					OnGameList(m_games);
				}
				break;
			}
			game = game->getNext();
		}
	}
}
