// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// BFME Object method at retail 0x001CC250, 831 bytes, ret 4. Identity unknown:
// its callers are the generated body 0x00216D90 (just after the SquishCollide
// module data, through ILT 0x0001FFBE) and itself, so the name keeps the address
// in the form the neighbours 0x001CC660 and 0x001CC790 use.
//
// What the body proves:
//  * it does nothing when `other` carries private-status bit 0 (+0x344);
//  * it plays sound slot 0x6C for this object: slot 10 of the Object vtable
//    (getDrawable, per vtable 0x0109EE58) feeds 0x00416FA0, which is pinned as
//    ThingTemplate::getSound but sits among Drawable.cpp bodies. The receiver
//    cast keeps the pinned symbol;
//  * when the container (+0x214) has KindOf 0x6C it re-dispatches to the
//    container and stops;
//  * with a positive template value at +0x3F4 it calls the matched
//    Object::rva001C7CF0 on `other`. The angle is this object's facing plus 0.3
//    of the relative angle to `other`, capped at PI/2, then converted to degrees.
//    The magnitude is +0x3F4 and the vertical scale +0x3F8;
//  * it then scales the current locomotor speed by template +0x3F0 and by
//    attribute-modifier kinds 8 and 16, divides by the contain count, and hands
//    the clamped shortfall to the locomotor at AI+0x1CC.
//
// 0x001BD790 has no ledger row. It is 24 bytes (`if (v < m_3c) m_3c = v;` on
// the locomotor), reached through ILT 0x00032A24, which carries an
// address-named pin.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

#include "ascii_string.h"

typedef float Real;
typedef bool Bool;
typedef int Int;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum ObjectID { INVALID_ID = 0 };
enum KindOfType { KINDOF_RVA001CC250_6C = 0x6C };

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &src);
	~AudioEventRTS();
	void setObjectID(ObjectID id);

private:
	unsigned int m_unmodelled[0x70 / 4];
};

class ThingTemplate
{
public:
	const AudioEventRTS *getSound(Int index) const;

	void *m_vtable;							// 0x000
	Overridable *m_nextOverride;			// 0x004
	unsigned char m_pad008[0x3ec - 0x008];
	Real m_real3EC;							// 0x3ec
	Real m_real3F0;							// 0x3f0
	Real m_real3F4;							// 0x3f4
	Real m_real3F8;							// 0x3f8
};

class AudioManager
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void unusedSlot05();
	virtual void unusedSlot06();
	virtual void unusedSlot07();
	virtual void unusedSlot08();
	virtual void unusedSlot09();
	virtual void unusedSlot10();
	virtual void unusedSlot11();
	virtual void unusedSlot12();
	virtual void unusedSlot13();
	virtual void unusedSlot14();
	virtual void unusedSlot15();
	virtual void unusedSlot16();
	virtual void addAudioEvent(const AudioEventRTS *event);	// vtable +0x44
};

extern AudioManager *TheAudio;

// The locomotor at AIUpdateInterface+0x1CC, named as Object_rva001CC660.cpp
// names it.
class BfmeSub1CC_EC3
{
public:
	float queryCached(class Object *val);
	// 0x001BD790 through ILT 0x00032A24: lowers the float at +0x3C to the value.
	void rva001BD790(float value);
	void cache1B4980(float value, unsigned int frames);
};

class AIUpdateInterface
{
public:
	Real getCurLocomotorSpeed();

	unsigned char m_pad[0x1cc];
	BfmeSub1CC_EC3 *m_curLocomotor;			// 0x1cc
};

class AttributeModifierPoolUpdate
{
public:
	Bool getAttributeModifierMultiplier(Int kind, Real *multiplier);
};

class ContainModuleInterface
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
	virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
	virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
	virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c();
	virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6c();
	virtual void s70(); virtual void s74(); virtual void s78(); virtual void s7c();
	virtual void s80(); virtual void s84(); virtual void s88(); virtual void s8c();
	virtual void s90(); virtual void s94(); virtual void s98(); virtual void s9c();
	virtual void sa0(); virtual void sa4(); virtual void sa8(); virtual void sac();
	virtual void sb0(); virtual void sb4(); virtual void sb8(); virtual void sbc();
	virtual void sc0(); virtual void sc4(); virtual void sc8(); virtual void scc();
	virtual void sd0(); virtual void sd4(); virtual void sd8(); virtual void sdc();
	virtual void se0(); virtual void se4(); virtual void se8(); virtual void sec();
	virtual void sf0(); virtual void sf4(); virtual void sf8(); virtual void sfc();
	virtual Int containSlot100(Int arg);	// vtable +0x100: the contained count
};

