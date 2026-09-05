// cl: /EHsc
// stlport
//
// Near-twin of ?erase@?$vector@UFXBoneInfo@@...@Z
// (Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp): same
// vector<T>::erase(first,last) shape, but T is 44 bytes (0x2c) here instead
// of 8, matching the element-walk stride already recovered for Gen00252A40
// in MemberStrideWalks.cpp.  The element destructor call is direct (no
// vtable indirection in the retail bytes), so the element carries no vptr;
// its destructor is pinned separately in reverse/symbols.csv as
// ??1Gen_dtor_00023989b@@QAE@XZ because the address already carries an
// unrelated (and wrongly virtual) name from another lane's guess.

#include <vector>

struct Gen_dtor_00023989b
{
	char m_bytes[ 0x2c ];
	~Gen_dtor_00023989b();
};

template class _STL::vector<Gen_dtor_00023989b>;
