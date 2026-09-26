// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME: TWIN lane. 0x0014E030 is a byte-twin (relocations masked) of
// std::list<crateCreationEntry>::operator= (retail 0x0037A0D0,
// game/GameEngine/Source/GameLogic/System/CrateSystem.cpp), which is
// std::list<T>::operator=(const list&) over the plain compiler-generated
// per-field assignment of T -- crateCreationEntry is `{ AsciiString
// crateName; Real crateChance; }` (inputs/reference/.../GameLogic/CrateSystem.h),
// 8 bytes: an AsciiString at +0 (assigned through StringBase<char>::set,
// retail 0x00887C90) and a plain 4-byte field at +4 (a straight mov, so its
// real type -- int or float -- is unrecoverable from these bytes; Real
// matches the twin). The two remaining calls are STLport's own list-node
// splice helpers (0x0014C540 / 0x0014C5A0, already pinned in
// game/gen_small/thunks_001.cpp and thunks_000.cpp), shared by every list<T>
// of this element size regardless of T, so they need no new pin.
//
// No caller or field name is recoverable for this address, so the element
// struct is address-derived.

#include "Common/AsciiString.h"
#include <list>

struct Gen0014E030Entry
{
	AsciiString name;
	float value;
};

typedef std::list<Gen0014E030Entry> Gen0014E030List;

template Gen0014E030List &Gen0014E030List::operator=(const Gen0014E030List &);
