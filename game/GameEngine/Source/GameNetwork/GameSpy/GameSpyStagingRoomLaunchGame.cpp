// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// GameSpyStagingRoom::launchGame, retail 0x00639950 (945 bytes), reached from
// the matched GameSpyStagingRoom::startGame and the WOL setup/quick-match
// updates.  The Zero Hour body (StagingRoomGameInfo.cpp) is the skeleton;
// BFME builds the network through createTheNetwork, hands setLocalAddress the
// room's address pair, appends four MSG_NEW_GAME arguments, clears game data
// with two Bools and, for quick-match rooms, queues two persistent-storage
// requests.  Layout follows the matched startGame slice (GameInfo 0x58,
// 0x78-byte slots, isQM at +0x43C).  _STLP_USE_STATIC_LIB keeps the temporary
// std::string destructor inline as retail has it; the inline profile-ID getter
// fixes the preorder loop's load order.

#include <stdio.h>
#include <string.h>
#include <string>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;

template <class T> struct StringData
{
	int refs;
	unsigned short length, capacity;
	T text[1];
};

template <class T> class StringBase
{
protected:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &s);
	~StringBase() { releaseBuffer(); }
	StringData<T> *m_data;

private:
	void releaseBuffer();

public:
	void set(const StringBase &s);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &s) : StringBase<char>(s) {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &s)
	{
		StringBase<char>::set(s);
		return *this;
	}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &s) : StringBase<WideChar>(s) {}
	~UnicodeString() {}
	const WideChar *str() const { return m_data ? m_data->text : L""; }
};

std::string WideCharStringToMultiByte(const WideChar *orig);

struct NetAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

class GameSlot
{
public:
	virtual void v0();
	Bool isHuman() const;

	Int getProfileID() const { return m_profileID; }

	char m_fields04[0x44 - 0x04];
	Int m_profileID;
};

class GameInfo
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void startGame(Int gameID);
	virtual void v4();
	virtual Int getLocalSlotNum();

	GameSlot *getSlot(Int index);
	void markPlayerAsPreorder(Int index);
	AsciiString getMap() const;

	char m_fields04[0x0d - 0x04];
	Bool m_inProgress;
	char m_fields0e[0x34 - 0x0e];
	NetAddress m_localAddress;
	char m_fields3c[0x4c - 0x3c];
	UnsignedInt m_seed;
	char m_fields50[0x58 - 0x50];

	void setGameInProgress(Bool inProgress) { m_inProgress = inProgress; }
	UnsignedInt getSeed() const { return m_seed; }
};

class GameSpyStagingRoom : public GameInfo
{
public:
	UnicodeString getGameName();
	void launchGame();

	char m_slots[0x43c - 0x58];
	Bool m_isQM;
	char m_fields43d[0x460 - 0x43d];
	Int m_int460;
	Int m_int464;
};

extern GameSpyStagingRoom *TheGameSpyGame;

