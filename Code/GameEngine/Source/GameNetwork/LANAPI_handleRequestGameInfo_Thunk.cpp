// cl: /DNDEBUG /MD /EHs-c-

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

extern "C" __declspec(dllimport) WideChar * __cdecl wcsncpy(WideChar *, const WideChar *, unsigned int);

enum { g_lanGameNameLength = 16, g_lanMaxOptionsLength = 406 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeStringData
{
public:
	unsigned char m_unreconstructed_00[8];
	WideChar m_stringdata[1];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	~UnicodeString() { releaseBuffer(); }

	const WideChar *str() const
	{
		return m_data ? m_data->m_stringdata : L"";
	}

protected:
	void releaseBuffer();

private:
	UnicodeStringData *m_data;
};

#pragma pack(push, 1)
struct LANAddress
{
	UnsignedInt m_ip;
	unsigned short m_port;
};
#pragma pack(pop)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo
{
public:
	UnicodeString getName();

	unsigned char m_unreconstructed_00[0x0D];
	Bool m_inProgress;
	unsigned char m_unreconstructed_0e[0x88 - 0x0E];
	LANAddress m_hostAddress;
	unsigned char m_unreconstructed_8e[0x3A4 - 0x8E];
	Bool m_isDirectConnect;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkInterface.h
class NetworkInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual Bool isPacketRouter() = 0;
};

extern NetworkInterface *TheNetwork;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
struct LANMessage
{
	enum { MSG_GAME_ANNOUNCE = 1 };

	UnsignedInt m_type;
	unsigned char m_unreconstructed_04[0x22 - 0x04];
	struct
	{
		WideChar m_gameName[g_lanGameNameLength + 1];
		Bool m_inProgress;
		Bool m_isDirectConnect;
		char m_options[g_lanMaxOptionsLength];
	} m_gameInfo;
};

void __cdecl writeLANGameInfo(const LANGameInfo *, char *, unsigned int);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
class LANAPI
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void fillInLANMessage(LANMessage *) = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual const LANAddress *getLocalAddress() = 0;

protected:
	void handleRequestGameInfo(LANMessage *, UnsignedInt);
	void sendMessage(LANMessage *, UnsignedInt);

private:
	unsigned char m_unreconstructed_04[0x40 - 0x04];
	LANGameInfo *m_currentGame;
};

// ?handleRequestGameInfo@LANAPI@@IAEXPAULANMessage@@I@Z
void LANAPI::handleRequestGameInfo(LANMessage *, UnsignedInt senderIP)
{
	LANGameInfo *game = m_currentGame;
	if (game)
	{
		const LANAddress *localAddress = getLocalAddress();
		if ((game->m_hostAddress.m_ip == localAddress->m_ip &&
			game->m_hostAddress.m_port == localAddress->m_port) ||
			(m_currentGame->m_inProgress && TheNetwork && TheNetwork->isPacketRouter()))
		{
			LANMessage reply;
			fillInLANMessage(&reply);
			reply.m_type = LANMessage::MSG_GAME_ANNOUNCE;
			writeLANGameInfo(m_currentGame, reply.m_gameInfo.m_options, g_lanMaxOptionsLength);
			wcsncpy(reply.m_gameInfo.m_gameName, m_currentGame->getName().str(), g_lanGameNameLength);
			reply.m_gameInfo.m_gameName[g_lanGameNameLength] = 0;
			reply.m_gameInfo.m_inProgress = m_currentGame->m_inProgress;
			reply.m_gameInfo.m_isDirectConnect = m_currentGame->m_isDirectConnect;
			sendMessage(&reply, senderIP);
		}
	}
}
