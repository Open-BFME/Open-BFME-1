// BFME retail 0x001CC790: crush-policy wrapper called by wantToSquishTarget.
// The lower-level Object::canCrushOrSquish body is at retail 0x001C7600.

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;

enum CrushSquishTestType
{
	TEST_CRUSH_OR_SQUISH = 2
};

enum Relationship
{
	RELATIONSHIP_ALLIES = 2
};

class Object;

class Rva001E1770ByteField
{
public:
	unsigned char get() const;
};

class Rva001CC790Weapon
{
private:
	unsigned char m_pad00[4];

public:
	Rva001E1770ByteField *m_template;
};

class Object
{
public:
	bool canCrushOrSquish(Object *other, CrushSquishTestType testType) const;
	Relationship getRelationship(const Object *other) const;

	bool crushPolicy(Object *other, CrushSquishTestType testType) const;

private:
	unsigned char m_pad00[0x94];
	UnsignedInt m_status;
	unsigned char m_pad98[0x11c - 0x98];
	UnsignedInt m_conditionFlags;
	unsigned char m_pad120[0x26c - 0x120];
	Rva001CC790Weapon *m_weapons[4];
	UnsignedInt m_curWeapon;
	unsigned char m_pad280[4];
	void *m_weaponSet;
};

// ?crushPolicy@Object@@QBE_NPAV1@W4CrushSquishTestType@@@Z
bool Object::crushPolicy(Object *other, CrushSquishTestType testType) const
{
	if (!canCrushOrSquish(other, testType))
		return false;
	if ((m_status & 0x01020000) != 0 ||
		(m_conditionFlags & 0x10000000) != 0)
		goto allowed;
	if (getRelationship(other) == RELATIONSHIP_ALLIES)
		return false;
	if (m_weaponSet != 0)
	{
		Rva001CC790Weapon *weapon = m_weapons[m_curWeapon];
		if (weapon != 0 && weapon->m_template->get() == 0)
			return false;
	}
allowed:
	return true;
}
