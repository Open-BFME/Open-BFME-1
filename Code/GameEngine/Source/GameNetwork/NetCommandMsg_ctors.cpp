// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The NetCommandMsg subclass constructors.
//
// Each one identifies itself: it stores its class vptr and stamps its own
// NetCommandType into m_commandType at +0x14 -- the offset CommandRequiresAck
// reads and Connection::doSend tests for FRAMEINFO. Reading the stamped constant
// off a constructor names it, which is how this family was recovered.
//
// The base is the reference's, in the reference's field order, with one BFME
// change: m_executionFrame starts at -1 rather than 0. FrameDataManager's
// addNetCommandMsg reads +8 as the execution frame, so -1 is "not yet bound to a
// frame" instead of "frame zero".
//
//   0x00  vptr
//   0x04  m_timestamp
//   0x08  m_executionFrame     (-1)
//   0x0C  m_playerID
//   0x10  m_id                 (UnsignedShort)
//   0x14  m_commandType
//   0x18  m_referenceCount     (1 -- construction implies an attach)
//
// The base assigns m_commandType = NETCOMMANDTYPE_UNKNOWN last; every derived
// constructor overwrites it, so the compiler elides the base's store and nothing
// is written to +0x14 in a subclass constructor. The standalone base body at
// 0x006735D0 is where that store survives, and it writes -1.
//
// BFME de-pooled this graph like the rest of the netcode, so there is no
// MemoryPoolObject base; the vptr comes from the virtual destructor. Declared
// locally rather than through a shim header because any file under
// reference/shims/ forces the full gate.

typedef int Int;

enum { MAX_SLOTS = 8 };
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

enum NetCommandType
{
	// -1, not 0. The standalone base constructor at 0x006735D0 stores -1 into
	// m_commandType; every derived constructor overwrites it, so the elided store
	// hides that in the subclasses.
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1 = 1,
	NETCOMMANDTYPE_ACKSTAGE2 = 2,
	NETCOMMANDTYPE_FRAMEINFO = 3,
	NETCOMMANDTYPE_GAMECOMMAND = 4,
	NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME = 8,
	NETCOMMANDTYPE_REQUESTFRAMEDATA = 9,
	NETCOMMANDTYPE_PLAYERLEAVE = 10,
	NETCOMMANDTYPE_DESTROYPLAYER = 11,
	NETCOMMANDTYPE_KEEPALIVE = 12,
	NETCOMMANDTYPE_DISCONNECTCHAT = 13,
	NETCOMMANDTYPE_CHAT = 14,
	NETCOMMANDTYPE_PROGRESS = 15,
	NETCOMMANDTYPE_WRAPPER = 18,
	NETCOMMANDTYPE_FILEPROGRESS = 21,
	NETCOMMANDTYPE_DISCONNECTKEEPALIVE = 24,
	NETCOMMANDTYPE_DISCONNECTPLAYER = 25,
	NETCOMMANDTYPE_DISCONNECTVOTE = 26,
	NETCOMMANDTYPE_DISCONNECTFRAME = 27,
	NETCOMMANDTYPE_DISCONNECTSCREENOFF = 28
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	NetCommandMsg();
	virtual ~NetCommandMsg() {}

	void attach();

	UnsignedShort getID() { return m_id; }
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedInt getExecutionFrame() { return m_executionFrame; }

protected:
	UnsignedInt m_timestamp;						// this+0x04
	UnsignedInt m_executionFrame;					// this+0x08
	UnsignedInt m_playerID;							// this+0x0C
	UnsignedShort m_id;								// this+0x10
	NetCommandType m_commandType;					// this+0x14
	Int m_referenceCount;							// this+0x18
};

void NetCommandMsg::attach()
{
	++m_referenceCount;
}

