// cl: /DNDEBUG /MD /GX
// readable body of ?setIsActive@LANAPI@@UAEX_N@Z: Code/GameEngine/Source/GameNetwork/lanapi.cpp

// Retail 0x00685320, LANAPI vtable slot 9 (table at 0x0111AF50).  BFME keeps
// the Zero Hour body, but its LANMessage is 0x1DC bytes and the recovered LANAPI
// layout puts m_inLobby, m_currentGame and m_isActive at +0x3D, +0x40 and +0x58.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum { LANMSG_INACTIVE = 0x10 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
struct LANMessage
{
	Int LANMessageType;
	unsigned char m_bfmeRest[0x1DC - sizeof(Int)];
};

class LANAPI
{
public:
	virtual void _bfme_slot00(void) = 0;
	virtual void _bfme_slot01(void) = 0;
	virtual void _bfme_slot02(void) = 0;
	virtual void _bfme_slot03(void) = 0;
	virtual void _bfme_slot04(void) = 0;
	virtual void _bfme_slot05(void) = 0;
	virtual void _bfme_slot06(void) = 0;
	virtual void _bfme_slot07(void) = 0;
	virtual void _bfme_slot08(void) = 0;
	virtual void setIsActive(Bool isActive); // slot 9
	virtual void _bfme_slot10(void) = 0;
	virtual void _bfme_slot11(void) = 0;
	virtual void _bfme_slot12(void) = 0;
	virtual void _bfme_slot13(void) = 0;
	virtual void _bfme_slot14(void) = 0;
	virtual void _bfme_slot15(void) = 0;
	virtual void _bfme_slot16(void) = 0;
	virtual void _bfme_slot17(void) = 0;
	virtual void _bfme_slot18(void) = 0;
	virtual void _bfme_slot19(void) = 0;
	virtual void _bfme_slot20(void) = 0;
	virtual void _bfme_slot21(void) = 0;
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual void _bfme_slot24(void) = 0;
	virtual void _bfme_slot25(void) = 0;
	virtual void _bfme_slot26(void) = 0;
	virtual void _bfme_slot27(void) = 0;
	virtual void _bfme_slot28(void) = 0;
	virtual void _bfme_slot29(void) = 0;
	virtual void _bfme_slot30(void) = 0;
	virtual void _bfme_slot31(void) = 0;
	virtual void _bfme_slot32(void) = 0;
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_slot34(void) = 0;
	virtual void _bfme_slot35(void) = 0;
	virtual void _bfme_slot36(void) = 0;
	virtual void _bfme_slot37(void) = 0;
	virtual void _bfme_slot38(void) = 0;
	virtual void _bfme_slot39(void) = 0;
	virtual void _bfme_slot40(void) = 0;
	virtual void _bfme_slot41(void) = 0;
	virtual void _bfme_slot42(void) = 0;
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual void _bfme_slot45(void) = 0;
	virtual void _bfme_slot46(void) = 0;
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void fillInLANMessage(LANMessage *msg) = 0; // slot 49, +0xC4

protected:
	void sendMessage(LANMessage *msg, UnsignedInt ip = 0); // ILT 0x0002B599

	unsigned char m_bfmeHeadA[0x3D - 4];
	Bool m_inLobby; // +0x3D
	unsigned char m_bfmeHeadB[0x40 - 0x3E];
	void *m_currentGame; // +0x40
	unsigned char m_bfmeHeadC[0x58 - 0x44];
	Bool m_isActive; // +0x58
};

// ?setIsActive@LANAPI@@UAEX_N@Z
void LANAPI::setIsActive(Bool isActive)
{
	if (isActive != m_isActive)
	{
		if (isActive == false)
		{
			if (m_inLobby == false && m_currentGame != 0)
			{
				LANMessage msg;
				fillInLANMessage(&msg);
				msg.LANMessageType = LANMSG_INACTIVE;
				sendMessage(&msg);
			}
		}
	}

	m_isActive = isActive;
}
