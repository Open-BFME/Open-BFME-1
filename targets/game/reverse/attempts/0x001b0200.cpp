// ?Gen001B0200ArmorMultiplier@@YGMPBXPAVObject@@PBM@Z
// partial score=0.1 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc

// Retail RVA 0x001B0200 (232 bytes). Served from Code/gen_asm/d_001aba80.asm.
// No named caller identity beyond the three ILT-thunk call sites already
// resolved in the lane brief (three callers, all still-dump thunks
// themselves). Fast path: when the first argument's +0xc type field is 7,
// the function returns that argument's +0x18 float unchanged. Otherwise it
// walks a small override chain off the second argument's (an Object*) +4
// field (falling back to the +4 pointer itself when its own +4 sub-field is
// null) through the pinned getFinalOverride/findArmorTemplateSet pair to
// find an ArmorTemplateSet, multiplies its +4->+0x5c float (or 1.0f when no
// set was found) by a per-kind float pulled from the caller's own array
// argument, then folds in Object::getAttributeModifierBonus(1, ...) capped
// against GlobalData::AttributeModifierArmorMaxBonus and finished against
// g_bfmeDefaultBU. The exact FPU compare/select shape at the tail
// (FCOMP/FNSTSW/JP choosing between the live bonus and the GlobalData cap)
// is reconstructed from the raw bytes and not independently confirmed.

typedef float Real;
typedef int Int;
typedef bool Bool;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

class ArmorTemplateSet;

class ThingTemplateArmor : public Overridable
{
public:
	const ArmorTemplateSet *findArmorTemplateSet(const void *flags) const;
};

class Object
{
public:
	Bool getAttributeModifierBonus(Int which, Real *out) const;
};

struct Rva006C9270GlobalData
{
	unsigned char m_bfmeHeadRW[0xbac];
	float m_attributeModifierArmorMaxBonus;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;
extern float g_bfmeDefaultBU;

// Virtual accessor on the object at Object+0x200 (a body-module style
// interface) that fills an ArmorSetFlags (a 4-byte BitFlags<ARMORSET_COUNT>)
// through a hidden-return pointer and hands the same address back in EAX.
class BodyModuleFlagsSource
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual unsigned int *getCurrentArmorSetFlags(unsigned int *out) const;
};

// ?bfmeArmorMultiplier@Gen_001B0200@@YGMPBXPAVObject@@PBM@Z
Real __stdcall Gen001B0200ArmorMultiplier(const void *param1, Object *object, const float *kindMultipliers)
{
	const unsigned char *p1 = (const unsigned char *)param1;
	int kind = *(const int *)(p1 + 0xc);
	float raw = *(const float *)(p1 + 0x18);

	if (kind == 7)
		return raw;

	const unsigned char *obj = (const unsigned char *)object;
	void *a = *(void **)(obj + 4);
	const ThingTemplateArmor *tmpl = 0;

	if (a)
	{
		void *b = *(void **)((unsigned char *)a + 4);
		if (b)
			tmpl = (const ThingTemplateArmor *)((const Overridable *)b)->getFinalOverride();
		else
			tmpl = (const ThingTemplateArmor *)a;
	}

	BodyModuleFlagsSource *flagsSource = *(BodyModuleFlagsSource **)(obj + 0x200);
	unsigned int flags = 0;
	flagsSource->getCurrentArmorSetFlags(&flags);

	const ArmorTemplateSet *set = tmpl->findArmorTemplateSet(&flags);

	Real multiplier = 1.0f;
	if (set)
		multiplier = *(const Real *)((const unsigned char *)(*(const void **)((const unsigned char *)set + 4)) + 0x5c);

	if (kind == 8)
		return multiplier * kindMultipliers[0];

	if (kind == 0)
		return multiplier * kindMultipliers[0];

	multiplier *= kindMultipliers[kind];

	Real bonus = 0.0f;
	object->getAttributeModifierBonus(1, &bonus);

	Real cap = TheWritableGlobalData->m_attributeModifierArmorMaxBonus;
	Real chosen = (bonus < cap || bonus > cap || bonus == cap) ? bonus : cap;

	return (g_bfmeDefaultBU - chosen) * multiplier;
}
