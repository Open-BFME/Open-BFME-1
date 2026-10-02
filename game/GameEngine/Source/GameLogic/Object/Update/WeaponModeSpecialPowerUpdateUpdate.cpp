// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "PreRTS.h"
#include "GameLogic/Module/UpdateModule.h"

// WeaponModeSpecialPowerUpdate secondary update receiver at +0x10.
// Identity and retained integer-argument callee ABI: identity_evidence/update-slot0.md.

class BfmeItem1005
{
public:
	void bfmeDoD1005(int value);
};

class BfmeMsgXI;
class BfmeOwnerXI
{
public:
	void bfmeSendXI(BfmeMsgXI *value);
};

class Gen001C9AC0
{
public:
	void handle(int value);
};

class Rva002B2DE0ModuleData
{
public:
	unsigned char m_pad[0x1dc];
	unsigned int m_flags;
};

class Rva002B2DE0UpdateInterface
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
	virtual void wake(int value);

};

class WeaponModeSpecialPowerUpdate
{
public:
	virtual UpdateSleepTime update();
};

UpdateSleepTime WeaponModeSpecialPowerUpdate::update()
{
	BfmeItem1005 *object = *(BfmeItem1005 **)((char *)this - 8);

	object->bfmeDoD1005(2);
	for (int i = 0; i < 0x1d; ++i)
	{
		if ((*(Rva002B2DE0ModuleData **)((char *)this - 0xc))->m_flags & (1u << (i & 0x1f)))
			((Gen001C9AC0 *)object)->handle(i);
	}

	((BfmeOwnerXI *)object)->bfmeSendXI(reinterpret_cast<BfmeMsgXI *>((char *)*(Rva002B2DE0ModuleData **)((char *)this - 0xc) + 0x1d0));
	*(unsigned char *)((char *)this + 0x28) = 0;
	((Rva002B2DE0UpdateInterface *)((char *)this + 0x14))->wake(0);
	return UPDATE_SLEEP_FOREVER;
}
