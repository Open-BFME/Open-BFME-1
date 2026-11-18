// ?rva001BD790@BfmeSub1CC_EC3@@QAEXM@Z
// Retail RVA 0x001BD790, 24 bytes.
// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-
//
// Lowers the float at +0x3C (the value effectiveMaxSpeed's queries share) to
// the argument. Its only caller is Object::rva001CC250 (0x001CC250), through
// ILT 0x00032A24. Identity unproven, so the name keeps the address.

#include "../../../Include/Common/ScalarTypes.h"

class BfmeSub1CC_EC3
{
public:
	void rva001BD790(Real value);

	unsigned char m_pad00[0x3C];
	Real m_3c;
};

void BfmeSub1CC_EC3::rva001BD790(Real value)
{
	if (m_3c > value)
		m_3c = value;
}
