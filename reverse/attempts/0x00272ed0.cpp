// ?chooseLocomotorSet@AIUpdateInterface@@UAE_NW4LocomotorSetType@@@Z
// partial score=0.93 date=2026-09-18
// Reviewer correction: the prior BfmeSelfGN label was refuted by the
// canonical AIUpdate mapping and the Zero-Hour chooseLocomotorSet twin.
// This bank keeps the worker's recovered retail offsets and control flow;
// only the identity and the witnessed override-chain types are corrected.

typedef bool Bool;
typedef float Real;

enum LocomotorSetType
{
	LOCOMOTORSET_NORMAL = 0,
	LOCOMOTORSET_NORMAL_UPGRADED = 1
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	void *m_vtable;
	const Overridable *m_nextOverride;
};

class Gen_001418F0
{
public:
	Real bfmeFindFloat(const void *key);
};

struct BFMEChooseLocomotorFields
{
	unsigned char m_unreconstructed_000[0x1D0];
	LocomotorSetType m_curLocomotorSet;
	Real m_unreconstructed_1D4;
	unsigned char m_unreconstructed_1D8[0x327 - 0x1D8];
	Bool m_upgradedLocomotors;
	unsigned char m_unreconstructed_328[0x337 - 0x328];
	Bool m_unreconstructed_337;
};

struct BFMEChooseLocomotorKey
{
	unsigned char m_unreconstructed_000[0x1D0];
	const void *m_key;
};

class BFMEChooseLocomotorObject
{
public:
	char m_unreconstructed_000[4];
	const Overridable *m_template;
};

class BFMEChooseLocomotorObjectSlot
{
public:
	char m_unreconstructed_000[8];
	BFMEChooseLocomotorObject *m_object;
};

class AIUpdateInterface
{
public:
	virtual Bool chooseLocomotorSet(LocomotorSetType wst);
	Bool chooseLocomotorSetExplicit(LocomotorSetType wst);
	void chooseGoodLocomotorFromCurrentSet();
};

Bool AIUpdateInterface::chooseLocomotorSet(LocomotorSetType wst)
{
	BFMEChooseLocomotorFields *fields = reinterpret_cast<BFMEChooseLocomotorFields *>(this);
	if (wst == LOCOMOTORSET_NORMAL && fields->m_upgradedLocomotors)
		wst = LOCOMOTORSET_NORMAL_UPGRADED;

	if (wst == fields->m_curLocomotorSet)
		return true;

	if (fields->m_unreconstructed_337 == false && chooseLocomotorSetExplicit(wst))
	{
		chooseGoodLocomotorFromCurrentSet();

		BFMEChooseLocomotorObject *object = reinterpret_cast<BFMEChooseLocomotorObjectSlot *>(this)->m_object;
		const Overridable *const volatile *templateSlot = &object->m_template;
		const Overridable *d = *templateSlot;
		const Overridable *f;
		if (d == 0)
			f = d;
		else
			f = d->m_nextOverride ? d->m_nextOverride->getFinalOverride() : d;

		fields->m_unreconstructed_1D4 =
			reinterpret_cast<Gen_001418F0 *>(const_cast<Overridable *>(f))->bfmeFindFloat(
				reinterpret_cast<BFMEChooseLocomotorKey *>(this)->m_key);
		return true;
	}

	return false;
}
