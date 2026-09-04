// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponSet::getModelConditionForWeaponSlot, retail 0x001EB8F0 size 244.
// Focused TU: WeaponSet.cpp keeps ZH WEAPONSLOT_COUNT==3 and one Using
// table. BFME still indexes three live slots but the rdata rows are
// five dwords, Lookup has six WSF entries (UNUSED and PREATTACK share
// the pre-attack row), and two extra per-slot tables are OR'd in for
// FIRING/UNUSED/PREATTACK and FIRING/RELOADING. Return is BitFlags<320>.

typedef int Int;
typedef unsigned int UnsignedInt;

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

enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};

template <int NUMBITS>
class BitFlags
{
public:
	void set(Int bit)
	{
		m_bits[(UnsignedInt)bit >> 5] |= 1 << ((UnsignedInt)bit & 31);
	}

	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<320> ModelConditionFlags;

class WeaponSet
{
public:
	static ModelConditionFlags getModelConditionForWeaponSlot(
		WeaponSlotType wslot, WeaponSetConditionType a);
};

// ?getModelConditionForWeaponSlot@WeaponSet@@SA?AV?$BitFlags@$0BEA@@@W4WeaponSlotType@@W4WeaponSetConditionType@@@Z
ModelConditionFlags WeaponSet::getModelConditionForWeaponSlot(
	WeaponSlotType wslot, WeaponSetConditionType a)
{
	static const ModelConditionFlagType Nothing[WEAPONSLOT_COUNT] =
		{ MODELCONDITION_INVALID, MODELCONDITION_INVALID, MODELCONDITION_INVALID, (ModelConditionFlagType)0, (ModelConditionFlagType)0 };
	static const ModelConditionFlagType Firing[WEAPONSLOT_COUNT] =
		{ (ModelConditionFlagType)40, (ModelConditionFlagType)46, (ModelConditionFlagType)52, (ModelConditionFlagType)0, (ModelConditionFlagType)0 };
	static const ModelConditionFlagType Betweening[WEAPONSLOT_COUNT] =
		{ (ModelConditionFlagType)43, (ModelConditionFlagType)49, (ModelConditionFlagType)55, (ModelConditionFlagType)0, (ModelConditionFlagType)0 };
	static const ModelConditionFlagType Reloading[WEAPONSLOT_COUNT] =
		{ (ModelConditionFlagType)44, (ModelConditionFlagType)50, (ModelConditionFlagType)56, (ModelConditionFlagType)0, (ModelConditionFlagType)0 };
	static const ModelConditionFlagType PreAttack[WEAPONSLOT_COUNT] =
		{ (ModelConditionFlagType)39, (ModelConditionFlagType)45, (ModelConditionFlagType)51, (ModelConditionFlagType)0, (ModelConditionFlagType)0 };
	static const ModelConditionFlagType *Lookup[WSF_COUNT] =
		{ Nothing, Firing, Betweening, Reloading, PreAttack, PreAttack };
	static const ModelConditionFlagType Using[WEAPONSLOT_COUNT] =
		{ (ModelConditionFlagType)116, (ModelConditionFlagType)117, (ModelConditionFlagType)118, (ModelConditionFlagType)0, (ModelConditionFlagType)0 };
	static const ModelConditionFlagType ExtraBetween[WEAPONSLOT_COUNT] =
		{ (ModelConditionFlagType)41, (ModelConditionFlagType)47, (ModelConditionFlagType)53, (ModelConditionFlagType)0, (ModelConditionFlagType)0 };
	static const ModelConditionFlagType ExtraReload[WEAPONSLOT_COUNT] =
		{ (ModelConditionFlagType)42, (ModelConditionFlagType)48, (ModelConditionFlagType)54, (ModelConditionFlagType)0, (ModelConditionFlagType)0 };

	WeaponSetConditionType cond = a;
	ModelConditionFlags flags = {};
	ModelConditionFlagType f = Lookup[cond][wslot];
	if (f != MODELCONDITION_INVALID)
		flags.set(f);
	if (cond != WSF_NONE)
		flags.set(Using[wslot]);
	if (cond == WSF_FIRING || cond == WSF_UNUSED || cond == WSF_PREATTACK)
		flags.set(ExtraBetween[wslot]);
	if (cond == WSF_FIRING || cond == WSF_RELOADING)
		flags.set(ExtraReload[wslot]);
	return flags;
}
