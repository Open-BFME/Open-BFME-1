// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc-

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

enum NetCommandType
{
	NETCOMMANDTYPE_DISCONNECTSCREENOFF = 28
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetCommandMsg
{
public:
	virtual ~NetCommandMsg();
	void detach();

	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	Int m_referenceCount;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectScreenOffCommandMsg : public NetCommandMsg
{
public:
	enum MagicEnum { GLUE_NOT_IMPLEMENTED = 0 };
	static void *operator new(unsigned int size, MagicEnum)
	{
		return ::operator new(size);
	}
	static void operator delete(void *pointer, MagicEnum)
	{
		::operator delete(pointer);
	}

	NetDisconnectScreenOffCommandMsg();
	void setNewFrame(UnsignedInt frame);
	UnsignedInt m_newFrame;
	void setPlayerID(UnsignedInt playerID)
	{
		m_playerID = playerID;
	}
	NetCommandType getNetCommandType() const
	{
		return m_commandType;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	UnsignedInt getLocalPlayerID();
	void sendLocalCommand(NetCommandMsg *message, UnsignedByte relay);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame() const
	{
		return *(const UnsignedInt *)((const char *)this + 0x3C);
	}
};

extern GameLogic *TheGameLogic;

bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

class BFMEDisconnectManager
{
public:
	void sendDisconnectScreenOff(Int slot, void *conMgr);
};

void BFMEDisconnectManager::sendDisconnectScreenOff(Int slot, void *conMgr)
{
	if (slot < 0 || slot >= 8)
		return;

	NetDisconnectScreenOffCommandMsg *message = new(NetDisconnectScreenOffCommandMsg::GLUE_NOT_IMPLEMENTED) NetDisconnectScreenOffCommandMsg;

	message->setNewFrame(TheGameLogic->getFrame());
	ConnectionManager *connectionManager = (ConnectionManager *)conMgr;
	message->setPlayerID(connectionManager->getLocalPlayerID());
	if (DoesCommandRequireACommandID(message->getNetCommandType()))
		message->m_id = GenerateNextCommandID();
	connectionManager->sendLocalCommand(message, 0xFF);
	message->detach();
}
