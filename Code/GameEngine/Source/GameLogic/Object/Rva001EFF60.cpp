// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /GX- /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: retail 0x001EFF60 size 244, dump d_001e7c30.
// Interior this at owner+0x20. Prefix through Owner vtable+0x2c is byte-true;
// tail is Object::setModelConditionState (bitset test/set at +0x110 word 4
// mask 0x10000 = bit 144) plus MAKE_OBJECT_STATUS_MASK(OBJECT_STATUS_NO_ATTACK)
// — the same BitFlags ctor ProneUpdate uses. Hand-rolled masks fold to test-imm.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum ModelConditionFlagType
{
	MODELCONDITION_BIT_144 = 144
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_NO_ATTACK = 5
};

template<int NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int idx1)
	{
		m_bits.set(idx1);
	}

	BitFlags() { }

	Bool test(Int idx) const { return m_bits.test(idx); }
	void set(Int idx) { m_bits.set(idx); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<288> ModelConditionFlags;
typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

struct Coord3D
{
	float x;
	float y;
	float z;
};

class BfmeSubC1054;
class BfmeD1054
{
public:
	void bfmeAdd1054(BfmeSubC1054 *item);
};

class Object
{
public:
	void notifyModelConditionChanged(void);
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set = true);

	void setModelConditionState(ModelConditionFlagType bit)
	{
		if (!m_conditionFlags.test(bit))
		{
			m_conditionFlags.set(bit);
			notifyModelConditionChanged();
		}
	}

	char m_pad000[0x38];
	Coord3D m_position;
	char m_pad044[0x74 - 0x44];
	int m_id;
	char m_pad078[0x110 - 0x78];
	ModelConditionFlags m_conditionFlags;
	char m_pad134[0x2a0 - 0x134];
	unsigned m_bonusMask;
};

class Weapon
{
public:
	static void positionProjectileForLaunch(Object *projectile, const Object *launcher,
		WeaponSlotType wslot, Int specificBarrelToUse);
};

class Owner
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
	virtual void _v10();
	virtual void notify(Object *victim, void *arg2);

	int m_pad04;
	Object *m_object;
};

class Rva001EFF60
{
public:
	void run(Object *victim, void *arg2, Object *source, WeaponSlotType wslot,
		Int barrel, void *a6, int a7, BfmeSubC1054 *a8);

	void *m_pad00;
	void *m_pad04;
	int m_sourceId;
	Coord3D m_pos;
	int m_victimId;
	int m_fromA6;
	int m_a7;
	char m_pad24[0x54 - 0x24];
	unsigned m_bonusMask;
	int m_clear58;
};

// ?run@Rva001EFF60@@QAEXPAVObject@@PAX0W4WeaponSlotType@@HPAXHPAVBfmeSubC1054@@@Z
void Rva001EFF60::run(Object *victim, void *arg2, Object *source, WeaponSlotType wslot,
	Int barrel, void *a6, int a7, BfmeSubC1054 *a8)
{
	m_sourceId = source ? source->m_id : 0;
	m_bonusMask = source ? source->m_bonusMask : 0;

	Object *vic = victim;
	m_victimId = vic ? vic->m_id : 0;
	m_fromA6 = ((int *)a6)[1];
	m_a7 = a7;
	m_clear58 = 0;

	Object *obj = *(Object **)((char *)this - 0x18);

	if (a8)
		((BfmeD1054 *)obj)->bfmeAdd1054(a8);
	else
		Weapon::positionProjectileForLaunch(obj, source, wslot, barrel);

	Coord3D *pos = source ? &source->m_position : &obj->m_position;
	Coord3D *dst = (Coord3D *)((char *)this + 0x0c);
	*dst = *pos;

	void *arg = arg2;
	((Owner *)((char *)this - 0x20))->notify(vic, arg);

	obj->setModelConditionState(MODELCONDITION_BIT_144);
	obj->setStatus(MAKE_OBJECT_STATUS_MASK(OBJECT_STATUS_NO_ATTACK), true);
}
