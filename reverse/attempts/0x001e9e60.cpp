// ?d_001e9e60@@YAXXZ
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

class ObjectFilter
{
public:
	Bool isValid() const;
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(Int id);

	char m_unreconstructed_00[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;
extern void j_00040589();

class Object
{
public:
	char m_unreconstructed_00[0x1fc];
	void *m_ammoModule;
};

class AmmoModule
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00c() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01c() = 0;
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02c() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038() = 0;
	virtual void slot03c() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual void slot04c() = 0;
	virtual void slot050() = 0;
	virtual void slot054() = 0;
	virtual void slot058() = 0;
	virtual void slot05c() = 0;
	virtual void slot060() = 0;
	virtual void slot064() = 0;
	virtual void slot068() = 0;
	virtual void slot06c() = 0;
	virtual void slot070() = 0;
	virtual void slot074() = 0;
	virtual void slot078() = 0;
	virtual void slot07c() = 0;
	virtual void slot080() = 0;
	virtual void slot084() = 0;
	virtual void slot088() = 0;
	virtual void slot08c() = 0;
	virtual void slot090() = 0;
	virtual void slot094() = 0;
	virtual void slot098() = 0;
	virtual void slot09c() = 0;
	virtual void slot0a0() = 0;
	virtual void slot0a4() = 0;
	virtual void slot0a8() = 0;
	virtual void slot0ac() = 0;
	virtual void slot0b0() = 0;
	virtual void slot0b4() = 0;
	virtual void slot0b8() = 0;
	virtual void slot0bc() = 0;
	virtual void slot0c0() = 0;
	virtual void slot0c4() = 0;
	virtual void slot0c8() = 0;
	virtual void slot0cc() = 0;
	virtual void slot0d0() = 0;
	virtual void slot0d4() = 0;
	virtual void slot0d8() = 0;
	virtual void slot0dc() = 0;
	virtual void slot0e0() = 0;
	virtual void slot0e4() = 0;
	virtual void slot0e8() = 0;
	virtual void slot0ec() = 0;
	virtual void slot0f0() = 0;
	virtual void slot0f4() = 0;
	virtual void slot0f8() = 0;
	virtual void slot0fc() = 0;
	virtual Int getRemainingAmmo(const ObjectFilter *filter) = 0;
};

class WeaponTemplate
{
public:
	Int getClipSize() const { return m_clipSize; }
	ObjectFilter *getAmmoFilter() const
	{
		return (ObjectFilter *)((char *)this + 0x4e8);
	}

	char m_unreconstructed_000[0x4ac];
	Int m_clipSize;
	char m_unreconstructed_4b0[0x4e8 - 0x4b0];
	ObjectFilter m_ammoFilter;
};

class Weapon
{
public:
	void setClipPercentFull(Real percent, Bool allowReduction);
	UnsignedInt getRemainingAmmo(Bool countReloadingAsEmpty) const;
	void rebuildScatterTargets();
	Int getStatusAmmo() const;

	char m_unreconstructed_00[4];
	const WeaponTemplate *m_template;
	Int m_projectileStreamID;
	Int m_wslot;
	Int m_status;
	Int m_ammoInClip;
	UnsignedInt m_whenWeCanFireAgain;
	char m_unreconstructed_1c[0xc];
	UnsignedInt m_whenLastReloadStarted;
};

__forceinline Int Weapon::getStatusAmmo() const
{
	if (m_template->getAmmoFilter()->isValid())
	{
		Object *projectileStream = TheGameLogic->findObjectByID(m_projectileStreamID);
		if (projectileStream)
		{
			AmmoModule *module = (AmmoModule *)projectileStream->m_ammoModule;
			if (module)
				return module->getRemainingAmmo(m_template->getAmmoFilter());
		}
	}
	return m_ammoInClip;
}

extern "C" __declspec(dllimport) double __cdecl floor(double);

__forceinline long fast_float2long_round(float value)
{
	long result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

void Weapon::setClipPercentFull(Real percent, Bool allowReduction)
{
	if (m_template->getClipSize() == 0)
		return;

	percent = (Real)floor((double)m_template->getClipSize() * percent);
	volatile Int ammo;
	__asm {
		fld [percent]
		fistp [ammo]
	}

	ObjectFilter *filter = m_template->getAmmoFilter();
	AmmoModule *module;
	if (!filter->isValid())
		goto fallbackAmmo;
	{
		Object *projectileStream = TheGameLogic->findObjectByID(m_projectileStreamID);
		if (projectileStream)
			module = (AmmoModule *)projectileStream->m_ammoModule;
		else
			module = 0;
	}

	if (module)
	{
		if (ammo > module->getRemainingAmmo(m_template->getAmmoFilter()))
			goto updateAmmo;
		goto checkReduction;
	}

fallbackAmmo:
	if (ammo > m_ammoInClip)
		goto updateAmmo;

checkReduction:
	if (!allowReduction || ammo >= getRemainingAmmo(false))
		return;

updateAmmo:
	m_ammoInClip = ammo;
	Int status = getStatusAmmo() ? 1 : 0;
	if (m_status != status)
		m_status = status;
	m_whenLastReloadStarted = TheGameLogic->m_frame;
	m_whenWeCanFireAgain = m_whenLastReloadStarted;
	rebuildScatterTargets();
}
