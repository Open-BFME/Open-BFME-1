// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Object::attemptHealingFromSoleBenefactor, retail 0x001CE240: Object vtable slot 17 (+0x44, ILT 0x00036D6D).
#include <bitset>

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

enum ObjectID { INVALID_ID = 0 };
enum DamageType { DAMAGE_HEALING_BFME = 7 };
enum DeathType { DEATH_NONE = 1 };
// Index 15 of the retail KindOf name table at 0x012AA068 is "SWARM_DOZER".
enum KindOfType { KINDOF_SWARM_DOZER = 15 };

class ModelConditionFlags { public:
	bool test(int bit) const { return bits.test(bit); }
	void set(int bit) { bits.set(bit); }
	void reset(int bit) { bits.reset(bit); }
private: _STL::bitset<320> bits;
};

class Snapshot
{
protected:
	virtual void crc();
	virtual void xfer();
	virtual void loadPostProcess();
};

class DamageInfoInput : public Snapshot
{
public:
	ObjectID m_sourceID;
	UnsignedInt m_sourcePlayerMask;
	DamageType m_damageType;
	DamageType m_damageFXOverride;
	DeathType m_deathType;
	Real m_amount;
	unsigned char m_unreconstructed[0x48 - 0x1C];
};

class DamageInfoOutput : public Snapshot
{
public:
	Real m_actualDamageDealt;
	Real m_actualDamageClipped;
	Bool m_noEffect;
};

class DamageInfo : public Snapshot
{
public:
	DamageInfo();
	DamageInfoInput in;
	DamageInfoOutput out;
};

class Overridable
{
public:
	virtual void overridableSlot00();
	const Overridable *getFinalOverride() const;
	const Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType t) const { return m_kindof.test(t); }
	unsigned char m_unreconstructed008[0xC8 - 0x08];
	ModelConditionFlags m_kindof;						// +0xC8 KindOf bits, same 320-bit storage
	unsigned char m_unreconstructed0F0[0x4CA - 0xF0];
	Bool m_bfme4CA;										// +0x4CA gates the revive-on-heal step below
};

template <class T> class OverridePtr
{
public:
	operator const T *() const
	{
		if (m_overridable == 0)
			return 0;
		if (m_overridable->m_nextOverride == 0)
			return m_overridable;
		return static_cast<const T *>(m_overridable->m_nextOverride->getFinalOverride());
	}
	const T *m_overridable;
};

class GameLogic
{
public:
	unsigned char m_pad[0x3C];
	UnsignedInt m_frame;
	UnsignedInt getFrame() const { return m_frame; }
};
extern GameLogic *TheGameLogic;

class Drawable {
public: void replaceModelConditionState(const ModelConditionFlags &, UnsignedInt, UnsignedInt);
};
class AIUpdateInterface { public: virtual void friend_notifyStateMachineChanged(); };

class BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
	virtual void attemptHealing(DamageInfo *damageInfo);	// slot 1 (+0x04)
};

class Thing
{
public:
	virtual void thingSlot00(); virtual void thingSlot01(); virtual void thingSlot02(); virtual void thingSlot03();
	virtual void thingSlot04(); virtual void thingSlot05(); virtual void thingSlot06(); virtual void thingSlot07();
	const ThingTemplate *getTemplate() const { return m_template; }
	Bool isKindOf(KindOfType t) const;
	OverridePtr<ThingTemplate> m_template;				// +0x04
	unsigned char m_unreconstructed008[0x60 - 0x08];
};

class Object : public Thing
{
public:
	virtual void objectSlot08(); virtual void objectSlot09(); virtual void objectSlot10(); virtual void objectSlot11();
	virtual void objectSlot12(); virtual void objectSlot13(); virtual void objectSlot14(); virtual void objectSlot15();
	virtual void objectSlot16();
	virtual Bool attemptHealingFromSoleBenefactor(Real amount, const Object *source, UnsignedInt duration);

	ObjectID getID() const { return m_id; }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	void setEffectivelyDead(Bool dead);
	__forceinline void clearModelConditionState(int bit)
	{
		if (m_modelConditionFlags.test(bit))
		{
			m_modelConditionFlags.reset(bit);
			if (m_drawable) m_drawable->replaceModelConditionState(m_modelConditionFlags, 0, 0);
			if (m_ai) m_ai->AIUpdateInterface::friend_notifyStateMachineChanged();
		}
	}
	__forceinline void setModelConditionState(int bit)
	{
		if (!m_modelConditionFlags.test(bit))
		{
			m_modelConditionFlags.set(bit);
			if (m_drawable) m_drawable->replaceModelConditionState(m_modelConditionFlags, 0, 0);
			if (m_ai) m_ai->AIUpdateInterface::friend_notifyStateMachineChanged();
		}
	}
	// Same body as the out-of-line Object::attemptHealing at 0x001C3080, inlined here in retail.
	__forceinline void attemptHealingInline(Real amount, const Object *source)
	{
		BodyModuleInterface *body = m_body;
		if (body)
		{
			DamageInfo damageInfo;
			damageInfo.in.m_damageType = DAMAGE_HEALING_BFME;
			damageInfo.in.m_deathType = DEATH_NONE;
			damageInfo.in.m_sourceID = source ? source->getID() : INVALID_ID;
			damageInfo.in.m_amount = amount;
			body->attemptHealing(&damageInfo);
		}
	}

	unsigned char m_unreconstructed060[0x74 - 0x60];
	ObjectID m_id;											// +0x74
	unsigned char m_unreconstructed078[0x80 - 0x78];
	Drawable *m_drawable;									// +0x80
	unsigned char m_unreconstructed084[0x110 - 0x84];
	ModelConditionFlags m_modelConditionFlags;				// +0x110
	unsigned char m_unreconstructed138[0x200 - 0x138];
	BodyModuleInterface *m_body;							// +0x200
	AIUpdateInterface *m_ai;								// +0x204
	unsigned char m_unreconstructed208[0x2D0 - 0x208];
	ObjectID m_soleHealingBenefactorID;						// +0x2D0
	UnsignedInt m_soleHealingBenefactorExpirationFrame;		// +0x2D4
	unsigned char m_unreconstructed2D8[0x344 - 0x2D8];
	unsigned char m_privateStatus;							// +0x344
};

// ?attemptHealingFromSoleBenefactor@Object@@UAE_NMPBV1@I@Z
Bool Object::attemptHealingFromSoleBenefactor(Real amount, const Object *source, UnsignedInt duration)
{
	if (!source)
		return false;

	UnsignedInt now = TheGameLogic->getFrame();
	ObjectID id = source->getID();

	if (now > m_soleHealingBenefactorExpirationFrame || m_soleHealingBenefactorID == id || source->isKindOf(KINDOF_SWARM_DOZER))
	{
		// A swarm dozer heals without claiming the sole benefactor slot.
		if (!source->getTemplate()->isKindOf(KINDOF_SWARM_DOZER))
		{
			m_soleHealingBenefactorID = id;
			m_soleHealingBenefactorExpirationFrame = now + duration;
		}

		attemptHealingInline(amount, source);

		if (getTemplate()->m_bfme4CA)
		{
			clearModelConditionState(5);
			if (isEffectivelyDead())
			{
				setModelConditionState(4);
				setEffectivelyDead(false);
			}
		}
		return true;
	}

	return false;
}
