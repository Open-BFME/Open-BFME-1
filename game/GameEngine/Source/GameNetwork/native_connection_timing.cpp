// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB
// stlport

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include <string.h>

// TU-scoped extension of the canonical StringInline owning ABI for format().
template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	const char *str( void ) const { return m_data ? m_data->m_text : ""; }
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	void format(UnicodeString pattern, ...);
	const unsigned short *str( void ) const;
};


// Retail string headers store ushort length/capacity before the text at +8.
// StringInline supplies the owning ABI; this local view supplies comparison.
struct BFMEAsciiStringHeader
{
	int references;
	unsigned short length;
	unsigned short capacity;
	char text[1];
};
static inline int filePathLength(const AsciiString &text)
{
	BFMEAsciiStringHeader *data = *reinterpret_cast<BFMEAsciiStringHeader * const *>(&text);
	return data ? data->length : 0;
}
static inline int compareFilePaths(const AsciiString &left, const AsciiString &right)
{
	int rightLength = filePathLength(right);
	const char *rightText = right.str();
	int leftLength = filePathLength(left);
	const char *leftText = left.str();
	int length = leftLength < rightLength ? leftLength : rightLength;
	int result = memcmp(leftText, rightText, length);
	return result ? result : leftLength - rightLength;
}

typedef std::map<unsigned short, AsciiString> FileCommandMap;
typedef std::map<unsigned short, unsigned char> FileMaskMap;
typedef std::map<unsigned short, int> FileProgressMap;

extern const UnicodeString BFMEEmptyPlayerName;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

typedef bool Bool;
typedef unsigned short UnsignedShort;

void __cdecl operator delete(void *block) throw();

enum NetCommandType
{
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1 = 1,
	NETCOMMANDTYPE_ACKSTAGE2 = 2,
	NETCOMMANDTYPE_FRAMEINFO = 3,
	NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY = 5,
	NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY = 6,
	NETCOMMANDTYPE_REQUESTPLAYERLEAVE = 7,
	NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME = 8,
	NETCOMMANDTYPE_REQUESTFRAMEDATA = 9,
	NETCOMMANDTYPE_PLAYERLEAVE = 10,
	NETCOMMANDTYPE_KEEPALIVE = 12,
	NETCOMMANDTYPE_DISCONNECTCHAT = 13,
	NETCOMMANDTYPE_CHAT = 14,
	NETCOMMANDTYPE_PROGRESS = 15,
	NETCOMMANDTYPE_LOADCOMPLETE = 16,
	NETCOMMANDTYPE_TIMEOUTSTART = 17,
	NETCOMMANDTYPE_WRAPPER = 18,
	NETCOMMANDTYPE_FILE = 19,
	NETCOMMANDTYPE_FILEANNOUNCE = 20,
	NETCOMMANDTYPE_FILEPROGRESS = 21,
	NETCOMMANDTYPE_ROUTERFALLBACK = 22
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	NetCommandMsg();
	virtual ~NetCommandMsg();
	virtual int getSortNumber();
	virtual void prepareForRelay();
	void attach();
	void detach();

	void setExecutionFrame(unsigned int frame) { m_executionFrame = frame; }
	unsigned int getExecutionFrame() { return m_executionFrame; }
	void setPlayerID(unsigned int playerID) { m_playerID = playerID; }
	unsigned int getPlayerID() { return m_playerID; }
	void setID(UnsignedShort id) { m_id = id; }
	UnsignedShort getID() { return m_id; }
	void setNetCommandType(NetCommandType type) { m_commandType = type; }
	NetCommandType getNetCommandType() { return m_commandType; }

protected:
	unsigned int m_timestamp;
	unsigned int m_executionFrame;
	unsigned int m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	int m_referenceCount;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetFrameCommandMsg : public NetCommandMsg
{
public:
	NetFrameCommandMsg() : NetCommandMsg()
	{
		m_frame = 0;
		m_playerFrame = 0;
		m_commandCount = -1;
		m_commandType = NETCOMMANDTYPE_FRAMEINFO;
	}

	void setFrame(unsigned int frame) { m_frame = frame; }
	unsigned int getFrame() { return m_frame; }
	unsigned int getPlayerFrame() { return m_playerFrame; }
	void setPlayerFrame(unsigned int frame) { m_playerFrame = frame; }
	int getCommandCount() { return m_commandCount; }
	void setCommandCount(int count) { m_commandCount = count; }

private:
	unsigned int m_frame;
	unsigned int m_playerFrame;
	int m_commandCount;
};

class NetAckBothCommandMsg : public NetCommandMsg
{
public:
	UnsignedShort getCommandID();
	unsigned char getOriginalPlayerID();
	unsigned int getOriginalExecutionFrame() { return m_originalExecutionFrame; }
private:
	UnsignedShort m_commandID;
	unsigned char m_originalPlayerID;
	unsigned int m_originalExecutionFrame;
};

class NetAckStage2CommandMsg : public NetCommandMsg
{
public:
	NetAckStage2CommandMsg(NetCommandMsg *msg);
	UnsignedShort getCommandID();
	unsigned char getOriginalPlayerID();
	unsigned int getOriginalExecutionFrame() { return m_originalExecutionFrame; }
private:
	UnsignedShort m_commandID;
	unsigned char m_originalPlayerID;
	unsigned int m_originalExecutionFrame;
};

class GameMessage;
class GameMessageArgument;

// The constructor at RVA 0x00674A40 copies a GameMessage's type and arguments.
// Its 0x30-byte allocation and field stores agree with the upstream layout.
class NetGameCommandMsg : public NetCommandMsg
{
public:
	NetGameCommandMsg(GameMessage *msg);

private:
	int m_numArgs;
	int m_argSize;
	int m_type;
	GameMessageArgument *m_argList;
	GameMessageArgument *m_argTail;
};

Bool DoesCommandRequireACommandID(NetCommandType type);
Bool CommandRequiresDirectSend(NetCommandMsg *msg);
Bool IsCommandSynchronized(NetCommandType type);
UnsignedShort GenerateNextCommandID();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
	public:
	NetCommandRef(NetCommandMsg *message);
	void setRelay(unsigned char value) { relay = value; }
	unsigned char getRelay() { return relay; }
	NetCommandMsg *getCommand() { return msg; }
	NetCommandRef *getNext() { return next; }
	~NetCommandRef();
	NetCommandMsg *msg;
	NetCommandRef *next;
	NetCommandRef *prev;
	unsigned char relay;
	unsigned int m_timeLastSent;
};

class NetCommandList
{
public:
	virtual ~NetCommandList();
	NetCommandRef *getFirstMessage() { return m_first; }
	NetCommandRef *findMessage(UnsignedShort id, unsigned char player);
	NetCommandRef *findMessage(UnsignedShort id, unsigned char player, unsigned int frame);
	void removeMessage(NetCommandRef *ref);
private:
	NetCommandRef *m_first;
};


// BFME-only type 22 broadcasts router succession order. The role-derived
// name follows producer 0x00666000 and disconnectPlayer consumer 0x00666300.
class BFMENetRouterFallbackCommandMsg : public NetCommandMsg
{
public:
	BFMENetRouterFallbackCommandMsg() { m_commandType = NETCOMMANDTYPE_ROUTERFALLBACK; }
	void setPlayerOrder(const int *players);
private:
	int m_players[8];
};

class NetKeepAliveCommandMsg : public NetCommandMsg
{
public:
	NetKeepAliveCommandMsg();
};

class NetPlayerLeaveCommandMsg : public NetCommandMsg
{
public:
	NetPlayerLeaveCommandMsg();
	void setLeavingPlayerID(unsigned char playerID);
private:
	unsigned char m_leavingPlayerID;
};
class NetDestroyPlayerCommandMsg : public NetCommandMsg
{
public:
	NetDestroyPlayerCommandMsg();
	void setPlayerIndex(unsigned int playerID);
private:
	unsigned int m_playerIndex;
};
// Retail copies this address as two dwords and aligns its local copy to eight
// bytes. The storage view expresses that alignment without changing ip/port.
struct NetPacketAddress
{
	union
	{
		struct { unsigned int ip; unsigned short port; };
		unsigned __int64 storage;
	};
};
#pragma pack(push, 1)
struct TransportMessage
{
	unsigned int crc;
	unsigned char data[0x400];
	int length;
	unsigned int addr;
	unsigned short port;
};
#pragma pack(pop)
class BFMETransport
{
public:
	char unknown[0x20700];
	TransportMessage received[128];
};
// Packet fields remain four-packed: address is at +0x1E4 and sizeof is 0x200.
#pragma pack(push, 4)
class NetPacket
{
public:
	NetPacket(TransportMessage *msg);
	virtual ~NetPacket();
	NetCommandList *getCommandList();
	NetPacketAddress getAddress() { return m_address; }
private:
	unsigned char m_packet[0x1DC];
	int m_packetLength;
	NetPacketAddress m_address;
	int m_numCommands;
	NetCommandRef *m_lastCommand;
	unsigned int m_lastFrame;
	unsigned short m_lastCommandID;
	unsigned char m_lastPlayerID;
	unsigned char m_lastCommandType;
	unsigned char m_lastRelay;
};
#pragma pack(pop)
class NetCommandWrapperList
{
public:
	NetCommandList *getReadyCommands();
	void processWrapper(NetCommandRef *ref);
	int getPercentComplete(unsigned short commandID);
};
class Network;
struct BFMEReceiveNetworkVTable
{
	void *unknown[55];
	Bool (__fastcall *isRouterLeavePending)(Network *network);
};
class Network
{
public:
	Bool isRouterLeavePending() { return m_vtable->isRouterLeavePending(this); }
private:
	BFMEReceiveNetworkVTable *m_vtable;
};
extern Network *TheNetwork;
Bool CommandRequiresAck(NetCommandMsg *msg);

class BFMENetInformPlayerLeaveFrameCommandMsg : public NetCommandMsg
{
public:
	unsigned int getLeaveFrame();
	int getLeavingPlayerID();
};

class BFMENetRequestFrameDataCommandMsg : public NetCommandMsg
{
public:
	BFMENetRequestFrameDataCommandMsg();
	void setFirstFrame(unsigned int firstFrame);
	void setLastFrame(unsigned int lastFrame);
	unsigned int getFirstFrame();
	unsigned int getLastFrame();
private:
	unsigned int m_firstFrame;
	unsigned int m_lastFrame;
};

class BFMENetRequestPlayerLeaveCommandMsg : public NetCommandMsg
{
public:
	BFMENetRequestPlayerLeaveCommandMsg();
	int getRequestedPlayerID();
	void setRequestedPlayerID(int player);
private:
	int m_requestedPlayer;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
	public:
	void processProgressComplete(int playerID);
	void processProgress(int playerID, int percentage);
	void timeOutGameStart();
	unsigned int getFrame() { return frame; }
	char unknown[0x3C];
	unsigned int frame;
};

extern GameLogic *TheGameLogic;

class GameClient;

struct GameClientVTable
{
	void *unknown[26];
	unsigned int (__fastcall *getFrame)(GameClient *gameClient);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
{
public:
	unsigned int getFrame() { return vtable->getFrame(this); }

private:
	GameClientVTable *vtable;
};

extern GameClient *TheGameClient;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char unknown[0xCB4];
	unsigned int networkRunAheadSlack;
	char unknownCB8[0xF4];
	Bool commandIDFiltering; // retail flag at +0xDAC; INI key not recovered here
};

extern GlobalData *TheWritableGlobalData;
extern unsigned int g_lastPacketRouterStallFrame;
extern int FRAMES_TO_KEEP;

template <class T> const T &frameMaximum(const T &a, const T &b)
{
	return b > a ? b : a;
}

template <class T> const T &frameMinimum(const T &a, const T &b)
{
	return b < a ? b : a;
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/FrameDataManager.h
class FrameDataManager
{
public:
	NetCommandList *getFrameCommandList(unsigned int frame);
	Bool getIsQuitting();
	unsigned int getCommandCount(unsigned int frame);
	unsigned int getFrameCommandCount(unsigned int frame);
	NetCommandRef *addNetCommandMsg(NetCommandMsg *msg);
	void setFrameCommandCount(unsigned int frame, unsigned int count);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/Connection.h
class Connection
{
	public:
	void sendNetCommandMsg(NetCommandMsg *msg, unsigned char relay);
	long getLastTimeSent() { return m_lastTimeSent; }
	int m_openState;
	char m_unknown04[0x10];
	UnicodeString m_playerName;
	char m_unknown18[8];
	float m_averageLatency;
	char m_unknown24[0x324];
	long m_lastTimeSent;
	unsigned int m_lastHeardFrom;
};

// Retail's real ConnectionManager, named so these two bodies carry their true
// mangled names; the BFME-native helpers below keep the BFMEConnectionManager
// name because theirs are unknown.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class DisconnectManager;
class NetDisconnectChatCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectChatCommandMsg();
	void setText(UnicodeString text);
private:
	UnicodeString m_text;
};
// These BFME-only request/reply messages carry narrow strings at +0x1C/+0x20.
class BFMENetRequestGameSpyStatsAuthKeyCommandMsg : public NetCommandMsg
{
public:
	AsciiString getText1C();
};
class BFMENetGameSpyStatsAuthKeyCommandMsg : public NetCommandMsg
{
public:
	BFMENetGameSpyStatsAuthKeyCommandMsg();
	void setText1C(AsciiString text);
	void setText20(AsciiString text);
private:
	AsciiString m_text1C;
	AsciiString m_text20;
};
// BFME adds two C-string accessors after the reference interface's eleven slots.
// Their names describe use here; no claim of recovered retail source names.
class GameSpyBuddyMessageQueueInterface
{
public:
	virtual void unknown00(); virtual void unknown04(); virtual void unknown08();
	virtual void unknown0C(); virtual void unknown10(); virtual void unknown14();
	virtual void unknown18(); virtual void unknown1C(); virtual void unknown20();
	virtual void unknown24(); virtual void unknown28();
	virtual const char *getReplyIdentityText();
	virtual const char *getAuthSecretText();
};
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
extern "C" char *goastrdup(const char *text) throw();
extern "C" char *GenerateAuthA(char *challenge, char *password, char *response);
extern "C" __declspec(dllimport) void __cdecl free(void *memory);

class NetChatCommandMsg : public NetCommandMsg
{
public:
	NetChatCommandMsg();
	void setText(UnicodeString text);
	void setPlayerMask(int playerMask);
private:
	UnicodeString m_text;
	int m_playerMask;
};

class NetDisconnectFrameCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectFrameCommandMsg();
	void setDisconnectFrame(unsigned int frame);
private:
	unsigned int m_disconnectFrame;
};

class NetProgressCommandMsg : public NetCommandMsg
{
public:
	NetProgressCommandMsg();
	void setPercentage(unsigned char percent);
	unsigned char getPercentage();
private:
	unsigned char m_percent;
};
class NetFileCommandMsg : public NetCommandMsg
{
public:
	AsciiString getRealFilename();
	unsigned char *getFileData();
	unsigned int getFileLength();
};
class File
{
public:
	enum { WRITE = 2, CREATE = 8, BINARY = 0x40 };
	virtual void unknown00();
	virtual void unknown04();
	virtual void close();
	virtual void unknown0C();
	virtual int write(const void *buffer, int length);
	virtual void unknown14(); virtual void unknown18(); virtual void unknown1C();
	virtual void unknown20(); virtual void unknown24(); virtual void unknown28();
	virtual int size();
};
class FileSystem
{
public:
	bool doesFileExist(const char *filename) const;
	File *openFile(const char *filename, int flags);
};
extern FileSystem *TheFileSystem;

// BFME LAN chat passes an IP/port record by address, unlike the ZH scalar IP.
struct BFMEFileTransferAddress
{
	unsigned int ip;
	unsigned short port;
	BFMEFileTransferAddress(unsigned int value, unsigned short portValue) : ip(value), port(portValue) {}
};
class LANAPI
{
public:
	virtual void unknown00();
	virtual void unknown04();
	virtual void unknown08();
	virtual void unknown0C();
	virtual void unknown10();
	virtual void unknown14();
	virtual void unknown18();
	virtual void unknown1C();
	virtual void unknown20();
	virtual void unknown24();
	virtual void unknown28();
	virtual void unknown2C();
	virtual void unknown30();
	virtual void unknown34();
	virtual void unknown38();
	virtual void unknown3C();
	virtual void unknown40();
	virtual void unknown44();
	virtual void unknown48();
	virtual void unknown4C();
	virtual void unknown50();
	virtual void unknown54();
	virtual void unknown58();
	virtual void unknown5C();
	virtual void unknown60();
	virtual void unknown64();
	virtual void unknown68();
	virtual void unknown6C();
	virtual void unknown70();
	virtual void unknown74();
	virtual void unknown78();
	virtual void unknown7C();
	virtual void unknown80();
	virtual void unknown84();
	virtual void unknown88();
	virtual void OnChat(UnicodeString player, const BFMEFileTransferAddress &address,
		UnicodeString message, int format);
};
extern LANAPI *TheLAN;

class NetFileAnnounceCommandMsg : public NetCommandMsg
{
public:
	NetFileAnnounceCommandMsg();
	void setRealFilename(AsciiString filename);
	void setPlayerMask(unsigned char playerMask);
	void setFileID(unsigned short fileID);
private:
	AsciiString m_filename;
	unsigned short m_fileID;
	unsigned char m_playerMask;
};
class NetFileProgressCommandMsg : public NetCommandMsg
{
public:
	NetFileProgressCommandMsg();
	void setFileID(unsigned short commandID);
	void setProgress(int progress);
private:
	unsigned short m_fileID;
	int m_progress;
};
class NetWrapperCommandMsg : public NetCommandMsg
{
public:
	unsigned short getWrappedCommandID();
};

class ConnectionManager
{
public:
	void sendLocalCommand(NetCommandMsg *msg, unsigned char relay);
	void sendLocalCommandDirect(NetCommandMsg *msg, unsigned char relay);
	int getNumPlayers();
	void flushConnections();
	void processChat(NetChatCommandMsg *msg);
	void sendDisconnectChat(UnicodeString text);
	UnicodeString getPlayerName(int slot);
	int getFileTransferProgress(int playerID, AsciiString path);
	unsigned short sendFileAnnounce(AsciiString path, unsigned char playerMask);
	friend class BFMEConnectionManager;
	unsigned int getPacketRouterSlot();

private:
	void processDisconnectChat(NetDisconnectChatCommandMsg *msg);
	void processProgress(NetProgressCommandMsg *msg);
	void processFileAnnounce(NetFileAnnounceCommandMsg *msg);
	void processFile(NetFileCommandMsg *msg);
	void processFileProgress(NetFileProgressCommandMsg *msg);
	char m_unknown00[4];
	Connection *m_connections[8];
	char m_unknown24[0x12004];
	unsigned int m_localSlot;
	unsigned int m_packetRouterSlot;
	char m_unknown12030[0x28];
	UnicodeString m_localPlayerName;
	char m_unknown1205C[0x88];
	FrameDataManager *m_frameData[8];
	char m_unknown12104[0x14];
	FileCommandMap m_fileCommandMap;
	FileMaskMap m_fileRecipientMaskMap;
	FileProgressMap m_fileProgressMap[8];
};

// Role-derived local identity: the native manager embeds nine 65536-bit
// command-ID histories. The retail source class name remains unrecovered.
class Gen_00667F30
{
public:
	void bfmeClearRange(UnsignedShort commandID);
};

class BFMECommandIDHistory
{
public:
	Bool accept(UnsignedShort commandID, unsigned int frame);
private:
	unsigned int word(unsigned int id) const { return m_bits[id >> 5]; }
	unsigned int &word(unsigned int id) { return m_bits[id >> 5]; }
	Bool isSet(unsigned int id) const { return (word(id) & (1u << (id & 31))) != 0; }
	void set(unsigned int id) { word(id) |= 1u << (id & 31); }
	unsigned int m_bits[0x800];
};

Bool BFMECommandIDHistory::accept(UnsignedShort commandID, unsigned int frame)
{
	if (TheWritableGlobalData->commandIDFiltering)
	{
		reinterpret_cast<Gen_00667F30 *>(this)->bfmeClearRange(commandID);
		unsigned int id = commandID;
		if (isSet(id))
			return false;
		set(commandID);
	}
	return true;
}

