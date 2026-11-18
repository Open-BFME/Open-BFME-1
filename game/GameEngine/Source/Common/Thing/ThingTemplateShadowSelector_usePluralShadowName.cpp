// ?usePluralShadowName@BfmeThingTemplateShadowSelector@@QBE_NXZ
// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc
//
// BfmeThingTemplateShadowSelector::usePluralShadowName, retail 0x0087E8D0/47:
// one body.  Its last 11 bytes (+0x24) happen to equal the code for
// W3DTerrainBackground::isCulled, but retail was linked without identical-code
// folding, the +0x24 entry is only the fall-through after the count test, and
// no caller reaches it.  The name is the ledger's; the callers (BuildAssistant
// footprint code, Weapon::isGoalPosWithinAttackRange) suggest a geometry
// predicate, so treat it as unproven.
//
// The selector sits at ThingTemplate+0x60 and its begin/end pointers walk a
// vector of 36-byte shadow-layer entries; the retail predicate is true only
// when the vector holds exactly one entry whose first field equals 2.

#include "../../../Include/Common/ScalarTypes.h"


class BfmeThingTemplateShadowSelector
{
public:
	Bool usePluralShadowName() const;

private:
	char m_pad[ 0x2c ];
	const char * volatile m_begin;
	const char *m_end;
};

Bool BfmeThingTemplateShadowSelector::usePluralShadowName() const
{
	Int count = (Int)(m_end - m_begin) / 36;
	if (count != 1)
		return false;
	return *(const Int *)m_begin == 2;
}
