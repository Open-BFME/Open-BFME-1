// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib
// Retail's base here is SubsystemInterface: bfmeInitCCF calls 0x009A1A30
// (??0SubsystemInterface@@QAE@XZ) and the vtable it stores, bfmeVftCCF at
// 0x010F9AAC, inherits slots 2, 3, 6 and 8 of SubsystemInterface's own vtable
// at 0x01141640 unchanged. Use the real header, not a stand-in base member.
#include "PreRTS.h"
#include "System/subsystem_interface.h"

// The vtable at 0x010F9AAC is ??_7Gen_00490100@@6B@ (dir32_addresses.csv),
// emitted by Bfme5BodyVectorDtors.cpp alongside the matched ??1Gen_00490100;
// __identifier spells that symbol so the store references the defining name.
extern "C" void *__identifier("??_7Gen_00490100@@6B@")[];

struct BfmeThingCCF : public SubsystemInterface
{
	BfmeThingCCF *bfmeInitCCF();
	volatile int m_bfmeA;
	volatile int m_bfmeB;
	volatile int m_bfmeC;
	volatile int m_bfmeD;
	volatile int m_bfmeE;
	volatile int m_bfmeF;
};

BfmeThingCCF *BfmeThingCCF::bfmeInitCCF()
{
	this->SubsystemInterface::SubsystemInterface();
	m_bfmeA = 0;
	// +0x00 is the vptr. The explicit base-constructor call above means the
	// compiler emits no derived vptr store of its own, so retail's own store --
	// bfmeVftCCF is ??_7Gen_00490100@@6B@ at 0x010F9AAC, a nine-slot
	// SubsystemInterface vtable -- is written here explicitly.
	*(void *volatile *)this = __identifier("??_7Gen_00490100@@6B@");
	m_bfmeB = 0;
	m_bfmeC = 0;
	m_bfmeD = 0;
	m_bfmeE = 0;
	m_bfmeF = 0;
	return this;
}
