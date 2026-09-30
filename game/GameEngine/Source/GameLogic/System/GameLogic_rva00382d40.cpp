// cl: /DNDEBUG /MD /EHsc
// Retail 0x00382D40: __stdcall(int, int) query reached only through ILT 0x00047A46.
// While game-logic mode +0x10C is 1 or 5, answers 3 when TheNetwork is absent or
// its vtable slot 44 (+0xB0) reports true; otherwise answers 3 once the unsigned
// counter at +0x3C reaches 6, else 1. Owner and meaning unproven: opaque name.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkInterface.h
class NetworkInterface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void slot36(void) = 0;
	virtual void slot37(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot41(void) = 0;
	virtual void slot42(void) = 0;
	virtual void slot43(void) = 0;
	virtual bool slot44(void) = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	char m_pad00[0x3c];
	unsigned int m_field3C;
	char m_pad40[0x10c - 0x40];
	int m_field10C;
};

extern GameLogic *TheBfmeGameLogic;
extern NetworkInterface *TheNetwork;

// ?Rva00382D40Query@@YGHHH@Z
int __stdcall Rva00382D40Query(int, int)
{
	int result = 1;
	int mode = TheBfmeGameLogic->m_field10C;
	if ((mode == 1 || mode == 5) && (TheNetwork == 0 || TheNetwork->slot44()))
		result = 3;
	else if (TheBfmeGameLogic->m_field3C >= 6)
		result = 3;
	return result;
}
