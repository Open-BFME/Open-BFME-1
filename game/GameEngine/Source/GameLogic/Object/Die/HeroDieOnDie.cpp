// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Iinputs/reference/shims/player /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// HeroDie::onDie at retail 0x00255790 (32 B): slot 0 of the one-slot
// DieModuleInterface table 0x010B3064, which HeroDie's registered constructor
// 0x00255670 stores at +0x10; the only route is ILT 0x00041CA9, whose VA
// appears once in the image. Zero Hour's DieModuleInterface declares one
// virtual, onDie(const DamageInfo *). The body ignores damageInfo and walks
// the controlling player's objects with the module data's +0x34 value.
// Evidence: targets/game/reverse/identity_evidence/diemodule-slot0-ondie.md
// Moved from BfmeConv926.cpp; the two lookup views below are copies of that
// file's, which its other rows still use.
#include "Common/Player.h"

class DamageInfo;
class BfmeTail926C;

struct BfmeObj926C
{
	char m_bfmePad[0x22c];
	BfmeTail926C *m_bfmeUse;
};

class BfmeKey926C
{
public:
	BfmeObj926C *bfmeFind926C();
};


struct BfmeA926E
{
	char m_bfmePad[0x34];
	void *m_bfmeVal;
};

// The controlling-player lookup is ILT 0x00020824 -> 0x001BE3F0
// (Object::getControllingPlayer), and the pushed callback 0x002555A0 is the
// ?rva002555a0FrameDispatch@@YAHPBVObject@@PBVSpecialPowerTemplate@@@Z row.
class SpecialPowerTemplate;
int rva002555a0FrameDispatch(const Object *object, const SpecialPowerTemplate *power);
#define g_bfme926Obj rva002555a0FrameDispatch

class HeroDie
{
public:
	virtual void onDie(const DamageInfo *damageInfo);
};

void HeroDie::onDie(const DamageInfo *)
{
	BfmeA926E *s = *(BfmeA926E **)((char *)this - 0xc);
	BfmeKey926C *k = *(BfmeKey926C **)((char *)this - 8);
	BfmeObj926C *o = (BfmeObj926C *)((const Object *)k)->getControllingPlayer();
	// retail calls 0x0002F1CB, Player::iterateObjects (const, five-byte void
	// thunk over the matched int body at 0x000CDCF0).
	((const Player *)o)->iterateObjects((ObjectIterateFunc)(void *)g_bfme926Obj,
		s->m_bfmeVal);
}
