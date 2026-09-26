// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /D_STLP_USE_STATIC_LIB
// stlport
// Split by hand out of game/gen_small/zhstl_001.cpp; the phase-5 ZH STLport
// instantiation spike left no generator behind (nothing under tools/ mentions
// zhstl), so the `cl:` line and the instantiation list are maintained by hand,
// as they already are in zhstl_003/004 (9323d7395).
//
// Why this TU exists at all. `_Rb_tree_base<pair<const NameKeyType,Real>>`'s
// ctor allocates its header node through STLport's _Node_alloc (retail:
// `push 0x18; call 0x0082E540`), which the sweep PreRTS.h cannot produce --
// it defines _STLP_USE_NEWALLOC, so _alloc.h picks __new_alloc and the call
// compiles to `operator new`. inputs/reference/shims/stlp_nodealloc fixes that for a
// whole TU. zhstl_001 cannot take the flag: its
// `hashtable<pair<const NameKeyType,DamageFX>>::clear` row deallocates through
// plain `operator delete` in retail and goes red the moment the flag is on.
// One allocator per TU, so the map<NameKeyType,Real> rows that want the node
// allocator live here and zhstl_001 keeps the ones that want operator new.
//
// The seven dup_* rows are retail's own duplicate emissions of that one ctor;
// each calls the _STLP_alloc_proxy ctor copy nearest itself, which is what the
// seven per-site pins in targets/game/reverse/symbols.csv name.

#include "PreRTS.h"

#include "Common/GameCommon.h"
#include "Common/NameKeyGenerator.h"

#include <map>

template class _STL::map<NameKeyType, Real>;
