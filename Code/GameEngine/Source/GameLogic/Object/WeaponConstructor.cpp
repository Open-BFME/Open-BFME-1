// cl: /DNDEBUG /MD /GX- /O2 /Ob2

enum WeaponSlotType
{
	WEAPON_SLOT_PLACEHOLDER
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponTemplate
{
public:
	float getMinTargetPitch() const { return *reinterpret_cast<const float *>(reinterpret_cast<const char *>(this) + 0x78); }
	float getMaxTargetPitch() const { return *reinterpret_cast<const float *>(reinterpret_cast<const char *>(this) + 0x7c); }
	int getShotsPerBarrel() const { return *reinterpret_cast<const int *>(reinterpret_cast<const char *>(this) + 0x4d0); }
	unsigned int getSuspendFXDelay() const { return *reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(this) + 0x518); }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame() const { return *reinterpret_cast<const unsigned int *>(reinterpret_cast<const char *>(this) + 0x3c); }
};

extern GameLogic *TheGameLogic;

class WeaponScatterTargets
{
public:
	WeaponScatterTargets() : m_begin(0), m_end(0), m_capacity(0) {}

private:
	int *m_begin;
	int *m_end;
	int *m_capacity;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
protected:
	Weapon(const WeaponTemplate *tmpl, WeaponSlotType wslot);
	virtual ~Weapon();

private:
	const WeaponTemplate *m_template;
	unsigned int m_unknown08;
	WeaponSlotType m_wslot;
	unsigned int m_status;
	unsigned int m_ammoInClip;
	unsigned int m_whenWeCanFireAgain;
	unsigned int m_whenPreAttackFinished;
	unsigned int m_whenLastReloadStarted;
	unsigned int m_lastFireFrame;
	unsigned int m_projectileStreamID;
	unsigned int m_unknown2c;
	unsigned int m_suspendFXFrame;
	int m_maxShotCount;
	int m_curBarrel;
	int m_numShotsForCurBarrel;
	WeaponScatterTargets m_scatterTargets;
	bool m_pitchLimited;
	unsigned char m_pad4d[3];
	unsigned int m_leechWeaponRangeActive;
	unsigned int m_unknown54;
	unsigned int m_tailState;
};

// ??0Weapon@@IAE@PBVWeaponTemplate@@W4WeaponSlotType@@@Z
Weapon::Weapon(const WeaponTemplate *tmpl, WeaponSlotType wslot)
{
	m_tailState = 0;
	m_template = tmpl;
	m_unknown08 = 0;
	m_wslot = wslot;
	m_status = 1;
	m_ammoInClip = 0;
	m_whenWeCanFireAgain = 0;
	m_whenPreAttackFinished = 0;
	m_whenLastReloadStarted = 0;
	m_lastFireFrame = 0;
	m_projectileStreamID = 0;
	m_leechWeaponRangeActive = 0;
	m_unknown54 = 0;
	m_pitchLimited = tmpl->getMinTargetPitch() > -3.14159265f || tmpl->getMaxTargetPitch() < 3.14159265f;
	m_curBarrel = 0;
	m_maxShotCount = 0x7fffffff;
	m_numShotsForCurBarrel = tmpl->getShotsPerBarrel();
	m_unknown2c = 0;
	m_suspendFXFrame = TheGameLogic->getFrame() + tmpl->getSuspendFXDelay();
}