NetCommandMsg::NetCommandMsg()
{
	m_executionFrame = -1;
	m_id = 0;
	m_playerID = 0;
	m_timestamp = 0;
	m_referenceCount = 1;
	m_commandType = NETCOMMANDTYPE_UNKNOWN;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetKeepAliveCommandMsg : public NetCommandMsg
{
public:
	NetKeepAliveCommandMsg();
};

NetKeepAliveCommandMsg::NetKeepAliveCommandMsg() : NetCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_KEEPALIVE;
}

// 0x673AA0, 45 bytes
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetPlayerLeaveCommandMsg : public NetCommandMsg
{
public:
	NetPlayerLeaveCommandMsg();
	UnsignedByte getLeavingPlayerID();
	void setLeavingPlayerID(UnsignedByte v);
	UnsignedByte m_leavingPlayerID;
};

NetPlayerLeaveCommandMsg::NetPlayerLeaveCommandMsg() : NetCommandMsg()
{
	m_leavingPlayerID = 0;
	m_commandType = NETCOMMANDTYPE_PLAYERLEAVE;
}

// 0x673B10, 45 bytes
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDestroyPlayerCommandMsg : public NetCommandMsg
{
public:
	NetDestroyPlayerCommandMsg();
	void setPlayerIndex(UnsignedInt v);
	UnsignedInt getPlayerIndex();
	UnsignedInt m_playerIndex;
};

NetDestroyPlayerCommandMsg::NetDestroyPlayerCommandMsg() : NetCommandMsg()
{
	m_playerIndex = 0;
	m_commandType = NETCOMMANDTYPE_DESTROYPLAYER;
}

// 0x673BD0, 42 bytes
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectKeepAliveCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectKeepAliveCommandMsg();

};

NetDisconnectKeepAliveCommandMsg::NetDisconnectKeepAliveCommandMsg() : NetCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_DISCONNECTKEEPALIVE;
}

// 0x673C20, 48 bytes
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectPlayerCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectPlayerCommandMsg();
	UnsignedInt getDisconnectFrame();
	void setDisconnectFrame(UnsignedInt v);
	UnsignedByte m_disconnectSlot;
	UnsignedInt m_disconnectFrame;
};

NetDisconnectPlayerCommandMsg::NetDisconnectPlayerCommandMsg() : NetCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_DISCONNECTPLAYER;
	m_disconnectSlot = 0;
	m_disconnectFrame = 0;
}

// 0x673CD0, 48 bytes
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectVoteCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectVoteCommandMsg();
	UnsignedByte getSlot();
	UnsignedInt getVoteFrame();
	UnsignedByte m_slot;
	UnsignedInt m_voteFrame;
};

NetDisconnectVoteCommandMsg::NetDisconnectVoteCommandMsg() : NetCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_DISCONNECTVOTE;
	m_slot = 0;
	m_voteFrame = 0;
}

// 0x673D60, 45 bytes
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetProgressCommandMsg : public NetCommandMsg
{
public:
	NetProgressCommandMsg();
	UnsignedByte m_percent;
};

NetProgressCommandMsg::NetProgressCommandMsg() : NetCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_PROGRESS;
	m_percent = 0;
}

// 0x674030, 49 bytes
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetFileProgressCommandMsg : public NetCommandMsg
{
public:
	NetFileProgressCommandMsg();
	UnsignedShort getFileID();
	void setFileID(UnsignedShort v);
	Int getProgress();
	void setProgress(Int v);
	UnsignedShort m_fileID;							// this+0x1C
	Int m_progress;									// this+0x20
};

NetFileProgressCommandMsg::NetFileProgressCommandMsg() : NetCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_FILEPROGRESS;
	m_fileID = 0;
	m_progress = 0;
}

// 0x6740C0, 45 bytes
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectFrameCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectFrameCommandMsg();
	void setDisconnectFrame(UnsignedInt v);
	UnsignedInt m_disconnectFrame;
};

NetDisconnectFrameCommandMsg::NetDisconnectFrameCommandMsg() : NetCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_DISCONNECTFRAME;
	m_disconnectFrame = 0;
}