template <class T> T clamp(T lo, T value, T hi);

#define BFME_HAVE_COORD3D
#define BFME_HAVE_OBJECTID
#define THING_TU_MEMBERS \
	Bool isKindOf(KindOfType kind) const; \
	const ThingTemplate *getTemplate() const; \
	Real bfmeRelativeAngleTo(const Coord3D *pos) const; \
	const ThingTemplate *getFinalTemplate() const \
	{ \
		const ThingTemplate *tmpl = m_template; \
		if (tmpl && tmpl->m_nextOverride) \
			tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride(); \
		return tmpl; \
	}
#define OBJECT_TU_MEMBERS \
	void rva001C7CF0(Real angleDegrees, Real magnitude, Real verticalScale, const AsciiString &rockName); \
	void rva001CC250(Object *other); \
	ObjectID getID() const { return m_id; } \
private: \
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const; \
public:
#include "object.h"

void Object::rva001CC250(Object *other)
{
	if (other->m_privateStatus & 1)
		return;

	if (getDrawable() && TheAudio)
	{
		// 0x00416FA0 is pinned under ThingTemplate; its receiver is what slot 10
		// returns.
		const ThingTemplate *soundOwner = (const ThingTemplate *)getDrawable();
		AudioEventRTS sound = *soundOwner->getSound(0x6C);
		sound.setObjectID(getID());
		TheAudio->addAudioEvent(&sound);
	}

	// One variable carries the +0x3F4 magnitude and then the speed factor:
	// retail keeps both in the same frame slot, and it keeps the AsciiString
	// temporary and the kind-16 multiplier in slots of their own. Declaring
	// the two at function scope reproduces that frame.
	Real factor;
	Real multiplier;
	Object *container = m_containedBy;
	if (container && container->isKindOf(KINDOF_RVA001CC250_6C))
	{
		container->rva001CC250(other);
		return;
	}

	{
		factor = getFinalTemplate()->m_real3F4;
		Real verticalScale = getFinalTemplate()->m_real3F8;
		if (factor > 0.0f)
		{
			Real angle = bfmeRelativeAngleTo(&other->m_cachedPos);
			if (angle > 1.5707964f)
				angle = 1.5707964f;
			angle = angle * 0.3f + m_cachedAngle;
			other->rva001C7CF0(angle * 57.2957763671875f, factor, verticalScale, AsciiString(""));
		}
	}

	AIUpdateInterface *ai = m_ai;
	if (!ai)
		return;

	factor = getFinalTemplate()->m_real3F0;
	Real bonus = 1.0f;
	AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
	if (pool && pool->getAttributeModifierMultiplier(8, &bonus))
		factor *= bonus;
	if (factor <= 0.0f)
		return;
	{
		if (!m_ai)
			return;
		BfmeSub1CC_EC3 *locomotor = m_ai->m_curLocomotor;
		if (!locomotor)
			return;

		Real current = locomotor->queryCached(this);
		factor = ai->getCurLocomotorSpeed() * factor;
		if (isKindOf(KINDOF_RVA001CC250_6C))
		{
			ContainModuleInterface *contain = m_contain;
			if (contain)
			{
				Int count = contain->containSlot100(0);
				if (count > 1)
					factor = factor / count;
			}
		}

		Real reduction;
		multiplier = 1.0f;
		pool = findAttributeModifierPoolUpdate();
		if (pool && pool->getAttributeModifierMultiplier(16, &multiplier))
		{
			Real base = clamp(0.05f, getTemplate()->m_real3EC, 0.95f);
			multiplier = clamp(0.05f, base * multiplier, 0.95f);
			reduction = (1.0f - base) / (1.0f - multiplier) * factor;
		}
		else
		{
			reduction = factor;
		}

		Real speed = current - reduction;
		if (speed < 0.0f)
			speed = 0.0f;
		locomotor->rva001BD790(speed);
		locomotor->cache1B4980(speed, 5);
	}
}