class GameSpyInfo
{
public:
#define GSI_SLOT(n) virtual void v##n();
	GSI_SLOT(00) GSI_SLOT(01) GSI_SLOT(02) GSI_SLOT(03) GSI_SLOT(04) GSI_SLOT(05) GSI_SLOT(06) GSI_SLOT(07)
	GSI_SLOT(08) GSI_SLOT(09) GSI_SLOT(10) GSI_SLOT(11) GSI_SLOT(12) GSI_SLOT(13) GSI_SLOT(14) GSI_SLOT(15)
	GSI_SLOT(16) GSI_SLOT(17) GSI_SLOT(18) GSI_SLOT(19) GSI_SLOT(20) GSI_SLOT(21) GSI_SLOT(22) GSI_SLOT(23)
	GSI_SLOT(24) GSI_SLOT(25) GSI_SLOT(26) GSI_SLOT(27) GSI_SLOT(28) GSI_SLOT(29) GSI_SLOT(30) GSI_SLOT(31)
	GSI_SLOT(32) GSI_SLOT(33) GSI_SLOT(34) GSI_SLOT(35) GSI_SLOT(36) GSI_SLOT(37) GSI_SLOT(38) GSI_SLOT(39)
	GSI_SLOT(40) GSI_SLOT(41) GSI_SLOT(42) GSI_SLOT(43) GSI_SLOT(44) GSI_SLOT(45) GSI_SLOT(46) GSI_SLOT(47)
	GSI_SLOT(48) GSI_SLOT(49) GSI_SLOT(50) GSI_SLOT(51) GSI_SLOT(52) GSI_SLOT(53) GSI_SLOT(54) GSI_SLOT(55)
	GSI_SLOT(56) GSI_SLOT(57) GSI_SLOT(58) GSI_SLOT(59) GSI_SLOT(60) GSI_SLOT(61) GSI_SLOT(62) GSI_SLOT(63)
	GSI_SLOT(64) GSI_SLOT(65) GSI_SLOT(66) GSI_SLOT(67) GSI_SLOT(68) GSI_SLOT(69) GSI_SLOT(70) GSI_SLOT(71)
	GSI_SLOT(72) GSI_SLOT(73) GSI_SLOT(74) GSI_SLOT(75) GSI_SLOT(76) GSI_SLOT(77) GSI_SLOT(78) GSI_SLOT(79)
	GSI_SLOT(80) GSI_SLOT(81) GSI_SLOT(82) GSI_SLOT(83) GSI_SLOT(84) GSI_SLOT(85) GSI_SLOT(86) GSI_SLOT(87)
#undef GSI_SLOT
	virtual Bool didPlayerPreorder(Int profileID);
};

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

class Transport;

// NAT::getTransport keeps the landed address-derived body name at 0x00670CA0.
class Gen_00670ca0
{
public:
	int m();
};

class NAT
{
public:
	virtual ~NAT();
	Int getSlotPort(Int slot);
	Transport *getTransport() { return (Transport *)((Gen_00670ca0 *)this)->m(); }
};

extern NAT *TheNAT;

class NetworkInterface
{
public:
	virtual ~NetworkInterface();
#define NI_SLOT(n) virtual void v##n();
	NI_SLOT(01) NI_SLOT(02) NI_SLOT(03) NI_SLOT(04) NI_SLOT(05) NI_SLOT(06) NI_SLOT(07)
	NI_SLOT(08) NI_SLOT(09) NI_SLOT(10)
#undef NI_SLOT
	virtual void parseUserList(const GameInfo *game);
	virtual void setLocalAddress(const NetAddress *address);
	virtual void attachTransport(Transport *transport);
	virtual void initTransport();
};

extern NetworkInterface *TheNetwork;
void createTheNetwork();

class GameLogic;
extern GameLogic *TheGameLogic;

// BFME's two-Bool clearGameData, through the pinned retail ILT spelling.
class BfmeGameLogicPause
{
public:
	void clearGameData(Bool showScoreScreen, Bool second);
};

class MapMetaData;

class MapCache
{
public:
	void updateCache();
	const MapMetaData *findMap(AsciiString mapName);
};

extern MapCache *TheMapCache;

class GlobalData
{
public:
	char m_fields00[0xb84];
	AsciiString m_pendingFile;
};

extern GlobalData *TheWritableGlobalData;

class GameMessage
{
public:
	void appendIntegerArgument(Int arg);
};

class MessageStream
{
public:
#define MS_SLOT(n) virtual void v##n();
	MS_SLOT(00) MS_SLOT(01) MS_SLOT(02) MS_SLOT(03) MS_SLOT(04) MS_SLOT(05) MS_SLOT(06) MS_SLOT(07)
	MS_SLOT(08) MS_SLOT(09) MS_SLOT(10) MS_SLOT(11) MS_SLOT(12)
#undef MS_SLOT
	virtual GameMessage *appendMessage(Int type);
};

extern MessageStream *TheMessageStream;

void InitGameLogicRandom(UnsignedInt seed);

