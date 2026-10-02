// Open-BFME5 conversions.
// cl: /Iinputs/reference/shims/bfmeobjectlayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "PreRTS.h"
#include "GameLogic/Object.h"

class BfmeSub942D
{
public:
	void *bfmeCall942D(void *a);
};

class BfmeThing942D
{
public:
	virtual void bfmeSlot942D00();
	virtual void bfmeSlot942D01();
	virtual void bfmeSlot942D02();
	virtual void bfmeSlot942D03();
	virtual void bfmeSlot942D04();
	virtual void bfmeSlot942D05();
	virtual void bfmeSlot942D06();
	virtual void bfmeSlot942D07();
	virtual void bfmeSlot942D08();
	virtual void bfmeVirt942D(void *r);
	void bfmeGo942D(void *a);
};

void BfmeThing942D::bfmeGo942D(void *a)
{
	Object *k = *(Object **)((char *)this - 0x18);
	if (!k->getControllingPlayer())
		return;
	Player *o = (*(Object **)((char *)this - 0x18))->getControllingPlayer();
	bfmeVirt942D(((BfmeSub942D *)((char *)o + 0x684))->bfmeCall942D(a));
}
