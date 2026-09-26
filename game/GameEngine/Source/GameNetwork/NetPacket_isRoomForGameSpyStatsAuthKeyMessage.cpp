// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// NetPacket::isRoomForGameSpyStatsAuthKeyMessage, retail 0x0067E2B0, 250B.
// The matched addGameSpyStatsAuthKeyCommand body at 0x00680620 opens with
// this guard, while the two matched text getters identify the payload as the
// BFME GameSpy stats auth-key message. Their existing ILT routes and the
// StringBase release body account for every retail REL32 callee.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum { MAX_PACKET_SIZE = 0x1DC };

struct BfmeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

class NetPacket;

template <typename T>
class StringBase
{
public:
	friend class NetPacket;
	Int getLength() const { return m_data ? m_data->m_len : 0; }

private:
	StringBase();
	StringBase(const StringBase &other);
	~StringBase();
	void releaseBuffer();
	BfmeStringData *m_data;
};

class NetCommandMsg
{
public:
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedShort getID() { return m_id; }
	Int getNetCommandType() { return m_commandType; }

	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	Int m_commandType;
	Int m_referenceCount;
};

class BFMENetGameSpyStatsAuthKeyCommandMsg
{
public:
	Int getPlayerID() { return m_playerID; }
	UnsignedShort getID() { return m_id; }
	Int getNetCommandType() { return m_commandType; }

	StringBase<char> getText1C(void);
	StringBase<char> getText20(void);

	UnsignedByte m_bfmeHead[0x0C];
	Int m_playerID;
	UnsignedShort m_id;
	UnsignedShort m_pad;
	Int m_commandType;
};

class NetCommandRef
{
public:
	NetCommandMsg *getCommand(void) { return m_command; }
	UnsignedByte getRelay(void) const { return m_relay; }

	NetCommandMsg *m_command;
	UnsignedByte m_bfmeMiddle[0x0C - 4];
	UnsignedByte m_relay;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
public:
	virtual ~NetPacket();

protected:
	Bool isRoomForGameSpyStatsAuthKeyMessage(NetCommandRef *msg);

public:
	UnsignedByte m_packet[0x1DC];
	Int m_packetLen;
	UnsignedInt m_destIP;
	UnsignedShort m_destPort;
	Int m_numCommands;
	NetCommandRef *m_lastCommand;
	UnsignedInt m_lastFrame;
	UnsignedShort m_lastCommandID;
	UnsignedByte m_lastPlayerID;
	UnsignedByte m_lastCommandType;
	UnsignedByte m_lastRelay;
};

// ?isRoomForGameSpyStatsAuthKeyMessage@NetPacket@@IAE_NPAVNetCommandRef@@@Z
Bool NetPacket::isRoomForGameSpyStatsAuthKeyMessage(NetCommandRef *msg)
{
	Int len = 0;
	Bool needNewCommandID = false;
	BFMENetGameSpyStatsAuthKeyCommandMsg *cmdMsg =
		(BFMENetGameSpyStatsAuthKeyCommandMsg *)(msg->getCommand());
	if (m_lastCommandType != cmdMsg->getNetCommandType())
	{
		++len;
		len += sizeof(UnsignedByte);
	}
	if (m_lastRelay != msg->getRelay())
	{
		len += sizeof(UnsignedByte) + sizeof(UnsignedByte);
	}
	if (m_lastPlayerID != cmdMsg->getPlayerID())
	{
		++len;
		len += sizeof(UnsignedByte);
		needNewCommandID = true;
	}
	if (((m_lastCommandID + 1) != (UnsignedShort)(cmdMsg->getID())) ||
		(needNewCommandID == true))
	{
		len += sizeof(UnsignedShort) + sizeof(UnsignedByte);
	}

	++len;
	len += cmdMsg->getText1C().getLength() +
		cmdMsg->getText20().getLength() + 2;

	if ((len + m_packetLen) > MAX_PACKET_SIZE)
		return false;
	return true;
}