// Zero Hour GameSpy/BuddyDefs.h, BFME-sized (0x2B8 bytes).
class BuddyRequest
{
public:
	enum
	{
		BUDDYREQUEST_SETSTATUS = 9
	};

	Int buddyRequestType;
	union
	{
		struct
		{
			Int status;
			char statusString[0x100];
			char locationString[0x100];
		} status;
		char raw[0x2b4];
	} arg;
};

class GameSpyBuddyMessageQueueInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void addRequest(const BuddyRequest &req);
};

extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;

class PSRequest
{
public:
	PSRequest();
	~PSRequest();

	Int requestType;
	char m_rest[0x210 - 4];
};

class GameSpyPSMessageQueueInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void addRequest(const PSRequest &req);
};

extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;

class GameTextInterface
{
public:
#define GT_SLOT(n) virtual void v##n();
	GT_SLOT(00) GT_SLOT(01) GT_SLOT(02) GT_SLOT(03) GT_SLOT(04) GT_SLOT(05) GT_SLOT(06) GT_SLOT(07)
	GT_SLOT(08) GT_SLOT(09)
#undef GT_SLOT
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);
};

extern GameTextInterface *TheGameText;

Bool DoAnyMapTransfers(GameInfo *game);
void GSMessageBoxOk(UnicodeString title, UnicodeString message, void (*okFunc)());
void PopBackToLobby();

enum
{
	MAX_SLOTS = 8,
	GP_PLAYING = 2
};

void GameSpyStagingRoom::launchGame()
{
	setGameInProgress(true);

	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		GameSlot *slot = getSlot(i);
		if (slot->isHuman())
		{
			if (reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->didPlayerPreorder(slot->getProfileID()))
				markPlayerAsPreorder(i);
		}
	}

	createTheNetwork();

	NetAddress address = m_localAddress;
	if (TheNAT)
		address.port = (UnsignedShort)TheNAT->getSlotPort(getLocalSlotNum());
	TheNetwork->setLocalAddress(&address);
	if (TheNAT)
		TheNetwork->attachTransport(TheNAT->getTransport());
	else
		TheNetwork->initTransport();

	TheNetwork->parseUserList(this);

	((BfmeGameLogicPause *)TheGameLogic)->clearGameData(false, false);

	Bool filesOk = DoAnyMapTransfers(this);

	TheMapCache->updateCache();
	if (!filesOk || TheMapCache->findMap(getMap()) == 0)
	{
		if (TheNetwork != 0)
		{
			delete TheNetwork;
			TheNetwork = 0;
		}
		GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:CouldNotTransferMap"), 0);
		PopBackToLobby();
		return;
	}

	TheWritableGlobalData->m_pendingFile = TheGameSpyGame->getMap();

	GameMessage *msg = TheMessageStream->appendMessage(0x1e);
	msg->appendIntegerArgument(5);
	msg->appendIntegerArgument(1);
	msg->appendIntegerArgument(0);
	msg->appendIntegerArgument(m_int460);

	InitGameLogicRandom(getSeed());

	BuddyRequest req;
	req.buddyRequestType = BuddyRequest::BUDDYREQUEST_SETSTATUS;
	req.arg.status.status = GP_PLAYING;
	strcpy(req.arg.status.statusString, "Loading");
	sprintf(req.arg.status.locationString, "%s",
		WideCharStringToMultiByte(TheGameSpyGame->getGameName().str()).c_str());
	TheGameSpyBuddyMessageQueue->addRequest(req);

	if (TheNAT != 0)
	{
		delete TheNAT;
		TheNAT = 0;
	}

	if (m_isQM)
	{
		if (m_int464 != 0)
		{
			PSRequest psReq;
			psReq.requestType = 7;
			TheGameSpyPSMessageQueue->addRequest(psReq);
		}

		PSRequest psReq;
		psReq.requestType = 5;
		if (TheGameSpyPSMessageQueue)
			TheGameSpyPSMessageQueue->addRequest(psReq);
	}
}
