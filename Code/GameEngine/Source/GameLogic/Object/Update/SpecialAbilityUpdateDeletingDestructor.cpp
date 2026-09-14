// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME: SpecialAbilityUpdate scalar-deleting destructor at retail RVA
// 0x002AAEC0 (30 bytes).  The unique dtor ILT 0x000243A7 enters the matched
// complete destructor at 0x002AA910; the exact ctor at 0x002A6360 and the
// recovered multi-base/module layout establish this wrapper's identity.

class SpecialAbilityUpdate
{
public:
	virtual ~SpecialAbilityUpdate();
};

void forceSpecialAbilityUpdateDeletingDestructor()
{
	SpecialAbilityUpdate value;
}
