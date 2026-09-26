// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
//
// NetPacket::ConstructBigCommandPacketList, retail 0x006814B0, 725 bytes.
//
// The shipped NetPacket.h declaration is the ABI authority: this factory is a
// public static member, while the two serializer helpers it calls remain
// protected static members.  The reference NetCommandRef inherits
// MemoryPoolObject, but BFME's retail command-reference object is the compact
// 0x14-byte layout used here (m_msg at +0x00).  This TU-local view is therefore
// deliberate and is constrained by the retail constructor/object flow and the
// matched NetCommandRef bodies; it is not a generic template or a byte lift.

#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <list>

#include "GameNetwork/NetworkDefs.h"

class NetCommandMsg
{
public:
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedInt getExecutionFrame() { return m_executionFrame; }
	UnsignedShort getID() { return m_id; }
	void setID(UnsignedShort id) { m_id = id; }
	void setPlayerID(UnsignedInt id) { m_playerID = id; }
	void setExecutionFrame(UnsignedInt frame) { m_executionFrame = frame; }
	NetCommandType getNetCommandType() { return m_commandType; }
	void detach();

	void *m_vptr;
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	Int m_referenceCount;
};

// The matched NetWrapperCommandMsg constructor and setters establish this
// genuine 0x38-byte wrapper layout and its command-type value.
class NetWrapperCommandMsg : public NetCommandMsg
{
public:
	NetWrapperCommandMsg();

	void setChunkNumber(UnsignedInt n);
	void setNumChunks(UnsignedInt n);
	void setDataOffset(UnsignedInt off);
	void setData(UnsignedByte *data, UnsignedInt len);
	void setTotalDataLength(UnsignedInt len);
	void setWrappedCommandID(UnsignedShort id);

	UnsignedByte *m_data;
	UnsignedInt m_dataLength;
	UnsignedInt m_dataOffset;
	UnsignedInt m_totalDataLength;
	UnsignedInt m_chunkNumber;
	UnsignedInt m_numChunks;
	UnsignedShort m_wrappedCommandID;
};

// Retail NetCommandRef has m_msg at +0; its matched ctor/dtor and relay
// accessors provide the remaining object-lifetime evidence for this view.
class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);
	~NetCommandRef();

	NetCommandMsg *getCommand() { return m_msg; }
	UnsignedByte getRelay() const { return m_relay; }
	void setRelay(UnsignedByte relay) { m_relay = relay; }

	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
	UnsignedInt m_timeLastSent;
};

struct NetPacketAddress
{
	NetPacketAddress() { ip = 0; port = 0; }

	UnsignedInt ip;
	UnsignedShort port;
};

class NetPacket;
typedef _STL::list<NetPacket *> NetPacketList;

class NetPacket
{
public:
	virtual ~NetPacket();
	NetPacket();
	void init();

	// Public in the real header; keeping this section public preserves the SA
	// decorated ABI required by the retail factory's callers.
	static NetPacketList ConstructBigCommandPacketList(NetCommandRef *ref);

protected:
	static UnsignedInt GetBufferSizeNeededForCommand(NetCommandMsg *msg);
	static void FillBufferWithCommand(UnsignedByte *buffer, NetCommandRef *ref);

public:
	Bool addCommand(NetCommandRef *ref);

	UnsignedByte m_packet[MAX_PACKET_SIZE];
	Int m_packetLen;
	NetPacketAddress m_dest;
	Int m_numCommands;
	NetCommandRef *m_lastCommand;
	UnsignedInt m_lastFrame;
	UnsignedShort m_lastCommandID;
	UnsignedByte m_lastPlayerID;
	UnsignedByte m_lastCommandType;
	UnsignedByte m_lastRelay;
};

void NetPacket::init()
{
	NetPacketAddress dest;
	m_dest = dest;
	m_numCommands = 0;
	m_packetLen = 0;
	m_packet[0] = 0;

	m_lastPlayerID = 0;
	m_lastFrame = 0;
	m_lastCommandID = 0;
	m_lastCommandType = 0;
	m_lastRelay = 0;

	m_lastCommand = 0;
}

NetPacket::NetPacket()
{
	init();
}

extern Bool DoesCommandRequireACommandID(NetCommandType type);
extern UnsignedShort GenerateNextCommandID(void);

NetPacketList NetPacket::ConstructBigCommandPacketList(NetCommandRef *ref)
{
	NetCommandMsg *msg = ref->getCommand();

	if (!DoesCommandRequireACommandID(msg->getNetCommandType()))
	{
		return NetPacketList();
	}

	UnsignedInt bufferSize = GetBufferSizeNeededForCommand(msg);
	UnsignedByte *bigPacketData = 0;

	NetPacketList packetList;

	UnsignedInt bigPacketCurrentOffset = 0;
	bigPacketData = new UnsignedByte[bufferSize];
	FillBufferWithCommand(bigPacketData, ref);

	NetWrapperCommandMsg *wrapperMsg = new NetWrapperCommandMsg;
	UnsignedInt wrapperSize = GetBufferSizeNeededForCommand(wrapperMsg);
	UnsignedInt commandSizePerPacket = MAX_PACKET_SIZE - wrapperSize;

	UnsignedInt numChunks = bufferSize / commandSizePerPacket;
	if ((bufferSize % commandSizePerPacket) > 0)
	{
		++numChunks;
	}
	UnsignedInt currentChunk = 0;

	while (currentChunk < numChunks)
	{
		NetPacket *packet = new NetPacket;

		UnsignedShort dataSizeThisPacket = (UnsignedShort)commandSizePerPacket;
		if ((bufferSize - bigPacketCurrentOffset) < dataSizeThisPacket)
		{
			dataSizeThisPacket = (UnsignedShort)(bufferSize - bigPacketCurrentOffset);
		}

		if (DoesCommandRequireACommandID(wrapperMsg->getNetCommandType()))
		{
			wrapperMsg->setID(GenerateNextCommandID());
		}
		wrapperMsg->setPlayerID(msg->getPlayerID());
		wrapperMsg->setExecutionFrame(msg->getExecutionFrame());

		wrapperMsg->setChunkNumber(currentChunk);
		wrapperMsg->setNumChunks(numChunks);
		wrapperMsg->setDataOffset(bigPacketCurrentOffset);
		wrapperMsg->setData(bigPacketData + bigPacketCurrentOffset, dataSizeThisPacket);
		wrapperMsg->setTotalDataLength(bufferSize);
		wrapperMsg->setWrappedCommandID(msg->getID());

		bigPacketCurrentOffset += dataSizeThisPacket;

		NetCommandRef *newref = new NetCommandRef(wrapperMsg);
		newref->setRelay(newref->getRelay());

		if (packet->addCommand(newref) == false)
		{
		}

		packetList.push_back(packet);

		delete newref;
		newref = 0;

		++currentChunk;
	}

	wrapperMsg->detach();
	wrapperMsg = 0;

	delete bigPacketData;
	bigPacketData = 0;

	return packetList;
}
