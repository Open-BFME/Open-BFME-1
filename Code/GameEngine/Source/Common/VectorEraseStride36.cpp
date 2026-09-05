// cl: /EHsc
// stlport
//
// Near-twin of ?erase@?$vector@UFXBoneInfo@@...@Z
// (Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp): same
// vector<T>::erase(first,last) shape, but T is 36 bytes (0x24) here instead
// of 8. The element destructor call in the retail bytes is direct (no
// vtable indirection), matching the already-pinned non-virtual destructor
// ??1Gen0003B8FE@@QAE@XZ (0x0003B8FE, "the element destructor the 36-byte-
// stride vector at 0x001439F0 calls" per reverse/symbols.csv) -- reused
// verbatim here as the element type name so the destructor call resolves
// against the existing pin; only a new __copy<T*> instantiation pin is
// required for the shift-down helper.

#include <vector>

struct Gen0003B8FE
{
	char m_bytes[ 0x24 ];
	~Gen0003B8FE();
};

template class _STL::vector<Gen0003B8FE>;
