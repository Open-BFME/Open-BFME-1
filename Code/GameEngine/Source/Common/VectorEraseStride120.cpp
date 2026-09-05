// cl: /EHsc
// stlport
//
// Near-twin of ?erase@?$vector@UFXBoneInfo@@...@Z
// (Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp): same
// vector<T>::erase(first,last) shape, but T is 120 bytes (0x78) here
// instead of 8. The element destructor call in the retail bytes is direct
// (no vtable indirection at the call site), matching the already-pinned
// non-virtual destructor ??1Gen_uw_0003fcec@@QAE@XZ (0x0003FCEC) -- reused
// verbatim here as the element type name so the destructor call resolves
// against the existing pin; only a new __copy<T*> instantiation pin is
// required for the shift-down helper.

#include <vector>

struct Gen_uw_0003fcec
{
	~Gen_uw_0003fcec();

	char m_body[ 0x78 ];
};

template class _STL::vector<Gen_uw_0003fcec>;
