// cl: /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// The symbols pin this STLport vector body to BfmeElemVKN. The two callers,
// bfmePushVKN and ThingTemplate::parseWeaponTemplateSet, confirm the 0xEC
// element stride and the owning module paths.

#include <vector>

struct BfmeElemVKN
{
	char m_bytes[0xEC];
};

template class _STL::vector<BfmeElemVKN>;
