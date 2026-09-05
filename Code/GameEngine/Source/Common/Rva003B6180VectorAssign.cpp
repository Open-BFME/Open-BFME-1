// cl: /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME5: STLport vector<Rva003B20C0Element>::operator=, retail
// 0x003B6180, 294 bytes. Element is 36 bytes (magic 0x38E38E39 sar 3).
// Same shape as GeometryShapeVectorAssign.cpp (0x000FF8F0, also 294B / 0x24).
//
// The _Destroy ILT 0x0004A593 jumps to 0x003A8F40, which loads [esi] as a
// vftable, push 0 / mov ecx,esi / call [eax], then add esi,0x24. That is
// MSVC's p->~T() on a type with a virtual destructor, so the element is
// vptr plus 32 bytes of payload, not a nonvirtual 36-byte blob. The other
// three helpers agree: allocate-and-copy 0x003B6020 and uninitialized_copy
// 0x003AB940 both stride 0x24 through _Construct at 0x00032BF0; __copy at
// 0x003B5EA0 uses the same /36 magic and assigns members while skipping +0
// (the vptr).

#include <vector>

namespace _STL
{

struct Rva003B20C0Element
{
	virtual ~Rva003B20C0Element();
	char m_payload[32];
};

template class vector<Rva003B20C0Element>;

}
