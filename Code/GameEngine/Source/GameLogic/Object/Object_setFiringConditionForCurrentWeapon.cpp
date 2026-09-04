// cl: /DNDEBUG /MD /EHsc
// BFME Object::setFiringConditionForCurrentWeapon.  The BFME build returns
// ten dwords from WeaponSet::getModelConditionForWeaponSlot, unlike the ZH
// three-dword layout used by Object.cpp.

typedef unsigned int UnsignedInt;

template <int NUMBITS>
class BitFlags
{
public:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<320> ModelConditionFlags;

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0,
	SECONDARY_WEAPON = 1,
	TERTIARY_WEAPON = 2,
	QUATERNARY_WEAPON = 3,
	WEAPONSLOT_COUNT = 5
};

enum WeaponSetConditionType
{
	WSF_INVALID = -1,
	WSF_NONE = 0,
	WSF_FIRING = 1,
	WSF_BETWEEN = 2,
	WSF_RELOADING = 3,
	WSF_UNUSED = 4,
	WSF_PREATTACK = 5,
	WSF_COUNT = 6
};

class WeaponSet
{
public:
	static ModelConditionFlags getModelConditionForWeaponSlot(
		WeaponSlotType slot, WeaponSetConditionType condition);
};

class Object
{
public:
	void setFiringConditionForCurrentWeapon() const;
	void clearAndSetModelConditionFlags(const ModelConditionFlags &clear,
		const ModelConditionFlags &set);
};

static const ModelConditionFlags s_allWeaponFireFlags[WEAPONSLOT_COUNT] = {};

// ?setFiringConditionForCurrentWeapon@Object@@QBEXXZ
void Object::setFiringConditionForCurrentWeapon() const
{
	Object *self = (Object *)this;
	if (*(void **)((char *)self + 0x80) != 0)
	{
		WeaponSlotType slot = *(WeaponSlotType *)((char *)self + 0x27c);
		ModelConditionFlags flags = WeaponSet::getModelConditionForWeaponSlot(
			slot, WSF_FIRING);
		self->clearAndSetModelConditionFlags(s_allWeaponFireFlags[slot], flags);
	}
}
