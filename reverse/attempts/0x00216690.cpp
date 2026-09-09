// ?shouldFireWeapon@FireWeaponCollide@@UAE_NXZ
// partial score=0.88 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail-layout ABI shim for FireWeaponCollide::shouldFireWeapon.

class BfmeFlagsZX
{
public:
	void set(unsigned int word0, unsigned int word1, unsigned int word2)
	{
		m_words[0] = word0;
		m_words[1] = word1;
		m_words[2] = word2;
	}

	bool bfmeAnyZX(const BfmeFlagsZX *other) const;
	bool bfmeRequiredAnyZX(const BfmeFlagsZX *other) const;

	unsigned int m_words[3];
};

class FireWeaponCollideModuleData
{
private:
	unsigned char m_prefix[0x0c];

public:
	BfmeFlagsZX m_requiredStatus;
	BfmeFlagsZX m_forbiddenStatus;
	bool m_fireOnce;
};

class FireWeaponCollideThing
{
public:
	unsigned char m_prefix[0x90];
	unsigned int m_status[3];
};

class FireWeaponCollide
{
public:
	virtual bool shouldFireWeapon();

private:
	FireWeaponCollideModuleData *m_moduleData;
	FireWeaponCollideThing *m_object;
	unsigned char m_between[0x0c];
	bool m_everFired;
};

// ?shouldFireWeapon@FireWeaponCollide@@ present-unmatched
bool FireWeaponCollide::shouldFireWeapon()
{
	FireWeaponCollideModuleData *d = m_moduleData;
	FireWeaponCollide *volatile self = this;
	unsigned int word0 = m_object->m_status[0];
	unsigned int word1 = m_object->m_status[1];
	unsigned int word2 = m_object->m_status[2];
	BfmeFlagsZX status;
	status.set(word0, word1, word2);

	if (status.bfmeAnyZX(&d->m_forbiddenStatus))
		return false;

	status.set(~word0, ~word1, (~word2) & 0x003fffff);
	if (status.bfmeAnyZX(&d->m_requiredStatus))
		return false;

	if (self->m_everFired && d->m_fireOnce)
		return false;

	return true;
}
