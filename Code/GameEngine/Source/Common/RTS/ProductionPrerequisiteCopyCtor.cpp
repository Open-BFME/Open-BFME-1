// cl: /DNDEBUG /MD /EHsc
// stlport

#include <vector>

enum ScienceType
{
};

template <class Type> class BfmeIntAllocator : public std::allocator<Type>
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		unsigned int m_data[3];
		~PrereqUnitRec();
	};

private:
	std::vector<PrereqUnitRec> m_prereqUnits;
	std::vector<ScienceType> m_prereqSciences;
	std::vector<int, BfmeIntAllocator<int> > m_unused;
};

// ??0ProductionPrerequisite@@QAE@ABV0@@Z
ProductionPrerequisite bfmeCopyProductionPrerequisite(
	const ProductionPrerequisite &value)
{
	return value;
}
