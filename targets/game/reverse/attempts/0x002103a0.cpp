// ?internalChangeHealth@ActiveBody@@UAEXM_N@Z
// partial score=0.29 date=2026-09-21
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ActiveBody::internalChangeHealth(Real delta, Bool something), retail
// 0x002103A0, size 592.
//
// Identity: ActiveBody_setMaxHealth.cpp already proves the vtable slot,
// signature (BFME adds a Bool second parameter over ZH's single-Real
// version) and the m_currentHealth(+0x08)/m_maxHealth(+0x10) layout; this
// body additionally proves m_prevHealth at +0x0c (ZH's declaration order:
// m_currentHealth, m_prevHealth, m_maxHealth). Pinned callees:
// GameLogic::findObjectByID (0x0001F253) and Object::setEffectivelyDead
// (0x00030887), both already used by the ZH tail
// `getObject()->setEffectivelyDead(m_currentHealth <= 0)`. The rest are
// indirect virtual calls through `this`'s own vtable and two BFME-only
// interfaces at this-8 (Object back-pointer, same as
// ActiveBody_setIndestructible.cpp) and this-0x10 (a second sub-object,
// unproven), so those stay address-derived.

typedef float Real;
typedef bool Bool;
typedef int Int;

#define BfmeZeroRange (*(const float *)0x01075350)
#define g_bfmeMul1 (*(const float *)0x01083b6c)
#define g_bfmeMul2 (*(const float *)0x0109f748)
#define g_bfmeDefaultBU (*(const float *)0x01075334)

class Object
{
public:
	void setEffectivelyDead(Bool isDead);		// pinned retail 0x00030887
	Bool getStatusBit90() const;			// this's own vtable slot 0x90, unproven
};

class BfmeActiveBodyGameLogic
{
public:
	Object *findObjectByID(int id);		// pinned retail 0x0001F253
};
extern BfmeActiveBodyGameLogic *TheBfmeGameLogic;	// VA 0x012F0898

class BfmeActiveBodySub10
{
public:
	void setCorrectDamageState(Int arg);		// this-0x10 sub-object, slot 0x48, unproven
};

class BodyModuleInterface
{
public:
	virtual void pad00(); virtual void pad04(); virtual void pad08(); virtual void pad0C();
	virtual void pad10(); virtual void pad14();
	virtual Real pad18();				// slot 0x18, returns a float seed
	virtual void pad1C(); virtual void pad20(); virtual void pad24(); virtual void pad28();
	virtual void pad2C(); virtual void pad30(); virtual void pad34(); virtual void pad38();
	virtual void pad3C(); virtual void pad40(); virtual void pad44(); virtual void pad48();
	virtual void pad4C(); virtual void pad50(); virtual void pad54(); virtual void pad58();
	virtual void pad5C(); virtual void pad60(); virtual void pad64(); virtual void pad68();
	virtual void pad6C(); virtual void pad70(); virtual void pad74(); virtual void pad78();
	virtual void pad7C();
	virtual void internalChangeHealth(Real delta, Bool something);
	virtual void setMaxHealth(Real maxHealth, int healthChangeType);
};

class ActiveBody : public BodyModuleInterface
{
public:
	virtual void internalChangeHealth(Real delta, Bool something);

private:
	unsigned char m_pad04[4];
	Real m_currentHealth;					// +0x08
	Real m_prevHealth;					// +0x0c
	Real m_maxHealth;					// +0x10
	unsigned char m_pad14[0x20 - 0x14];
	Int m_curDamageState;					// +0x20, unproven
	Int m_unreconstructed_24;
	unsigned char m_pad28[0x9c - 0x28];
	Real m_unreconstructed_9c;
	Real m_unreconstructed_a0;
	Real m_unreconstructed_a4;
	Real m_unreconstructed_a8;
	unsigned char m_pad_ac[0xbc - 0xac];
	Int m_linkedObjectId;					// +0xbc, unproven
};

void ActiveBody::internalChangeHealth(Real delta, Bool something)
{
	m_prevHealth = m_currentHealth;
	m_currentHealth += delta;

	Real maxHealth = m_maxHealth;
	if (m_currentHealth > maxHealth)
	{
		m_currentHealth = maxHealth;
		m_unreconstructed_9c = 0;
		m_unreconstructed_a0 = 0;
		m_unreconstructed_a4 = 0;
		m_unreconstructed_a8 = 0;
	}
	else
	{
		if (m_prevHealth < BfmeZeroRange)
		{
			Real v = pad18();
			v = v * g_bfmeMul1 * g_bfmeMul2 - g_bfmeDefaultBU;
			m_unreconstructed_9c = v;
			m_unreconstructed_a0 = v;
			m_unreconstructed_a4 = v;
			m_unreconstructed_a8 = v;
		}
		else if (delta > BfmeZeroRange)
		{
			Real reduce = delta * g_bfmeMul1 * g_bfmeMul2;

			m_unreconstructed_9c -= reduce;
			if (m_unreconstructed_9c < BfmeZeroRange)
				m_unreconstructed_9c = 0.0f;

			m_unreconstructed_a0 -= reduce;
			if (m_unreconstructed_a0 < BfmeZeroRange)
				m_unreconstructed_a0 = 0.0f;

			m_unreconstructed_a4 -= reduce;
			if (m_unreconstructed_a4 < BfmeZeroRange)
				m_unreconstructed_a4 = 0.0f;

			m_unreconstructed_a8 -= reduce;
			if (m_unreconstructed_a8 < BfmeZeroRange)
				m_unreconstructed_a8 = 0.0f;
		}
	}

	if (m_currentHealth < 0.0f)
		m_currentHealth = 0.0f;

	Object *us = *(Object **)((unsigned char *)this - 8);
	BfmeActiveBodySub10 *other = *(BfmeActiveBodySub10 **)((unsigned char *)this - 0x10);
	Int savedState = m_curDamageState;
	Int savedOther = m_unreconstructed_24;

	other->setCorrectDamageState(0);

	if (m_curDamageState != savedState || m_unreconstructed_24 != savedOther)
	{
		us->setEffectivelyDead(m_currentHealth <= 0.0f);

		Int linkedId = m_linkedObjectId;
		if (linkedId)
		{
			Object *other2 = TheBfmeGameLogic->findObjectByID(linkedId);
			if (other2)
			{
				BodyModuleInterface *body2 = *(BodyModuleInterface **)((unsigned char *)other2 + 0x200);
				if (body2)
				{
					body2->internalChangeHealth(m_currentHealth, delta > BfmeZeroRange);
					*(Int *)((unsigned char *)other2 + 0x220) = *(Int *)((unsigned char *)us + 0x220);
				}
			}
		}
	}
}
