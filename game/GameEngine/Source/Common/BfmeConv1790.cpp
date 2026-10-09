class BfmeThingMD;

// retail walks the override chain through ILT 0x000022BB, which targets
// Overridable::getFinalOverride (matching row 0x00087A80).
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;
};

class BfmeInnerMD
{
};

class BfmeThingMD
{
public:
	int m_bfmeSpareMD;
	BfmeInnerMD *m_bfmeInnerMD;
	unsigned char m_bfmeGapMD[0xcc];
	int m_bfmeFlagsMD;
};

class BfmeSubMD
{
public:
	char bfmeTestMD(void);
};

class BfmeItemMD
{
public:
	int m_bfmeSpareMD;
	BfmeSubMD *m_bfmeSubMD;
};

class BfmeHolderMD
{
public:
	BfmeItemMD *bfmeFindMD(int flag);

	int m_bfmeSpareMD;
	BfmeThingMD *m_bfmeThingMD;
};

class BfmeOwnerMD
{
public:
	char bfmeCheckMD(void);

	unsigned char m_bfmeHeadMD[8];
	BfmeHolderMD *m_bfmeHolderMD;
};

class Weapon;
enum WeaponSlotType;

class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
};

class Rva001E1770ByteField
{
public:
	unsigned char get(void) const;
};

char BfmeOwnerMD::bfmeCheckMD(void)
{
	BfmeHolderMD *holder = m_bfmeHolderMD;
	BfmeThingMD *thing = holder->m_bfmeThingMD;

	if (thing && thing->m_bfmeInnerMD)
		thing = (BfmeThingMD *)(const void *)((const Overridable *)thing->m_bfmeInnerMD)->getFinalOverride();

	if (thing->m_bfmeFlagsMD & 0x400000)
	{
		BfmeItemMD *item = (BfmeItemMD *)((Object *)(void *)holder)->getCurrentWeapon((WeaponSlotType *)0);

		if (item)
			return ((Rva001E1770ByteField *)(void *)item->m_bfmeSubMD)->get();

		return 1;
	}

	return 0;
}
