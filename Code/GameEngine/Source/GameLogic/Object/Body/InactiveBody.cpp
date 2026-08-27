// cl: /DNDEBUG /MD /EHsc

class DamageInfo;

// Retail's estimateDamage reads the damage type at +0xc and the amount at
// +0x18 of its DamageInfoInput argument.  DamageInfo below spells the same
// two fields four bytes further out, so BFME's DamageInfo carries a four-byte
// prefix ahead of the embedded input block; nothing here needs the rest.
class DamageInfoInput
{
public:
	char m_pad[0xc];
	int m_damageType;
	char m_padAfterType[8];
	float m_amount;
};

class Object
{
public:
	void onDie(DamageInfo *);
};

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	unsigned int m_moduleData;
	Object *m_object;
	unsigned int m_behaviorState;
};

class BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *) = 0;
	virtual void attemptHealing(DamageInfo *) = 0;
	virtual float estimateDamage(DamageInfoInput &) const = 0;
};

class DamageInfo
{
	public:
	char m_inputPrefix[0x10];
	int m_damageType;
	char m_inputTail[0x3c];
	float m_actualDamageDealt;
	float m_actualDamageClipped;
	bool m_noEffect;
};

class InactiveBody : public BehaviorModule, public BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *);
	virtual void attemptHealing(DamageInfo *);
	virtual float estimateDamage(DamageInfoInput &) const;

private:
	float m_health;
	bool m_dieCalled;
};

void InactiveBody::attemptDamage(DamageInfo *damageInfo)
{
	if (!damageInfo) {
		return;
	}

	if (damageInfo->m_damageType == 7) {
		attemptHealing(damageInfo);
		return;
	}

	damageInfo->m_actualDamageDealt = 0.0f;
	damageInfo->m_actualDamageClipped = 0.0f;
	damageInfo->m_noEffect = true;

	if (damageInfo->m_damageType == 8) {
		damageInfo->m_noEffect = false;
		if (!m_dieCalled) {
			m_object->onDie(damageInfo);
			m_dieCalled = true;
		}
	}
}

// ?estimateDamage@InactiveBody@@UBEMAAVDamageInfoInput@@@Z
float InactiveBody::estimateDamage(DamageInfoInput &damageInfo) const
{
	// Inactive bodies have no health so no damage can really be done
	float amount = 0.0f;

	// exception!
	if (damageInfo.m_damageType == 8)	// DAMAGE_UNRESISTABLE
	{
		amount = damageInfo.m_amount;
	}

	return amount;
}
