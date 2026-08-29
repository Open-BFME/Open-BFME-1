// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef unsigned int UnsignedInt;

class Object;

enum WeaponStatus
{
	READY_TO_FIRE = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
friend class Object;

private:
	WeaponStatus bfmeComputeStatus(Bool *unknown) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/FiringTracker.h
class FiringTracker
{
public:
	unsigned char m_pad[0x44];
	UnsignedInt m_recentActivityFrame;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_pad[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool bfmeHasActiveOrRecentlyActiveWeapon() const;

private:
	unsigned char m_pad000[0x1ec];
	FiringTracker *m_firingTracker;
	unsigned char m_pad1f0[0x26c - 0x1f0];
	Weapon *m_weapons[4];
	int m_currentWeaponSlot;
	unsigned char m_pad280[4];
	void *m_currentWeaponTemplateSet;
};

Bool Object::bfmeHasActiveOrRecentlyActiveWeapon() const
{
	if (m_currentWeaponTemplateSet)
	{
		Weapon *weapon = m_weapons[m_currentWeaponSlot];
		if (weapon)
		{
			if (weapon->bfmeComputeStatus(0) != READY_TO_FIRE)
				return true;

			FiringTracker *tracker = m_firingTracker;
			if (tracker)
			{
				UnsignedInt recentFrame = tracker->m_recentActivityFrame;
				if (recentFrame > 2 && recentFrame + 10 > TheGameLogic->m_frame)
					return true;
			}
		}
	}
	return false;
}
