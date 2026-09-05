// ?generatePortNumbers@NAT@@IAEXPAPAVGameSlot@@H@Z
// partial score=0.95 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// readable body of ?generatePortNumbers@NAT@@IAEXPAPAVGameSlot@@H@Z:
// Code/GameEngine/Source/GameNetwork/nat.cpp
//
// NAT::generatePortNumbers, 0x00670A30, 448 bytes (present-unmatched in nat.cpp).
//
// Ported beside the tracked source rather than into it. GameSlot's connect info
// (NAT behavior + port) is an 8-byte struct BFME "passes around as a unit" (see
// GameInfo.h's own comment on GameSlotConnectInfo / GameSlot::setState): setPort
// reads the whole struct into a local copy, updates the port half, and writes
// the whole struct back, so retail re-stores the unchanged NAT-behavior dword
// at +0x30 alongside the changed port dword at +0x34 every time. The override
// field at TheWritableGlobalData+0xB1C is tested as a full dword (`!= 0`) but
// only its low word is used as the port value, so it is a 4-byte field here,
// not the 2-byte one OptionsMenu.cpp models at the same address for a different
// accessor.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

#define NULL 0
#define MAX_SLOTS 8

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
struct GameSlotConnectInfo
{
	Int m_nat;
	UnsignedShort m_port;
	UnsignedShort m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
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
	GameSlotConnectInfo m_connectInfo;			///< retail this+0x30
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
struct BfmeGlobalDataFlags
{
	UnsignedByte m_unreconstructed_00[0xb1c];
	Int m_firewallPortOverride;				///< retail this+0xB1C (tested full-width)
};
extern BfmeGlobalDataFlags *TheWritableGlobalData;		///< retail [0x012ED5C8]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NAT.h
class NAT
{
protected:
	void generatePortNumbers(GameSlot **slotList, Int localSlot);

	UnsignedByte m_unreconstructed_00[0xb4];
	UnsignedShort m_startingPortNumber;			///< retail this+0xB4
};

// ?generatePortNumbers@NAT@@IAEXPAPAVGameSlot@@H@Z
void NAT::generatePortNumbers(GameSlot **slotList, Int localSlot)
{
	for (Int i = 0; i < MAX_SLOTS; ++i) {
		if (slotList[i] != NULL) {
			if ((i == localSlot) && (TheWritableGlobalData->m_firewallPortOverride != 0)) {
				UnsignedShort overridePort = (UnsignedShort)TheWritableGlobalData->m_firewallPortOverride;
				slotList[i]->setPort(overridePort);
			} else {
				slotList[i]->setPort((UnsignedShort)(i + m_startingPortNumber));
			}
		}
	}
}
