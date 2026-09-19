// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: vector<ProductionPrerequisite>::_M_insert_overflow, retail
// 0x00787E80, 338 bytes. The body carried no ledger row; its name sat on a
// 5-byte thunk.
//
// The element is 0x18 bytes with an out-of-line copy constructor, which is the
// four calls between the allocation and the release. It is modelled without
// the virtual destructor its sibling _M_clear proves, because this body never
// destroys anything: giving the element one here makes MSVC add a destroy loop
// retail does not have, and the body comes out 51 bytes short.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
public:
	ProductionPrerequisite(const ProductionPrerequisite &other);

private:
	char m_bfmeBody[0x18];
};

void BfmeProductionPrerequisiteVectorInsertAnchor(_STL::vector<ProductionPrerequisite> &v, const ProductionPrerequisite &value)
{
	v.insert(v.begin(), value);
}
