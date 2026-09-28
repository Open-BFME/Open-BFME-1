// cl: /O2
// PartitionFilterRelationship::PartitionFilterRelationship(const Object*, Int, Bool)
// retail RVA 0x000EC770, 39 bytes.
//
// Identity: the body installs ??_7PartitionFilterRelationship@@6B@ (0x01085DC0,
// dir32_addresses.csv) at +0, zeroes the PartitionFilter::m_next link at +4 and
// stores its three arguments at +8, +0xC and +0x10 before returning `this`,
// which is the out-of-line form of Zero Hour's PartitionFilterRelationship
// constructor with BFME's extra Bool.  Its callers reach it through ILT
// 0x0000F4B1 to build full-expression filter temporaries (DumbProjectileBehavior
// 0x001F0960 among them).  The base-class layout is the one the matched
// ScriptConditionsTeamSighted_Rva00328020.cpp and ObjectCountNearbyEnemies.cpp
// filters use.

typedef bool Bool;
typedef int Int;

class Object;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *m_next;
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(const Object *obj, Int flags, Bool allowRelationship);

	virtual Bool allow(Object *objOther);

private:
	const Object *m_obj;
	Int m_flags;
	Bool m_allow;
};

// ??0PartitionFilterRelationship@@QAE@PBVObject@@H_N@Z
PartitionFilterRelationship::PartitionFilterRelationship(const Object *obj, Int flags, Bool allowRelationship)
	: m_obj(obj), m_flags(flags), m_allow(allowRelationship)
{
}
