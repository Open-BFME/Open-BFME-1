// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Two STLport hash_map<int, T>::operator[] instantiations:
//
//   0x00498C40  99 bytes
//   0x006141F0  99 bytes
//
// Both are byte-twins of the hash_map<int, Relationship>::operator[] at
// 0x00787D80 in Player.cpp -- the same 99 bytes once relocations are masked,
// differing only in the per-caller insertion-thunk reloc. Any 4-byte mapped
// type reproduces the layout, so each gets a synthetic enum whose only job is
// to give its instantiation a mangled name distinct from the real Relationship
// one and from the other's.
//
// That is also why the two enums cannot be collapsed into one: the enum name
// is inside each row's decoration, so a shared type would be a single
// instantiation and one of the two rows would stop existing.

#include <hash_map>

enum Gen_e_00498c40 { Gen_e_00498c40_Zero = 0 };
enum Gen_e_006141f0 { Gen_e_006141f0_Zero = 0 };

typedef _STL::pair<const int, Gen_e_00498c40> TgPair_hash_int_e_00498c40;
template class _STL::hash_map<int, Gen_e_00498c40, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<TgPair_hash_int_e_00498c40> >;

typedef _STL::pair<const int, Gen_e_006141f0> TgPair_hash_int_e_006141f0;
template class _STL::hash_map<int, Gen_e_006141f0, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<TgPair_hash_int_e_006141f0> >;