class BFMEConnectionManager
{
public:
	Bool isPlayerConnectedDefaultTimeout(int playerID);
	Bool isPlayerConnectedForTimeout(int playerID, unsigned int timeout);
	Bool hasPacketRouterFrameStall();
	void processRequestFrameDataCommand(void *msg);
	Bool areFrameCommandsComplete(unsigned int frame, Bool debugSpewage);
	int getFrameHeadroom();
	void processInformPlayerLeaveFrameCommand(void *msg);
	void sendFrameInfo();
	Bool processIncomingCommand(void *ref);
	void *construct();
	void init();
	void broadcastRouterFallbackPlan();
	int isPlayerInGame(int slot);
	int isPlayerSlotActive(int slot);
	void processRequestPlayerLeaveCommand(void *msg);
	void relayCommand(void *ref);
	void update();
	void runRelayPass();
	void destroy();
	void processWrappedCommand(NetCommandRef *ref);
	void sendFileChunk(const char *path, int playerMask, int chunk);
	void buildPlayerStatusText(void *out);
	void queueLocalCommand(void *msg); // legacy assembly identity; actual ABI is ackCommand below
	void ackCommand(NetCommandRef *ref, NetPacketAddress *source);
	void sendGameCommand(void *msg);
	Bool isDuplicateCommand(NetCommandMsg *msg);
	void sendPlayerLeaveCommands();
	void sendFrameInfoToPlayer(int slot);
	void sendChat(UnicodeString text, int playerMask);
	void sendGameSpyStatsAuthKey(void *key);
	void sendKeepAliveCommand();
	void sendProgressCommand(int percent);
	void sendDisconnectFrameCommand();
	void sendDisconnectScreenOffCommand(int slot);
	void sendRequestPlayerLeaveCommand();
	void sendLoadCompleteCommand();
	void attachPlayersFromGameInfo(void *gameInfo);
	void resolvePlayerFromName(void *msg);
	void processAck(NetCommandMsg *msg);
	void processGameSpyStatsAuthKeyCommand(void *msg);
	void processAckCommand(void *msg);
	void beginPlayerLeave(void *msg);
	void resendFrameRangeToPlayer(int playerID, unsigned int startFrame, unsigned int endFrame);

private:
	char m_unknown00[4];
	Connection *m_connections[8];
	BFMECommandIDHistory m_commandHistory[9];
	BFMETransport *m_transport;
	int m_localSlot;
	int m_packetRouterSlot;
	unsigned int m_packetRouterFallback[8];
	char m_unknown12050[0xC];
	unsigned int m_frameCeiling;
	unsigned int m_playerLatestFrame[8];
	int m_playerState[8];
	unsigned int m_playerClientFrame[8];
	char m_unknown120C0[0x20];
	DisconnectManager *m_disconnectManager;
	FrameDataManager *m_frameData[8];
	NetCommandList *m_pendingCommands;
	NetCommandList *m_pendingRelays;
	NetCommandWrapperList *m_wrapperList;
	unsigned int m_localLeaveStarted;
	char m_unknown12114[4];
	FileCommandMap m_fileCommandMap;
	FileMaskMap m_fileRecipientMaskMap;
	FileProgressMap m_fileProgressMap[8];
};


// Retail's real DisconnectManager, for the one body here whose true mangled name
// is known. Protected, to match the IAE in the decorated name.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/DisconnectManager.h
class DisconnectManager
{
public:
	// Public in the reference's header, so QAE in the decorated names.
	void processDisconnectCommand(NetCommandRef *ref, ConnectionManager *conMgr);
	DisconnectManager();
	void init();
protected:
	// Protected there, so IAE.
	void processDisconnectFrame(NetCommandMsg *msg, ConnectionManager *conMgr);
	void processDisconnectPlayer(NetCommandMsg *msg, ConnectionManager *conMgr);
};

class BFMEDisconnectManager
{
public:
	void update(void *conMgr);
};

__declspec(naked) Bool BFMEConnectionManager::isPlayerConnectedDefaultTimeout(int playerID)
{
	__asm {
		mov eax, dword ptr [esp+04h]
		cmp eax, dword ptr [ecx+12028h]
		jne notLocalPlayer
		mov al, 1
		ret 4
notLocalPlayer:
		push esi
		mov esi, dword ptr [ecx+eax*4+04h]
		test esi, esi
		je connected
		mov eax, dword ptr [esi+34Ch]
		test eax, eax
		jne testTimeout
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		mov dword ptr [esi+34Ch], eax
connected:
		mov al, 1
		pop esi
		ret 4
testTimeout:
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h
		mov edx, dword ptr [ecx+3Ch]
		__emit 03Bh
		__emit 015h
		__emit 050h
		__emit 0ADh
		__emit 00Eh
		__emit 001h
		jb earlyFrameTimeout
		mov edx, dword ptr [esi+34Ch]
		__emit 08Bh
		__emit 00Dh
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov ecx, dword ptr [ecx+0CBCh]
		sub eax, edx
		cmp ecx, eax
		sbb al, al
		inc al
		pop esi
		ret 4
earlyFrameTimeout:
		__emit 08Bh
		__emit 015h
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov ecx, dword ptr [edx+0CBCh]
		sub eax, dword ptr [esi+34Ch]
		shl ecx, 2
		cmp ecx, eax
		sbb al, al
		inc al
		pop esi
		ret 4
	}
}

__declspec(naked) Bool BFMEConnectionManager::isPlayerConnectedForTimeout(int playerID, unsigned int timeout)
{
	__asm {
		mov eax, dword ptr [esp+04h]
		cmp eax, dword ptr [ecx+12028h]
		jne notLocalPlayer
		mov al, 1
		ret 8
notLocalPlayer:
		push esi
		mov esi, dword ptr [ecx+eax*4+04h]
		test esi, esi
		je connected
		mov eax, dword ptr [esi+34Ch]
		test eax, eax
		jne testTimeout
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		mov dword ptr [esi+34Ch], eax
connected:
		mov al, 1
		pop esi
		ret 8
testTimeout:
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h
		mov edx, dword ptr [ecx+3Ch]
		__emit 03Bh
		__emit 015h
		__emit 050h
		__emit 0ADh
		__emit 00Eh
		__emit 001h
		jb earlyFrameTimeout
		mov edx, dword ptr [esi+34Ch]
		mov ecx, dword ptr [esp+0Ch]
		sub eax, edx
		cmp ecx, eax
		sbb al, al
		inc al
		pop esi
		ret 8
earlyFrameTimeout:
		__emit 08Bh
		__emit 00Dh
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h
		mov edx, dword ptr [esi+34Ch]
		mov ecx, dword ptr [ecx+0CBCh]
		sub eax, edx
		shl ecx, 2
		cmp ecx, eax
		sbb al, al
		inc al
		pop esi
		ret 8
	}
}

// The router stalls once an open peer outside slot states 1 through 3 falls
// farther behind than NetworkRunAheadSlack. During startup the horizon is 3.
Bool BFMEConnectionManager::hasPacketRouterFrameStall()
{
	if (m_localSlot != m_packetRouterSlot)
		return false;

	unsigned int frame = TheGameLogic->frame;
	unsigned int slack = frame > 5 ? TheWritableGlobalData->networkRunAheadSlack : 3;
	int slot = 0;
	Connection **connectionSlot = m_connections;
	for (; slot < 8; ++slot, ++connectionSlot) {
		Connection *connection = *connectionSlot;
		if (connection != 0 && connection->m_openState == -1 &&
			!((unsigned int)slot < 8 &&
				*(int *)((char *)connectionSlot + 0x1207C) >= 1 &&
				*(int *)((char *)connectionSlot + 0x1207C) <= 3) &&
			*(unsigned int *)((char *)connectionSlot + 0x1205C) + slack < frame) {
			unsigned int stalledFrame = m_playerLatestFrame[slot];
			if (stalledFrame != g_lastPacketRouterStallFrame)
				g_lastPacketRouterStallFrame = stalledFrame;
			return true;
		}
	}
	return false;
}

void BFMEConnectionManager::processRequestFrameDataCommand(void *command)
{
	BFMENetRequestFrameDataCommandMsg *msg = static_cast<BFMENetRequestFrameDataCommandMsg *>(command);
	if (msg == 0)
		return;
	unsigned int startFrame = msg->getFirstFrame();
	unsigned int endFrame = msg->getLastFrame();
	if (endFrame < startFrame)
		return;
	unsigned int slack = TheWritableGlobalData->networkRunAheadSlack;
	unsigned int currentFrame = TheGameLogic->getFrame();
	if (endFrame + slack < currentFrame)
		return;
	unsigned int lastFrame = frameMinimum(endFrame, TheGameLogic->getFrame());
	unsigned int firstFrame = frameMaximum(startFrame, currentFrame >= slack ? currentFrame - slack : 0);
	if (firstFrame <= lastFrame)
		resendFrameRangeToPlayer(msg->getPlayerID(), firstFrame, lastFrame);
}

// The readiness gate the frame scheduler consults (0x00681F70 calls it with
// (frame, 0); the second argument is accepted and ignored). Sums
// getCommandCount(frame) over the eight FrameDataManagers at this+0x120E4,
// skipping null and quitting ones, and compares the total against the LOCAL
// manager's getFrameCommandCount(frame), which the FRAMEINFO path stores as the
// announced expected total. Zero Hour instead matches counts per player.
Bool BFMEConnectionManager::areFrameCommandsComplete(unsigned int frame, Bool debugSpewage)
{
	unsigned int commandCount = 0;
	FrameDataManager **manager = m_frameData;
	int slotsRemaining = 8;
	do {
		if (*manager != 0 && !(*manager)->getIsQuitting())
			commandCount += (*manager)->getCommandCount(frame);
		++manager;
	} while (--slotsRemaining != 0);

	Bool commandsComplete =
		m_frameData[m_localSlot]->getFrameCommandCount(frame) == commandCount;
	return commandsComplete;
	}

// Frames of headroom. Off the packet router that is the shared ceiling at
// this+0x1205C minus the current frame plus one -- the same expression the
// scheduler returns. As router it is the current frame minus the furthest-ahead
// connected player's frame plus one, so the router cannot outrun its clients.
// The player scan is unrolled four slots at a time, reading m_connections
// (this+0x04) as this+0x12060-0x1205C.
int BFMEConnectionManager::getFrameHeadroom()
{
	if (m_localSlot != m_packetRouterSlot)
		return m_frameCeiling - TheGameLogic->frame + 1;

	unsigned int furthestPlayerFrame = 0;
	for (int slot = 0; slot < 8; slot += 4) {
		if (m_connections[slot] != 0 &&
			furthestPlayerFrame <= m_playerLatestFrame[slot])
			furthestPlayerFrame = m_playerLatestFrame[slot];
		if (m_connections[slot + 1] != 0 &&
			furthestPlayerFrame <= m_playerLatestFrame[slot + 1])
			furthestPlayerFrame = m_playerLatestFrame[slot + 1];
		if (m_connections[slot + 2] != 0 &&
			furthestPlayerFrame <= m_playerLatestFrame[slot + 2])
			furthestPlayerFrame = m_playerLatestFrame[slot + 2];
		if (m_connections[slot + 3] != 0 &&
			furthestPlayerFrame <= m_playerLatestFrame[slot + 3])
			furthestPlayerFrame = m_playerLatestFrame[slot + 3];
	}

	return TheGameLogic->frame - furthestPlayerFrame + 1;
}

// Command type 8 handler. Records the sender's announced frame in the
// per-player latest-frame array at this+0x12060 when it is within
// NetworkKeepAliveDelay of our own, then -- if that frame is still ahead of us
// and the leaving player is not us -- allocates a 0x24-byte command type 9
// (REQUESTFRAMEDATA), stamps the range [currentFrame+1, announcedFrame] into its
// two payload dwords at +0x1C and +0x20, and sends it back to the sender alone.
void BFMEConnectionManager::processInformPlayerLeaveFrameCommand(void *command)
{
	BFMENetInformPlayerLeaveFrameCommandMsg *msg = static_cast<BFMENetInformPlayerLeaveFrameCommandMsg *>(command);
	if (msg == 0)
		return;
	unsigned int leaveFrame = msg->getLeaveFrame();
	unsigned short leavingPlayer = msg->getLeavingPlayerID();
	if (leaveFrame < TheGameLogic->getFrame() + TheWritableGlobalData->networkRunAheadSlack)
	{
		if (msg->getPlayerID() < 8)
			m_playerLatestFrame[msg->getPlayerID()] = frameMaximum(leaveFrame, m_playerLatestFrame[msg->getPlayerID()]);
	}
	if (TheGameLogic->getFrame() < leaveFrame && leavingPlayer != m_localSlot)
	{
		BFMENetRequestFrameDataCommandMsg *request = new BFMENetRequestFrameDataCommandMsg;
		request->setPlayerID(m_localSlot);
		request->setExecutionFrame(-1);
		request->setFirstFrame(TheGameLogic->getFrame() + 1);
		request->setLastFrame(leaveFrame);
		if (DoesCommandRequireACommandID(request->getNetCommandType()))
			request->setID(GenerateNextCommandID());
		if (msg->getPlayerID() < 8)
			reinterpret_cast<ConnectionManager *>(this)->sendLocalCommandDirect(request, (unsigned char)1 << msg->getPlayerID());
		request->detach();
	}
}

void BFMEConnectionManager::sendFrameInfo()
{
	int commandCount = -1;
	NetFrameCommandMsg *msg = new NetFrameCommandMsg;
	msg->setFrame(TheGameLogic->getFrame());
	msg->setPlayerFrame(TheGameClient->getFrame());
	msg->setPlayerID(m_localSlot);
	if (DoesCommandRequireACommandID(msg->getNetCommandType()))
		msg->setID(GenerateNextCommandID());

	if (m_frameData[m_localSlot] != 0 && m_localSlot == m_packetRouterSlot)
	{
		commandCount = 0;
		for (int i = 0; i < 8; ++i)
		{
			if (m_frameData[i] != 0 && !m_frameData[i]->getIsQuitting())
				commandCount += m_frameData[i]->getCommandCount(TheGameLogic->getFrame());
		}
		m_frameData[m_localSlot]->setFrameCommandCount(msg->getFrame(), commandCount);
	}
	msg->setCommandCount(commandCount);

	if (m_localSlot == m_packetRouterSlot)
	{
		reinterpret_cast<ConnectionManager *>(this)->sendLocalCommand(
			msg, (unsigned char)~(1 << m_localSlot));
		m_frameCeiling = TheGameLogic->frame;
	}
	else
	{
		reinterpret_cast<ConnectionManager *>(this)->sendLocalCommand(
			msg, (unsigned char)(1 << m_packetRouterSlot));
	}
	msg->detach();
}

// The incoming-command dispatcher: switch on the command type at message
// +0x14 through the jump table at 0x0066A634 (data, deliberately outside this
// row). Case 3 is the FRAMEINFO receiver and the other half of the delay path --
// it updates the sender's latest frame at this+0x12060 and its aux dword at
// this+0x120A0, and when we are NOT the packet router it raises the shared
// ceiling at this+0x1205C to the announced frame. Only then, if the frame is not
// behind us and the message's count at +0x24 is not -1, it stores that count on
// the local FrameDataManager as the expected total. Case 8 calls
// processInformPlayerLeaveFrameCommand and case 9
// processRequestFrameDataCommand.
Bool BFMEConnectionManager::processIncomingCommand(void *ref)
{
	NetCommandRef *commandRef = static_cast<NetCommandRef *>(ref);
	NetCommandMsg *msg = commandRef->msg;
	unsigned int playerID = msg->getPlayerID();
	if (playerID >= 8)
		goto ignored;
	if (playerID != (unsigned int)m_localSlot)
	{
		Connection *connection = m_connections[playerID];
		if (connection == 0)
			goto ignored;
		connection->m_lastHeardFrom = timeGetTime();
	}

	switch (msg->getNetCommandType())
	{
	case NETCOMMANDTYPE_ACKBOTH:
	case NETCOMMANDTYPE_ACKSTAGE1:
	case NETCOMMANDTYPE_ACKSTAGE2:
		processAck(msg);
		return true;
	case NETCOMMANDTYPE_WRAPPER:
		processWrappedCommand(commandRef);
		return true;
	case NETCOMMANDTYPE_FRAMEINFO:
	{
		NetFrameCommandMsg *frameMsg = static_cast<NetFrameCommandMsg *>(msg);
		if (m_localSlot == m_packetRouterSlot)
		{
			if (frameMsg->getFrame() > m_playerLatestFrame[playerID])
			{
				m_playerLatestFrame[playerID] = frameMsg->getFrame();
				m_playerClientFrame[playerID] = frameMsg->getPlayerFrame();
			}
		}
		else
		{
			if (frameMsg->getFrame() > m_playerLatestFrame[playerID])
			{
				m_playerLatestFrame[playerID] = frameMsg->getFrame();
				m_playerClientFrame[playerID] = frameMsg->getPlayerFrame();
			}
			if (m_frameCeiling < frameMsg->getFrame())
				m_frameCeiling = frameMsg->getFrame();
			if (frameMsg->getFrame() >= TheGameLogic->getFrame() &&
				frameMsg->getCommandCount() != -1)
				m_frameData[m_localSlot]->setFrameCommandCount(
					frameMsg->getFrame(), frameMsg->getCommandCount());
		}
		return false;
	}
	case NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME:
		processInformPlayerLeaveFrameCommand(msg);
		return false;
	case NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY:
		sendGameSpyStatsAuthKey(msg);
		return false;
	case NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY:
		processGameSpyStatsAuthKeyCommand(msg);
		return false;
	case NETCOMMANDTYPE_REQUESTFRAMEDATA:
		processRequestFrameDataCommand(msg);
		return false;
	case NETCOMMANDTYPE_REQUESTPLAYERLEAVE:
		processRequestPlayerLeaveCommand(msg);
		return false;
	case NETCOMMANDTYPE_ROUTERFALLBACK:
		// Payload entries are player IDs in router fallback order, not per-player metrics.
		struct RouterFallbackOrder { unsigned int player[8]; };
		*reinterpret_cast<RouterFallbackOrder *>(m_packetRouterFallback) =
			*reinterpret_cast<RouterFallbackOrder *>(reinterpret_cast<char *>(msg) + 0x1C);
		return true;
	case NETCOMMANDTYPE_PROGRESS:
		reinterpret_cast<ConnectionManager *>(this)->processProgress(
			reinterpret_cast<NetProgressCommandMsg *>(msg));
		commandRef->relay &= (unsigned char)~(1 << m_localSlot);
		return true;
	case NETCOMMANDTYPE_TIMEOUTSTART:
		TheGameLogic->timeOutGameStart();
		return true;
	case NETCOMMANDTYPE_DISCONNECTCHAT:
		reinterpret_cast<ConnectionManager *>(this)->processDisconnectChat(
			reinterpret_cast<NetDisconnectChatCommandMsg *>(msg));
		return true;
	case NETCOMMANDTYPE_LOADCOMPLETE:
		TheGameLogic->processProgressComplete(playerID);
		return true;
	case NETCOMMANDTYPE_CHAT:
		resolvePlayerFromName(msg);
		return true;
	case NETCOMMANDTYPE_FILE:
		reinterpret_cast<ConnectionManager *>(this)->processFile(
			static_cast<NetFileCommandMsg *>(msg));
		return true;
	case NETCOMMANDTYPE_FILEANNOUNCE:
		reinterpret_cast<ConnectionManager *>(this)->processFileAnnounce(
			reinterpret_cast<NetFileAnnounceCommandMsg *>(msg));
		return true;
	case NETCOMMANDTYPE_FILEPROGRESS:
		reinterpret_cast<ConnectionManager *>(this)->processFileProgress(
			reinterpret_cast<NetFileProgressCommandMsg *>(msg));
		return true;
	case NETCOMMANDTYPE_KEEPALIVE:
		return false;
	default:
		if (msg->getNetCommandType() > 23 && msg->getNetCommandType() < 29)
		{
			if (m_disconnectManager != 0)
				m_disconnectManager->processDisconnectCommand(commandRef,
					reinterpret_cast<ConnectionManager *>(this));
			goto ignored;
		}
		return true;
	}
ignored:
	return false;
}

