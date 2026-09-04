// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include <wchar.h>
#include "../../../../reference/shims/stringinline/StringInline.h"

typedef unsigned int UnsignedInt;

#pragma pack(push, 1)
struct LANMessage
{
	unsigned char m_pad22[0x22];
	unsigned short gameName[20];
	UnsignedInt playerIP;
	unsigned short playerPort;
	UnsignedInt reason;
};
#pragma pack(pop)

struct BfmeAddress
{
	UnsignedInt ip;
	unsigned short port;
};

class LANGameInfo;

class LANAPI
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void onGameJoin(UnsignedInt reason, LANGameInfo *game,
		LANMessage *message);
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual LANGameInfo *lookupGame(UnicodeString gameName);
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual BfmeAddress *getLocalAddress();

	protected:
	void handleJoinDeny(LANMessage *msg, UnsignedInt senderIP);

	unsigned char m_pad24[0x20];
	UnsignedInt m_pendingAction;
	UnsignedInt m_expiration;
};

void LANAPI::handleJoinDeny(LANMessage *msg, UnsignedInt senderIP)
{
	BfmeAddress *address = getLocalAddress();
	if (msg->playerIP != address->ip)
		return;

	address = getLocalAddress();
	if (msg->playerPort != address->port)
		return;

	if (m_pendingAction == 1)
	{
		onGameJoin(msg->reason,
			lookupGame(UnicodeString(msg->gameName)), msg);
		m_pendingAction = 0;
		m_expiration = 0;
	}
}