// 0x674310, 45 bytes
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectScreenOffCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectScreenOffCommandMsg();
	void setNewFrame(UnsignedInt v);
	UnsignedInt m_newFrame;
};

NetDisconnectScreenOffCommandMsg::NetDisconnectScreenOffCommandMsg() : NetCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_DISCONNECTSCREENOFF;
	m_newFrame = 0;
}

// 0x6750E0, 45 bytes
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectChatCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectChatCommandMsg();
	void *m_text;
};

NetDisconnectChatCommandMsg::NetDisconnectChatCommandMsg() : NetCommandMsg()
{
	m_text = 0;
	m_commandType = NETCOMMANDTYPE_DISCONNECTCHAT;
}

// 0x675210, 48 bytes
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetChatCommandMsg : public NetCommandMsg
{
public:
	NetChatCommandMsg();
	void setPlayerMask(Int playerMask);
	void *m_text;
	Int m_playerMask;
};

NetChatCommandMsg::NetChatCommandMsg() : NetCommandMsg()
{
	m_text = 0;
	m_commandType = NETCOMMANDTYPE_CHAT;
	m_playerMask = 0;
}

// 0x006738A0 (53B) and 0x00673840 (69B), type 1 = ACKSTAGE1. BFME adds a third field the reference
// does not have: at +0x20 it keeps the execution frame of the command being
// acknowledged, which the copying constructor takes from the source message and
// the default constructor leaves at -1, matching m_executionFrame's own default.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetAckStage1CommandMsg : public NetCommandMsg
{
public:
	NetAckStage1CommandMsg();
	NetAckStage1CommandMsg(NetCommandMsg *msg);

	void setCommandID(UnsignedShort commandID);
	void setOriginalPlayerID(UnsignedByte originalPlayerID);

	UnsignedShort m_commandID;						// this+0x1C
	UnsignedByte m_originalPlayerID;				// this+0x1E
	UnsignedInt m_originalExecutionFrame;			// this+0x20, BFME-only
};

NetAckStage1CommandMsg::NetAckStage1CommandMsg() : NetCommandMsg()
{
	m_commandID = 0;
	m_originalPlayerID = 0;
	m_originalExecutionFrame = -1;
	m_commandType = NETCOMMANDTYPE_ACKSTAGE1;
}

NetAckStage1CommandMsg::NetAckStage1CommandMsg(NetCommandMsg *msg) : NetCommandMsg()
{
	m_commandID = msg->getID();
	m_commandType = NETCOMMANDTYPE_ACKSTAGE1;
	m_originalPlayerID = msg->getPlayerID();
	m_originalExecutionFrame = msg->getExecutionFrame();
}

// 0x00673DD0, 64 bytes. Declaration order is pinned by the offsets retail writes
// (+0x1C..+0x34); assignment order is the reference's, which is why the stores
// come out as type, numChunks, data, totalDataLength, chunkNumber, dataLength,
// dataOffset, wrappedCommandID.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetWrapperCommandMsg : public NetCommandMsg
{
public:
	NetWrapperCommandMsg();

	UnsignedByte *m_data;							// this+0x1C
	UnsignedInt m_dataLength;						// this+0x20
	UnsignedInt m_dataOffset;						// this+0x24
	UnsignedInt m_totalDataLength;					// this+0x28
	UnsignedInt m_chunkNumber;						// this+0x2C
	UnsignedInt m_numChunks;						// this+0x30
	UnsignedShort m_wrappedCommandID;				// this+0x34
};

NetWrapperCommandMsg::NetWrapperCommandMsg() : NetCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_WRAPPER;
	m_numChunks = 0;
	m_data = 0;
	m_totalDataLength = 0;
	m_chunkNumber = 0;
	m_dataLength = 0;
	m_dataOffset = 0;
	m_wrappedCommandID = 0;
}

