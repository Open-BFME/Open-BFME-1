// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /D_STLP_USE_STATIC_LIB
// stlport
// Split by hand out of game/gen_small/zhstl_001.cpp; the phase-5 ZH STLport
// instantiation spike left no generator behind (nothing under tools/ mentions
// zhstl), so the `cl:` line and the instantiation list are maintained by hand,
// as they already are in zhstl_003/004 (9323d7395).
//
// Every row here is one of retail's DUPLICATE emissions of a container member
// zhstl_001 already claims, and each duplicate calls the copy of its callee
// nearest itself -- five copies of ??A?$map@PBVThingTemplate@@H... call five
// different copies of _Rb_tree::insert_unique. One name cannot pin five
// divergent bodies (pin_consistency, "one name, one function", and it is right
// to refuse: those bodies differ at +0x2B because their own callees differ).
//
// So each duplicate gets its own instantiation, exactly as gen-tgrid does for
// the same problem: the key and value types stay EXACT -- the identity in
// dup-of= is unchanged and still true -- and only the comparator (or, for the
// vector rows, the pointed-to element) is a per-RVA stand-in, which changes
// every decorated name in that instantiation without changing one byte of its
// code. Each stand-in name then pins exactly one address, read out of the
// retail call site, so the bytes prove the callee and no name is overloaded.

#include "PreRTS.h"

#include "Common/GameCommon.h"
#include "Common/NameKeyGenerator.h"
#include "Common/ThingTemplate.h"
#include "Common/PlayerTemplate.h"
#include "Common/Science.h"
#include "Common/MultiplayerSettings.h"
#include "Common/DiscreteCircle.h"

#include <vector>
#include <map>
#include <hash_map>
#include <utility>

// map<const ThingTemplate *, Int>::operator[] -- one stand-in comparator per duplicate
struct Gen_lt_001ac9d0 : public _STL::less<const ThingTemplate * > {};
template class _STL::map<const ThingTemplate *, Int, Gen_lt_001ac9d0 >;
struct Gen_lt_003e7dd0 : public _STL::less<const ThingTemplate * > {};
template class _STL::map<const ThingTemplate *, Int, Gen_lt_003e7dd0 >;
struct Gen_lt_004019f0 : public _STL::less<const ThingTemplate * > {};
template class _STL::map<const ThingTemplate *, Int, Gen_lt_004019f0 >;
struct Gen_lt_005874c0 : public _STL::less<const ThingTemplate * > {};
template class _STL::map<const ThingTemplate *, Int, Gen_lt_005874c0 >;
struct Gen_lt_000ea510 : public _STL::less<const ThingTemplate * > {};
template class _STL::map<const ThingTemplate *, Int, Gen_lt_000ea510 >;

// map<NameKeyType, VeterancyLevel>::operator[] -- one stand-in comparator per duplicate
struct Gen_lt_001bae30 : public _STL::less<NameKeyType > {};
template class _STL::map<NameKeyType, VeterancyLevel, Gen_lt_001bae30 >;
struct Gen_lt_00226fa0 : public _STL::less<NameKeyType > {};
template class _STL::map<NameKeyType, VeterancyLevel, Gen_lt_00226fa0 >;
struct Gen_lt_00227110 : public _STL::less<NameKeyType > {};
template class _STL::map<NameKeyType, VeterancyLevel, Gen_lt_00227110 >;
struct Gen_lt_00228410 : public _STL::less<NameKeyType > {};
template class _STL::map<NameKeyType, VeterancyLevel, Gen_lt_00228410 >;
struct Gen_lt_00401a80 : public _STL::less<NameKeyType > {};
template class _STL::map<NameKeyType, VeterancyLevel, Gen_lt_00401a80 >;
struct Gen_lt_004e5d60 : public _STL::less<NameKeyType > {};
template class _STL::map<NameKeyType, VeterancyLevel, Gen_lt_004e5d60 >;
struct Gen_lt_000e2560 : public _STL::less<NameKeyType > {};
template class _STL::map<NameKeyType, VeterancyLevel, Gen_lt_000e2560 >;

// map<NameKeyType, Real>::operator[] -- one stand-in comparator per duplicate
struct Gen_lt_000e24d0 : public _STL::less<NameKeyType > {};
template class _STL::map<NameKeyType, Real, Gen_lt_000e24d0 >;

// map<UnsignedShort, Int>::operator[] -- one stand-in comparator per duplicate
struct Gen_lt_00940b40 : public _STL::less<UnsignedShort > {};
template class _STL::map<UnsignedShort, Int, Gen_lt_00940b40 >;

// vector<void *>::swap -- one stand-in element per duplicate
class Gen_ve_001949c0 {};
template class _STL::vector<Gen_ve_001949c0 * >;
class Gen_ve_00194a00 {};
template class _STL::vector<Gen_ve_00194a00 * >;
class Gen_ve_000de000 {};
template class _STL::vector<Gen_ve_000de000 * >;
class Gen_ve_000de0a0 {};
template class _STL::vector<Gen_ve_000de0a0 * >;

// vector<Object *>::vector(const vector &) -- one stand-in element per duplicate.
// Retail emits this copy constructor five times; each copy calls the copy of
// get_allocator and of _Vector_base's constructor nearest itself, so the four
// duplicates diverge from 0x00135A10 (which game/GameEngine/Source/Common/RTS/
// Player.cpp claims) at those two rel32 slots and one name cannot pin all five.
class Gen_ve_00135ab0 {};
template class _STL::vector<Gen_ve_00135ab0 * >;
class Gen_ve_001f9520 {};
template class _STL::vector<Gen_ve_001f9520 * >;
class Gen_ve_003628f0 {};
template class _STL::vector<Gen_ve_003628f0 * >;
class Gen_ve_0039d5d0 {};
template class _STL::vector<Gen_ve_0039d5d0 * >;
