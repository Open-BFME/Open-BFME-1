// ?generatePortNumbers@NAT@@IAEXPAPAVGameSlot@@H@Z
// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

#define NULL 0
#define MAX_SLOTS 8

// BFME stores the NAT behavior dword before the port and padding dword.
struct GameSlotConnectInfo
{
	Int m_nat;
	UnsignedShort m_port;
	UnsignedShort m_pad;
};

class GameSlot
{
public:
	void setPort(UnsignedShort port)
	{
		GameSlotConnectInfo temp = m_connectInfo;
		temp.m_port = port;
		m_connectInfo = temp;
	}

	UnsignedByte m_unreconstructed_00[0x30];
	GameSlotConnectInfo m_connectInfo;
};

struct BfmeGlobalDataFlags
{
	UnsignedByte m_unreconstructed_00[0xb1c];
	Int m_firewallPortOverride;
};

extern BfmeGlobalDataFlags *TheWritableGlobalData;

class NAT
{
protected:
	void generatePortNumbers(GameSlot **slotList, Int localSlot);

	UnsignedByte m_unreconstructed_00[0xb4];
	UnsignedShort m_startingPortNumber;
};

void NAT::generatePortNumbers(GameSlot **slotList, Int localSlot)
{
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if (slotList[i] != NULL) {
			if ((i == localSlot) && (TheWritableGlobalData->m_firewallPortOverride != 0)) {
				UnsignedShort overridePort = (UnsignedShort)TheWritableGlobalData->m_firewallPortOverride;
				GameSlotConnectInfo temp = slotList[i]->m_connectInfo;
				temp.m_port = overridePort;
				slotList[i]->m_connectInfo = temp;
			} else {
				slotList[i]->setPort((UnsignedShort)(i + m_startingPortNumber));
			}
		}
	}
}