// 0x006737A0 (47B) and 0x00673740 (68B), type ACKBOTH. Same three-field shape as AckStage1.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetAckBothCommandMsg : public NetCommandMsg
{
public:
	NetAckBothCommandMsg();
	NetAckBothCommandMsg(NetCommandMsg *msg);

	void setCommandID(UnsignedShort commandID);
	void setOriginalPlayerID(UnsignedByte originalPlayerID);

	UnsignedShort m_commandID;						// this+0x1C
	UnsignedByte m_originalPlayerID;				// this+0x1E
	UnsignedInt m_originalExecutionFrame;			// this+0x20, BFME-only
};

NetAckBothCommandMsg::NetAckBothCommandMsg() : NetCommandMsg()
{
	m_commandID = 0;
	m_originalPlayerID = 0;
	m_originalExecutionFrame = -1;
	m_commandType = NETCOMMANDTYPE_ACKBOTH;
}

NetAckBothCommandMsg::NetAckBothCommandMsg(NetCommandMsg *msg) : NetCommandMsg()
{
	m_commandID = msg->getID();
	m_commandType = NETCOMMANDTYPE_ACKBOTH;
	m_originalPlayerID = msg->getPlayerID();
	m_originalExecutionFrame = msg->getExecutionFrame();
}


// 0x006739B0 (51B) and 0x00673950 (70B), type ACKSTAGE2. Same three-field shape as AckStage1.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetAckStage2CommandMsg : public NetCommandMsg
{
public:
	NetAckStage2CommandMsg();
	NetAckStage2CommandMsg(NetCommandMsg *msg);

	void setCommandID(UnsignedShort commandID);
	void setOriginalPlayerID(UnsignedByte originalPlayerID);

	UnsignedShort m_commandID;						// this+0x1C
	UnsignedByte m_originalPlayerID;				// this+0x1E
	UnsignedInt m_originalExecutionFrame;			// this+0x20, BFME-only
};

NetAckStage2CommandMsg::NetAckStage2CommandMsg() : NetCommandMsg()
{
	m_commandID = 0;
	m_originalPlayerID = 0;
	m_originalExecutionFrame = -1;
	m_commandType = NETCOMMANDTYPE_ACKSTAGE2;
}

NetAckStage2CommandMsg::NetAckStage2CommandMsg(NetCommandMsg *msg) : NetCommandMsg()
{
	m_commandID = msg->getID();
	m_commandType = NETCOMMANDTYPE_ACKSTAGE2;
	m_originalPlayerID = msg->getPlayerID();
	m_originalExecutionFrame = msg->getExecutionFrame();
}

void NetAckBothCommandMsg::setCommandID(UnsignedShort commandID)
{
	m_commandID = commandID;
}

void NetAckBothCommandMsg::setOriginalPlayerID(UnsignedByte originalPlayerID)
{
	m_originalPlayerID = originalPlayerID;
}

void NetAckStage1CommandMsg::setCommandID(UnsignedShort commandID)
{
	m_commandID = commandID;
}

void NetAckStage1CommandMsg::setOriginalPlayerID(UnsignedByte originalPlayerID)
{
	m_originalPlayerID = originalPlayerID;
}

void NetAckStage2CommandMsg::setCommandID(UnsignedShort commandID)
{
	m_commandID = commandID;
}

void NetAckStage2CommandMsg::setOriginalPlayerID(UnsignedByte originalPlayerID)
{
	m_originalPlayerID = originalPlayerID;
}

UnsignedByte NetPlayerLeaveCommandMsg::getLeavingPlayerID()
{
	return m_leavingPlayerID;
}

void NetPlayerLeaveCommandMsg::setLeavingPlayerID(UnsignedByte v)
{
	m_leavingPlayerID = v;
}

void NetDestroyPlayerCommandMsg::setPlayerIndex(UnsignedInt v)
{
	m_playerIndex = v;
}

UnsignedInt NetDestroyPlayerCommandMsg::getPlayerIndex()
{
	return m_playerIndex;
}

