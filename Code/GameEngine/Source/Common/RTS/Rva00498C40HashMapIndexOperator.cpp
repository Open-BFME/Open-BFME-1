// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: STLport hash_map<int, T>::operator[], byte-twin of the
// hash_map<int, Relationship>::operator[] instantiation at 0x00787D80
// (Code/GameEngine/Source/Common/RTS/Player.cpp) -- same 99 bytes once
// relocations are masked; only the per-caller insertion-thunk reloc differs.
// A 4-byte mapped type (int) reproduces the same layout so the codegen
// matches; it gets a distinct mangled name from the real Relationship
// specialization.

#include <hash_map>

enum Gen_e_00498c40 { Gen_e_00498c40_Zero = 0 };

typedef _STL::pair<const int, Gen_e_00498c40> TgPair_hash_int_e_00498c40;
template class _STL::hash_map<int, Gen_e_00498c40, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<TgPair_hash_int_e_00498c40> >;
