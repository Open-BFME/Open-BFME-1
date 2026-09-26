// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

// 0x00189E80 is a real partition-query body, but no named BFME caller or
// registration has been recovered yet.  Keep this TU's owner neutral until
// that identity evidence exists.  The stores below are the retail data
// contract, not filler: Object::m_position is at +0x38, the first filter has
// a vptr/next/Object layout, the second has vptr/next/Object/int/int, and the
// third has vptr/next/Object/int/Bool.  The two relationship-shaped filters
// are intentionally separate because retail stores the second trailing value
// as a dword but the confirmed 0x01085DC0 relationship filter stores a byte.

typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object
{
private:
	unsigned char m_unreconstructed_00[0x38];

public:
	Coord3D m_position; // +0x38 in the actual Object layout below
};

class AI
{
public:
	static Real getAdjustedVisionRangeForObject(const Object *object, int factors);
};

class PartitionFilter
{
public:
	__forceinline PartitionFilter(void) : m_next(0) {}
	PartitionFilter *link(PartitionFilter *next);

	// Retail's three filter objects use this explicit polymorphic prefix.  The
	// vptr values below are the observed BFME tables, not compiler-generated
	// tables for this neutral TU.
	unsigned int m_vptr;
	PartitionFilter *m_next;
};

class Rva00189E80SameMapFilter : public PartitionFilter
{
public:
	__forceinline explicit Rva00189E80SameMapFilter(const Object *object)
		: PartitionFilter()
	{
		m_vptr = 0x01085DD0;
		m_object = object;
	}

	~Rva00189E80SameMapFilter(void)
	{
		m_vptr = 0x01083B80;
	}

private:
	const Object *m_object;
};

// The 0x010956C4 table's slot-1 target is an ICF'd BFME body whose public
// class identity is not established.  Its constructor layout is established
// by the retail stores and by the matched 0x00149E60 setter, so retain a
// truthful neutral type rather than borrowing a nearby filter name.
class Rva00189E80RelationshipShapedFilter : public PartitionFilter
{
public:
	__forceinline Rva00189E80RelationshipShapedFilter(const Object *object, int flags, int state)
		: PartitionFilter()
	{
		m_vptr = 0x010956C4;
		m_object = object;
		m_flags = flags;
		m_state = state;
	}

	~Rva00189E80RelationshipShapedFilter(void)
	{
		m_vptr = 0x01083B80;
	}

private:
	const Object *m_object;
	int m_flags;
	int m_state;
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	__forceinline PartitionFilterRelationship(const Object *object, int flags, Bool state)
		: PartitionFilter()
	{
		m_vptr = 0x01085DC0;
		m_object = object;
		m_flags = flags;
		m_state = state;
	}

	~PartitionFilterRelationship(void)
	{
		m_vptr = 0x01083B80;
	}

private:
	const Object *m_object;
	int m_flags;
	Bool m_state;
};

// The 0x009F26A0 wrapper is the BFME four-argument PartitionManager query,
// not an integer transport helper.  Its retail body forwards the typed
// Coord3D*, Real, distance discriminator, and filter head through the
// manager's +0xC implementation and returns that implementation's Object*.
class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		int distanceCalculation, PartitionFilter *filters);
};

extern PartitionManager *ThePartitionManager;

class Rva00189E80ObjectVision : public Object
{
public:
	Object *query(void);
};

Object *Rva00189E80ObjectVision::query(void)
{
	Rva00189E80SameMapFilter sameMap(this);
	Rva00189E80RelationshipShapedFilter relationshipShaped(this, 2, 0);
	PartitionFilterRelationship relationship(this, 1, false);

	Real range = AI::getAdjustedVisionRangeForObject(this, 7);
	PartitionFilter *filters = relationshipShaped.link(&sameMap);
	filters = relationship.link(filters);

	return ThePartitionManager->getClosestObject(
		&m_position, range, 0, filters);
}
