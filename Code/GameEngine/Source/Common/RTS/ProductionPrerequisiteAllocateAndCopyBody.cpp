// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport ProductionPrerequisite vector allocation and copy
// helper, retail 0x003B6460, 97 bytes. The name sat on the 5-byte
// incremental-link thunk at 0x00014961 and the body it jumps to carried only a
// machine byte-dump row.
//
// The element is the same 0x18 bytes its __copy sibling models, and the
// per-element call is _Construct at 0x003ABAD0 through the ILT at 0x000027A2 --
// the same _Construct whose inlined copy constructor stores the vtable at +0,
// a dword at +4, a byte at +8 and copy-constructs the member at +0xC.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
private:
	unsigned char m_data[0x18];
};

namespace _STL
{
void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);

// Named apart from _STL::_Construct on purpose: the ledger already pins
// ??$_Construct@VProductionPrerequisite@@V1@@_STL@@... to the ILT at
// 0x0003AA26, which jumps to 0x00784DB0, while this body calls the ILT at
// 0x000027A2, which jumps to the 0x003ABAD0 copy-construct. Reusing the name
// would put one symbol on two divergent bodies.
void __cdecl BfmeProductionPrerequisiteConstruct(void *destination, const ProductionPrerequisite &value);

template <class Type>
class allocator {};

template <class Type, class Allocator>
class vector
{
protected:
	template <class Iterator>
	Type *_M_allocate_and_copy(unsigned int, Iterator, Iterator);
};

template <class Type, class Allocator>
template <class Iterator>
Type *vector<Type, Allocator>::_M_allocate_and_copy(
	unsigned int count, Iterator first, Iterator last)
{
	Type *result;
	if (count)
	{
		unsigned int bytes = count * sizeof(Type);
		if (bytes > 128)
			result = (Type *)vectorLargeAllocate(bytes);
		else
			result = (Type *)vectorSmallAllocate(bytes);
	}
	else
	{
		result = 0;
	}

	if (first != last)
	{
		int offset = (char *)result - (char *)first;
		do
		{
			BfmeProductionPrerequisiteConstruct((Type *)((char *)first + offset), *first);
			++first;
		}
		while (first != last);
	}
	return result;
}

template ProductionPrerequisite *vector<
	ProductionPrerequisite,
	allocator<ProductionPrerequisite>
>::_M_allocate_and_copy<const ProductionPrerequisite *>(
	unsigned int, const ProductionPrerequisite *, const ProductionPrerequisite *);
}
