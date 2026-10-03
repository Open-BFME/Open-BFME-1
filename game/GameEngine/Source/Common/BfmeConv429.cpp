// cl: /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

// The call at +0x0009 goes through the ILT entry at 0x00046538, which is
// GameWindow::winGetUserData()'s thunk; the body it reaches is matched at
// 0x00478C70.  Retail loads the key into ecx and returns the user data in
// eax, which is what the thiscall member spells, so the call uses the real
// name.  The header is included for its declaration rather than redeclared.
#include "GameClient/GameWindow.h"

// Retail's global at 0x012F12CC is EA's DisplayStringManager; defined once in
// GameClient/DisplayStringManager.cpp.  The local view below only exists to spell
// the slots this TU calls, so the use casts.
class DisplayStringManager;

class BfmeMakerAWB
{
public:
	virtual void bfmeSpareAWB0();
	virtual void bfmeSpareAWB1();
	virtual void bfmeSpareAWB2();
	virtual void bfmeSpareAWB3();
	virtual void bfmeSpareAWB4();
	virtual void bfmeSpareAWB5();
	virtual void bfmeSpareAWB6();
	virtual void bfmeSpareAWB7();
	virtual void bfmeSpareAWB8();
	virtual void *bfmeMakeAWB();
};

extern DisplayStringManager *TheDisplayStringManager;

struct BfmeNodeAWB
{
	unsigned char m_bfmeHead[0x28];
	bool m_bfmeFlag;
	unsigned char m_bfmePad[3];
	int m_bfmeZero;
	void *m_bfmeWhat;
};

class BfmeKeyAWB
{
public:
};

void bfmeGoAWB(BfmeKeyAWB *key)
{
	if (key == 0)
		return;
	BfmeNodeAWB *node = (BfmeNodeAWB *)((GameWindow *)key)->winGetUserData();
	if (node == 0)
		return;
	void *have = node->m_bfmeWhat;
	node->m_bfmeFlag = true;
	node->m_bfmeZero = 0;
	if (have == 0)
		node->m_bfmeWhat = ((BfmeMakerAWB *)TheDisplayStringManager)->bfmeMakeAWB();
}