void NetDisconnectPlayerCommandMsg::setDisconnectFrame(UnsignedInt v)
{
	m_disconnectFrame = v;
}

UnsignedByte NetDisconnectVoteCommandMsg::getSlot()
{
	return m_slot;
}

UnsignedInt NetDisconnectVoteCommandMsg::getVoteFrame()
{
	return m_voteFrame;
}

void NetDisconnectFrameCommandMsg::setDisconnectFrame(UnsignedInt v)
{
	m_disconnectFrame = v;
}

void NetDisconnectScreenOffCommandMsg::setNewFrame(UnsignedInt v)
{
	m_newFrame = v;
}


UnsignedInt NetDisconnectPlayerCommandMsg::getDisconnectFrame() { return m_disconnectFrame; }

UnsignedShort NetFileProgressCommandMsg::getFileID() { return m_fileID; }
void NetFileProgressCommandMsg::setFileID(UnsignedShort v) { m_fileID = v; }
Int NetFileProgressCommandMsg::getProgress() { return m_progress; }
void NetFileProgressCommandMsg::setProgress(Int v) { m_progress = v; }

// NetFileCommandMsg carries the file payload. setFileData at 0x00673FA0 pins the
// two fields the accessors below read: it stores the length at +0x24 and the
// freshly allocated buffer at +0x20, in that order. Only the portable form of
// the path is stored -- getRealFilename converts on the way out, which is what
// puts the payload pair at +0x20/+0x24 rather than the reference's +0x24/+0x28.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetFileCommandMsg : public NetCommandMsg
{
public:
	UnsignedInt getFileLength();
	UnsignedByte *getFileData();

	void *m_portableFilename;						// this+0x1C
	UnsignedByte *m_data;							// this+0x20
	UnsignedInt m_dataLength;						// this+0x24
};

UnsignedInt NetFileCommandMsg::getFileLength() { return m_dataLength; }
UnsignedByte *NetFileCommandMsg::getFileData() { return m_data; }

// NetFileAnnounceCommandMsg announces a file to a subset of players. Its two
// scalars are packed rather than aligned to dwords -- the id is a word at +0x20
// and the mask a byte immediately after it at +0x22.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetFileAnnounceCommandMsg : public NetCommandMsg
{
public:
	UnsignedShort getFileID();
	void setFileID(UnsignedShort v);
	UnsignedByte getPlayerMask();
	void setPlayerMask(UnsignedByte v);

	void *m_portableFilename;						// this+0x1C
	UnsignedShort m_fileID;							// this+0x20
	UnsignedByte m_playerMask;						// this+0x22
};

UnsignedShort NetFileAnnounceCommandMsg::getFileID() { return m_fileID; }
void NetFileAnnounceCommandMsg::setFileID(UnsignedShort v) { m_fileID = v; }
UnsignedByte NetFileAnnounceCommandMsg::getPlayerMask() { return m_playerMask; }
void NetFileAnnounceCommandMsg::setPlayerMask(UnsignedByte v) { m_playerMask = v; }

// Command types 8 and 9 have no counterpart in the reference: BFME added them.
// Retail ships without RTTI, so the class names below are not recovered from the
// image -- they are built from the type constant each constructor stamps, in the
// BFMENet* style the other BFME-only additions in this tree already use. The
// layouts and the type constants ARE from the image.

// Stamps 8. m_leaveFrame starts at -1 rather than 0, the same "not yet bound to a
// frame" convention the base uses for m_executionFrame -- which is what makes the
// +0x20 field the frame and the +0x1C field the player.
class BFMENetInformPlayerLeaveFrameCommandMsg : public NetCommandMsg
{
public:
	BFMENetInformPlayerLeaveFrameCommandMsg();
	Int getLeavingPlayerID();
	void setLeavingPlayerID(Int playerID);
	UnsignedInt getLeaveFrame();
	void setLeaveFrame(UnsignedInt frame);
	void setLeaveInfo(UnsignedInt frame, Int playerID);

