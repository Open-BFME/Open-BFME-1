// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// NetGameCommandMsg's own constructor. Base layout and field order follow
// NetCommandMsg_ctors.cpp; kept in its own TU so the "new NetGameCommandMsg"
// call site in NetPacket_readGameMessage.cpp cannot inline this body.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_GAMECOMMAND = 4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	// Defined in-class, so it is implicitly inline: retail inlines this base ctor
	// into the derived ctor below, but the out-of-line copy is already matched at
	// 0x006735D0 in NetCommandMsg_ctors.cpp. An in-class body gives the inlining
	// without emitting a second external definition of the same mangled name.
	NetCommandMsg()
	{
		m_executionFrame = -1;
		m_id = 0;
		m_playerID = 0;
		m_timestamp = 0;
		m_referenceCount = 1;
		m_commandType = NETCOMMANDTYPE_UNKNOWN;
	}
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

// NetCommandMsg::NetCommandMsg is deliberately NOT defined here -- it is already
// matched at 0x006735D0 in NetCommandMsg_ctors.cpp. Defining it again would be an
// ODR violation and a second ledger claim on one mangled name; the declaration
// above is enough for the base-ctor call below to resolve at link time.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetGameCommandMsg : public NetCommandMsg
{
public:
	NetGameCommandMsg();

	UnsignedInt m_gameMessageFields[5];			// this+0x1C .. +0x2F
};

// ??0NetGameCommandMsg@@QAE@XZ
NetGameCommandMsg::NetGameCommandMsg() : NetCommandMsg()
{
	m_gameMessageFields[1] = 0;
	m_gameMessageFields[0] = 0;
	m_gameMessageFields[2] = 0;
	m_commandType = NETCOMMANDTYPE_GAMECOMMAND;
	m_gameMessageFields[3] = 0;
	m_gameMessageFields[4] = 0;
}
