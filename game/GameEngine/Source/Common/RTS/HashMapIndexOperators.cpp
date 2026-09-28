// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Two STLport hash_map<int, T>::operator[] instantiations:
//
//   0x00498C40  99 bytes  (mapped type still synthetic)
//   0x006141F0  99 bytes  hash_map<int, BfmeItemAM *>
//
// Both are byte-twins of the hash_map<int, Relationship>::operator[] at
// 0x00787D80 in Player.cpp -- the same 99 bytes once relocations are masked,
// differing only in the per-instantiation insertion-thunk reloc.
//
// 0x00498C40 keeps a synthetic enum whose only job is to give its
// instantiation a mangled name distinct from the real Relationship one.
//
// 0x006141F0 is the LivingWorld item table's operator[]: the matched
// BfmeSinkAM::registerItem (0x006176A0) calls it on the +0x210
// hash_map<int, BfmeItemAM *> whose erase the matched bfmeDrop (0x00617A10)
// links (identity_evidence/hash_map_item_index_006141f0.md). Only operator[] is
// instantiated so no other member of that table is emitted here.

#include <hash_map>

enum Gen_e_00498c40 { Gen_e_00498c40_Zero = 0 };

typedef _STL::pair<const int, Gen_e_00498c40> TgPair_hash_int_e_00498c40;
template class _STL::hash_map<int, Gen_e_00498c40, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<TgPair_hash_int_e_00498c40> >;

class BfmeItemAM;
template BfmeItemAM *&_STL::hash_map<int, BfmeItemAM *>::operator[](const int &);