	Int m_leavingPlayerID;							// this+0x1C
	UnsignedInt m_leaveFrame;						// this+0x20
};

BFMENetInformPlayerLeaveFrameCommandMsg::BFMENetInformPlayerLeaveFrameCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME;
	m_leavingPlayerID = 0;
	m_leaveFrame = -1;
}

Int BFMENetInformPlayerLeaveFrameCommandMsg::getLeavingPlayerID() { return m_leavingPlayerID; }

// Re-stamps the command type on the way in. Nothing else in the family does
// that, and the constructor has already set it -- but the store is there in
// retail, ahead of the field write.
void BFMENetInformPlayerLeaveFrameCommandMsg::setLeavingPlayerID(Int playerID)
{
	m_commandType = NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME;
	m_leavingPlayerID = playerID;
}
UnsignedInt BFMENetInformPlayerLeaveFrameCommandMsg::getLeaveFrame() { return m_leaveFrame; }
void BFMENetInformPlayerLeaveFrameCommandMsg::setLeaveFrame(UnsignedInt frame) { m_leaveFrame = frame; }

// Retail assigns the frame first and the player second even though the frame is
// the second parameter, which is why the two stores read [ecx+0x1c] = arg2 then
// [ecx+0x20] = arg1.
void BFMENetInformPlayerLeaveFrameCommandMsg::setLeaveInfo(UnsignedInt frame, Int playerID)
{
	m_leavingPlayerID = playerID;
	m_leaveFrame = frame;
}

// Stamps 9. Both fields start at zero, so neither carries the -1 sentinel and the
// pairing below follows type 8's rather than being pinned by the constructor.
class BFMENetRequestFrameDataCommandMsg : public NetCommandMsg
{
public:
	BFMENetRequestFrameDataCommandMsg();
	Int getRequestedPlayerID();
	UnsignedInt getRequestedFrame();
	void setRequestedPlayerID(Int playerID);
	void setRequestedFrame(UnsignedInt frame);

	Int m_requestedPlayerID;						// this+0x1C
	UnsignedInt m_requestedFrame;					// this+0x20
};

BFMENetRequestFrameDataCommandMsg::BFMENetRequestFrameDataCommandMsg()
{
	m_commandType = NETCOMMANDTYPE_REQUESTFRAMEDATA;
	m_requestedPlayerID = 0;
	m_requestedFrame = 0;
}

Int BFMENetRequestFrameDataCommandMsg::getRequestedPlayerID() { return m_requestedPlayerID; }
UnsignedInt BFMENetRequestFrameDataCommandMsg::getRequestedFrame() { return m_requestedFrame; }
void BFMENetRequestFrameDataCommandMsg::setRequestedPlayerID(Int playerID) { m_requestedPlayerID = playerID; }
void BFMENetRequestFrameDataCommandMsg::setRequestedFrame(UnsignedInt frame) { m_requestedFrame = frame; }

void NetChatCommandMsg::setPlayerMask(Int playerMask) { m_playerMask = playerMask; }


// BFME-only command type 22 -- one of the two the shim's enum leaves unnamed.
// It is not a disconnect-menu command despite sitting in that numeric range: it
// carries the eight per-slot frame ratios BFMEConnectionManager::
// computePlayerFrameRatios (0x00666000) computes, and NetPacket's dispatcher
// tests for it immediately after FRAMEINFO rather than down with the disconnect
// types, which is where per-frame traffic sits.
class BFMENetPlayerFrameRatiosCommandMsg : public NetCommandMsg
{
public:
	void setPlayerFrameRatios(const Int *ratios);

	Int m_ratios[MAX_SLOTS];						// this+0x1C .. +0x38
};

void BFMENetPlayerFrameRatiosCommandMsg::setPlayerFrameRatios(const Int *ratios)
{
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		m_ratios[i] = ratios[i];
	}
}