// Constructor. Zeroes the whole tail of the object, which is what pins its
// layout: the frame ceiling at +0x1205C, the scalar trio at +0x12050/+0x12054
// (word)/+0x12058, +0x120E0, and the pointer block +0x12104..+0x12110 plus a
// byte at +0x12114.
__declspec(naked) void *BFMEConnectionManager::construct()
{
	__asm {
		push 0FFFFFFFFh
		push 10445DAh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push ebx
		push ebp
		push esi
		mov esi, ecx
		push edi
		mov dword ptr [esp+10h], esi
		mov dword ptr [esi], 111A2B0h
		lea edx,  [esi+24h]
		mov ebp, 9h
		xor ebx, ebx
L00_669660:
		xor eax, eax
		mov edi, edx
		mov ecx, 800h
		rep stosd
		mov dword ptr [edx], ebx
		add edx, 2000h
		dec ebp
		jne L00_669660
		mov dword ptr [esi+12024h], ebx
		or edi, 0FFFFFFFFh
		mov dword ptr [esi+12028h], edi
		mov dword ptr [esi+1202Ch], ebx
		mov dword ptr [esi+12050h], ebx
		mov word ptr [esi+12054h], bx
		mov dword ptr [esi+12058h], ebx
		mov dword ptr [esi+1205Ch], ebx
		mov dword ptr [esi+120E0h], ebx
		mov dword ptr [esi+12104h], ebx
		mov dword ptr [esi+12108h], ebx
		mov dword ptr [esi+1210Ch], ebx
		mov dword ptr [esi+12110h], ebx
		mov byte ptr [esi+12114h], bl
		mov byte ptr [esi+12115h], 1h
		push 18h
		mov dword ptr [esp+20h], ebx
		mov dword ptr [esi+12118h], ebx
		__emit 0E8h
		__emit 060h
		__emit 04Eh
		__emit 01Ch
		__emit 000h   // call 0x82E540
		mov dword ptr [esi+12118h], eax
		mov dword ptr [esi+1211Ch], ebx
		mov byte ptr [eax], bl
		mov eax, dword ptr [esi+12118h]
		mov dword ptr [eax+4h], ebx
		mov eax, dword ptr [esi+12118h]
		mov dword ptr [eax+8h], eax
		mov eax, dword ptr [esi+12118h]
		mov dword ptr [eax+0Ch], eax
		push 14h
		mov byte ptr [esp+24h], 1h
		mov dword ptr [esi+12124h], ebx
		__emit 0E8h
		__emit 025h
		__emit 04Eh
		__emit 01Ch
		__emit 000h   // call 0x82E540
		mov dword ptr [esi+12124h], eax
		mov dword ptr [esi+12128h], ebx
		mov byte ptr [eax], bl
		mov ecx, dword ptr [esi+12124h]
		mov dword ptr [ecx+4h], ebx
		mov eax, dword ptr [esi+12124h]
		mov dword ptr [eax+8h], eax
		mov eax, dword ptr [esi+12124h]
		add esp, 8h
		mov dword ptr [eax+0Ch], eax
		push 43C961h
		push 443649h
		push 8h
		push 0Ch
		lea edx,  [esi+12130h]
		push edx
		mov byte ptr [esp+30h], 2h
		__emit 0E8h
		__emit 07Eh
		__emit 0D7h
		__emit 038h
		__emit 000h   // call 0x9F6EE4
		mov dword ptr [esi+4h], ebx
		mov dword ptr [esi+12030h], edi
		mov dword ptr [esi+120E4h], ebx
		mov dword ptr [esi+12060h], ebx
		mov dword ptr [esi+120A0h], ebx
		mov dword ptr [esi+120C0h], ebx
		mov dword ptr [esi+12080h], ebx
		mov dword ptr [esi+8h], ebx
		mov dword ptr [esi+12034h], edi
		mov dword ptr [esi+120E8h], ebx
		mov dword ptr [esi+12064h], ebx
		mov dword ptr [esi+120A4h], ebx
		mov dword ptr [esi+120C4h], ebx
		mov dword ptr [esi+12084h], ebx
		mov dword ptr [esi+0Ch], ebx
		mov dword ptr [esi+12038h], edi
		mov dword ptr [esi+120ECh], ebx
		mov dword ptr [esi+12068h], ebx
		mov dword ptr [esi+120A8h], ebx
		mov dword ptr [esi+120C8h], ebx
		mov dword ptr [esi+12088h], ebx
		mov dword ptr [esi+10h], ebx
		mov dword ptr [esi+1203Ch], edi
		mov dword ptr [esi+120F0h], ebx
		mov dword ptr [esi+1206Ch], ebx
		mov dword ptr [esi+120ACh], ebx
		mov dword ptr [esi+120CCh], ebx
		mov dword ptr [esi+1208Ch], ebx
		mov ecx, dword ptr [esp+14h]
		mov dword ptr [esi+12040h], edi
		mov dword ptr [esi+12044h], edi
		mov dword ptr [esi+12048h], edi
		mov dword ptr [esi+1204Ch], edi
		pop edi
		mov dword ptr [esi+14h], ebx
		mov dword ptr [esi+120F4h], ebx
		mov dword ptr [esi+12070h], ebx
		mov dword ptr [esi+120B0h], ebx
		mov dword ptr [esi+120D0h], ebx
		mov dword ptr [esi+12090h], ebx
		mov dword ptr [esi+18h], ebx
		mov dword ptr [esi+120F8h], ebx
		mov dword ptr [esi+12074h], ebx
		mov dword ptr [esi+120B4h], ebx
		mov dword ptr [esi+120D4h], ebx
		mov dword ptr [esi+12094h], ebx
		mov dword ptr [esi+1Ch], ebx
		mov dword ptr [esi+120FCh], ebx
		mov dword ptr [esi+12078h], ebx
		mov dword ptr [esi+120B8h], ebx
		mov dword ptr [esi+120D8h], ebx
		mov dword ptr [esi+12098h], ebx
		mov dword ptr [esi+20h], ebx
		mov dword ptr [esi+12100h], ebx
		mov dword ptr [esi+1207Ch], ebx
		mov dword ptr [esi+120BCh], ebx
		mov dword ptr [esi+120DCh], ebx
		mov dword ptr [esi+1209Ch], ebx
		mov eax, esi
		pop esi
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret
	}
}

// init/reset. Clears the eight Connection pointers at +0x04, rebuilds the two
// 16-byte objects at +0x12104 and +0x12108, sets m_localSlot to -1, zeroes the
// frame ceiling and m_packetRouterSlot, then walks eight slots at once writing
// -1 to the id array at +0x12030 and zero to the per-player arrays at +0x12060,
// +0x120A0 and +0x120C0.
__declspec(naked) void BFMEConnectionManager::init()
{
	__asm {
		push 0FFFFFFFFh
		push 104458Ch
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		xor eax, eax
		push ebx
		mov ebx, ecx
		mov dword ptr [ebx+4h], eax
		mov dword ptr [ebx+8h], eax
		mov dword ptr [ebx+0Ch], eax
		mov dword ptr [ebx+10h], eax
		mov dword ptr [ebx+14h], eax
		mov dword ptr [ebx+18h], eax
		mov dword ptr [ebx+1Ch], eax
		push ebp
		mov dword ptr [ebx+20h], eax
		mov eax, dword ptr [ebx+12104h]
		xor ebp, ebp
		cmp eax, ebp
		push esi
		push edi
		jne L00_6690C9
		push 10h
		__emit 0E8h
		__emit 097h
		__emit 08Eh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		cmp eax, ebp
		mov dword ptr [esp+1Ch], ebp
		je L01_6690B1
		mov ecx, eax
		__emit 0E8h
		__emit 0F7h
		__emit 072h
		__emit 09Bh
		__emit 0FFh   // call 0x203A6
		jmp L02_6690B3
L01_6690B1:
		xor eax, eax
L02_6690B3:
		or esi, 0FFFFFFFFh
		mov ecx, eax
		mov dword ptr [esp+1Ch], esi
		mov dword ptr [ebx+12104h], eax
		__emit 0E8h
		__emit 007h
		__emit 029h
		__emit 09Ah
		__emit 0FFh   // call 0xB9CE
		jmp L03_6690CC
L00_6690C9:
		or esi, 0FFFFFFFFh
L03_6690CC:
		mov ecx, dword ptr [ebx+12104h]
		__emit 0E8h
		__emit 0F7h
		__emit 028h
		__emit 09Ah
		__emit 0FFh   // call 0xB9CE
		cmp dword ptr [ebx+12108h], ebp
		jne L04_669115
		push 10h
		__emit 0E8h
		__emit 04Ah
		__emit 08Eh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		cmp eax, ebp
		mov dword ptr [esp+1Ch], 1h
		je L05_669102
		mov ecx, eax
		__emit 0E8h
		__emit 0A6h
		__emit 072h
		__emit 09Bh
		__emit 0FFh   // call 0x203A6
		jmp L06_669104
L05_669102:
		xor eax, eax
L06_669104:
		mov ecx, eax
		mov dword ptr [esp+1Ch], esi
		mov dword ptr [ebx+12108h], eax
		__emit 0E8h
		__emit 0B9h
		__emit 028h
		__emit 09Ah
		__emit 0FFh   // call 0xB9CE
L04_669115:
		mov ecx, dword ptr [ebx+12108h]
		__emit 0E8h
		__emit 0AEh
		__emit 028h
		__emit 09Ah
		__emit 0FFh   // call 0xB9CE
		mov dword ptr [ebx+12028h], esi
		mov dword ptr [ebx+1205Ch], ebp
		mov dword ptr [ebx+1202Ch], ebp
		lea eax,  [ebx+12060h]
		mov ecx, 8h
		__emit 08Dh
		__emit 049h
		__emit 000h   // lea ecx, [ecx]
L07_669140:
		mov dword ptr [eax-30h], esi
		mov dword ptr [eax], ebp
		mov dword ptr [eax+40h], ebp
		mov dword ptr [eax+60h], ebp
		add eax, 4h
		dec ecx
		mov dword ptr [ebx+120A0h], ebp
		jne L07_669140
		lea esi,  [ebx+120E4h]
		mov edi, 8h
L09_669162:
		mov ecx, dword ptr [esi]
		cmp ecx, ebp
		je L08_669170
		mov edx, dword ptr [ecx]
		push 1h
		call dword ptr [edx]
		mov dword ptr [esi], ebp
L08_669170:
		add esi, 4h
		dec edi
		jne L09_669162
		push 28Ch
		__emit 0E8h
		__emit 0B0h
		__emit 08Dh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		cmp eax, ebp
		mov dword ptr [esp+1Ch], 2h
		je L10_66919C
		mov ecx, eax
		__emit 0E8h
		__emit 0BEh
		__emit 0ECh
		__emit 09Bh
		__emit 0FFh   // call 0x27E58
		jmp L11_66919E
L10_66919C:
		xor eax, eax
L11_66919E:
		or esi, 0FFFFFFFFh
		mov ecx, eax
		mov dword ptr [esp+1Ch], esi
		mov dword ptr [ebx+120E0h], eax
		__emit 0E8h
		__emit 030h
		__emit 01Ch
		__emit 09Ch
		__emit 0FFh   // call 0x2ADE2
		push 8h
		__emit 0E8h
		__emit 077h
		__emit 08Dh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		cmp eax, ebp
		mov dword ptr [esp+1Ch], 3h
		je L12_6691D5
		mov ecx, eax
		__emit 0E8h
		__emit 0D0h
		__emit 0D4h
		__emit 09Ah
		__emit 0FFh   // call 0x166A3
		jmp L13_6691D7
L12_6691D5:
		xor eax, eax
L13_6691D7:
		mov ecx, eax
		mov dword ptr [esp+1Ch], esi
		mov dword ptr [ebx+1210Ch], eax
		__emit 0E8h
		__emit 0C0h
		__emit 004h
		__emit 09Dh
		__emit 0FFh   // call 0x396A8
		mov eax, dword ptr [ebx+1211Ch]
		cmp eax, ebp
		lea edi,  [ebx+12118h]
		je L14_66923A
		mov eax, dword ptr [edi]
		mov esi, dword ptr [eax+4h]
		cmp esi, ebp
		je L15_669228
L16_669201:
		mov ecx, dword ptr [esi+0Ch]
		push ecx
		mov ecx, edi
		__emit 0E8h
		__emit 0DFh
		__emit 096h
		__emit 09Ah
		__emit 0FFh   // call 0x128EB
		mov ebp, dword ptr [esi+8h]
		lea ecx,  [esi+14h]
		__emit 0E8h
		__emit 029h
		__emit 0E7h
		__emit 021h
		__emit 000h   // call 0x887940
		push 18h
		push esi
		__emit 0E8h
		__emit 0D1h
		__emit 053h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
		test ebp, ebp
		mov esi, ebp
		jne L16_669201
L15_669228:
		mov eax, dword ptr [edi]
		mov dword ptr [eax+8h], eax
		mov edx, dword ptr [edi]
		mov dword ptr [edx+4h], ebp
		mov eax, dword ptr [edi]
		mov dword ptr [eax+0Ch], eax
		mov dword ptr [edi+4h], ebp
L14_66923A:
		mov eax, dword ptr [ebx+12128h]
		cmp eax, ebp
		lea edi,  [ebx+12124h]
		je L17_669284
		mov eax, dword ptr [edi]
		mov esi, dword ptr [eax+4h]
		cmp esi, ebp
		je L18_669272
L19_669253:
		mov ecx, dword ptr [esi+0Ch]
		push ecx
		mov ecx, edi
		__emit 0E8h
		__emit 0C1h
		__emit 0F8h
		__emit 09Ah
		__emit 0FFh   // call 0x18B1F
		mov ebp, dword ptr [esi+8h]
		push 14h
		push esi
		__emit 0E8h
		__emit 087h
		__emit 053h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
		test ebp, ebp
		mov esi, ebp
		jne L19_669253
L18_669272:
		mov eax, dword ptr [edi]
		mov dword ptr [eax+8h], eax
		mov edx, dword ptr [edi]
		mov dword ptr [edx+4h], ebp
		mov eax, dword ptr [edi]
		mov dword ptr [eax+0Ch], eax
		mov dword ptr [edi+4h], ebp
L17_669284:
		lea edi,  [ebx+12130h]
		mov dword ptr [esp+10h], 8h
L23_669292:
		cmp dword ptr [edi+4h], ebp
		je L20_6692D1
		mov eax, dword ptr [edi]
		mov esi, dword ptr [eax+4h]
		cmp esi, ebp
		je L21_6692BF
L22_6692A0:
		mov ecx, dword ptr [esi+0Ch]
		push ecx
		mov ecx, edi
		__emit 0E8h
		__emit 0AFh
		__emit 0F2h
		__emit 09Ch
		__emit 0FFh   // call 0x3855A
		mov ebp, dword ptr [esi+8h]
		push 18h
		push esi
		__emit 0E8h
		__emit 03Ah
		__emit 053h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
		test ebp, ebp
		mov esi, ebp
		jne L22_6692A0
L21_6692BF:
		mov eax, dword ptr [edi]
		mov dword ptr [eax+8h], eax
		mov edx, dword ptr [edi]
		mov dword ptr [edx+4h], ebp
		mov eax, dword ptr [edi]
		mov dword ptr [eax+0Ch], eax
		mov dword ptr [edi+4h], ebp
L20_6692D1:
		mov eax, dword ptr [esp+10h]
		add edi, 0Ch
		dec eax
		mov dword ptr [esp+10h], eax
		jne L23_669292
		mov ecx, dword ptr [esp+14h]
		pop edi
		mov dword ptr [ebx+12110h], ebp
		pop esi
		mov byte ptr [ebx+12114h], 0h
		mov byte ptr [ebx+12115h], 1h
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret
	}
}

struct BFMEPlayerRouterScore
{
	float score;
	int player;
	BFMEPlayerRouterScore *next;
};

// Builds the router succession list: local player first, then remote players
// ordered by latency with a penalty for the client/logic frame ratio.
void BFMEConnectionManager::broadcastRouterFallbackPlan()
{
	BFMEPlayerRouterScore *head = 0;
	for (int player = 0; player < 8; ++player)
	{
		if (m_connections[player])
		{
			float score = m_connections[player]->m_averageLatency;
			if ((float)m_playerClientFrame[player] / (float)m_playerLatestFrame[player] <= 20.0f)
				score += 1000.0f;
			BFMEPlayerRouterScore *node = new BFMEPlayerRouterScore;
			node->score = score;
			node->player = player;
			BFMEPlayerRouterScore *previous = 0;
			BFMEPlayerRouterScore *current = head;
			while (current)
			{
				if (current->score > score)
					break;
				previous = current;
				current = current->next;
			}
			node->next = current;
			if (previous)
				previous->next = node;
			else
				head = node;
		}
	}
	int players[8];
	unsigned int count = 1;
	players[0] = m_localSlot;
	if (head)
	{
		while (head)
		{
			if (count < 8)
				players[count++] = head->player;
			BFMEPlayerRouterScore *next = head->next;
			delete head;
			head = next;
		}
		if (count > 2)
		{
			for (unsigned int i = count; i < 8; ++i)
				players[i] = -1;
			BFMENetRouterFallbackCommandMsg *msg = new BFMENetRouterFallbackCommandMsg;
			msg->setPlayerOrder(players);
			msg->setPlayerID(m_localSlot);
			if (DoesCommandRequireACommandID(msg->getNetCommandType()))
				msg->setID(GenerateNextCommandID());
			reinterpret_cast<ConnectionManager *>(this)->sendLocalCommand(msg, 0xFF);
			msg->detach();
		}
	}
}

// Direct sending preserves an assigned execution frame; otherwise it uses the
// current logic frame, with a minimum of 2. Local synchronized commands enter
// frame storage, and each requested remote connection gets its own relay bit.
void ConnectionManager::sendLocalCommandDirect(NetCommandMsg *msg, unsigned char relay)
{
	msg->attach();
	if (msg->getExecutionFrame() == (unsigned int)-1)
	{
		unsigned int frame = TheGameLogic->getFrame();
		if (frame <= 2)
			frame = 2;
		msg->setExecutionFrame(frame);
	}
	int relayMask = relay;
	if ((relayMask & (1 << m_localSlot)) != 0 &&
		IsCommandSynchronized(msg->getNetCommandType()) &&
		m_localSlot < 8 && m_frameData[m_localSlot] != 0)
		m_frameData[m_localSlot]->addNetCommandMsg(msg);

	for (int i = 0; i < 8; ++i)
	{
		if ((relayMask & (1 << i)) != 0 && m_connections[i] != 0)
			m_connections[i]->sendNetCommandMsg(msg, (unsigned char)(1 << i));
	}
	msg->detach();
}

void ConnectionManager::sendLocalCommand(NetCommandMsg *msg, unsigned char relay)
{
	if (CommandRequiresDirectSend(msg) ||
		m_packetRouterSlot >= 8 || m_connections[m_packetRouterSlot] == 0)
	{
		sendLocalCommandDirect(msg, relay);
		return;
	}

	msg->attach();
	if (m_localSlot == m_packetRouterSlot)
	{
		unsigned int frame = TheGameLogic->getFrame();
		if (frame <= 2)
			frame = 2;
		int relayMask = relay;
		msg->setExecutionFrame(frame);

		// Retail splits msg's live range here so ESI can hold the loop index;
		// these reads preserve VC7.1's reloads from the original argument slot.
		for (int i = 0; i < 8; ++i)
		{
			if ((relayMask & (1 << i)) != 0 && m_connections[i] != 0)
				m_connections[i]->sendNetCommandMsg(
					*(NetCommandMsg * volatile *)&msg, (unsigned char)(1 << i));
		}

		if (m_localSlot < 8 && (relayMask & (1 << m_localSlot)) != 0 &&
			m_frameData[m_localSlot] != 0)
			m_frameData[m_localSlot]->addNetCommandMsg(*(NetCommandMsg * volatile *)&msg);
	}
	else if (m_packetRouterSlot < 8 && m_connections[m_packetRouterSlot] != 0)
	{
		m_connections[m_packetRouterSlot]->sendNetCommandMsg(msg, relay);
	}

	msg->detach();
}

// A slot is in the game when its per-player state at this+0x12080 is exactly 1
// and either it is our own slot or its Connection at this+0x04 is open (the
// dword at Connection+0 is the -1 sentinel).
int BFMEConnectionManager::isPlayerInGame(int slot)
{
	if ((unsigned int)slot >= 8 || m_playerState[slot] != 1)
		goto notInGame;
	if (slot == m_localSlot)
		goto inGame;
	Connection *connection = m_connections[slot];
	if (connection == 0 || connection->m_openState != -1)
		goto notInGame;
inGame:
	return 1;
notInGame:
	return 0;
}

// Same test as isPlayerInGame but accepting states 1 through 3, so a player who
// is on the way out still counts. Together the two bound the state values:
// 0 is an empty slot, 1 is in the game, 2 and 3 are leaving.
int BFMEConnectionManager::isPlayerSlotActive(int slot)
{
	if ((unsigned int)slot >= 8 ||
		m_playerState[slot] < 1 || m_playerState[slot] > 3)
		goto inactive;
	if (slot == m_localSlot)
		goto active;
	Connection *connection = m_connections[slot];
	if (connection == 0 || connection->m_openState != -1)
		goto inactive;
active:
	return 1;
inactive:
	return 0;
}

// Moves a slot from empty to in-game: reads the message's player id (retail
// re-reads it through the accessor all three times rather than keeping it in a
// register) and, if the state at this+0x12080 is still 0, sets it to 1.
void BFMEConnectionManager::processRequestPlayerLeaveCommand(void *msg)
{
	BFMENetRequestPlayerLeaveCommandMsg *command =
		(BFMENetRequestPlayerLeaveCommandMsg *)msg;
	if ((unsigned int)command->getRequestedPlayerID() < 8 &&
		m_playerState[command->getRequestedPlayerID()] == 0)
		m_playerState[command->getRequestedPlayerID()] = 1;
}

void BFMEConnectionManager::relayCommand(void *ref)
{
	NetCommandRef *commandRef = (NetCommandRef *)ref;
	NetCommandMsg *msg = commandRef->msg;
	if (msg == 0)
		return;

	if (msg->getExecutionFrame() == (unsigned int)-1)
		msg->setExecutionFrame(TheGameLogic->frame);
	if (msg->getExecutionFrame() + TheWritableGlobalData->networkRunAheadSlack < TheGameLogic->frame)
		return;

	unsigned int relay = commandRef->relay;
	if ((relay & (1 << m_localSlot)) == 0)
		return;

	if (m_frameData[msg->getPlayerID()] == 0 ||
		!IsCommandSynchronized(msg->getNetCommandType()))
		return;

	if (msg->getPlayerID() == (unsigned int)m_localSlot &&
		msg->getNetCommandType() != NETCOMMANDTYPE_PLAYERLEAVE)
		msg->prepareForRelay();

	if (m_frameData[msg->getPlayerID()]->addNetCommandMsg(msg) == 0)
		return;

	for (int i = 0; i < 8; ++i)
	{
		if ((relay & (1 << i)) != 0 && m_connections[i] != 0)
			m_connections[i]->sendNetCommandMsg(msg, (unsigned char)(1 << i));
	}
}

