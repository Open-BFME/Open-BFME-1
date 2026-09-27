// ??4?$vector@VArmorTemplateSet@@V?$allocator@VArmorTemplateSet@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z
// partial score=0.95 date=2026-09-27
// cl: /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// STLport vector<ArmorTemplateSet>::operator=, retail 0x00136D60, 280 bytes.
//
// The body is STLport 4.5's __vector__<_Tp,_Alloc>::operator= verbatim.  All
// three size computations go through the signed divide-by-twelve magic
// (0x2AAAAAAB, sar 1, shr 31, add), so the element is 12 bytes, and the five
// call sites are the four helpers the ledger already names for this element
// plus _M_clear:
//
//   +0x52  _M_allocate_and_copy       ILT 0x0004245B -> 0x00134C20 (0x0C elem)
//   +0x5B  _M_clear                   ILT 0x00015DAC -> 0x00136250
//   +0xA6  __copy<ArmorTemplateSet*>  ILT 0x0003ADC8 -> 0x00133790 (matched)
//   +0xCA  __copy<ArmorTemplateSet*>  ILT 0x0003ADC8
//   +0xFC  __uninitialized_copy<..>   ILT 0x00031E4E -> 0x00133FD0 (0x0C elem)
//
// IDENTITY.  The sole caller is the matched ThingTemplate::operator=
// (ThingTemplateCopyAssignment.cpp), which assigns m_armorTemplateSets, an
// ArmorTemplateSetVector.  Both __copy call sites resolve to the matched
// __copy<VArmorTemplateSet*,VArmorTemplateSet*> at 0x00133790 -- 77 bytes that
// assign three dwords per element -- so the element is the record of
// GameLogic/ArmorSet.h rather than a same-size lookalike, and the /12 magic
// agrees with ArmorSetFlags + const ArmorTemplate* + const DamageFX*.
//
// The empty inline destructor below is a codegen lever, not a witnessed member
// function: it is the only spelling for which MSVC 7.1 leaves _M_clear() out of
// line, which is how retail has it.  With a trivially destructible element the
// compiler inlines _M_clear into this body at +0x57 and the shape comes out 324
// bytes; the empty destructor makes the _Destroy call inside _M_clear big
// enough to stay out of line, while the empty _Destroy of the
// size() >= __xlen path folds away -- retail pops five arguments there
// (add esp,0x14), not the seven the same spelling gives a real destructor.
//
// This file carries the assignment member only.  The rest of the family --
// begin 0x0010BDB0, clear 0x002E78E0, capacity 0x000E6B90, _M_set 0x000FB9C0,
// __copy 0x00133790, __uninitialized_copy 0x0013DA80 -- is already matched out
// of ThingTemplate.cpp, so a whole-class instantiation here would only mint
// second copies of those bodies.

#include <vector>

class ArmorTemplate;
class DamageFX;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ArmorSet.h
class ArmorTemplateSet
{
public:
	~ArmorTemplateSet() {}

private:
	unsigned int m_types;			// ArmorSetFlags
	const ArmorTemplate *m_template;
	const DamageFX *m_fx;
};

namespace _STL
{
template vector<ArmorTemplateSet, allocator<ArmorTemplateSet> > &
	vector<ArmorTemplateSet, allocator<ArmorTemplateSet> >::operator=(
		const vector<ArmorTemplateSet, allocator<ArmorTemplateSet> > &);
}
