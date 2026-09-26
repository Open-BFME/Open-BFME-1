// Neutral raw-ABI reconstruction of retail RVA 0x001C9380 (215 bytes).
// The retail boundary is an Object-like thiscall: ECX is the receiver,
// two four-byte arguments are stack-owned, and the epilogue is ret 8.
// Union members model reuse of both argument slots after their inputs die.
// The volatile integer store preserves the retail x87 conversion spill.

typedef bool Bool;
typedef int Int;
typedef float Real;

class Object;

union Rva001C9380VictimArgument
{
	Object *object;
	Int experience;
	Real gain;
};

union Rva001C9380Argument
{
	Bool allow;
	Real multiplier;
};

class ExperienceTracker
{
public:
	Bool isAcceptingExperiencePoints() const;
	void addExperiencePoints(
		Real experienceGain,
		Bool canScaleForBonus,
		Bool isShared,
		Bool allowLevelGain,
		Bool provideFeedback);

	unsigned char m_unreconstructed00[0x24];
	unsigned char m_state24;
};

class AttributeModifierPoolUpdate
{
public:
	Bool getAttributeModifierMultiplier(Int attribute, Real *multiplier);
};

class BfmeOtherCGG
{
};

class BfmeThingCGG
{
public:
	void *bfmeGoCGG(BfmeOtherCGG *other, Bool flag);
};

class Bfme5WalkOwner
{
};

class Bfme5WalkHit
{
public:
	virtual void applyExperience(Real experience) = 0;
};

Bfme5WalkHit * __cdecl bfme5WalkFindHit(Bfme5WalkOwner *owner);
extern const Real BfmeZeroRange;

class Object
{
public:
	void rva001c9380(Rva001C9380VictimArgument victim, Rva001C9380Argument allow);

private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;

	unsigned char m_unreconstructed000[0x90];
	unsigned char m_status;
	unsigned char m_unreconstructed091[0x17f];
	ExperienceTracker *m_experienceTracker;
	unsigned char m_unreconstructed214[0x170];
	unsigned char m_feedbackFlags384;
};

void Object::rva001c9380(Rva001C9380VictimArgument victim, Rva001C9380Argument allow)
{
	if (m_experienceTracker == 0
		|| !m_experienceTracker->isAcceptingExperiencePoints())
		return;

	if ((victim.object->m_status & 4) != 0)
		return;

	BfmeThingCGG *victimTracker =
		reinterpret_cast<BfmeThingCGG *>(victim.object->m_experienceTracker);
	static_cast<volatile Int &>(victim.experience) = reinterpret_cast<Int>(victimTracker->bfmeGoCGG(
		reinterpret_cast<BfmeOtherCGG *>(this), allow.allow));
	victim.gain = static_cast<Real>(victim.experience);
	Real &experienceGain = victim.gain;
	allow.multiplier = 1.0f;
	Real &multiplier = allow.multiplier;
	AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
	if (pool != 0 && pool->getAttributeModifierMultiplier(5, &multiplier))
		experienceGain *= multiplier;

	m_experienceTracker->addExperiencePoints(
		experienceGain, true, true, true, false);
	if (experienceGain > BfmeZeroRange)
	{
		m_feedbackFlags384 |= m_experienceTracker->m_state24;
		Bfme5WalkHit *hit = bfme5WalkFindHit(
			reinterpret_cast<Bfme5WalkOwner *>(this));
		if (hit != 0)
			hit->applyExperience(experienceGain);
	}
}