// The frame-data resender, and the far end of the REQUESTFRAMEDATA round trip.
// Distinct from retail's own two-argument ConnectionManager::sendFrameDataToPlayer
// (0x00664D20), which only raises a per-player watermark:
// the matched processRequestFrameDataCommand (0x006659B0) reaches it through the
// ILT thunk at 0x0000D8CD after clamping the requested window. It walks the
// eight FrameDataManagers at this+0x120E4 over the requested frame range,
// re-sends each stored command to the requesting slot alone, and issues a
// FRAMEINFO carrying getFrameCommandCount so the receiver knows how many to
// expect.
void BFMEConnectionManager::resendFrameRangeToPlayer(int playerID, unsigned int startFrame, unsigned int endFrame)
{
	unsigned int lastFrame = frameMinimum(endFrame, TheGameLogic->getFrame() - 1);
	if (startFrame + FRAMES_TO_KEEP < lastFrame)
		startFrame = lastFrame > (unsigned int)FRAMES_TO_KEEP ? lastFrame - FRAMES_TO_KEEP : 0;
	for (unsigned int frame = startFrame; frame <= lastFrame; ++frame)
	{
		unsigned char relay = (unsigned char)1 << playerID;
		FrameDataManager **manager = m_frameData;
		int slotsRemaining = 8;
		do
		{
			if (*manager != 0)
			{
				NetCommandList *list = (*manager)->getFrameCommandList(frame);
				if (list != 0)
				{
					for (NetCommandRef *ref = list->getFirstMessage(); ref != 0; ref = ref->getNext())
						reinterpret_cast<ConnectionManager *>(this)->sendLocalCommandDirect(ref->getCommand(), relay);
				}
			}
			++manager;
		} while (--slotsRemaining != 0);
		NetFrameCommandMsg *msg = new NetFrameCommandMsg;
		msg->setFrame(frame);
		if (DoesCommandRequireACommandID(msg->getNetCommandType()))
			msg->setID(GenerateNextCommandID());
		msg->setPlayerID(m_localSlot);
		msg->setCommandCount(m_frameData[m_localSlot]->getFrameCommandCount(frame));
		reinterpret_cast<ConnectionManager *>(this)->sendLocalCommandDirect(msg, relay);
		msg->detach();
	}
}

// The per-tick network update, and what drives the delay cadence: it is the
// only caller of sendFrameInfo, so the frame ceiling is published from here.
// It also runs the relay pass (0x0066A740) and the disconnect/timeout sweep
// (0x0066C8D0), builds keep-alive and progress commands, and touches the tail
// scalars at this+0x12050, +0x12054, +0x120E0, +0x12114 and +0x12115. Nothing
// in .text calls it directly and it is in no recovered vtable, so retail must
// reach it through a stored function pointer.
__declspec(naked) void BFMEConnectionManager::update()
{
	__asm {
		push 0FFFFFFFFh
		push 104473Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 44h
		push ebx
		push ebp
		mov ebp, ecx
		mov eax, dword ptr [ebp+12050h]
		xor ebx, ebx
		cmp eax, ebx
		push esi
		push edi
		mov dword ptr [esp+10h], ebx
		jne L00_66AB6B
		cmp word ptr [ebp+12054h], bx
		je L01_66AE49
L00_66AB6B:
		mov ecx, dword ptr [ebp+12024h]
		cmp ecx, ebx
		je L02_66AB7A
		__emit 0E8h
		__emit 055h
		__emit 0E5h
		__emit 099h
		__emit 0FFh   // call 0x90CF
L02_66AB7A:
		mov al, byte ptr [esp+64h]
		test al, al
		je L03_66ABCA
		mov ecx, dword ptr [ebp+120E0h]
		cmp ecx, ebx
		je L04_66AB92
		push ebp
		__emit 0E8h
		__emit 0EEh
		__emit 0E4h
		__emit 09Dh
		__emit 0FFh   // call 0x49080
L04_66AB92:
		mov ecx, ebp
		__emit 0E8h
		__emit 0E5h
		__emit 0FAh
		__emit 09Dh
		__emit 0FFh   // call 0x4A67E
		cmp dword ptr [esp+68h], ebx
		je L03_66ABCA
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		cmp ecx, ebx
		je L05_66ABC3
		mov eax, dword ptr [ecx]
		call dword ptr [eax+0DCh]
		test al, al
		je L05_66ABC3
		mov ecx, dword ptr [ebp+12028h]
		cmp ecx, dword ptr [ebp+1202Ch]
		je L03_66ABCA
L05_66ABC3:
		mov ecx, ebp
		__emit 0E8h
		__emit 043h
		__emit 04Bh
		__emit 09Bh
		__emit 0FFh   // call 0x1F70D
L03_66ABCA:
		__emit 0A1h
		__emit 098h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f7198]
		cmp eax, ebx
		je L06_66AD90
		__emit 039h
		__emit 01Dh
		__emit 0B4h
		__emit 071h
		__emit 02Fh
		__emit 001h   // cmp dword ptr [0x12f71b4], ebx
		je L06_66AD90
		mov cl, byte ptr [ebp+12115h]
		test cl, cl
		je L06_66AD90
		mov cl, byte ptr [eax+43Ch]
		test cl, cl
		je L07_66AD89
		mov edx, dword ptr [eax+464h]
		push edx
		mov edi, 111A2C0h
		__emit 0E8h
		__emit 090h
		__emit 08Dh
		__emit 036h
		__emit 000h   // call 0x9D39A0
		add esp, 4h
		mov esi, eax
		mov ecx, 9h
		xor eax, eax
		repe cmpsb
		je L06_66AD90
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7198]
		mov edx, dword ptr [ecx+464h]
		push edx
		__emit 0E8h
		__emit 06Ah
		__emit 08Dh
		__emit 036h
		__emit 000h   // call 0x9D39A0
		push eax
		__emit 0E8h
		__emit 074h
		__emit 097h
		__emit 01Eh
		__emit 000h   // call 0x8543B0
		push 20h
		mov ebx, eax
		__emit 0E8h
		__emit 0EBh
		__emit 072h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 0Ch
		mov dword ptr [esp+64h], eax
		xor esi, esi
		cmp eax, esi
		mov dword ptr [esp+5Ch], esi
		je L08_66AC5F
		mov ecx, eax
		__emit 0E8h
		__emit 00Dh
		__emit 0E3h
		__emit 09Bh
		__emit 0FFh   // call 0x28F6A
		mov esi, eax
L08_66AC5F:
		mov ecx, dword ptr [ebp+12028h]
		or eax, 0FFFFFFFFh
		mov dword ptr [esp+5Ch], eax
		mov dword ptr [esi+8h], eax
		mov eax, dword ptr [esi+14h]
		push eax
		mov dword ptr [esi+0Ch], ecx
		__emit 0E8h
		__emit 0F7h
		__emit 0AEh
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L09_66AC8B
		__emit 0E8h
		__emit 0D1h
		__emit 058h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L09_66AC8B:
		push ecx
		mov ecx, esp
		mov dword ptr [esp+68h], esp
		push ebx
		__emit 0E8h
		__emit 0AAh
		__emit 07Fh
		__emit 09Ah
		__emit 0FFh   // call 0x12C42
		mov ecx, esi
		__emit 0E8h
		__emit 0C6h
		__emit 0FDh
		__emit 099h
		__emit 0FFh   // call 0xAA65
		mov ecx, dword ptr [ebp+12028h]
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, ebp
		not dl
		push edx
		push esi
		__emit 0E8h
		__emit 021h
		__emit 065h
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		mov ecx, esi
		__emit 0E8h
		__emit 0E7h
		__emit 053h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		__emit 08Bh
		__emit 00Dh
		__emit 0B4h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f71b4]
		mov eax, dword ptr [ecx]
		call dword ptr [eax+30h]
		push eax
		__emit 0E8h
		__emit 0E2h
		__emit 096h
		__emit 01Eh
		__emit 000h   // call 0x8543B0
		lea ecx,  [esp+18h]
		push ecx
		mov edi, eax
		push edi
		push ebx
		__emit 0E8h
		__emit 0D4h
		__emit 07Dh
		__emit 036h
		__emit 000h   // call 0x9D2AB0
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7198]
		mov edx, dword ptr [ecx]
		add esp, 10h
		call dword ptr [edx+14h]
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7198]
		push eax
		__emit 0E8h
		__emit 0E0h
		__emit 0B4h
		__emit 099h
		__emit 0FFh   // call 0x61D6
		mov esi, eax
		test esi, esi
		je L10_66AD22
		lea eax,  [esp+68h]
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 0D0h
		__emit 0C0h
		__emit 09Ah
		__emit 0FFh   // call 0x16DD8
		mov eax, dword ptr [eax]
		test eax, eax
		mov ecx, 1h
		je L11_66AD1B
		movzx eax, word ptr [eax+4h]
		test eax, eax
		jne L12_66AD26
L11_66AD1B:
		mov byte ptr [esp+64h], 1h
		jmp L13_66AD2B
L10_66AD22:
		mov cl, byte ptr [esp+10h]
L12_66AD26:
		mov byte ptr [esp+64h], 0h
L13_66AD2B:
		test cl, 1h
		je L14_66AD39
		lea ecx,  [esp+68h]
		__emit 0E8h
		__emit 007h
		__emit 0CCh
		__emit 021h
		__emit 000h   // call 0x887940
L14_66AD39:
		mov al, byte ptr [esp+64h]
		test al, al
		je L15_66AD78
		push ecx
		lea edx,  [esp+18h]
		mov dword ptr [esp+68h], esp
		mov ecx, esp
		push edx
		__emit 0E8h
		__emit 06Eh
		__emit 0DEh
		__emit 021h
		__emit 000h   // call 0x888BC0
		mov ecx, esi
		__emit 0E8h
		__emit 0F9h
		__emit 0DBh
		__emit 09Bh
		__emit 0FFh   // call 0x28952
		__emit 08Bh
		__emit 00Dh
		__emit 0B4h
		__emit 071h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f71b4]
		mov eax, dword ptr [ecx]
		call dword ptr [eax+2Ch]
		push ecx
		mov ecx, esp
		mov dword ptr [esp+68h], esp
		push eax
		__emit 0E8h
		__emit 0D1h
		__emit 07Eh
		__emit 09Ah
		__emit 0FFh   // call 0x12C42
		mov ecx, esi
		__emit 0E8h
		__emit 0B9h
		__emit 0BFh
		__emit 09Ch
		__emit 0FFh   // call 0x36D31
L15_66AD78:
		__emit 08Bh
		__emit 035h
		__emit 0D4h
		__emit 093h
		__emit 035h
		__emit 001h   // mov esi, dword ptr [0x13593d4]
		push ebx
		call esi
		push edi
		call esi
		add esp, 8h
		xor ebx, ebx
L07_66AD89:
		mov byte ptr [ebp+12115h], 0h
L06_66AD90:
		mov ecx, ebp
		__emit 0E8h
		__emit 022h
		__emit 0A3h
		__emit 09Ah
		__emit 0FFh   // call 0x150B9
		lea esi,  [ebp+4h]
		mov dword ptr [esp+64h], 8h
L20_66ADA2:
		mov ecx, dword ptr [esi]
		cmp ecx, ebx
		je L16_66ADE6
		xor edx, edx
		mov dl, byte ptr [ebp+12114h]
		push edx
		__emit 0E8h
		__emit 07Dh
		__emit 088h
		__emit 09Ah
		__emit 0FFh   // call 0x13633
		mov ecx, dword ptr [esi]
		__emit 08Bh
		__emit 015h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov edx, dword ptr [0x12f0898]
		mov eax, dword ptr [ecx]
		cmp eax, dword ptr [edx+3Ch]
		ja L16_66ADE6
		__emit 0E8h
		__emit 0EEh
		__emit 02Fh
		__emit 09Bh
		__emit 0FFh   // call 0x1DDB8
		test al, al
		je L16_66ADE6
		mov edi, dword ptr [esi]
		cmp edi, ebx
		je L17_66ADE4
		mov ecx, edi
		__emit 0E8h
		__emit 0F4h
		__emit 020h
		__emit 09Dh
		__emit 0FFh   // call 0x3CECF
		push edi
		__emit 0E8h
		__emit 0CFh
		__emit 070h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
L17_66ADE4:
		mov dword ptr [esi], ebx
L16_66ADE6:
		mov ecx, dword ptr [esi+120E0h]
		cmp ecx, ebx
		je L18_66AE26
		__emit 0E8h
		__emit 0E7h
		__emit 088h
		__emit 09Bh
		__emit 0FFh   // call 0x236DC
		test al, al
		je L18_66AE26
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov ecx, dword ptr [esi+120E0h]
		mov edi, dword ptr [eax+3Ch]
		__emit 0E8h
		__emit 0ADh
		__emit 009h
		__emit 09Dh
		__emit 0FFh   // call 0x3B7B9
		cmp eax, edi
		jne L18_66AE26
		mov ecx, dword ptr [esi+120E0h]
		cmp ecx, ebx
		je L19_66AE20
		mov edx, dword ptr [ecx]
		push 1h
		call dword ptr [edx]
L19_66AE20:
		mov dword ptr [esi+120E0h], ebx
L18_66AE26:
		mov eax, dword ptr [esp+64h]
		add esi, 4h
		dec eax
		mov dword ptr [esp+64h], eax
		jne L20_66ADA2
		mov ebp, dword ptr [ebp+12024h]
		cmp ebp, ebx
		je L01_66AE49
		mov ecx, ebp
		__emit 0E8h
		__emit 0F5h
		__emit 0AEh
		__emit 09Ah
		__emit 0FFh   // call 0x15D3E
L01_66AE49:
		mov ecx, dword ptr [esp+54h]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 50h
		ret 8h
	}
}

// update() drives this on every peer. The router additionally broadcasts
// confirmed departures before draining received packets and ready wrappers.
void BFMEConnectionManager::runRelayPass()
{
	if (m_localSlot == m_packetRouterSlot)
	{
		for (int player = 0; player < 8; ++player)
		{
			if ((unsigned int)player < 8 && m_playerState[player] == 1 &&
				(player == m_localSlot || (m_connections[player] && m_connections[player]->m_openState == -1)))
			{
				NetPlayerLeaveCommandMsg *leave = new NetPlayerLeaveCommandMsg;
				leave->setLeavingPlayerID(player);
				leave->setExecutionFrame(-1);
				if (DoesCommandRequireACommandID(leave->getNetCommandType()))
					leave->setID(GenerateNextCommandID());
				leave->setPlayerID(m_localSlot);
				reinterpret_cast<ConnectionManager *>(this)->sendLocalCommand(leave, 0xFF);
				leave->detach();
				NetDestroyPlayerCommandMsg *destroy = new NetDestroyPlayerCommandMsg;
				if (DoesCommandRequireACommandID(destroy->getNetCommandType()))
					destroy->setID(GenerateNextCommandID());
				destroy->setPlayerID(m_localSlot);
				destroy->setPlayerIndex(player);
				reinterpret_cast<ConnectionManager *>(this)->sendLocalCommand(destroy, 0xFF);
				destroy->detach();
				m_playerState[player] = 2;
			}
		}
	}
	for (int packetIndex = 0; packetIndex < 128; ++packetIndex)
	{
		if (m_transport->received[packetIndex].length)
		{
			NetPacket packet(&m_transport->received[packetIndex]);
			m_transport->received[packetIndex].length = 0;
			NetCommandList *commands = packet.getCommandList();
			NetCommandRef *ref = commands->getFirstMessage();
			NetPacketAddress source = packet.getAddress();
			for (; ref; ref = ref->getNext())
			{
				if (TheNetwork && TheNetwork->isRouterLeavePending() &&
					m_localSlot == m_packetRouterSlot && ref->getCommand()->getNetCommandType() != NETCOMMANDTYPE_FRAMEINFO)
					continue;
				if (CommandRequiresAck(ref->getCommand()))
					ackCommand(ref, &source);
				if (!isDuplicateCommand(ref->getCommand()) && processIncomingCommand(ref))
					relayCommand(ref);
			}
			delete commands;
		}
	}
	if (m_wrapperList)
	{
		NetCommandList *commands = m_wrapperList->getReadyCommands();
		for (NetCommandRef *ref = commands->getFirstMessage(); ref; ref = ref->getNext())
		{
			if (TheNetwork && TheNetwork->isRouterLeavePending() &&
				m_localSlot == m_packetRouterSlot && ref->getCommand()->getNetCommandType() != NETCOMMANDTYPE_FRAMEINFO)
				continue;
			if (CommandRequiresAck(ref->getCommand()))
				ackCommand(ref, 0);
			if (processIncomingCommand(ref))
				relayCommand(ref);
		}
		delete commands;
	}
}

// The disconnect and timeout sweep, run once per tick from
// BFMEConnectionManager::update. It reaches every timing gate already matched
// in this file -- isPlayerConnected, isPlayerConnectedForTimeout,
// isPlayerSlotActive -- and maintains the blame-assignment tail of
// DisconnectManager: m_timeOfDisconnectScreenOn at +0x25C, m_pingsSent at
// +0x260, m_pingsRecieved at +0x264 and m_pingFrame at +0x268, which is the
// same tail the disconnectmanager shim pins. Ghidra sizes it 1119, three bytes
// short of its ret.
__declspec(naked) void BFMEDisconnectManager::update(void *conMgr)
{
	__asm {
		push 0FFFFFFFFh
		push 1044848h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 34h
		push ebx
		push ebp
		push esi
		push edi
		mov esi, ecx
		__emit 0E8h
		__emit 009h
		__emit 06Eh
		__emit 099h
		__emit 0FFh   // call 0x36FC
		mov ebx, dword ptr [esp+54h]
		xor edi, edi
		mov ecx, ebx
		mov dword ptr [esp+14h], edi
		mov byte ptr [esp+13h], 0h
		__emit 0E8h
		__emit 088h
		__emit 0D9h
		__emit 09Dh
		__emit 0FFh   // call 0x4A291
		mov ebp, eax
		mov dword ptr [esp+54h], ebp
		nop
L08_66C910:
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 09Ah
		__emit 0BDh
		__emit 09Dh
		__emit 0FFh   // call 0x486B2
		test al, al
		jne L00_66C93E
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 026h
		__emit 088h
		__emit 09Ah
		__emit 0FFh   // call 0x1514A
		test al, al
		je L00_66C93E
		push 1388h
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 026h
		__emit 08Eh
		__emit 09Ch
		__emit 0FFh   // call 0x3575B
		test al, al
		jne L00_66C93E
		mov byte ptr [esp+13h], 1h
L00_66C93E:
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 0F0h
		__emit 027h
		__emit 09Bh
		__emit 0FFh   // call 0x1F136
		test al, al
		jne L01_66C9AC
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 060h
		__emit 0BDh
		__emit 09Dh
		__emit 0FFh   // call 0x486B2
		test al, al
		jne L01_66C9AC
		push edi
		mov ecx, ebx
		__emit 0E8h
		__emit 0ECh
		__emit 087h
		__emit 09Ah
		__emit 0FFh   // call 0x1514A
		test al, al
		je L01_66C9AC
		inc dword ptr [esp+14h]
		mov eax, dword ptr [esi+260h]
		test eax, eax
		mov ecx, edi
		mov dword ptr [esp+18h], eax
		jle L02_66C98F
		fild dword ptr [esi+264h]
		fidiv dword ptr [esp+18h]
		__emit 0D8h
		__emit 01Dh
		__emit 070h
		__emit 05Ch
		__emit 007h
		__emit 001h   // fcomp dword ptr [0x1075c70]
		fnstsw ax
		test ah, 5h
		jp L02_66C98F
		mov ecx, ebp
L02_66C98F:
		mov al, byte ptr [ecx+esi+282h]
		test al, al
		jne L03_66C9ED
		mov byte ptr [ecx+esi+282h], 1h
		inc word ptr [esi+ecx*2+272h]
		jmp L03_66C9ED
L01_66C9AC:
		cmp edi, ebp
		je L04_66C9B8
		mov byte ptr [edi+esi+282h], 0h
L04_66C9B8:
		mov ecx, ebx
		__emit 0E8h
		__emit 0D2h
		__emit 0D8h
		__emit 09Dh
		__emit 0FFh   // call 0x4A291
		cmp edi, eax
		jge L05_66C9CE
		mov eax, edi
		__emit 08Dh
		__emit 02Ch
		__emit 0BDh
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // lea ebp, [edi*4]
		jmp L06_66C9DA
L05_66C9CE:
		je L03_66C9ED
		lea eax,  [edi-1h]
		lea ebp,  [edi*4-4h]
L06_66C9DA:
		cmp eax, 0FFFFFFFFh
		je L07_66C9E9
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // call dword ptr [0x1359544]
		mov dword ptr [esi+ebp+14h], eax
L07_66C9E9:
		mov ebp, dword ptr [esp+54h]
L03_66C9ED:
		inc edi
		cmp edi, 8h
		jl L08_66C910
		mov eax, dword ptr [esp+14h]
		test eax, eax
		jne L09_66CA78
		mov byte ptr [esi+ebp+282h], al
L15_66CA06:
		mov eax, dword ptr [esi+0Ch]
		test eax, eax
		mov byte ptr [esi+270h], 0h
		jne L10_66CA4B
		mov ecx, ebx
		__emit 0E8h
		__emit 076h
		__emit 0D8h
		__emit 09Dh
		__emit 0FFh   // call 0x4A291
		mov edi, eax
		cmp dword ptr [esi+0Ch], 1h
		je L10_66CA4B
		__emit 0E8h
		__emit 043h
		__emit 083h
		__emit 09Bh
		__emit 0FFh   // call 0x24D6B
		mov dword ptr [esi+0Ch], 1h
		lea eax,  [esi+edi*8+30h]
		mov ecx, 8h
L11_66CA38:
		mov byte ptr [eax], 0h
		add eax, 40h
		dec ecx
		jne L11_66CA38
		mov dword ptr [esi+25Ch], 0h
L10_66CA4B:
		cmp dword ptr [esi+8h], 0FFFFFFFFh
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		je L12_66CA62
		mov ecx, dword ptr [eax+3Ch]
		cmp dword ptr [esi+4h], ecx
		je L13_66CB1D
L12_66CA62:
		mov eax, dword ptr [eax+3Ch]
		__emit 08Bh
		__emit 02Dh
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // mov ebp, dword ptr [0x1359544]
		mov dword ptr [esi+4h], eax
		call ebp
		mov dword ptr [esi+8h], eax
		jmp L14_66CB23
L09_66CA78:
		jle L15_66CA06
		mov byte ptr [esi+270h], 1h
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		test eax, eax
		je L16_66CA94
		mov ecx, dword ptr [eax+118h]
		test ecx, ecx
		jne L17_66CB10
L16_66CA94:
		cmp dword ptr [esi+0Ch], 1h
		jne L17_66CB10
		cmp word ptr [esi+ebp*2+272h], 5h
		jb L18_66CAAF
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		test ecx, ecx
		jne L19_66CB0B
L18_66CAAF:
		mov ecx, ebx
		__emit 0E8h
		__emit 0A7h
		__emit 06Ah
		__emit 099h
		__emit 0FFh   // call 0x355D
		cmp eax, 2h
		jl L20_66CB01
		__emit 08Bh
		__emit 00Dh
		__emit 09Ch
		__emit 007h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f079c]
		test ecx, ecx
		je L21_66CAEC
		mov edx, dword ptr [ecx]
		call dword ptr [edx+38h]
		test al, al
		jne L20_66CB01
		__emit 08Bh
		__emit 00Dh
		__emit 09Ch
		__emit 007h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f079c]
		mov eax, dword ptr [ecx]
		call dword ptr [eax+34h]
		test al, al
		jne L20_66CB01
		__emit 08Bh
		__emit 00Dh
		__emit 09Ch
		__emit 007h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f079c]
		mov edx, dword ptr [ecx]
		call dword ptr [edx+40h]
		test al, al
		jne L20_66CB01
