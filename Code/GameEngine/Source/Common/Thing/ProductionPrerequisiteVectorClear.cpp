// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: vector<ProductionPrerequisite>::_M_clear, retail 0x003AFE10, 99
// bytes. The name was parked on a 5-byte thunk.
//
// STLport's own body out of the real header. Two things about the element are
// in the loop: the stride is 0x18, and the destruction is a call through the
// object's own vtable slot 0 with a zero flag, which is what MSVC emits for
// ~T() on a class with a virtual destructor.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
public:
	virtual ~ProductionPrerequisite();

private:
	char m_bfmeBody[0x18 - 4];				// what the stride leaves after the vptr
};

void BfmeProductionPrerequisiteVectorAnchor(_STL::vector<ProductionPrerequisite> &out, const _STL::vector<ProductionPrerequisite> &in)
{
	out = in;
}
