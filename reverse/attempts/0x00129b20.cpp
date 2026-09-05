// ??1?$_Rb_tree@IU?$pair@$$CBIPAUOpen2State129B20@@@_STL@@U?$_Select1st@U?$pair@$$CBIPAUOpen2State129B20@@@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIPAUOpen2State129B20@@@_STL@@@2@@_STL@@QAE@XZ
// partial score=0.85 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// twin of the eighteen-way ICF fold at retail 0x006587F0 (matched in
// Code/GameEngine/Source/Common/StateMachine.cpp as
// _Rb_tree<int, pair<const int, State *> >::~_Rb_tree). Retail 0x00129B20 is
// the same 8-byte-node destructor body for a different int-keyed pointer map;
// the sole pinned callee (reverse/symbols.csv) already names the payload
// "Open2State129B20", so this is that instantiation's destructor. No matched
// caller further identifies the owning class, so the type stays
// address-derived per the twin-lane identity policy.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

struct Open2State129B20;

typedef _STL::pair<const unsigned int, Open2State129B20 *> Rva00129B20Pair;

template class _STL::_Rb_tree<unsigned int, Rva00129B20Pair, _STL::_Select1st<Rva00129B20Pair>,
	_STL::less<unsigned int>, _STL::allocator<Rva00129B20Pair> >;