L21_66CAEC:
		push ebx
		mov ecx, esi
		__emit 0E8h
		__emit 00Ch
		__emit 07Eh
		__emit 09Ch
		__emit 0FFh   // call 0x34900
		push ebx
		mov ecx, esi
		__emit 0E8h
		__emit 01Ch
		__emit 0CDh
		__emit 099h
		__emit 0FFh   // call 0x9818
		jmp L10_66CA4B
L20_66CB01:
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7714]
		test ecx, ecx
		je L17_66CB10
L19_66CB0B:
		mov eax, dword ptr [ecx]
		call dword ptr [eax+78h]
L17_66CB10:
		push ebx
		mov ecx, esi
		__emit 0E8h
		__emit 000h
		__emit 0CDh
		__emit 099h
		__emit 0FFh   // call 0x9818
		jmp L10_66CA4B
L13_66CB1D:
		__emit 08Bh
		__emit 02Dh
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // mov ebp, dword ptr [0x1359544]
L14_66CB23:
		cmp dword ptr [esi+0Ch], 1h
		je L22_66CB31
		push ebx
		mov ecx, esi
		__emit 0E8h
		__emit 0E4h
		__emit 0AAh
		__emit 09Bh
		__emit 0FFh   // call 0x27615
L22_66CB31:
		mov al, byte ptr [esp+13h]
		test al, al
		mov ebx, 7D0h
		je L23_66CC5E
		__emit 0A1h
		__emit 0F4h
		__emit 076h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f76f4]
		test eax, eax
		je L24_66CD1D
		call ebp
		sub eax, dword ptr [esi+268h]
		cmp eax, 0BB8h
		jbe L25_66CC72
		mov eax, dword ptr [esp+14h]
		test eax, eax
		je L26_66CB7D
		call ebp
		sub eax, dword ptr [esi+25Ch]
		cmp eax, 1388h
		jae L25_66CC72
L26_66CB7D:
		lea ecx,  [esp+1Ch]
		__emit 0E8h
		__emit 004h
		__emit 039h
		__emit 09Dh
		__emit 0FFh   // call 0x4048A
		__emit 08Bh
		__emit 00Dh
		__emit 0E4h
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f70e4]
		mov edx, dword ptr [ecx]
		lea eax,  [esp+54h]
		push eax
		mov dword ptr [esp+50h], 0h
		call dword ptr [edx+4h]
		mov ecx, dword ptr [eax]
		mov eax, dword ptr [ecx]
		mov eax, dword ptr [eax+8h]
		test eax, eax
		mov byte ptr [esp+4Ch], 1h
		lea ecx,  [eax+8h]
		jne L27_66CBB6
		mov ecx, 107388Bh
L27_66CBB6:
		mov eax, ecx
		lea edi,  [eax+1h]
		jmp L28_66CBC0
		__emit 08Dh
		__emit 049h
		__emit 000h   // lea ecx, [ecx]
L28_66CBC0:
		mov dl, byte ptr [eax]
		inc eax
		test dl, dl
		jne L28_66CBC0
		sub eax, edi
		add eax, ecx
		push eax
		push ecx
		lea ecx,  [esp+24h]
		__emit 0E8h
		__emit 0C1h
		__emit 0E6h
		__emit 09Bh
		__emit 0FFh   // call 0x2B297
		lea ecx,  [esp+54h]
		mov byte ptr [esp+4Ch], 0h
		__emit 0E8h
		__emit 027h
		__emit 0C4h
		__emit 09Ah
		__emit 0FFh   // call 0x1900B
		mov eax, dword ptr [esp+54h]
		test eax, eax
		je L29_66CBF7
		push 0Ch
		push eax
		__emit 0E8h
		__emit 0FCh
		__emit 019h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
L29_66CBF7:
		mov ecx, dword ptr [esi+260h]
		mov eax, 5h
		add ecx, eax
		mov dword ptr [esp+28h], eax
		mov dword ptr [esi+260h], ecx
		__emit 08Bh
		__emit 00Dh
		__emit 0F4h
		__emit 076h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f76f4]
		lea eax,  [esp+1Ch]
		mov dword ptr [esp+2Ch], ebx
		mov edx, dword ptr [ecx]
		push eax
		call dword ptr [edx+10h]
		call ebp
		mov ecx, dword ptr [esp+1Ch]
		mov dword ptr [esi+268h], eax
		mov eax, dword ptr [esp+24h]
		sub eax, ecx
		test ecx, ecx
		mov dword ptr [esp+4Ch], 0FFFFFFFFh
		je L25_66CC72
		cmp eax, 80h
		jbe L30_66CC52
		push ecx
		__emit 0E8h
		__emit 063h
		__emit 052h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
		jmp L25_66CC72
L30_66CC52:
		push eax
		push ecx
		__emit 0E8h
		__emit 097h
		__emit 019h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
		jmp L25_66CC72
L23_66CC5E:
		xor eax, eax
		mov dword ptr [esi+260h], eax
		mov dword ptr [esi+264h], eax
		mov dword ptr [esi+268h], eax
L25_66CC72:
		__emit 0A1h
		__emit 0F4h
		__emit 076h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f76f4]
		test eax, eax
		je L24_66CD1D
		lea ecx,  [esp+30h]
		__emit 0E8h
		__emit 002h
		__emit 038h
		__emit 09Dh
		__emit 0FFh   // call 0x4048A
		__emit 08Bh
		__emit 00Dh
		__emit 0F4h
		__emit 076h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f76f4]
		mov edx, dword ptr [ecx]
		lea eax,  [esp+30h]
		push eax
		mov dword ptr [esp+50h], 2h
		call dword ptr [edx+1Ch]
		test al, al
		je L31_66CCD8
L33_66CCA4:
		mov al, byte ptr [esp+13h]
		test al, al
		je L32_66CCC4
		cmp dword ptr [esp+3Ch], ebx
		jge L32_66CCC4
		mov eax, dword ptr [esi+264h]
		mov ecx, dword ptr [esp+40h]
		add eax, ecx
		mov dword ptr [esi+264h], eax
L32_66CCC4:
		__emit 08Bh
		__emit 00Dh
		__emit 0F4h
		__emit 076h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f76f4]
		mov edx, dword ptr [ecx]
		lea eax,  [esp+30h]
		push eax
		call dword ptr [edx+1Ch]
		test al, al
		jne L33_66CCA4
L31_66CCD8:
		mov ecx, dword ptr [esp+30h]
		mov eax, dword ptr [esp+38h]
		sub eax, ecx
		test ecx, ecx
		mov dword ptr [esp+4Ch], 0FFFFFFFFh
		je L24_66CD1D
		cmp eax, 80h
		jbe L34_66CD13
		push ecx
		__emit 0E8h
		__emit 0B5h
		__emit 051h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
		pop edi
		pop esi
		pop ebp
		pop ebx
		mov ecx, dword ptr [esp+34h]
		mov dword ptr fs:[0h], ecx
		add esp, 40h
		ret 4h
L34_66CD13:
		push eax
		push ecx
		__emit 0E8h
		__emit 0D6h
		__emit 018h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
L24_66CD1D:
		mov ecx, dword ptr [esp+44h]
		pop edi
		pop esi
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 40h
		ret 4h
	}
}

// The destructor body. 0x00681E10 is its scalar deleting wrapper -- call this,
// then operator delete when the low bit of the flag argument is set -- and the
// native Network teardown at 0x00681E40 and 0x006823B0 call it too. It releases
// the tail objects at this+0x12104, +0x12108, +0x1210C, +0x12118, +0x1211C,
// +0x12124, +0x12128 and +0x12130 and hands their STL nodes back to the pool.
// Ghidra sizes it 558, three bytes short of its ret.
__declspec(naked) void BFMEConnectionManager::destroy()
{
	__asm {
		push 0FFFFFFFFh
		push 104453Dh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 0Ch
		push ebx
		push ebp
		mov ebp, ecx
		push esi
		push edi
		mov dword ptr [esp+14h], ebp
		mov dword ptr [ebp], 111A2B0h
		mov esi, dword ptr [ebp+12024h]
		test esi, esi
		mov dword ptr [esp+24h], 3h
		je L00_668DDB
		mov ecx, esi
		__emit 0E8h
		__emit 0B9h
		__emit 016h
		__emit 09Dh
		__emit 0FFh   // call 0x3A48B
		push esi
		__emit 0E8h
		__emit 0D8h
		__emit 090h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
L00_668DDB:
		lea edi,  [ebp+4h]
		mov dword ptr [esp+10h], 8h
		mov ebx, 4h
		jmp L01_668DF0
		__emit 08Dh
		__emit 049h
		__emit 000h   // lea ecx, [ecx]
L01_668DF0:
		mov ecx, dword ptr [edi+120E0h]
		test ecx, ecx
		je L02_668E00
		mov eax, dword ptr [ecx]
		push 1h
		call dword ptr [eax]
L02_668E00:
		mov esi, dword ptr [edi]
		test esi, esi
		je L03_668E31
		mov dword ptr [esp+18h], esi
		mov ecx, dword ptr [esi+18h]
		test ecx, ecx
		mov byte ptr [esp+24h], bl
		je L04_668E1B
		mov edx, dword ptr [ecx]
		push 1h
		call dword ptr [edx]
L04_668E1B:
		lea ecx,  [esi+14h]
		mov byte ptr [esp+24h], 3h
		__emit 0E8h
		__emit 0A8h
		__emit 0F3h
		__emit 021h
		__emit 000h   // call 0x8881D0
		push esi
		__emit 0E8h
		__emit 082h
		__emit 090h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
L03_668E31:
		mov eax, dword ptr [esp+10h]
		add edi, ebx
		dec eax
		mov dword ptr [esp+10h], eax
		jne L01_668DF0
		__emit 0E8h
		__emit 028h
		__emit 0BFh
		__emit 09Bh
		__emit 0FFh   // call 0x24D6B
		mov ecx, dword ptr [ebp+120E0h]
		xor edi, edi
		cmp ecx, edi
		je L05_668E55
		mov eax, dword ptr [ecx]
		push 1h
		call dword ptr [eax]
L05_668E55:
		mov ecx, dword ptr [ebp+12104h]
		cmp ecx, edi
		je L06_668E65
		mov edx, dword ptr [ecx]
		push 1h
		call dword ptr [edx]
L06_668E65:
		mov ecx, dword ptr [ebp+12108h]
		cmp ecx, edi
		je L07_668E75
		mov eax, dword ptr [ecx]
		push 1h
		call dword ptr [eax]
L07_668E75:
		mov ecx, dword ptr [ebp+1210Ch]
		cmp ecx, edi
		je L08_668E85
		mov edx, dword ptr [ecx]
		push 1h
		call dword ptr [edx]
L08_668E85:
		mov eax, dword ptr [ebp+1211Ch]
		cmp eax, edi
		lea esi,  [ebp+12118h]
		je L09_668EB4
		mov eax, dword ptr [esi]
		mov ecx, dword ptr [eax+4h]
		push ecx
		mov ecx, esi
		__emit 0E8h
		__emit 049h
		__emit 09Ah
		__emit 09Ah
		__emit 0FFh   // call 0x128EB
		mov eax, dword ptr [esi]
		mov dword ptr [eax+8h], eax
		mov edx, dword ptr [esi]
		mov dword ptr [edx+4h], edi
		mov eax, dword ptr [esi]
		mov dword ptr [eax+0Ch], eax
		mov dword ptr [esi+4h], edi
L09_668EB4:
		mov eax, dword ptr [ebp+12128h]
		lea ebx,  [ebp+12124h]
		xor ecx, ecx
		cmp eax, ecx
		je L10_668F03
		mov eax, dword ptr [ebx]
		mov esi, dword ptr [eax+4h]
		cmp esi, ecx
		je L11_668EF1
		nop
L12_668ED0:
		mov ecx, dword ptr [esi+0Ch]
		push ecx
		mov ecx, ebx
		__emit 0E8h
		__emit 044h
		__emit 0FCh
		__emit 09Ah
		__emit 0FFh   // call 0x18B1F
		mov edi, dword ptr [esi+8h]
		push 14h
		push esi
		__emit 0E8h
		__emit 00Ah
		__emit 057h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
		test edi, edi
		mov esi, edi
		jne L12_668ED0
		xor ecx, ecx
L11_668EF1:
		mov eax, dword ptr [ebx]
		mov dword ptr [eax+8h], eax
		mov edx, dword ptr [ebx]
		mov dword ptr [edx+4h], ecx
		mov eax, dword ptr [ebx]
		mov dword ptr [eax+0Ch], eax
		mov dword ptr [ebx+4h], ecx
L10_668F03:
		lea edi,  [ebp+12130h]
		mov dword ptr [esp+10h], 8h
L16_668F11:
		cmp dword ptr [edi+4h], ecx
		je L13_668F57
		mov eax, dword ptr [edi]
		mov esi, dword ptr [eax+4h]
		cmp esi, ecx
		je L14_668F45
		nop
L15_668F20:
		mov ecx, dword ptr [esi+0Ch]
		push ecx
		mov ecx, edi
		__emit 0E8h
		__emit 02Fh
		__emit 0F6h
		__emit 09Ch
		__emit 0FFh   // call 0x3855A
		mov ebp, dword ptr [esi+8h]
		push 18h
		push esi
		__emit 0E8h
		__emit 0BAh
		__emit 056h
		__emit 01Ch
		__emit 000h   // call 0x82E5F0
		add esp, 8h
		test ebp, ebp
		mov esi, ebp
		jne L15_668F20
		mov ebp, dword ptr [esp+14h]
		xor ecx, ecx
L14_668F45:
		mov eax, dword ptr [edi]
		mov dword ptr [eax+8h], eax
		mov edx, dword ptr [edi]
		mov dword ptr [edx+4h], ecx
		mov eax, dword ptr [edi]
		mov dword ptr [eax+0Ch], eax
		mov dword ptr [edi+4h], ecx
L13_668F57:
		mov eax, dword ptr [esp+10h]
		add edi, 0Ch
		dec eax
		mov dword ptr [esp+10h], eax
		jne L16_668F11
		push 43C961h
		push 8h
		push 0Ch
		lea eax,  [ebp+12130h]
		push eax
		mov byte ptr [esp+34h], 2h
		__emit 0E8h
		__emit 0F7h
		__emit 0DDh
		__emit 038h
		__emit 000h   // call 0x9F6D76
		mov ecx, ebx
		mov byte ptr [esp+24h], 1h
		__emit 0E8h
		__emit 08Ch
		__emit 0C7h
		__emit 09Ah
		__emit 0FFh   // call 0x15717
		lea ecx,  [ebp+12118h]
		mov byte ptr [esp+24h], 0h
		__emit 0E8h
		__emit 0F5h
		__emit 090h
		__emit 099h
		__emit 0FFh   // call 0x2090
		lea ecx,  [ebp+12058h]
		mov dword ptr [esp+24h], 0FFFFFFFFh
		__emit 0E8h
		__emit 022h
		__emit 0F2h
		__emit 021h
		__emit 000h   // call 0x8881D0
		mov ecx, dword ptr [esp+1Ch]
		pop edi
		pop esi
		pop ebp
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 18h
		ret
	}
}

// Reassembles a chunked command through the wrapper list at +0x1210C.
// Announced files also publish increased completion percentages below 100;
// the file maps at +0x12118/+0x12130 associate wrapped IDs with transfers.
void BFMEConnectionManager::processWrappedCommand(NetCommandRef *ref)
{
	unsigned short commandID = static_cast<NetWrapperCommandMsg *>(ref->getCommand())->getWrappedCommandID();
	int originalProgress = 0;
	FileCommandMap::iterator file = m_fileCommandMap.find(commandID);
	if (file != m_fileCommandMap.end())
		originalProgress = m_fileProgressMap[m_localSlot][commandID];
	if (m_wrapperList)
	{
		m_wrapperList->processWrapper(ref);
		if (file != m_fileCommandMap.end())
		{
			int progress = m_wrapperList->getPercentComplete(commandID);
			if (progress > originalProgress && progress < 100)
			{
				m_fileProgressMap[m_localSlot][commandID] = progress;
				int relay = 0xFF ^ (1 << m_localSlot);
				NetFileProgressCommandMsg *msg = new NetFileProgressCommandMsg;
				msg->setPlayerID(m_localSlot);
				msg->setID(0);
				if (DoesCommandRequireACommandID(msg->getNetCommandType()))
					msg->setID(GenerateNextCommandID());
				msg->setFileID(commandID);
				msg->setProgress(progress);
				reinterpret_cast<ConnectionManager *>(this)->sendLocalCommand(msg, relay);
				reinterpret_cast<ConnectionManager *>(this)->processFileProgress(msg);
				msg->detach();
			}
		}
	}
}

// Retires acknowledged commands. Reads the acknowledged id and originating
// player from either a stage-2 or a both-stages ack message, then searches the
// two pending-command lists at this+0x12104 and this+0x12108 with
// NetCommandList::findMessage and removes the entry.
void BFMEConnectionManager::processAckCommand(void *command)
{
	NetCommandMsg *msg = static_cast<NetCommandMsg *>(command);
	UnsignedShort commandID;
	unsigned char originalPlayerID;
	unsigned int originalExecutionFrame;
	if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE2)
	{
		NetAckStage2CommandMsg *ack = static_cast<NetAckStage2CommandMsg *>(msg);
		commandID = ack->getCommandID();
		originalPlayerID = ack->getOriginalPlayerID();
		originalExecutionFrame = ack->getOriginalExecutionFrame();
	}
	else if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKBOTH)
	{
		NetAckBothCommandMsg *ack = static_cast<NetAckBothCommandMsg *>(msg);
		commandID = ack->getCommandID();
		originalPlayerID = ack->getOriginalPlayerID();
		originalExecutionFrame = ack->getOriginalExecutionFrame();
	}
	else
		return;

	if (m_pendingCommands != 0)
	{
		NetCommandRef *ref = m_pendingCommands->findMessage(commandID, originalPlayerID);
		if (ref != 0)
		{
			m_pendingCommands->removeMessage(ref);
			delete ref;
		}
	}
	if (m_pendingRelays != 0)
	{
		NetCommandRef *ref = m_pendingRelays->findMessage(commandID, originalPlayerID, originalExecutionFrame);
		if (ref != 0)
		{
			unsigned char relay = ref->getRelay() & ~(1 << msg->getPlayerID());
			if (relay == 0)
			{
				m_pendingRelays->removeMessage(ref);
				NetAckStage2CommandMsg *ack = new NetAckStage2CommandMsg(ref->msg);
				reinterpret_cast<ConnectionManager *>(this)->sendLocalCommand(ack, (unsigned char)1 << ack->getOriginalPlayerID());
				delete ref;
				ack->detach();
			}
			else
				ref->relay = relay;
		}
	}
}

