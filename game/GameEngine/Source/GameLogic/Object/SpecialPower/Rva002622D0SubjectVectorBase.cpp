// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// Retail 0x001D95B0 is the 97-byte STLport _Vector_base(size_t, const
// allocator &) constructor for the pointer vector that Rva002622D0Collect.cpp
// copies (element named after its matched caller at 0x002622D0; the pointee
// class is unproven). Its _M_end_of_storage proxy is the pointer proxy at
// 0x000CCC70, so the element is a pointer
// (targets/game/reverse/identity_evidence/001d95b0-pointer-vector-base.md).
// The allocator's count != 0 guard produces retail's test ebx / je, and the
// node allocator is reached out of line through its 0x00061CE0 body view.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>

class Rva002622D0Subject;

void *__cdecl bfmeNodeAllocateAt00061CE0(unsigned int bytes);

namespace _STL
{
	template <>
	inline Rva002622D0Subject **allocator<Rva002622D0Subject *>::allocate(
		size_type count, const void *)
	{
		if (count != 0)
			return static_cast<Rva002622D0Subject **>(
				bfmeNodeAllocateAt00061CE0(count * sizeof(Rva002622D0Subject *)));
		return 0;
	}

	template _Vector_base<Rva002622D0Subject *, allocator<Rva002622D0Subject *> >::_Vector_base(
		size_t, const allocator<Rva002622D0Subject *> &);
}
