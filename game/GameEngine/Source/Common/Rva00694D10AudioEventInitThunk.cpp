// cl: /DNDEBUG /MD /EHs-c- /Iinputs/reference/shims/turretai /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "PreRTS.h"
#include "Common/AudioEventRTS.h"
//
// Address-derived body: retail 0x00694D10, size 27. Ghidra names this only as
// a dump; the real name is not proven. Bytes decode to a small "init" method
// on a class holding an AudioEventRTS by value: it copy-constructs the
// caller's AudioEventRTS argument in place at this+0 (thiscall into the
// callee at reloc target 0x00047B27, which targets/game/reverse/functions.csv already
// binds to ??0AudioEventRTS@@QAE@ABV0@@Z, the AudioEventRTS copy ctor at
// 0x000B2FB0), then zeroes an Int at this+0x70 and a Bool at this+0x74, and
// returns this -- the exact shape of the landed sibling
// BfmeThingBQF::bfmeInitBQF (game/GameEngine/Source/Common/BfmeConv515.cpp),
// whose m_bfmeHead[0x70]/m_bfmeZero/m_bfmeFlag layout this reuses, except
// this variant's head is copy-constructed from an argument instead of being
// built from a fixed text pointer + flag.

struct Rva00694D10Fields
{
	unsigned char m_bfmeHead[0x70];		///< occupies the embedded AudioEventRTS-sized region
	int m_bfmeZero;					///< +0x70
	bool m_bfmeFlag;					///< +0x74

	Rva00694D10Fields *bfmeInit( const void *event );
};

// ?bfmeInit@Rva00694D10Fields@@QAEPAU1@PBX@Z
Rva00694D10Fields *Rva00694D10Fields::bfmeInit( const void *event )
{
	__assume(this != 0);
	::new ((void *)this) AudioEventRTS(*static_cast<const AudioEventRTS *>(event));
	m_bfmeZero = 0;
	m_bfmeFlag = false;
	return this;
}
