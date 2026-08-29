// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// A map lookup landed as a relocation-blind twin.
//
// 0x006148F0 is a twin of the map<int,unsigned>::operator[] in
// Code/GameEngine/Source/GameLogic/System/GameLogicDispatch.cpp (0x006473A0)
// and differs from it in one callee: the tree's insert.
//
// Neither key nor mapped type is observable from this body -- the key is
// compared as a dword and the mapped half is never touched -- so both are
// spelled with the widths the model uses and the key is named by address.
#define _STLP_NO_EXCEPTIONS 1
#include <map>

// A distinct enum key rather than `int`: it compares exactly as an int does,
// which is what the bytes show, and it keeps this instantiation's symbols
// apart from the model's.
enum Open2Key6148F0 { OPEN2_KEY_6148F0 };

typedef _STL::map<Open2Key6148F0, unsigned int, _STL::less<Open2Key6148F0> > Open2Map6148F0;

void Open2MapAnchor6148F0( Open2Map6148F0 &target, const Open2Key6148F0 &key )
{
	target[ key ];
}

