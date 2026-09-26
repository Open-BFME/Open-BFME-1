// cl: /DNDEBUG /MD /EHsc
// PassiveAreaEffectBehavior vtable slot 13, retail 0x00201FD0 (114 bytes).
//
// The class identity is established by the matched constructor/destructor
// family and primary vtable 0x010A5304.  The method spelling is intentionally
// address-derived: retail's slot has no surviving semantic symbol.  Its
// operation is a passive health effect on one candidate object.
// BodyModuleInterface slot +0x18 is maximum health, as also used by the
// matched GarrisonContain::healSingleObject and Object damage/healing paths.

typedef unsigned int UnsignedInt;
typedef UnsignedInt ObjectID;
typedef float Real;
typedef bool Bool;

extern const Real BfmeZeroRange;

class BodyModule
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual Real getMaxHealth() const = 0;
};

class Object
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void attemptHealing(Real amount, const Object *source) = 0;
	virtual Bool attemptHealingFromSoleBenefactor(
		Real amount, const Object *source, UnsignedInt duration) = 0;

	Bool bfmeGetRecentDamageSource(ObjectID *sourceID, UnsignedInt seconds) const;

	unsigned char m_unmodelled[0x1fc];
	BodyModule *m_body;	// +0x200
};

struct PassiveAreaEffectBehaviorModuleData
{
	unsigned char m_unmodelled[0x0c];
	Real m_healPercentPerSecond;	// +0x0c
	UnsignedInt m_pingDelay;		// +0x10
};

class PassiveAreaEffectBehavior
{
public:
	virtual void rva00201fd0(Object *object);

	const PassiveAreaEffectBehaviorModuleData *m_moduleData;	// +0x04
	Object *m_object;										// +0x08
};

// ?rva00201fd0@PassiveAreaEffectBehavior@@UAEXPAVObject@@@Z
void PassiveAreaEffectBehavior::rva00201fd0(Object *object)
{
	if (object == 0)
		return;

	ObjectID sourceID;
	if (object->bfmeGetRecentDamageSource(&sourceID, 4))
		return;

	const PassiveAreaEffectBehaviorModuleData *data = m_moduleData;
	if (!(data->m_healPercentPerSecond > BfmeZeroRange))
		return;

	BodyModule *body = object->m_body;
	if (body == 0)
		return;

	const Real healPercentPerSecond = data->m_healPercentPerSecond;
	const Real amount = body->getMaxHealth() * healPercentPerSecond / 5.0f;
	object->attemptHealingFromSoleBenefactor(amount, m_object, data->m_pingDelay);
}
