// cl: /EHsc
// stlport
//
// Near-twin of ?erase@?$vector@UFXBoneInfo@@...@Z
// (Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp), and sibling of
// Code/GameEngine/Source/Common/VectorEraseStride44A.cpp (0x00252E70): same
// vector<T>::erase(first,last) shape at the same 44-byte (0x2c) stride, but
// a different element destructor.  Direct (non-vtable) destructor call, so
// no vptr; pinned in reverse/symbols.csv as ??1Gen_dtor_0002a8bab@@QAE@XZ.

#include <vector>

struct Gen_dtor_0002a8bab
{
	char m_bytes[ 0x2c ];
	~Gen_dtor_0002a8bab();
};

template class _STL::vector<Gen_dtor_0002a8bab>;
