// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;

enum WeaponStatus
{
	READY_TO_FIRE,
	OUT_OF_AMMO,
	BETWEEN_FIRING_SHOTS,
	RELOADING_CLIP,
	PRE_ATTACK,
	BETWEEN_FIRING_SHOTS_2
};

class GameLogic40D9
{
public:
	char m_fields[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic40D9 *TheGameLogic;

class Weapon
{
public:
	float getPercentReadyToFire() const;

private:
	WeaponStatus bfmeComputeStatus(bool *cacheStatus) const;

	char m_fields[0x18];
	UnsignedInt m_whenWeCanFireAgain;
	char m_fields1c[0x0c];
	UnsignedInt m_whenLastReloadStarted;
};

float Weapon::getPercentReadyToFire() const
{
	switch (bfmeComputeStatus(0))
	{
		case OUT_OF_AMMO:
		case PRE_ATTACK:
			return 0.0f;

		case READY_TO_FIRE:
			return 1.0f;

		case BETWEEN_FIRING_SHOTS:
		case RELOADING_CLIP:
		case BETWEEN_FIRING_SHOTS_2:
		{
			UnsignedInt now = TheGameLogic->m_frame;
			UnsignedInt nextShot = m_whenWeCanFireAgain;
			if (now >= nextShot)
				return 1.0f;

			UnsignedInt totalTime = nextShot - m_whenLastReloadStarted;
			if (totalTime == 0)
				return 1.0f;

			UnsignedInt timeSoFar = totalTime - (nextShot - now);
			if (timeSoFar >= totalTime)
				return 1.0f;

			return static_cast<float>(timeSoFar) /
				static_cast<float>(totalTime);
		}

	}

	return 0.0f;
}
