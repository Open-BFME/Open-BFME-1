// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
struct ProductionPrerequisite
{
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
	struct PrereqUnitRec
	{
	};
};

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
	template <class Iterator>
	Type *_M_allocate_and_copy(unsigned int, Iterator, Iterator);
	void _M_clear();
};

class PrereqUnitRecAllocateAndCopyShim
{
public:
	ProductionPrerequisite::PrereqUnitRec *allocate_and_copy(unsigned int n, const ProductionPrerequisite::PrereqUnitRec *first, const ProductionPrerequisite::PrereqUnitRec *last);
	void clear();
};

template <class Type, class Allocator>
template <class Iterator>
Type *vector<Type, Allocator>::_M_allocate_and_copy(unsigned int n, Iterator first, Iterator last)
{
	return (Type *)((PrereqUnitRecAllocateAndCopyShim *)this)->allocate_and_copy(
		n,
		(const ProductionPrerequisite::PrereqUnitRec *)first,
		(const ProductionPrerequisite::PrereqUnitRec *)last);
}

template ProductionPrerequisite::PrereqUnitRec *vector<
	ProductionPrerequisite::PrereqUnitRec,
	allocator<ProductionPrerequisite::PrereqUnitRec>
>::_M_allocate_and_copy<ProductionPrerequisite::PrereqUnitRec const *>(
	unsigned int, ProductionPrerequisite::PrereqUnitRec const *,
	ProductionPrerequisite::PrereqUnitRec const *);

void vector<ProductionPrerequisite::PrereqUnitRec, allocator<ProductionPrerequisite::PrereqUnitRec> >::_M_clear()
{
	((PrereqUnitRecAllocateAndCopyShim *)this)->clear();
}
}
