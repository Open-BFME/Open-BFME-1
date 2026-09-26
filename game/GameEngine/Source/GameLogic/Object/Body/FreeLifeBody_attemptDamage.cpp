// cl: /DNDEBUG /MD /EHsc

// FreeLifeBody::attemptDamage, retail 0x00213690.
//
// The function is the slot-zero override in FreeLifeBody's BodyModuleInterface
// secondary table.  Calls through that table enter with ECX pointing at the
// +0x10 interface subobject, so the +0xE0 flag is seen at +0xD0 and the
// BehaviorModule fields at +0x04/+0x08 are reached as -0x0C/-0x08.

class DamageInfo;

class FreeLifeBodyModuleData
{
private:
	unsigned char m_unmodelled_00[0x70];

public:
	unsigned int m_respawnPolicyIndex;
};

class Object
{
private:
	unsigned char m_unmodelled_00[0x110];

public:
	unsigned int m_statusBits[1];
};

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const FreeLifeBodyModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
};

class RespawnBody : public BehaviorModule,
	public BehaviorModuleInterface,
	public BodyModuleInterface
{
public:
	virtual ~RespawnBody();

private:
	unsigned char m_unmodelled_14[0xE0 - 0x14];
};

class FreeLifeBody : public RespawnBody
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);

private:
	bool m_unmodelled_E0;
};

// ?attemptDamage@FreeLifeBody@@UAEXPAVDamageInfo@@@Z
void FreeLifeBody::attemptDamage(DamageInfo *damageInfo)
{
	if (m_unmodelled_E0)
	{
		const unsigned int index = m_moduleData->m_respawnPolicyIndex;
		if ((m_object->m_statusBits[index >> 5] & (1u << (index & 31))) != 0)
			return;
	}

	BodyModuleInterface::attemptDamage(damageInfo);
}
