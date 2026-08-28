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
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *, const Type &, const __false_type &, unsigned int, bool);
};

class ProductionPrerequisitePrereqUnitRecInsertOverflowShim
{
public:
	void insert_overflow(ProductionPrerequisite::PrereqUnitRec *pos, const ProductionPrerequisite::PrereqUnitRec &x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<ProductionPrerequisite::PrereqUnitRec, allocator<ProductionPrerequisite::PrereqUnitRec> >::_M_insert_overflow(
	ProductionPrerequisite::PrereqUnitRec *pos, const ProductionPrerequisite::PrereqUnitRec &x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((ProductionPrerequisitePrereqUnitRecInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