// Starts a player's departure. Marks that player's FrameDataManager at
// this+0x120E4 with setQuitFrame, skipping managers already reporting
// getIsQuitting, and builds and sends the follow-up command directly to the
// affected peers. NetworkKeepAliveDelay from TheGlobalData +0xCB4 bounds how far
// ahead the quit frame may be placed.
__declspec(naked) void BFMEConnectionManager::beginPlayerLeave(void *msg)
{
	__asm {
		mov eax, dword ptr fs:[0h]
		push 0FFFFFFFFh
		push 104444Bh
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 0Ch
		push ebp
		push esi
		push edi
		movzx edi, byte ptr [esp+28h]
		mov ebp, ecx
		cmp edi, dword ptr [ebp+12028h]
		jne L00_66737E
		lea esi,  [ebp+4h]
		mov edi, 8h
L02_667352:
		mov ecx, dword ptr [esi]
		test ecx, ecx
		je L01_667376
		mov eax, dword ptr [ebp+12028h]
		push eax
		__emit 0E8h
		__emit 0FDh
		__emit 0B6h
		__emit 09Bh
		__emit 0FFh   // call 0x22A61
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		mov eax, dword ptr [ecx+3Ch]
		mov ecx, dword ptr [esi]
		inc eax
		push eax
		__emit 0E8h
		__emit 0E4h
		__emit 010h
		__emit 09Eh
		__emit 0FFh   // call 0x4845A
L01_667376:
		add esi, 4h
		dec edi
		jne L02_667352
		jmp L03_6673C6
L00_66737E:
		__emit 08Bh
		__emit 015h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov edx, dword ptr [0x12f0898]
		mov ecx, dword ptr [ebp+edi*4+4h]
		test ecx, ecx
		mov eax, dword ptr [edx+3Ch]
		lea esi,  [eax+1h]
		je L04_667398
		push esi
		__emit 0E8h
		__emit 0C2h
		__emit 010h
		__emit 09Eh
		__emit 0FFh   // call 0x4845A
L04_667398:
		mov ecx, dword ptr [ebp+edi*4+120E4h]
		test ecx, ecx
		je L03_6673C6
		__emit 0E8h
		__emit 034h
		__emit 0C3h
		__emit 09Bh
		__emit 0FFh   // call 0x236DC
		test al, al
		jne L03_6673C6
		__emit 0A1h
		__emit 0C8h
		__emit 0D5h
		__emit 02Eh
		__emit 001h   // mov eax, dword ptr [0x12ed5c8]
		mov ecx, dword ptr [eax+0CB4h]
		add ecx, esi
		push ecx
		mov ecx, dword ptr [ebp+edi*4+120E4h]
		__emit 0E8h
		__emit 0A1h
		__emit 039h
		__emit 09Ah
		__emit 0FFh   // call 0xAD67
L03_6673C6:
		movzx eax, byte ptr [esp+28h]
		push eax
		mov ecx, ebp
		__emit 0E8h
		__emit 08Ah
		__emit 019h
		__emit 09Ch
		__emit 0FFh   // call 0x28D5D
		cmp eax, 2h
		mov dword ptr [esp+10h], eax
		__emit 00Fh
		__emit 085h
		__emit 031h
		__emit 001h
		__emit 000h
		__emit 000h   // jne 0x667511
		push ebx
		xor bl, bl
		mov byte ptr [esp+10h], bl
		lea edi,  [ebp+8h]
		__emit 08Dh
		__emit 09Bh
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // lea ebx, [ebx]
L11_6673F0:
		mov ecx, dword ptr [ebp+12028h]
		lea edx,  [eax-2h]
		cmp edx, ecx
		je L06_667412
		mov ecx, dword ptr [edi-4h]
		test ecx, ecx
		je L06_667412
		cmp dword ptr [ecx], 0FFFFFFFFh
		jne L06_667412
		lea ecx,  [eax-2h]
		mov dl, 1h
		shl dl, cl
		or bl, dl
L06_667412:
		mov edx, dword ptr [ebp+12028h]
		lea ecx,  [eax-1h]
		cmp ecx, edx
		je L07_667433
		mov ecx, dword ptr [edi]
		test ecx, ecx
		je L07_667433
		cmp dword ptr [ecx], 0FFFFFFFFh
		jne L07_667433
		lea ecx,  [eax-1h]
		mov dl, 1h
		shl dl, cl
		or bl, dl
L07_667433:
		cmp eax, dword ptr [ebp+12028h]
		je L08_66744F
		mov ecx, dword ptr [edi+4h]
		test ecx, ecx
		je L08_66744F
		cmp dword ptr [ecx], 0FFFFFFFFh
		jne L08_66744F
		mov dl, 1h
		mov ecx, eax
		shl dl, cl
		or bl, dl
L08_66744F:
		mov ecx, dword ptr [ebp+12028h]
		lea esi,  [eax+1h]
		cmp esi, ecx
		je L09_667474
		mov edx, dword ptr [edi+8h]
		test edx, edx
		je L09_667474
		cmp esi, ecx
		je L10_66746C
		cmp dword ptr [edx], 0FFFFFFFFh
		jne L09_667474
L10_66746C:
		mov dl, 1h
		mov ecx, esi
		shl dl, cl
		or bl, dl
L09_667474:
		add eax, 4h
		lea ecx,  [eax-2h]
		add edi, 10h
		cmp ecx, 8h
		jl L11_6673F0
		mov byte ptr [esp+10h], bl
		test bl, bl
		pop ebx
		__emit 00Fh
		__emit 084h
		__emit 07Eh
		__emit 000h
		__emit 000h
		__emit 000h   // je 0x667511
		push 24h
		__emit 0E8h
		__emit 096h
		__emit 0AAh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+14h], eax
		xor esi, esi
		cmp eax, esi
		mov dword ptr [esp+20h], esi
		je L12_6674B4
		mov ecx, eax
		__emit 0E8h
		__emit 07Dh
		__emit 032h
		__emit 09Ch
		__emit 0FFh   // call 0x2A72F
		mov esi, eax
L12_6674B4:
		mov edx, dword ptr [ebp+12028h]
		or eax, 0FFFFFFFFh
		mov dword ptr [esp+20h], eax
		mov dword ptr [esi+8h], eax
		mov eax, dword ptr [esi+14h]
		push eax
		mov dword ptr [esi+0Ch], edx
		__emit 0E8h
		__emit 0A2h
		__emit 0E6h
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L13_6674E0
		__emit 0E8h
		__emit 07Ch
		__emit 090h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L13_6674E0:
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov ecx, dword ptr [eax+3Ch]
		push ecx
		mov ecx, esi
		__emit 0E8h
		__emit 0DBh
		__emit 036h
		__emit 09Ch
		__emit 0FFh   // call 0x2ABCB
		movzx eax, byte ptr [esp+28h]
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 035h
		__emit 030h
		__emit 09Bh
		__emit 0FFh   // call 0x1A532
		mov edx, dword ptr [esp+0Ch]
		push edx
		push esi
		mov ecx, ebp
		__emit 0E8h
		__emit 0CDh
		__emit 09Ch
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		mov ecx, esi
		__emit 0E8h
		__emit 093h
		__emit 08Bh
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
L05_667511:
		__emit 0E8h
		__emit 038h
		__emit 01Ah
		__emit 09Ah
		__emit 0FFh   // call 0x8F4E
		mov ecx, dword ptr [esp+18h]
		mov eax, dword ptr [esp+10h]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		add esp, 18h
		ret 4h
	}
}

// Reads a slice of a file through TheFileSystem and ships it as a
// NetFileCommandMsg -- it is the only caller of NetFileCommandMsg::setFileData
// in this band -- then hands the message to sendLocalCommand. The progress text
// it formats goes out as a UnicodeString.
__declspec(naked) void BFMEConnectionManager::sendFileChunk(const char *path, int playerMask, int chunk)
{
	__asm {
		push 0FFFFFFFFh
		push 10443B3h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 0Ch
		push ebx
		push ebp
		push esi
		push edi
		mov ebx, ecx
		mov eax, dword ptr [esp+2Ch]
		xor edi, edi
		cmp eax, edi
		mov dword ptr [esp+24h], edi
		je L00_666A41
		add eax, 8h
		jmp L01_666A46
L00_666A41:
		mov eax, 107388Bh
L01_666A46:
		__emit 08Bh
		__emit 00Dh
		__emit 048h
		__emit 0CBh
		__emit 034h
		__emit 001h   // mov ecx, dword ptr [0x134cb48]
		push edi
		push eax
		__emit 0E8h
		__emit 00Dh
		__emit 01Eh
		__emit 036h
		__emit 000h   // call 0x9C8860
		mov esi, eax
		cmp esi, edi
		je L02_666AFC
		mov eax, dword ptr [esi]
		mov ecx, esi
		call dword ptr [eax+2Ch]
		test eax, eax
		je L02_666AFC
		mov edx, dword ptr [esi]
		mov ecx, esi
		call dword ptr [edx+2Ch]
		mov ebp, eax
		mov eax, dword ptr [esi]
		mov ecx, esi
		call dword ptr [eax+34h]
		push 28h
		mov edi, eax
		__emit 0E8h
		__emit 0ABh
		__emit 0B4h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+10h], eax
		test eax, eax
		mov byte ptr [esp+24h], 3h
		je L03_666AA0
		mov ecx, eax
		__emit 0E8h
		__emit 0AFh
		__emit 0BEh
		__emit 099h
		__emit 0FFh   // call 0x294B
		mov esi, eax
		jmp L04_666AA2
L03_666AA0:
		xor esi, esi
L04_666AA2:
		mov cx, word ptr [esp+34h]
		mov eax, dword ptr [ebx+12028h]
		mov word ptr [esi+10h], cx
		lea edx,  [esp+2Ch]
		mov byte ptr [esp+24h], 0h
		mov dword ptr [esi+0Ch], eax
		push ecx
		mov dword ptr [esp+14h], esp
		mov ecx, esp
		push edx
		__emit 0E8h
		__emit 096h
		__emit 010h
		__emit 022h
		__emit 000h   // call 0x887B60
		mov ecx, esi
		__emit 0E8h
		__emit 025h
		__emit 046h
		__emit 09Eh
		__emit 0FFh   // call 0x4B0F6
		push ebp
		push edi
		mov ecx, esi
		__emit 0E8h
		__emit 0FBh
		__emit 028h
		__emit 09Bh
		__emit 0FFh   // call 0x193D5
		push edi
		__emit 0E8h
		__emit 010h
		__emit 0B4h
		__emit 021h
		__emit 000h   // call 0x881EF0
		mov eax, dword ptr [esp+34h]
		add esp, 4h
		push eax
		push esi
		mov ecx, ebx
		__emit 0E8h
		__emit 08Ah
		__emit 086h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		mov ecx, esi
		__emit 0E8h
		__emit 0ADh
		__emit 095h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		jmp L05_666B9D
L02_666AFC:
		mov dword ptr [esp+34h], edi
		movzx ecx, byte ptr [esp+30h]
		mov eax, dword ptr [esp+2Ch]
		cmp eax, edi
		mov bl, 1h
		mov byte ptr [esp+24h], bl
		push ecx
		je L06_666B19
		add eax, 8h
		jmp L07_666B1E
L06_666B19:
		mov eax, 107388Bh
L07_666B1E:
		push eax
		push ecx
		mov dword ptr [esp+3Ch], esp
		mov ecx, esp
		push 111A268h
		__emit 0E8h
		__emit 0B0h
		__emit 022h
		__emit 022h
		__emit 000h   // call 0x888DE0
		lea edx,  [esp+40h]
		push edx
		__emit 0E8h
		__emit 056h
		__emit 026h
		__emit 022h
		__emit 000h   // call 0x889190
		__emit 0A1h
		__emit 030h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f7730]
		add esp, 10h
		cmp eax, edi
		je L08_666B8F
		push 2h
		push ecx
		lea eax,  [esp+3Ch]
		mov dword ptr [esp+38h], esp
		mov ecx, esp
		push eax
		__emit 0E8h
		__emit 0A7h
		__emit 018h
		__emit 022h
		__emit 000h   // call 0x888400
		lea ecx,  [esp+1Ch]
		push ecx
		push ecx
		mov dword ptr [esp+20h], esp
		mov ecx, esp
		push 111A250h
		mov byte ptr [esp+38h], 2h
		mov dword ptr [esp+28h], edi
		mov word ptr [esp+2Ch], di
		__emit 0E8h
		__emit 063h
		__emit 022h
		__emit 022h
		__emit 000h   // call 0x888DE0
		__emit 08Bh
		__emit 00Dh
		__emit 030h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f7730]
		mov edx, dword ptr [ecx]
		mov byte ptr [esp+34h], bl
		call dword ptr [edx+8Ch]
L08_666B8F:
		lea ecx,  [esp+34h]
		mov byte ptr [esp+24h], 0h
		__emit 0E8h
		__emit 033h
		__emit 016h
		__emit 022h
		__emit 000h   // call 0x8881D0
L05_666B9D:
		lea ecx,  [esp+2Ch]
		mov dword ptr [esp+24h], 0FFFFFFFFh
		__emit 0E8h
		__emit 092h
		__emit 00Dh
		__emit 022h
		__emit 000h   // call 0x887940
		mov ecx, dword ptr [esp+1Ch]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 18h
		ret 0Ch
	}
}

// Network::getFileTransferProgress proves the player and by-value filename ABI.
// Search announced filenames and return the corresponding player's percentage.
int ConnectionManager::getFileTransferProgress(int playerID, AsciiString path)
{
	FileCommandMap::iterator command = m_fileCommandMap.begin();
	while (command != m_fileCommandMap.end())
	{
		if (compareFilePaths(command->second, path) == 0)
			return m_fileProgressMap[playerID][command->first];
		++command;
	}
	return 0;
}

// Composes the per-player status line the disconnect and load screens show. It
// reads the slot list through GameInfo::getConstSlot, asks each
// FrameDataManager at this+0x120E4 whether it is quitting, consults the id
// array at this+0x12030 and the state array at this+0x12080, and assembles the
// result as a UnicodeString.
__declspec(naked) void BFMEConnectionManager::buildPlayerStatusText(void *out)
{
	__asm {
		push 0FFFFFFFFh
		push 10442F0h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 0Ch
		push ebx
		mov ebx, dword ptr [esp+20h]
		push ebp
		push esi
		push edi
		xor edi, edi
		cmp ebx, edi
		mov ebp, ecx
		mov dword ptr [esp+10h], edi
		__emit 00Fh
		__emit 08Ch
		__emit 0F8h
		__emit 001h
		__emit 000h
		__emit 000h   // jl 0x666528
		cmp ebx, 8h
		__emit 00Fh
		__emit 08Dh
		__emit 0EFh
		__emit 001h
		__emit 000h
		__emit 000h   // jge 0x666528
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		cmp ecx, edi
		je L01_66635E
		push ebx
		__emit 0E8h
		__emit 0CFh
		__emit 088h
		__emit 09Bh
		__emit 0FFh   // call 0x1EC18
		cmp eax, edi
		je L01_66635E
		cmp dword ptr [eax+3Ch], edi
		jne L01_66635E
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		mov edx, dword ptr [ecx+3Ch]
		mov dword ptr [eax+3Ch], edx
L01_66635E:
		mov dword ptr [esp+2Ch], edi
		push ebx
		lea eax,  [esp+18h]
		push eax
		mov ecx, ebp
		mov dword ptr [esp+2Ch], edi
		__emit 0E8h
		__emit 0EFh
		__emit 0C6h
		__emit 09Ah
		__emit 0FFh   // call 0x12A62
		push eax
		lea ecx,  [esp+30h]
		mov byte ptr [esp+28h], 1h
		__emit 0E8h
		__emit 0AEh
		__emit 021h
		__emit 022h
		__emit 000h   // call 0x888530
		lea ecx,  [esp+14h]
		mov byte ptr [esp+24h], 0h
		__emit 0E8h
		__emit 040h
		__emit 01Eh
		__emit 022h
		__emit 000h   // call 0x8881D0
		mov eax, dword ptr [esp+2Ch]
		cmp eax, edi
		je L02_6663CE
		movzx ecx, word ptr [eax+4h]
		cmp ecx, edi
		jle L02_6663CE
		cmp dword ptr [ebp+ebx*4+4h], edi
		je L02_6663CE
		add eax, 8h
		push eax
		push ecx
		mov dword ptr [esp+20h], esp
		mov ecx, esp
		push 1104E54h
		__emit 0E8h
		__emit 005h
		__emit 028h
		__emit 022h
		__emit 000h   // call 0x888BC0
		__emit 0A1h
		__emit 08Ch
		__emit 014h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f148c]
		mov ecx, dword ptr [eax]
		push eax
		call dword ptr [ecx+3Ch]
		add esp, 0Ch
		__emit 0E8h
		__emit 012h
		__emit 0C9h
		__emit 0FFh
		__emit 0FFh   // call 0x662CE0
L02_6663CE:
		mov ecx, dword ptr [ebp+ebx*4+120E4h]
		cmp ecx, edi
		je L03_6663FA
		__emit 0E8h
		__emit 0FEh
		__emit 0D2h
		__emit 09Bh
		__emit 0FFh   // call 0x236DC
		test al, al
		jne L03_6663FA
		mov ecx, dword ptr [ebp+ebx*4+120E4h]
		cmp ecx, edi
		je L04_6663F3
		mov edx, dword ptr [ecx]
		push 1h
		call dword ptr [edx]
L04_6663F3:
		mov dword ptr [ebp+ebx*4+120E4h], edi
L03_6663FA:
		mov esi, dword ptr [ebp+ebx*4+4h]
		cmp esi, edi
		je L05_66641B
		cmp dword ptr [esi], 0FFFFFFFFh
		jne L05_66641B
		mov ecx, esi
		__emit 0E8h
		__emit 0C1h
		__emit 06Ah
		__emit 09Dh
		__emit 0FFh   // call 0x3CECF
		push esi
		__emit 0E8h
		__emit 09Ch
		__emit 0BAh
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
		mov dword ptr [ebp+ebx*4+4h], edi
L05_66641B:
		mov dword ptr [ebp+ebx*4+12080h], 3h
		mov eax, dword ptr [ebp+1202Ch]
		cmp ebx, eax
		__emit 00Fh
		__emit 085h
		__emit 07Dh
		__emit 000h
		__emit 000h
		__emit 000h   // jne 0x6664b1
		cmp eax, 8h
		jae L07_66644B
		shl eax, 0Dh
		lea edi,  [eax+ebp+24h]
		xor eax, eax
		mov ecx, 800h
		rep stosd
		xor edi, edi
L07_66644B:
		xor eax, eax
		lea ecx,  [ebp+12030h]
L09_666453:
		mov edx, dword ptr [ecx]
		cmp edx, dword ptr [ebp+1202Ch]
		je L08_666466
		inc eax
		add ecx, 4h
		cmp eax, 7h
		jb L09_666453
L08_666466:
		mov eax, dword ptr [ebp+eax*4+12034h]
		cmp eax, 8h
		mov dword ptr [ebp+1202Ch], eax
		jae L10_66648A
		shl eax, 0Dh
		lea edi,  [eax+ebp+24h]
		xor eax, eax
		mov ecx, 800h
		rep stosd
		xor edi, edi
L10_66648A:
		mov eax, dword ptr [ebp+12028h]
		cmp eax, dword ptr [ebp+1202Ch]
		je L11_6664A9
		xor eax, eax
		mov ecx, 800h
		lea edi,  [ebp+10024h]
		rep stosd
		xor edi, edi
L11_6664A9:
		mov dword ptr [esp+10h], 2h
L06_6664B1:
		cmp dword ptr [ebp+12028h], ebx
		jne L12_6664C1
		mov dword ptr [esp+10h], 1h
L12_6664C1:
		xor eax, eax
		lea ecx,  [ebp+12030h]
		__emit 08Dh
		__emit 0A4h
		__emit 024h
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 000h   // lea esp, [esp]
L14_6664D0:
		cmp dword ptr [ecx], ebx
		je L13_6664DD
		inc eax
		add ecx, 4h
		cmp eax, 8h
		jl L14_6664D0
L13_6664DD:
		cmp eax, 7h
		jge L15_6664F9
		mov ecx, 7h
		lea edi,  [ebp+eax*4+12030h]
		lea esi,  [ebp+eax*4+12034h]
		sub ecx, eax
		rep movsd
L15_6664F9:
		or eax, 0FFFFFFFFh
		lea ecx,  [esp+2Ch]
		mov dword ptr [ebp+1204Ch], eax
		mov dword ptr [esp+24h], eax
		__emit 0E8h
		__emit 0C1h
		__emit 01Ch
		__emit 022h
		__emit 000h   // call 0x8881D0
		mov eax, dword ptr [esp+10h]
		mov ecx, dword ptr [esp+1Ch]
		mov dword ptr fs:[0h], ecx
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 18h
		ret 4h
L00_666528:
		mov ecx, dword ptr [esp+1Ch]
		pop edi
		pop esi
		pop ebp
		mov eax, 3h
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 18h
		ret 4h
	}
}

