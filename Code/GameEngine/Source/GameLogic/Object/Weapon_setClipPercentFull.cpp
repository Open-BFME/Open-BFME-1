// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Weapon::setClipPercentFull(Real, Bool), retail 0x001E9E60 (288 bytes).
// The Zero Hour body with BFME's ammo source: while the template's object filter
// at +0x4E8 is valid and the object at Weapon+0x08 has a contain module, the
// ammo count comes from that module's slot 64 instead of m_ammoInClip. The count
// helper is inlined twice (the compare and the status), and REAL_TO_INT_FLOOR
// is floorf (the VC7.1 math.h inline over the floor import) fed to the
// fast_float2long_round x87 helper from Lib/BaseType.h.

#include <math.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;
typedef Int ObjectID;

// verbatim from Lib/BaseType.h
__forceinline long fast_float2long_round(float f)
{
	long i;

	__asm {
		fld [f]
		fistp [i]
	}

	return i;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(floorf(x)))

class ObjectFilter
{
public:
	Bool isValid() const;
};

// The contain module Object+0x1FC holds; only its slot 64 (+0x100) is used here.
class Rva001E9E60ContainView
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual UnsignedInt slot64(const ObjectFilter *filter);
};

class Object
{
public:
	Rva001E9E60ContainView *getContain() const { return m_contain; }

	char m_unreconstructed_00[0x1fc];
	Rva001E9E60ContainView *m_contain;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	UnsignedInt getFrame() const { return m_frame; }

	char m_unreconstructed_00[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class WeaponTemplate
{
public:
	Int getClipSize() const { return m_clipSize; }
	const ObjectFilter &getObjectFilter4e8() const { return m_objectFilter4e8; }

	char m_unreconstructed_000[0x4ac];
	Int m_clipSize;
	char m_unreconstructed_4b0[0x4e8 - 0x4b0];
	ObjectFilter m_objectFilter4e8;
};

class Weapon
{
public:
	void setClipPercentFull(Real percent, Bool allowReduction);
	UnsignedInt getRemainingAmmo(Bool countReloadingAsEmpty) const;
	const WeaponTemplate *getTemplate() const { return m_template; }

protected:
	void rebuildScatterTargets();

private:
	__forceinline Rva001E9E60ContainView *rva001E9E60Contain() const
	{
		Object *obj = TheGameLogic->findObjectByID(m_objectID08);
		return obj ? obj->getContain() : 0;
	}
	__forceinline UnsignedInt rva001E9E60AmmoCount() const
	{
		if (getTemplate()->getObjectFilter4e8().isValid())
		{
			Rva001E9E60ContainView *contain = rva001E9E60Contain();
			if (contain)
				return contain->slot64(&getTemplate()->getObjectFilter4e8());
		}
		return m_ammoInClip;
	}

	Int m_dword00;
	const WeaponTemplate *m_template;
	ObjectID m_objectID08;
	Int m_dword0c;
	Int m_status;
	UnsignedInt m_ammoInClip;
	UnsignedInt m_whenWeCanFireAgain;
	char m_unreconstructed_1c[0x28 - 0x1c];
	UnsignedInt m_whenLastReloadStarted;
};

// ?setClipPercentFull@Weapon@@QAEXM_N@Z
void Weapon::setClipPercentFull(Real percent, Bool allowReduction)
{
	if (m_template->getClipSize() == 0)
		return;

	Int ammo = REAL_TO_INT_FLOOR(m_template->getClipSize() * percent);
	if (ammo > rva001E9E60AmmoCount() || (allowReduction && ammo < getRemainingAmmo(false)))
	{
		m_ammoInClip = ammo;
		Int status = rva001E9E60AmmoCount() ? 1 : 0;
		if (m_status != status)
			m_status = status;
		m_whenLastReloadStarted = TheGameLogic->getFrame();
		m_whenWeCanFireAgain = m_whenLastReloadStarted;
		rebuildScatterTargets();
	}
}
