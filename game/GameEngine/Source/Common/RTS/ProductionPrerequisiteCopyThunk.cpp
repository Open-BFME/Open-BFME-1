// ?Rva000181A1ProductionPrerequisiteCopyThunk@@YAXXZ
// Retail 0x000181A1 is a five-byte ILT tail jump to the matched
// ProductionPrerequisite __copy body at 0x00753280, whose clean C++ definition
// lives in ProductionPrerequisiteCopyBody.cpp. That body is named by its real
// STLport instantiation, so the thunk takes the address of that specialization
// (declared here, never defined here, so no second body is emitted) and tail
// calls it through a zero-argument cdecl pointer: the five bytes are the same
// tail call, but the object now references the real __copy name instead of a
// stand-in hidden behind a linker alias pragma.
// cl: /O2 /MD /D_STLP_USE_STATIC_LIB

// Only the class name matters here: it is what spells the __copy specialization
// the same way its definition spells it. The element layout lives in
// ProductionPrerequisiteCopyBody.cpp, which is where this body is compiled.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result,
	const random_access_iterator_tag &, Distance *);
}

void Rva000181A1ProductionPrerequisiteCopyThunk(void)
{
	typedef ProductionPrerequisite *(__cdecl *CopyBody)(ProductionPrerequisite *,
		ProductionPrerequisite *, ProductionPrerequisite *, const _STL::random_access_iterator_tag &, int *);
	CopyBody body = &_STL::__copy<ProductionPrerequisite *, ProductionPrerequisite *, int>;
	((void (__cdecl *)(void))(void *)body)();
}