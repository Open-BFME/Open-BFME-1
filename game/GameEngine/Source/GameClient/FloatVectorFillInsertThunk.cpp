// cl: /DNDEBUG /MD /EHsc
// stlport

// Open-BFME5: STLport vector<float>::_M_fill_insert, retail 0x00459D90.
//
// Unlike the resize family this one needs no local spelling at all -- it is the
// vendored 4.5.3 header's own body, byte for byte, once memmove is routed
// through the import slot the way VectorIntegerInsertOverflowThunk.cpp routes
// it.  resize is the member BFME changed (its fill value is by value where the
// vendored header takes a reference); _M_fill_insert is not, which is exactly
// what the three landed resize thunks assumed when each of them declared it
// with a `const Type &` parameter and let retail hand it the address of a
// stack slot.
//
// The element type is float and not one of the other four-byte PODs because of
// the size: every four-byte instantiation already in the ledger compiles this
// function to 282 bytes (vector<int> at 0x00067740, vector<Object *> at
// 0x00754260, vector<void *> at 0x003D3D50) and retail here is 283.  float is
// the four-byte type that costs the extra byte.  The two callees agree: the
// overflow arm reaches 0x000D32E0, which the ledger already carries under a
// generated four-byte-POD _M_insert_overflow identity, and both fill arms reach
// 0x00459A00, 0x390 bytes below this body in the same TU.
//
// Placement follows the nearest named neighbour (SelectionInfo.cpp at
// 0x00458F60) and is not a claim about which retail TU this was compiled in;
// nothing in the 283 bytes settles that.

#include <cstring>

// Retail reaches memmove through the import slot (`ff 15`); the pin
// `_bfme_memmove_ptr` is already in targets/game/reverse/symbols.csv at that slot.
extern "C" void *(__cdecl *bfme_memmove_ptr)(void *, const void *, unsigned int);

#define memmove (*bfme_memmove_ptr)
#include <vector>
#undef memmove

template class _STL::vector<float>;
