// ?bfmeComputeStatus@Weapon@@ABE?AW4WeaponStatus@@PA_N@Z
// partial score=0.45 date=2026-09-01
// cl: /O2 /Ob0

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum WeaponStatus
{
	READY_TO_FIRE = 0,
	OUT_OF_AMMO = 1,
	PRE_ATTACK = 4,
	BFME_STATUS_5 = 5
};

class GameLogic
{
public:
	unsigned char m_pad[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class BfmeAmmoDescriptor
{
public:
	Bool isValid() const;
};

class WeaponTemplate
{
public:
	unsigned char m_pad00[0x68];
	int m_flag68;
	unsigned char m_pad6c[0x4e8 - 0x6c];
	BfmeAmmoDescriptor m_ammo;
};

class Weapon
{
public:
	UnsignedInt getRemainingAmmo(Bool countReloadingAsEmpty) const;
	Bool bfmeAmmoReady() const;

private:
	WeaponStatus bfmeComputeStatus(Bool *valid) const;

	void *m_vptr;
	const WeaponTemplate *m_template;
	unsigned char m_pad08[0x08];
	WeaponStatus m_status;
	unsigned char m_pad14[4];
	UnsignedInt m_whenWeCanFireAgain;
	UnsignedInt m_whenPreAttackFinished;
	UnsignedInt m_whenStatus5;
};

WeaponStatus Weapon::bfmeComputeStatus(Bool *valid) const
{
	UnsignedInt now = TheGameLogic->m_frame;
	if (now < m_whenPreAttackFinished)
	{
		if (valid)
			*valid = false;
		return PRE_ATTACK;
	}
	if (now < m_whenStatus5)
	{
		if (valid)
			*valid = false;
		return BFME_STATUS_5;
	}

	{
		const WeaponTemplate *n1 = m_template;
		int n2 = n1->m_flag68;
		UnsignedInt n3 = m_whenWeCanFireAgain;
		if (n2 >= 0)
		{
			if (now < n3)
			{
				if (n1->m_ammo.isValid())
				{
					if (getRemainingAmmo(0) > 0)
						return READY_TO_FIRE;
				}
			}
		}
	}

	if (now >= m_whenWeCanFireAgain)
	{
		if (m_template->m_ammo.isValid())
		{
			if (bfmeAmmoReady())
				return READY_TO_FIRE;
		}
		return OUT_OF_AMMO;
	}

	if (now < m_whenWeCanFireAgain)
	{
		if (m_template->m_ammo.isValid())
			return m_status;
	}

	return getRemainingAmmo(0) ? READY_TO_FIRE : OUT_OF_AMMO;
}