// Emits ACKBOTH or ACKSTAGE1 for a received command reference, selecting the
// original player, source address, or packet router as the return route. The
// runRelayPass caller and ret 8 prove the two-argument ABI. A clean C++ attempt
// is banked at targets/game/reverse/attempts/0x00662e80.cpp; this original body remains.
__declspec(naked) void BFMEConnectionManager::queueLocalCommand(void *msg)
{
	__asm {
		mov eax, dword ptr fs:[0h]
		push 0FFFFFFFFh
		push 1043FA6h
		push eax
		mov dword ptr fs:[0h], esp
		push ebx
		push ebp
		push esi
		mov esi, ecx
		mov eax, dword ptr [esi+4h]
		push edi
		mov edi, dword ptr [esp+20h]
		mov ebx, dword ptr [edi]
		xor cl, cl
		or ebp, 0FFFFFFFFh
		test eax, eax
		je L00_662EB3
		cmp dword ptr [eax], ebp
		jne L00_662EB3
		mov cl, 1h
L00_662EB3:
		mov eax, dword ptr [esi+8h]
		test eax, eax
		je L01_662EC1
		cmp dword ptr [eax], ebp
		jne L01_662EC1
		or cl, 2h
L01_662EC1:
		mov eax, dword ptr [esi+0Ch]
		test eax, eax
		je L02_662ECF
		cmp dword ptr [eax], ebp
		jne L02_662ECF
		or cl, 4h
L02_662ECF:
		mov eax, dword ptr [esi+10h]
		test eax, eax
		je L03_662EDD
		cmp dword ptr [eax], ebp
		jne L03_662EDD
		or cl, 8h
L03_662EDD:
		mov eax, dword ptr [esi+14h]
		test eax, eax
		je L04_662EEB
		cmp dword ptr [eax], ebp
		jne L04_662EEB
		or cl, 10h
L04_662EEB:
		mov eax, dword ptr [esi+18h]
		test eax, eax
		je L05_662EF9
		cmp dword ptr [eax], ebp
		jne L05_662EF9
		or cl, 20h
L05_662EF9:
		mov eax, dword ptr [esi+1Ch]
		test eax, eax
		je L06_662F07
		cmp dword ptr [eax], ebp
		jne L06_662F07
		or cl, 40h
L06_662F07:
		mov eax, dword ptr [esi+20h]
		test eax, eax
		je L07_662F15
		cmp dword ptr [eax], ebp
		jne L07_662F15
		or cl, 80h
L07_662F15:
		and cl, byte ptr [edi+0Ch]
		push 24h
		jne L08_662F40
		__emit 0E8h
		__emit 00Fh
		__emit 0F0h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+20h], eax
		test eax, eax
		mov dword ptr [esp+18h], 0h
		je L09_662F64
		mov edx, dword ptr [edi]
		push edx
		mov ecx, eax
		__emit 0E8h
		__emit 0CAh
		__emit 054h
		__emit 09Bh
		__emit 0FFh   // call 0x18408
		jmp L10_662F66
L08_662F40:
		__emit 0E8h
		__emit 0EBh
		__emit 0EFh
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+20h], eax
		test eax, eax
		mov dword ptr [esp+18h], 1h
		je L09_662F64
		mov ecx, dword ptr [edi]
		push ecx
		mov ecx, eax
		__emit 0E8h
		__emit 0B1h
		__emit 0E2h
		__emit 09Dh
		__emit 0FFh   // call 0x41213
		jmp L10_662F66
L09_662F64:
		xor eax, eax
L10_662F66:
		mov dword ptr [esp+18h], ebp
		mov ebp, eax
		mov eax, dword ptr [esi+12028h]
		push ebx
		mov dword ptr [ebp+0Ch], eax
		__emit 0E8h
		__emit 0D9h
		__emit 0C1h
		__emit 09Bh
		__emit 0FFh   // call 0x1F154
		add esp, 4h
		test al, al
		je L11_662FA8
		mov eax, dword ptr [ebx+0Ch]
		cmp eax, 8h
		jae L12_663048
		mov ecx, dword ptr [esi+eax*4+4h]
		test ecx, ecx
		je L12_663048
		xor edx, edx
		mov dl, 1h
		mov ecx, eax
		shl dl, cl
		push edx
		jmp L13_66303E
L11_662FA8:
		mov edi, dword ptr [esp+24h]
		xor dl, dl
		mov edi, edi
L16_662FB0:
		movzx eax, dl
		mov eax, dword ptr [esi+eax*4+4h]
		test eax, eax
		je L14_662FCF
		test edi, edi
		je L14_662FCF
		mov ecx, dword ptr [eax+0Ch]
		cmp ecx, dword ptr [edi]
		mov eax, dword ptr [eax+10h]
		jne L14_662FCF
		cmp ax, word ptr [edi+4h]
		je L15_662FF4
L14_662FCF:
		inc dl
		cmp dl, 8h
		jb L16_662FB0
		mov ecx, dword ptr [esi+1202Ch]
		cmp ecx, 8h
		jae L12_663048
		mov eax, dword ptr [esi+ecx*4+4h]
		test eax, eax
		je L17_66301D
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, eax
		push edx
		jmp L18_663042
L15_662FF4:
		movzx ecx, dl
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, dword ptr [esi+ecx*4+4h]
		push edx
		push ebp
		__emit 0E8h
		__emit 034h
		__emit 03Dh
		__emit 09Ch
		__emit 0FFh   // call 0x26D3C
		mov ecx, dword ptr [esp+10h]
		mov dword ptr fs:[0h], ecx
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0Ch
		ret 8h
L17_66301D:
		cmp dword ptr [esi+12028h], ecx
		jne L12_663048
		mov eax, dword ptr [ebx+0Ch]
		cmp eax, 8h
		jae L12_663048
		mov ecx, dword ptr [esi+eax*4+4h]
		test ecx, ecx
		je L12_663048
		mov ecx, eax
		xor eax, eax
		mov al, 1h
		shl al, cl
		push eax
L13_66303E:
		mov ecx, dword ptr [esi+ecx*4+4h]
L18_663042:
		push ebp
		__emit 0E8h
		__emit 0F4h
		__emit 03Ch
		__emit 09Ch
		__emit 0FFh   // call 0x26D3C
L12_663048:
		mov ecx, ebp
		__emit 0E8h
		__emit 055h
		__emit 0D0h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov ecx, dword ptr [esp+10h]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 0Ch
		ret 8h
	}
}

// Populates the per-player state from the lobby's GameInfo: for each slot it
// checks GameSlot::isHuman, copies the name out with GameSlot::getName, fills
// the id array at this+0x12030, and constructs that slot's FrameDataManager
// (0x00670410) into this+0x120E4.
__declspec(naked) void BFMEConnectionManager::attachPlayersFromGameInfo(void *gameInfo)
{
	__asm {
		push 0FFFFFFFFh
		mov eax, dword ptr fs:[0h]
		push 1044339h
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 20h
		push ebx
		push ebp
		push esi
		mov esi, dword ptr [esp+3Ch]
		test esi, esi
		push edi
		mov ebx, ecx
		je L00_666850
		mov eax, dword ptr [esi]
		mov ecx, esi
		call dword ptr [eax+14h]
		xor ecx, ecx
		mov cx, ax
		mov dword ptr [ebx+12028h], eax
		push ecx
		__emit 0E8h
		__emit 092h
		__emit 0B8h
		__emit 09Ch
		__emit 0FFh   // call 0x31EE4
		add esp, 4h
		xor ebp, ebp
		lea edx,  [ebx+12030h]
		mov dword ptr [esp+14h], ebp
		mov dword ptr [esp+10h], edx
		lea edi,  [ebx+120E4h]
		jmp L01_666671
L12_66666D:
		mov esi, dword ptr [esp+40h]
L01_666671:
		push ebp
		mov ecx, esi
		__emit 0E8h
		__emit 0E7h
		__emit 02Dh
		__emit 09Ch
		__emit 0FFh   // call 0x29460
		mov esi, eax
		test esi, esi
		je L02_66683F
		mov ecx, esi
		__emit 0E8h
		__emit 041h
		__emit 013h
		__emit 09Ch
		__emit 0FFh   // call 0x279CB
		test al, al
		je L02_66683F
		cmp ebp, dword ptr [ebx+12028h]
		jne L03_666701
		lea eax,  [esp+18h]
		push eax
		mov ecx, esi
		__emit 0E8h
		__emit 065h
		__emit 03Bh
		__emit 09Dh
		__emit 0FFh   // call 0x3A20B
		lea ecx,  [ebx+12058h]
		push eax
		mov dword ptr [esp+3Ch], 0h
		__emit 0E8h
		__emit 076h
		__emit 01Eh
		__emit 022h
		__emit 000h   // call 0x888530
		or esi, 0FFFFFFFFh
		lea ecx,  [esp+18h]
		mov dword ptr [esp+38h], esi
		__emit 0E8h
		__emit 006h
		__emit 01Bh
		__emit 022h
		__emit 000h   // call 0x8881D0
		push 10h
		__emit 0E8h
		__emit 05Fh
		__emit 0B8h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+14h], eax
		test eax, eax
		mov dword ptr [esp+38h], 1h
		je L04_6666F6
		push 1h
		mov ecx, eax
		__emit 0E8h
		__emit 039h
		__emit 0E5h
		__emit 09Bh
		__emit 0FFh   // call 0x24C26
		mov dword ptr [esp+38h], esi
		jmp L05_666822
L04_6666F6:
		xor eax, eax
		mov dword ptr [esp+38h], esi
		jmp L05_666822
L03_666701:
		push 358h
		__emit 0E8h
		__emit 025h
		__emit 0B8h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+24h], eax
		test eax, eax
		mov dword ptr [esp+38h], 2h
		je L06_666727
		mov ecx, eax
		__emit 0E8h
		__emit 0A7h
		__emit 0CAh
		__emit 09Ch
		__emit 0FFh   // call 0x331CC
		jmp L07_666729
L06_666727:
		xor eax, eax
L07_666729:
		lea ecx,  [esp+1Ch]
		push ecx
		or ebp, 0FFFFFFFFh
		mov ecx, esi
		mov dword ptr [esp+3Ch], ebp
		mov dword ptr [edi-120E0h], eax
		__emit 0E8h
		__emit 0C9h
		__emit 03Ah
		__emit 09Dh
		__emit 0FFh   // call 0x3A20B
		mov edx, dword ptr [ebx+12024h]
		mov ecx, dword ptr [edi-120E0h]
		push edx
		push eax
		lea eax,  [esi+30h]
		push eax
		mov dword ptr [esp+44h], 3h
		__emit 0E8h
		__emit 03Ah
		__emit 0E7h
		__emit 09Ch
		__emit 0FFh   // call 0x34E9B
		lea ecx,  [esp+1Ch]
		mov dword ptr [esp+38h], ebp
		__emit 0E8h
		__emit 062h
		__emit 01Ah
		__emit 022h
		__emit 000h   // call 0x8881D0
		__emit 0A0h
		__emit 0E9h
		__emit 0D4h
		__emit 02Eh
		__emit 001h   // mov al, byte ptr [0x12ed4e9]
		test al, al
		je L08_6667F3
		mov ecx, dword ptr [ebx+12024h]
		push ecx
		lea edx,  [esp+24h]
		push edx
		mov ecx, esi
		__emit 0E8h
		__emit 081h
		__emit 03Ah
		__emit 09Dh
		__emit 0FFh   // call 0x3A20B
		push eax
		__emit 0A1h
		__emit 0F0h
		__emit 0D4h
		__emit 02Eh
		__emit 001h   // mov eax, dword ptr [0x12ed4f0]
		test eax, eax
		mov dword ptr [esp+40h], 4h
		lea ebp,  [eax+8h]
		jne L09_6667A4
		mov ebp, 107388Bh
L09_6667A4:
		push ecx
		mov dword ptr [esp+30h], esp
		mov ecx, esp
		push 12ED4ECh
		__emit 0E8h
		__emit 0ABh
		__emit 013h
		__emit 022h
		__emit 000h   // call 0x887B60
		__emit 0E8h
		__emit 04Eh
		__emit 074h
		__emit 09Dh
		__emit 0FFh   // call 0x3DC08
		push ebp
		mov esi, eax
		__emit 0FFh
		__emit 015h
		__emit 084h
		__emit 093h
		__emit 035h
		__emit 001h   // call dword ptr [0x1359384]
		mov ecx, dword ptr [edi-120E0h]
		mov word ptr [esp+3Ch], ax
		add esp, 8h
		lea eax,  [esp+30h]
		push eax
		mov dword ptr [esp+34h], esi
		__emit 0E8h
		__emit 0BCh
		__emit 0E6h
		__emit 09Ch
		__emit 0FFh   // call 0x34E9B
		lea ecx,  [esp+20h]
		mov dword ptr [esp+38h], 0FFFFFFFFh
		__emit 0E8h
		__emit 0E0h
		__emit 019h
		__emit 022h
		__emit 000h   // call 0x8881D0
		or ebp, 0FFFFFFFFh
L08_6667F3:
		push 10h
		__emit 0E8h
		__emit 036h
		__emit 0B7h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+24h], eax
		test eax, eax
		mov dword ptr [esp+38h], 5h
		je L10_666818
		push 0h
		mov ecx, eax
		__emit 0E8h
		__emit 010h
		__emit 0E4h
		__emit 09Bh
		__emit 0FFh   // call 0x24C26
		jmp L11_66681A
L10_666818:
		xor eax, eax
L11_66681A:
		mov dword ptr [esp+38h], ebp
		mov ebp, dword ptr [esp+14h]
L05_666822:
		mov ecx, eax
		mov dword ptr [edi], eax
		__emit 0E8h
		__emit 0B7h
		__emit 0AAh
		__emit 09Bh
		__emit 0FFh   // call 0x212E2
		mov ecx, dword ptr [edi]
		__emit 0E8h
		__emit 014h
		__emit 07Dh
		__emit 09Ch
		__emit 0FFh   // call 0x2E546
		mov eax, dword ptr [esp+10h]
		mov dword ptr [eax], ebp
		add eax, 4h
		mov dword ptr [esp+10h], eax
L02_66683F:
		inc ebp
		add edi, 4h
		cmp ebp, 8h
		mov dword ptr [esp+14h], ebp
		jl L12_66666D
L00_666850:
		mov ecx, dword ptr [esp+30h]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 2Ch
		ret 4h
	}
}

// Turns a player name into a Player. It formats the name into a UnicodeString,
// puts it through NameKeyGenerator::nameToKey, and looks the result up with
// PlayerList::findPlayerWithNameKey.
__declspec(naked) void BFMEConnectionManager::resolvePlayerFromName(void *msg)
{
	__asm {
		push 0FFFFFFFFh
		push 1044420h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		sub esp, 1Ch
		push ebx
		push ebp
		push esi
		xor ebx, ebx
		push edi
		mov ebp, ecx
		mov dword ptr [esp+10h], ebx
		mov esi, dword ptr [esp+3Ch]
		lea eax,  [esp+18h]
		push eax
		mov ecx, esi
		mov dword ptr [esp+38h], ebx
		__emit 0E8h
		__emit 0A0h
		__emit 0E2h
		__emit 09Bh
		__emit 0FFh   // call 0x25338
		mov eax, dword ptr [eax]
		cmp eax, ebx
		mov byte ptr [esp+34h], 1h
		je L00_6670A8
		add eax, 8h
		jmp L01_6670AD
L00_6670A8:
		mov eax, 107388Ch
L01_6670AD:
		push eax
		mov eax, dword ptr [esi+0Ch]
		push eax
		lea ecx,  [esp+44h]
		push ecx
		mov ecx, ebp
		__emit 0E8h
		__emit 0A4h
		__emit 0B9h
		__emit 09Ah
		__emit 0FFh   // call 0x12A62
		mov eax, dword ptr [eax]
		cmp eax, ebx
		mov byte ptr [esp+38h], 2h
		je L02_6670CE
		add eax, 8h
		jmp L03_6670D3
L02_6670CE:
		mov eax, 107388Ch
L03_6670D3:
		push eax
		push ecx
		mov dword ptr [esp+28h], esp
		mov ecx, esp
		push 1117AECh
		__emit 0E8h
		__emit 0FBh
		__emit 01Ch
		__emit 022h
		__emit 000h   // call 0x888DE0
		lea edx,  [esp+1Ch]
		push edx
		__emit 0E8h
		__emit 0A1h
		__emit 020h
		__emit 022h
		__emit 000h   // call 0x889190
		add esp, 10h
		lea ecx,  [esp+3Ch]
		mov byte ptr [esp+34h], 1h
		__emit 0E8h
		__emit 0D0h
		__emit 010h
		__emit 022h
		__emit 000h   // call 0x8881D0
		lea ecx,  [esp+18h]
		mov byte ptr [esp+34h], 0h
		__emit 0E8h
		__emit 0C2h
		__emit 010h
		__emit 022h
		__emit 000h   // call 0x8881D0
		mov eax, dword ptr [esi+0Ch]
		cmp eax, 8h
		jae L04_66726B
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		push eax
		__emit 0E8h
		__emit 0F2h
		__emit 07Ah
		__emit 09Bh
		__emit 0FFh   // call 0x1EC18
		add eax, 2Ch
		push eax
		lea ecx,  [esp+18h]
		__emit 0E8h
		__emit 02Dh
		__emit 00Ah
		__emit 022h
		__emit 000h   // call 0x887B60
		mov eax, dword ptr [esp+14h]
		cmp eax, ebx
		mov byte ptr [esp+34h], 3h
		je L05_667145
		add eax, 8h
		jmp L06_66714A
L05_667145:
		mov eax, 107388Bh
L06_66714A:
		__emit 08Bh
		__emit 00Dh
		__emit 000h
		__emit 0D6h
		__emit 02Eh
		__emit 001h   // mov ecx, dword ptr [0x12ed600]
		push eax
		__emit 0E8h
		__emit 081h
		__emit 03Ch
		__emit 09Dh
		__emit 0FFh   // call 0x3ADD7
		__emit 08Bh
		__emit 00Dh
		__emit 048h
		__emit 0D7h
		__emit 02Eh
		__emit 001h   // mov ecx, dword ptr [0x12ed748]
		push eax
		__emit 0E8h
		__emit 024h
		__emit 084h
		__emit 09Ch
		__emit 0FFh   // call 0x2F586
		mov edi, eax
		cmp edi, ebx
		jne L07_6671C6
		__emit 08Bh
		__emit 00Dh
		__emit 068h
		__emit 0D6h
		__emit 02Eh
		__emit 001h   // mov ecx, dword ptr [0x12ed668]
		cmp ecx, ebx
		je L08_66718F
		mov eax, dword ptr [ecx]
		call dword ptr [eax+124h]
		cmp eax, ebx
		je L08_66718F
		__emit 08Bh
		__emit 00Dh
		__emit 068h
		__emit 0D6h
		__emit 02Eh
		__emit 001h   // mov ecx, dword ptr [0x12ed668]
		mov edx, dword ptr [ecx]
		add eax, 0C40h
		push eax
		call dword ptr [edx+44h]
L08_66718F:
		mov eax, dword ptr [esp+10h]
		cmp eax, ebx
		je L09_66719C
		add eax, 8h
		jmp L10_6671A1
L09_66719C:
		mov eax, 107388Ch
L10_6671A1:
		push eax
		push ecx
		mov dword ptr [esp+44h], esp
		mov ecx, esp
		push 10FF4BCh
		__emit 0E8h
		__emit 02Dh
		__emit 01Ch
		__emit 022h
		__emit 000h   // call 0x888DE0
		__emit 0A1h
		__emit 08Ch
		__emit 014h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f148c]
		mov ecx, dword ptr [eax]
		push eax
		call dword ptr [ecx+40h]
		add esp, 0Ch
		jmp L11_66725D
L07_6671C6:
		mov ecx, edi
		__emit 0E8h
		__emit 0F0h
		__emit 007h
		__emit 09Bh
		__emit 0FFh   // call 0x179BD
		neg al
		sbb al, al
		inc al
		mov byte ptr [esp+3Ch], al
		jne L12_6671F3
		mov eax, dword ptr [esi+0Ch]
		__emit 08Bh
		__emit 00Dh
		__emit 08Ch
		__emit 070h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f708c]
		push eax
		__emit 0E8h
		__emit 078h
		__emit 022h
		__emit 09Ch
		__emit 0FFh   // call 0x29460
		mov cl, byte ptr [eax+0Ah]
		test cl, cl
		jne L12_6671F3
		mov bl, 1h
		jmp L13_6671F5
L12_6671F3:
		xor bl, bl
L13_6671F5:
		mov ecx, esi
		__emit 0E8h
		__emit 020h
		__emit 0B9h
		__emit 099h
		__emit 0FFh   // call 0x2B1C
		mov ecx, dword ptr [ebp+12028h]
		mov edx, 1h
		shl edx, cl
		__emit 085h
		__emit 0C2h   // test edx, eax
		je L11_66725D
		test bl, bl
		je L11_66725D
		__emit 0E8h
		__emit 0CAh
		__emit 0BAh
		__emit 0FFh
		__emit 0FFh   // call 0x662CE0
		mov eax, dword ptr [edi+1C4h]
		push eax
		lea ecx,  [esp+24h]
		__emit 0E8h
		__emit 0A1h
		__emit 05Bh
		__emit 09Ch
		__emit 0FFh   // call 0x2CDC7
		mov eax, dword ptr [esp+10h]
		test eax, eax
		je L14_667233
		add eax, 8h
		jmp L15_667238
