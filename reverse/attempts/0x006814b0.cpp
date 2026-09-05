// ConstructBigCommandPacketList
// partial score=0.75 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// readable body of ?ConstructBigCommandPacketList@NetPacket@@KA?AV?$list@PAVNetPacket@@V?$allocator@PAVNetPacket@@@_STL@@@_STL@@PAVNetCommandRef@@@Z
// Code/GameEngine/Source/GameNetwork/NetPacket.cpp:152

// NetPacket::ConstructBigCommandPacketList, retail 0x006814B0, 725 bytes.
// A static method (no ecx, hidden struct-return pointer + one arg, "ret" with
// no immediate == __cdecl-style cleanup) that splits an oversized command into
// MAX_PACKET_SIZE-sized NetWrapperCommandMsg-wrapped NetPacket chunks.
//
// Reuses the NetPacket / NetCommandRef / NetCommandMsg layouts from
// NetPacket_addWrapperCommand.cpp. NetWrapperCommandMsg's extra fields are
// only ever touched through its already-matched setters
// (Code/GameEngine/Source/GameNetwork/NetCommandMsg.cpp), so no layout for
// them is needed here -- setPlayerID/setExecutionFrame are the only two
// inlined as direct NetCommandMsg field writes (+0x0C, +0x08), matching
// retail exactly.
//
// GetBufferSizeNeededForCommand and FillBufferWithCommand are already
// ledgered (the latter still a gen-dump body, which resolves the call the
// same as clean C++). NetPacketList is the real STLport std::list<NetPacket*>
// per NetPacket.h -- the empty-list early return and the final
// copy-construct-into-return-slot + local destructor are exactly STLport's
// codegen for "return NetPacketList();" and "return packetList;".

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum { MAX_PACKET_SIZE = 0x1DC };

enum NetCommandType
{
	NETCOMMANDTYPE_ACKBOTH = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
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
	void detach();		// ILT thunk 0x000200A4, matched

	void *m_vptr;									// this+0x00
	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;								// this+0x10
	NetCommandType m_commandType;					// this+0x14
	Int m_referenceCount;							// this+0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetWrapperCommandMsg : public NetCommandMsg
{
public:
	NetWrapperCommandMsg();		// ILT thunk 0x0002A586, matched (pinned)

	void setChunkNumber(UnsignedInt n);			// matched, NetCommandMsg.cpp
	void setNumChunks(UnsignedInt n);				// matched, NetCommandMsg.cpp
	void setDataOffset(UnsignedInt off);			// matched, NetCommandMsg.cpp
	void setData(UnsignedByte *data, UnsignedInt len);	// matched, NetCommandMsg.cpp
	void setTotalDataLength(UnsignedInt len);		// matched, NetCommandMsg.cpp
	void setWrappedCommandID(UnsignedShort id);	// matched, NetCommandMsg.cpp
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);		// ILT thunk 0x000079E6, matched
	~NetCommandRef();						// ILT thunk 0x00038960, matched

	NetCommandMsg *getCommand() { return m_msg; }
	UnsignedByte getRelay() const { return m_relay; }
	void setRelay(UnsignedByte relay) { m_relay = relay; }

	NetCommandMsg *m_msg;							// this+0x00
	NetCommandRef *m_next;							// this+0x04
	NetCommandRef *m_prev;							// this+0x08
	UnsignedByte m_relay;							// this+0x0C
	UnsignedInt m_timeLastSent;						// this+0x10
};

struct NetPacketAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
public:
	NetPacket();							// installs vtable 0x0111A84C
	virtual ~NetPacket();

	Bool addCommand(NetCommandRef *ref);	// ILT thunk 0x00049CE7, matched

protected:
	static _STL::list<NetPacket *> ConstructBigCommandPacketList(NetCommandRef *ref);

public:
	UnsignedByte m_packet[0x1DC];					// this+0x004
	Int m_packetLen;								// this+0x1E0
	NetPacketAddress m_dest;						// this+0x1E4
	Int m_numCommands;								// this+0x1EC
	NetCommandRef *m_lastCommand;					// this+0x1F0
	UnsignedInt m_lastFrame;						// this+0x1F4
	UnsignedShort m_lastCommandID;					// this+0x1F8
	UnsignedByte m_lastPlayerID;					// this+0x1FA
	UnsignedByte m_lastCommandType;					// this+0x1FB
	UnsignedByte m_lastRelay;						// this+0x1FC
};

typedef _STL::list<NetPacket *> NetPacketList;

extern Bool DoesCommandRequireACommandID(NetCommandType type);				// pinned 0x00015B72
extern UnsignedShort GenerateNextCommandID(void);								// pinned 0x00030558
extern UnsignedInt GetBufferSizeNeededForCommand(NetCommandMsg *msg);			// ?GetBufferSizeNeededForCommand@NetPacket@@KAIPAVNetCommandMsg@@@Z, matched
extern void FillBufferWithCommand(UnsignedByte *buffer, NetCommandRef *ref);	// still a gen-dump body, resolves fine

// ?ConstructBigCommandPacketList@NetPacket@@KA?AV?$list@PAVNetPacket@@V?$allocator@PAVNetPacket@@@_STL@@@_STL@@PAVNetCommandRef@@@Z
NetPacketList NetPacket::ConstructBigCommandPacketList(NetCommandRef *ref)
{
	NetCommandMsg *msg = ref->getCommand();

	if (!DoesCommandRequireACommandID(msg->getNetCommandType()))
	{
		return NetPacketList();
	}

	UnsignedInt bufferSize = GetBufferSizeNeededForCommand(msg);
	UnsignedByte *bigPacketData = NULL;

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
			// DEBUG_LOG compiled out in release
		}

		packetList.push_back(packet);

		delete newref;
		newref = NULL;

		++currentChunk;
	}
	wrapperMsg->detach();
	wrapperMsg = NULL;

	delete bigPacketData;
	bigPacketData = NULL;

	return packetList;
}
