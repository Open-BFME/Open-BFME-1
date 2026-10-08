class BfmeSubCLE;

class Object;

// retail ILT 0x0002E85C -> 0x001E8930 is the matched
// Weapon::isWithinAttackRange(const Object *, const Object *, int) row
class Weapon
{
public:
	bool isWithinAttackRange(const Object *source, const Object *target, int extra) const;
};

// retail ILT 0x00009C41 -> 0x001BE270 is the matched
// AssistedTargetingObjectShim::find row
class AssistedTargetingObjectShim
{
public:
	void *find(int value);
};

class BfmeThingCLE
{
public:
	bool bfmeGoCLE(void *what);
	unsigned char m_bfmeHead[0xc];
	BfmeSubCLE *m_bfmeSub;
};

bool BfmeThingCLE::bfmeGoCLE(void *what)
{
	if (((AssistedTargetingObjectShim *)m_bfmeSub)->find(0) == 0)
		return true;
	return ((Weapon *)((AssistedTargetingObjectShim *)m_bfmeSub)->find(0))->isWithinAttackRange((const Object *)m_bfmeSub, (const Object *)what, 0);
}
