// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "../../../../reference/shims/stringinline/StringInline.h"

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#pragma pack(push, 1)
struct LANMessage
{
	UnsignedByte padding[0x22];
	char options[0x197];
};

struct BfmeNetAddress
{
	UnsignedInt ip;
	unsigned short port;
};
#pragma pack(pop)

struct BfmeGameSlot
{
	BfmeNetAddress address;
	UnsignedByte padding[0x60];
};

class BfmeGameInfo
{
public:
	Bool isGameInProgress() const
	{
		return *(const UnsignedByte *)((const char *)this + 0x0d) != 0;
	}

	BfmeGameSlot *slots()
	{
		return (BfmeGameSlot *)((char *)this + 0x88);
	}
};

class BfmeLANOptionsCallbacks
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
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void onGameOptions(BfmeNetAddress *sender, UnsignedInt player,
		AsciiString options);
};

class LANAPI
{
public:
	protected:
	void handleGameOptions(LANMessage *msg, UnsignedInt senderIP);

	UnsignedByte padding[0x3d];
	Bool m_inLobby;
	BfmeGameInfo *m_currentGame;
};

void LANAPI::handleGameOptions(LANMessage *msg, UnsignedInt senderIP)
{
	if (!m_inLobby && m_currentGame && !m_currentGame->isGameInProgress())
	{
		BfmeNetAddress *sender = (BfmeNetAddress *)senderIP;
		int player = 0;
		BfmeGameSlot *slot = m_currentGame->slots();
		do
		{
			if (slot->address.ip == sender->ip &&
				slot->address.port == sender->port)
			{
				((BfmeLANOptionsCallbacks *)this)->onGameOptions(
					sender, player, AsciiString(msg->options));
				break;
			}
			++player;
			slot = (BfmeGameSlot *)((char *)slot + 0x68);
		}
		while (player < 8);
	}
}