L14_667233:
		mov eax, 107388Ch
L15_667238:
		push eax
		push ecx
		mov dword ptr [esp+44h], esp
		mov ecx, esp
		push 10FF4BCh
		__emit 0E8h
		__emit 096h
		__emit 01Bh
		__emit 022h
		__emit 000h   // call 0x888DE0
		__emit 0A1h
		__emit 08Ch
		__emit 014h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f148c]
		mov ecx, dword ptr [eax]
		lea edx,  [esp+28h]
		push edx
		push eax
		call dword ptr [ecx+38h]
		add esp, 10h
L11_66725D:
		lea ecx,  [esp+14h]
		mov byte ptr [esp+34h], 0h
		__emit 0E8h
		__emit 0D5h
		__emit 006h
		__emit 022h
		__emit 000h   // call 0x887940
L04_66726B:
		lea ecx,  [esp+10h]
		mov dword ptr [esp+34h], 0FFFFFFFFh
		__emit 0E8h
		__emit 054h
		__emit 00Fh
		__emit 022h
		__emit 000h   // call 0x8881D0
		mov ecx, dword ptr [esp+2Ch]
		pop edi
		pop esi
		pop ebp
		mov dword ptr fs:[0h], ecx
		pop ebx
		add esp, 28h
		ret 4h
	}
}

// Receives the completed file payload, writes it and publishes 100% progress.
// Retail still emits completion if opening the destination fails.
void ConnectionManager::processFile(NetFileCommandMsg *msg)
{
	TheFileSystem->doesFileExist(msg->getRealFilename().str());
	unsigned char *buffer = msg->getFileData();
	int length = msg->getFileLength();
	File *file = TheFileSystem->openFile(msg->getRealFilename().str(),
		File::CREATE | File::BINARY | File::WRITE);
	if (file)
	{
		file->write(buffer, length);
		file->close();
	}
	int commandID = msg->getID();
	m_fileProgressMap[m_localSlot][commandID] = 100;
	int relay = 0xFF ^ (1 << m_localSlot);
	NetFileProgressCommandMsg *progress = new NetFileProgressCommandMsg;
	progress->setPlayerID(m_localSlot);
	progress->setID(0);
	if (DoesCommandRequireACommandID(progress->getNetCommandType()))
		progress->setID(GenerateNextCommandID());
	progress->setFileID(commandID);
	progress->setProgress(100);
	sendLocalCommand(progress, relay);
	processFileProgress(progress);
	progress->detach();
}

// Opens the source and publishes its filename, recipients and a separately reserved file ID.
unsigned short ConnectionManager::sendFileAnnounce(AsciiString path, unsigned char playerMask)
{
	File *file = TheFileSystem->openFile(path.str(), 0);
	if (!file || !file->size())
	{
		UnicodeString log;
		log.format(UnicodeString(L"Not sending file '%hs' to %X\n"), path.str(), playerMask);
		if (TheLAN)
		{
			TheLAN->OnChat(UnicodeString(L"sendFile"), BFMEFileTransferAddress(0, 0), log, 2);
		}
		return 0;
	}
	file->close();
	int relay = 0xFF ^ (1 << m_localSlot);
	NetFileAnnounceCommandMsg *msg = new NetFileAnnounceCommandMsg;
	msg->setPlayerID(m_localSlot);
	if (DoesCommandRequireACommandID(msg->getNetCommandType()) == true)
		msg->setID(GenerateNextCommandID());
	msg->setRealFilename(path);
	msg->setPlayerMask(playerMask);
	unsigned short fileID = GenerateNextCommandID();
	msg->setFileID(fileID);
	processFileAnnounce(msg);
	sendLocalCommand(msg, relay);
	msg->detach();
	return fileID;
}

// Retail's name -- the ZH reference declares it with this signature. Returns
// m_packetRouterSlot at this+0x1202C.
unsigned int ConnectionManager::getPacketRouterSlot()
{
	return *(unsigned int *)((char *)this + 0x1202C);
}

// Retail's name, and the callee DisconnectManager::isPlayerVotedOut wants.
// Counts the connected slots exactly as the reference does, except that BFME
// inlines isPlayerConnected: a slot counts when it is our own or its Connection
// pointer at this+0x04 is set.
int ConnectionManager::getNumPlayers()
{
	int playerCount = 0;
	for (int slot = 0; slot < 8; ++slot) {
		if (slot == m_localSlot ||
			(m_connections[slot] != 0 && m_connections[slot]->m_openState == -1))
			++playerCount;
	}
	return playerCount;
}

// Queues a direct keepalive after a connection has been silent for more than
// one second. The send path owns updating the connection's last-send time.
void BFMEConnectionManager::sendKeepAliveCommand()
{
	unsigned int now = timeGetTime();
	for (int player = 0; player < 8; ++player)
	{
		if (m_connections[player] && now - m_connections[player]->getLastTimeSent() > 1000)
		{
			NetKeepAliveCommandMsg *msg = new NetKeepAliveCommandMsg;
			msg->setPlayerID(m_localSlot);
			if (DoesCommandRequireACommandID(msg->getNetCommandType()) == true)
				msg->setID(GenerateNextCommandID());
			reinterpret_cast<ConnectionManager *>(this)->sendLocalCommandDirect(msg, (unsigned char)(1 << player));
			msg->detach();
		}
	}
}

// Updates local loading progress immediately and sends it directly to every peer.
void BFMEConnectionManager::sendProgressCommand(int percent)
{
	NetProgressCommandMsg *msg = new NetProgressCommandMsg;
	msg->setPercentage((unsigned char)percent);
	msg->setPlayerID(m_localSlot);
	if (DoesCommandRequireACommandID(msg->getNetCommandType()) == true)
		msg->setID(GenerateNextCommandID());
	TheGameLogic->processProgress(msg->getPlayerID(), msg->getPercentage());
	reinterpret_cast<ConnectionManager *>(this)->sendLocalCommandDirect(msg,
		(unsigned char)~(unsigned char)(1 << m_localSlot));
	msg->detach();
}

// Announces the current simulation frame and applies the same disconnect event locally.
void BFMEConnectionManager::sendDisconnectFrameCommand()
{
	unsigned int frame = TheGameLogic->getFrame();
	NetDisconnectFrameCommandMsg *msg = new NetDisconnectFrameCommandMsg;
	msg->setPlayerID(m_localSlot);
	msg->setDisconnectFrame(frame);
	if (DoesCommandRequireACommandID(msg->getNetCommandType()))
		msg->setID(GenerateNextCommandID());
	reinterpret_cast<ConnectionManager *>(this)->sendLocalCommandDirect(msg,
		(unsigned char)~(unsigned char)(1 << m_localSlot));
	if (m_disconnectManager)
	{
		NetCommandRef *ref = new NetCommandRef(msg);
		ref->setRelay((unsigned char)(1 << m_localSlot));
		m_disconnectManager->processDisconnectCommand(ref,
			reinterpret_cast<ConnectionManager *>(this));
		delete ref;
	}
	msg->detach();
}

// Sends command type 28 (DISCONNECTSCREENOFF), built by 0x00674310; it also calls
// DisconnectManager::turnOffScreen, which is the same pairing
// processDisconnectScreenOff has on the receiving side. Named from the type its message carries, which is
// evidence rather than inference now that the enum at 0x00683020 is recovered.
__declspec(naked) void BFMEConnectionManager::sendDisconnectScreenOffCommand(int slot)
{
	__asm {
		push 0FFFFFFFFh
		push 1044086h
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push ebx
		push esi
		mov esi, ecx
		mov eax, dword ptr [esi+12028h]
		mov ecx, dword ptr [esi+120E0h]
		push edi
		push eax
		__emit 0E8h
		__emit 043h
		__emit 010h
		__emit 09Eh
		__emit 0FFh   // call 0x44AD0
		push 20h
		__emit 0E8h
		__emit 09Ch
		__emit 0E4h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+0Ch], eax
		xor ebx, ebx
		cmp eax, ebx
		mov dword ptr [esp+18h], ebx
		je L00_663AB0
		mov ecx, eax
		__emit 0E8h
		__emit 024h
		__emit 0BEh
		__emit 09Ah
		__emit 0FFh   // call 0xF8D0
		mov edi, eax
		jmp L01_663AB2
L00_663AB0:
		xor edi, edi
L01_663AB2:
		mov eax, dword ptr [esi+12028h]
		mov dword ptr [edi+0Ch], eax
		mov eax, dword ptr [esp+20h]
		push eax
		mov ecx, edi
		mov dword ptr [esp+1Ch], 0FFFFFFFFh
		__emit 0E8h
		__emit 036h
		__emit 05Ah
		__emit 09Ch
		__emit 0FFh   // call 0x29505
		mov eax, dword ptr [edi+14h]
		push eax
		__emit 0E8h
		__emit 09Ah
		__emit 020h
		__emit 09Bh
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L02_663AE8
		__emit 0E8h
		__emit 074h
		__emit 0CAh
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [edi+10h], ax
L02_663AE8:
		mov ecx, dword ptr [esi+12028h]
		xor edx, edx
		mov dl, 1h
		shl dl, cl
		mov ecx, esi
		not dl
		push edx
		push edi
		__emit 0E8h
		__emit 0D8h
		__emit 0D6h
		__emit 09Dh
		__emit 0FFh   // call 0x411D7
		cmp dword ptr [esi+120E0h], ebx
		je L03_663B5D
		push 14h
		__emit 0E8h
		__emit 022h
		__emit 0E4h
		__emit 021h
		__emit 000h   // call 0x881F30
		add esp, 4h
		mov dword ptr [esp+20h], eax
		cmp eax, ebx
		mov dword ptr [esp+18h], 1h
		je L04_663B2B
		push edi
		mov ecx, eax
		__emit 0E8h
		__emit 0BDh
		__emit 03Eh
		__emit 09Ah
		__emit 0FFh   // call 0x79E6
		mov ebx, eax
L04_663B2B:
		mov ecx, dword ptr [esi+12028h]
		mov al, 1h
		shl al, cl
		push esi
		push ebx
		mov dword ptr [esp+20h], 0FFFFFFFFh
		mov byte ptr [ebx+0Ch], al
		mov ecx, dword ptr [esi+120E0h]
		__emit 0E8h
		__emit 023h
		__emit 04Eh
		__emit 09Ch
		__emit 0FFh   // call 0x28970
		mov ecx, ebx
		__emit 0E8h
		__emit 00Ch
		__emit 04Eh
		__emit 09Dh
		__emit 0FFh   // call 0x38960
		push ebx
		__emit 0E8h
		__emit 056h
		__emit 0E3h
		__emit 021h
		__emit 000h   // call 0x881EB0
		add esp, 4h
L03_663B5D:
		mov ecx, edi
		__emit 0E8h
		__emit 040h
		__emit 0C5h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov ecx, dword ptr [esp+10h]
		pop edi
		pop esi
		pop ebx
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret 4h
	}
}

// Requests agreement on the local player's departure and flushes the request immediately.
void BFMEConnectionManager::sendRequestPlayerLeaveCommand()
{
	BFMENetRequestPlayerLeaveCommandMsg *msg = new BFMENetRequestPlayerLeaveCommandMsg;
	msg->setRequestedPlayerID(m_localSlot);
	msg->setPlayerID(m_localSlot);
	if (DoesCommandRequireACommandID(msg->getNetCommandType()))
		msg->setID(GenerateNextCommandID());
	msg->setExecutionFrame(-1);
	reinterpret_cast<ConnectionManager *>(this)->sendLocalCommandDirect(msg,
		(unsigned char)~(unsigned char)(1 << m_localSlot));
	reinterpret_cast<ConnectionManager *>(this)->flushConnections();
	msg->detach();
	if (!m_localLeaveStarted)
		m_localLeaveStarted = timeGetTime();
}

void BFMEConnectionManager::sendLoadCompleteCommand()
{
	NetCommandMsg *msg = new NetCommandMsg;
	msg->setNetCommandType(NETCOMMANDTYPE_LOADCOMPLETE);
	msg->setPlayerID(m_localSlot);
	if (DoesCommandRequireACommandID(NETCOMMANDTYPE_LOADCOMPLETE))
	{
		msg->setID(GenerateNextCommandID());
	}

	TheGameLogic->processProgressComplete(msg->getPlayerID());
	reinterpret_cast<ConnectionManager *>(this)->sendLocalCommand(msg, 0xff ^ (1 << m_localSlot));
	msg->detach();
}

// Announces the local departure, then starts the leave timeout clock. The
// router's receive pass separately emits the eventual DESTROYPLAYER command.
void BFMEConnectionManager::sendPlayerLeaveCommands()
{
	NetPlayerLeaveCommandMsg *msg = new NetPlayerLeaveCommandMsg;
	msg->setLeavingPlayerID((unsigned char)m_localSlot);
	msg->setExecutionFrame(-1);
	if (DoesCommandRequireACommandID(msg->getNetCommandType()))
		msg->setID(GenerateNextCommandID());
	msg->setPlayerID(m_localSlot);
	reinterpret_cast<ConnectionManager *>(this)->sendLocalCommand(msg, 0xFF);
	msg->detach();
	m_localLeaveStarted = timeGetTime();
}

// Sends command type 3 (FRAMEINFO), the single-recipient counterpart to sendFrameInfo. Named from the type its message carries.
__declspec(naked) void BFMEConnectionManager::sendFrameInfoToPlayer(int slot)
{
	__asm {
		push 0FFFFFFFFh
		push 104428Bh
		mov eax, dword ptr fs:[0h]
		push eax
		mov dword ptr fs:[0h], esp
		push ecx
		push esi
		push edi
		push 28h
		mov edi, ecx
		__emit 0E8h
		__emit 03Fh
		__emit 0C0h
		__emit 021h
		__emit 000h   // call 0x881F30
		mov esi, eax
		add esp, 4h
		mov dword ptr [esp+8h], esi
		test esi, esi
		mov dword ptr [esp+14h], 0h
		je L00_665F31
		mov ecx, esi
		__emit 0E8h
		__emit 0A7h
		__emit 0D3h
		__emit 09Ah
		__emit 0FFh   // call 0x132B4
		mov dword ptr [esi], 111A220h
		mov dword ptr [esi+1Ch], 0h
		mov dword ptr [esi+20h], 0h
		mov dword ptr [esi+24h], 0FFFFFFFFh
		mov dword ptr [esi+14h], 3h
		jmp L01_665F33
L00_665F31:
		xor esi, esi
L01_665F33:
		__emit 0A1h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov eax, dword ptr [0x12f0898]
		mov eax, dword ptr [eax+3Ch]
		dec eax
		mov dword ptr [esi+1Ch], eax
		__emit 08Bh
		__emit 00Dh
		__emit 064h
		__emit 014h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f1464]
		mov edx, dword ptr [ecx]
		mov dword ptr [esp+14h], 0FFFFFFFFh
		call dword ptr [edx+68h]
		mov dword ptr [esi+20h], eax
		mov eax, dword ptr [esi+14h]
		push eax
		__emit 0E8h
		__emit 014h
		__emit 0FCh
		__emit 09Ah
		__emit 0FFh   // call 0x15B72
		add esp, 4h
		test al, al
		je L02_665F6E
		__emit 0E8h
		__emit 0EEh
		__emit 0A5h
		__emit 09Ch
		__emit 0FFh   // call 0x30558
		mov word ptr [esi+10h], ax
L02_665F6E:
		mov eax, dword ptr [edi+12028h]
		mov dword ptr [esi+0Ch], eax
		mov eax, dword ptr [edi+12028h]
		mov ecx, dword ptr [edi+1202Ch]
		cmp eax, ecx
		jne L03_665F94
		xor edx, edx
		mov dl, 1h
		mov ecx, eax
		shl dl, cl
		not dl
		push edx
		jmp L04_665F9B
L03_665F94:
		xor eax, eax
		mov al, 1h
		shl al, cl
		push eax
L04_665F9B:
		mov ecx, edi
		push esi
		__emit 0E8h
		__emit 0D7h
		__emit 091h
		__emit 09Dh
		__emit 0FFh   // call 0x3F17A
		mov ecx, esi
		__emit 0E8h
		__emit 0FAh
		__emit 0A0h
		__emit 09Bh
		__emit 0FFh   // call 0x200A4
		mov ecx, dword ptr [esp+0Ch]
		pop edi
		pop esi
		mov dword ptr fs:[0h], ecx
		add esp, 10h
		ret
	}
}

// Network::sendDisconnectChat forwards a by-value string here through ILT 0x00001B54.
void ConnectionManager::sendDisconnectChat(UnicodeString text)
{
	NetDisconnectChatCommandMsg *msg = new NetDisconnectChatCommandMsg;
	msg->setPlayerID(m_localSlot);
	if (DoesCommandRequireACommandID(msg->getNetCommandType()))
		msg->setID(GenerateNextCommandID());
	msg->setText(text);
	sendLocalCommandDirect(msg, (unsigned char)~(unsigned char)(1 << m_localSlot));
	processDisconnectChat(msg);
	msg->detach();
}

// Network::sendChat at 0x00682440 proves the by-value text and recipient-mask ABI.
// This was formerly misidentified as a disconnect vote despite constructing CHAT.
void BFMEConnectionManager::sendChat(UnicodeString text, int playerMask)
{
	NetChatCommandMsg *msg = new NetChatCommandMsg;
	msg->setText(text);
	msg->setPlayerMask(playerMask);
	msg->setPlayerID(m_localSlot);
	if (DoesCommandRequireACommandID(msg->getNetCommandType()))
		msg->setID(GenerateNextCommandID());
	reinterpret_cast<ConnectionManager *>(this)->sendLocalCommandDirect(msg,
		(unsigned char)~(unsigned char)(1 << m_localSlot));
	reinterpret_cast<ConnectionManager *>(this)->processChat(msg);
	msg->detach();
}

// Replies to the request's challenge using the GameSpy authentication helper.
void BFMEConnectionManager::sendGameSpyStatsAuthKey(void *command)
{
	BFMENetRequestGameSpyStatsAuthKeyCommandMsg *request =
		static_cast<BFMENetRequestGameSpyStatsAuthKeyCommandMsg *>(command);
	char *challenge = goastrdup(request->getText1C().str());
	char *secret = goastrdup(TheGameSpyBuddyMessageQueue->getAuthSecretText());
	char response[256];
	GenerateAuthA(challenge, secret, response);
	free(challenge);
	free(secret);
	BFMENetGameSpyStatsAuthKeyCommandMsg *msg = new BFMENetGameSpyStatsAuthKeyCommandMsg;
	msg->setPlayerID(m_localSlot);
	msg->setExecutionFrame(-1);
	if (DoesCommandRequireACommandID(msg->getNetCommandType()))
		msg->setID(GenerateNextCommandID());
	msg->setText1C(AsciiString(response));
	msg->setText20(AsciiString(TheGameSpyBuddyMessageQueue->getReplyIdentityText()));
	if (request->getPlayerID() < 8)
		reinterpret_cast<ConnectionManager *>(this)->sendLocalCommandDirect(msg,
			(unsigned char)(1 << request->getPlayerID()));
	msg->detach();
}

// Sends command type 4 (GAMECOMMAND), built by the constructor at 0x00674A40.
// This is where a player's order enters the lockstep: it is the BFME analogue of
// the reference's ConnectionManager::sendLocalGameMessage.
void BFMEConnectionManager::sendGameCommand(void *msg)
{
	NetCommandMsg *netmsg = new NetGameCommandMsg(static_cast<GameMessage *>(msg));
	netmsg->setExecutionFrame((unsigned int)-1);
	netmsg->setPlayerID(m_localSlot);
	if (DoesCommandRequireACommandID(netmsg->getNetCommandType()))
		netmsg->setID(GenerateNextCommandID());
	reinterpret_cast<ConnectionManager *>(this)->sendLocalCommand(netmsg, 0xFF);
	netmsg->detach();
}

// A router filters each originating player's command IDs separately. Clients
// filter the router's stream through the ninth history. A true result means
// this copy has already been accepted and must not be dispatched again.
Bool BFMEConnectionManager::isDuplicateCommand(NetCommandMsg *msg)
{
	if (m_localSlot == m_packetRouterSlot)
	{
		if (msg->getPlayerID() != m_packetRouterSlot && msg->getPlayerID() < 8 &&
			DoesCommandRequireACommandID(msg->getNetCommandType()))
		{
			if (!m_commandHistory[msg->getPlayerID()].accept(msg->getID(), TheGameLogic->getFrame()))
				return true;
		}
	}
	else
	{
		if (msg->getPlayerID() == m_packetRouterSlot &&
			DoesCommandRequireACommandID(msg->getNetCommandType()))
		{
			if (!m_commandHistory[8].accept(msg->getID(), msg->getExecutionFrame()))
				return true;
		}
	}
	return false;
}

// Returns an owning string copy from the local name or a peer connection.
// ILT 0x00012A62 and the named DisconnectManager callers prove the return ABI.
UnicodeString ConnectionManager::getPlayerName(int slot)
{
	if (slot == m_localSlot)
		return m_localPlayerName;
	if (m_connections[slot])
		return m_connections[slot]->m_playerName;
	return BFMEEmptyPlayerName;
}
