// ?preFireWeapon@Weapon@@QAEXPBVObject@@HH@Z
// partial score=0.98 date=2026-09-04
// ?preFireWeapon@Weapon@@QAEXPBVObject@@HH@Z
// partial score=0.98 date=2026-09-04
// cl: /DNDEBUG /MD
// Open-BFME5: Weapon::preFireWeapon, retail 0x001E8970 size 403.
// Three-arg BFME pre-fire: GameLogicRandomValue(0, template+0x504) into this+0x58,
// then getPreAttackDelay; on a positive delay set PRE_ATTACK, computeBonus, write
// the pre-attack / last-fire / leech frames from template+0x50C and +0x500, run
// the template pre-fire list, then the four-arg FXList::doFXPos on the source
// drawable. Size-exact 403; six ModRM bytes remain (fx in ebx vs retail edi,
// first getPosition in edi vs retail ebx). Register-rotation wall.

typedef unsigned int UnsignedInt;

int GetGameLogicRandomValue(int low, int high, char *file, int line);

struct Coord3D
{
	float x, y, z;
};

class Matrix3D;

class WeaponBonus
{
public:
	WeaponBonus()
	{
		m_field[0] = 1.0f;
		m_field[1] = 1.0f;
		m_field[2] = 1.0f;
		m_field[3] = 1.0f;
		m_field[4] = 1.0f;
		m_field[5] = 1.0f;
	}

	float m_field[6];
};

class FXList
{
public:
	bool isEmpty() const;
	void doFXPos(const Coord3D *primary, const Matrix3D *mtx, float speed,
			const Coord3D *secondary) const;
};

class Drawable
{
public:
	const Coord3D *getPosition() const;
	const Matrix3D *getTransformMatrix() const;
};

class Object
{
public:
	virtual void _v00();
	virtual void _v01();
	virtual void _v02();
	virtual void _v03();
	virtual void _v04();
	virtual void _v05();
	virtual void _v06();
	virtual void _v07();
	virtual void _v08();
	virtual void _v09();
	virtual Drawable *getDrawable() const;
};

class GameLogic
{
public:
	unsigned int getFrame() const
	{
		return *reinterpret_cast<const unsigned int *>(
			reinterpret_cast<const char *>(this) + 0x3c);
	}
};

extern GameLogic *TheGameLogic;

class Weapon;

class WeaponTemplate
{
public:
	void notifyPreFire(Weapon *weapon, const Object *source, int a, int b);

	unsigned char m_pad000[0x58];
	float m_weaponSpeed;
	unsigned char m_pad05c[0xa4 - 0x5c];
	FXList *m_fireFX;
	unsigned char m_pad0a8[0x4f8 - 0xa8];
	unsigned char m_isLeechRangeWeapon;
	unsigned char m_pad4f9[3];
	unsigned char m_pad4fc[4];
	int m_preAttackDelay;
	int m_preAttackRandom;
	unsigned char m_pad508[4];
	int m_timingExtra;
};

enum WeaponStatus
{
	READY_TO_FIRE,
	OUT_OF_AMMO,
	BETWEEN_FIRING_SHOTS,
	RELOADING_CLIP,
	PRE_ATTACK
};

class Weapon
{
public:
	void preFireWeapon(const Object *source, int arg2, int arg3);
	int getPreAttackDelay(const Object *source, int arg2, int arg3) const;

protected:
	void computeBonus(const Object *source, UnsignedInt extra, WeaponBonus &bonus) const;

private:
	void *m_vptr;
	WeaponTemplate *m_template;
	unsigned int m_unknown08;
	unsigned int m_wslot;
	unsigned int m_status;
	unsigned int m_ammoInClip;
	unsigned int m_whenWeCanFireAgain;
	unsigned int m_whenPreAttackFinished;
	unsigned int m_whenLastReloadStarted;
	unsigned int m_lastFireFrame;
	unsigned char m_pad028[0x50 - 0x28];
	unsigned int m_leechWeaponRangeActive;
	unsigned int m_unknown54;
	unsigned int m_preAttackJitter;
};

// ?preFireWeapon@Weapon@@QAEXPBVObject@@HH@Z
void Weapon::preFireWeapon(const Object *source, int arg2, int arg3)
{
	int jitter = m_template->m_preAttackRandom;
	if (jitter)
		jitter = GetGameLogicRandomValue(
			0,
			jitter,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Weapon.cpp",
			3292);
	else
		jitter = 0;
	m_preAttackJitter = jitter;

	int delay = getPreAttackDelay(source, arg2, arg3);
	if (delay <= 0)
		return;

	if (m_status != PRE_ATTACK)
		m_status = PRE_ATTACK;

	WeaponBonus bonus;
	computeBonus(source, 0, bonus);

	WeaponTemplate *tmpl = m_template;
	int extra = (int)(float)tmpl->m_timingExtra;
	UnsignedInt now = TheGameLogic->getFrame();
	if (m_whenPreAttackFinished + ((UnsignedInt)extra >> 1) <= now)
	{
		m_whenPreAttackFinished = now + delay;
		extra = (int)(float)tmpl->m_timingExtra;
		if (extra > 0)
			m_lastFireFrame = TheGameLogic->getFrame() + extra + delay;
	}

	if (tmpl->m_isLeechRangeWeapon)
	{
		int leech = (int)((float)tmpl->m_preAttackDelay * bonus.m_field[4]);
		int extra2 = (int)(float)tmpl->m_timingExtra;
		m_leechWeaponRangeActive = TheGameLogic->getFrame() + leech + extra2;
	}

	tmpl->notifyPreFire(this, source, arg2, arg3);

	float speed = tmpl->m_weaponSpeed;
	FXList *fx = tmpl->m_fireFX;
	const Coord3D *posA = source->getDrawable()->getPosition();
	const Matrix3D *mtx = source->getDrawable()->getTransformMatrix();
	const Coord3D *posB = source->getDrawable()->getPosition();
	if (fx)
	{
		if (!fx->isEmpty())
			fx->doFXPos(posB, mtx, speed, posA);
	}
}
