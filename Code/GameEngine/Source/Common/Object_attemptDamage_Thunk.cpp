// cl: /DNDEBUG /MD /EHsc
// Clean reconstruction of ?attemptDamage@Object@@QAEXPAVDamageInfo@@@Z.
//
// Retail keeps the body module at Object+0x200 and the private-status byte at
// Object+0x344.  The two non-virtual calls are retained as address-derived
// effect shims: their retail entries are incremental-link thunks, so the
// resolver selects the same thunk encoded by this body.

extern "C" const float bfmeConst1075350; // retail 0x01075350

class DamageInfo
{
public:
	char m_unreconstructed_00[0x3c];
	float m_damageAmount;
};

class BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
};

class ObjectAttemptDamageHook
{
public:
	void apply(DamageInfo *damageInfo);
};

class ObjectAttemptDamageFlagHook
{
public:
	int value();
};

// Existing clean source owns this method at 0x00414010; the retail call here
// uses its incremental-link entry at 0x00037FA6.
class Rva00414010GuardedVCall
{
public:
	void forward(int value);

	char m_unreconstructed_00[0x3ac];
	unsigned char m_flag3ac;
};

class Object
{
public:
	virtual void bfmeSlot00();
	virtual void bfmeSlot04();
	virtual void bfmeSlot08();
	virtual void bfmeSlot0c();
	virtual void bfmeSlot10();
	virtual void bfmeSlot14();
	virtual void bfmeSlot18();
	virtual void bfmeSlot1c();
	virtual void bfmeSlot20();
	virtual void bfmeSlot24();
	virtual Rva00414010GuardedVCall *getAttemptDamageEffect();

	void attemptDamage(DamageInfo *damageInfo);

private:
	char m_unreconstructed_000[0x1fc];
	BodyModuleInterface *m_body;          // retail this+0x200
	char m_unreconstructed_204[0x140];
	unsigned char m_privateStatus;         // retail this+0x344
};

// ?attemptDamage@Object@@QAEXPAVDamageInfo@@@Z
void Object::attemptDamage(DamageInfo *damageInfo)
{
	if ((m_privateStatus & 1) == 0)
	{
		BodyModuleInterface *body = m_body;
		if (body != 0)
			body->attemptDamage(damageInfo);
	}

	if ((m_privateStatus & 1) == 0
		|| damageInfo->m_damageAmount > bfmeConst1075350)
	{
		reinterpret_cast<ObjectAttemptDamageHook *>(this)->apply(damageInfo);
	}

	Rva00414010GuardedVCall *effect = getAttemptDamageEffect();
	if (effect != 0 && effect->m_flag3ac != 0)
	{
		int value = reinterpret_cast<ObjectAttemptDamageFlagHook *>(this)->value();
		effect->forward(value);
	}
}
