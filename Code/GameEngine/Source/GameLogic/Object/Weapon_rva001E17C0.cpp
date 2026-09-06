// cl: /DNDEBUG /MD
// Open-BFME5: retail 0x001E17C0, 150 bytes.
//
// This is Weapon::operator=(const Weapon&).  The live BFME record places the
// template pointer at +4 (the older shared header has a different base
// layout), so this focused TU states only the retail offsets used by this
// body.  The reference implementation documents the copy/reset semantics;
// the unnamed padding fields are BFME state whose owners are not yet matched.

class WeaponTemplate
{
public:
	float getMinTargetPitch() const
	{
		return *(const float *)((const char *)this + 0x78);
	}

	float getMaxTargetPitch() const
	{
		return *(const float *)((const char *)this + 0x7C);
	}

	int getShotsPerBarrel() const
	{
		return *(const int *)((const char *)this + 0x4D0);
	}
};

class Weapon
{
private:
	Weapon& operator=(const Weapon& that);

	void *m_baseVtable;
	const WeaponTemplate *m_template;
	unsigned int m_wslot;
	unsigned int m_copyC;
	unsigned int m_status;
	unsigned int m_ammoInClip;
	unsigned int m_whenWeCanFireAgain;
	unsigned int m_whenPreAttackFinished;
	unsigned int m_whenLastReloadStarted;
	unsigned int m_lastFireFrame;
	unsigned int m_field28;
	unsigned int m_reset2C;
	unsigned int m_field30;
	unsigned int m_maxShotCount;
	unsigned int m_curBarrel;
	unsigned int m_numShotsForCurBarrel;
	unsigned char m_pad40[0x0C];
	unsigned char m_pitchLimited;
	unsigned char m_pad4D[3];
	unsigned int m_reset50;
	unsigned int m_reset54;
	unsigned int m_reset58;
};

Weapon& Weapon::operator=(const Weapon& that)
{
	if (this != &that)
	{
		this->m_template = that.m_template;
		this->m_wslot = that.m_wslot;
		this->m_copyC = that.m_copyC;
		this->m_status = 1;
		this->m_ammoInClip = 0;
		this->m_whenPreAttackFinished = 0;
		this->m_whenLastReloadStarted = 0;
		this->m_lastFireFrame = 0;
		this->m_field28 = 0;
		this->m_whenWeCanFireAgain = 0;
		this->m_reset50 = 0;
		this->m_reset54 = 0;
		const int pitchLimited = (m_template->getMinTargetPitch() > -3.14159265358979323846f ||
			m_template->getMaxTargetPitch() < 3.14159265358979323846f) ? 1 : 0;
		this->m_pitchLimited = (unsigned char)pitchLimited;
		this->m_maxShotCount = 0x7FFFFFFF;
		this->m_curBarrel = 0;
		this->m_reset2C = 0;
		this->m_field30 = that.m_field30;
		this->m_numShotsForCurBarrel = (unsigned int)m_template->getShotsPerBarrel();
		this->m_reset58 = 0;
	}
	return *this;
}
