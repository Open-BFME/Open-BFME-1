// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/ini /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Retail 0xCA880 is std::bitset<>'s generic _M_do_count() byte-counting loop
// (movzx through the STLport 256-entry popcount table) with an end pointer at
// this+0x18: six 32-bit words. game/GameEngine/Source/GameLogic/System/
// CrateSystem.cpp already proves BFME's KINDOF_COUNT is wider than Zero
// Hour's 121-bit reference and falls in (160,192] -- CrateTemplate zeroes six
// dwords for m_killedByTypeKindof there. std::bitset rounds to whole 32-bit
// words, so any KINDOF_COUNT in that range compiles this loop identically;
// only the six-word width is provable from bytes, not the exact bit count or
// the extra enumerator names past ZH's list. This substitutes the same
// width-only, TU-scoped KindOfType CrateSystem.cpp uses, purely to force the
// compiler to emit KindOfMaskType::count()'s underlying _M_do_count() body so
// its bytes can be compared against retail; it is not a claim that 192 is the
// exact real BFME KINDOF_COUNT.
#define __PLACEMENT_VEC_NEW_INLINE
#define __KINDOF_H_
#include "Common/BitFlags.h"
enum KindOfType
{
	KINDOF_INVALID = -1,
	KINDOF_FIRST = 0,
	KINDOF_COUNT = 192						///< width pin only; see CrateSystem.cpp
};
typedef BitFlags<KINDOF_COUNT>	KindOfMaskType;

#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

unsigned int forceKindOfMaskCountInstantiation(const KindOfMaskType &mask)
{
	return (unsigned int)mask.count();
}
