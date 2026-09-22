// ?d_002d0a80@@YAXXZ
// partial score=0.33 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob1 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// ?bfmeQueryRallyOverride@...@@YAPAVObject@@PAV1@PBUCoord3D@@@Z

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags() {}

	BitFlags(BogusInitType, Int first, Int second)
	{
		m_bits[0] = 0;
		m_bits[1] = 0;
		m_bits[2] = 0;
		m_bits[3] = 0x00200000;
		m_bits[4] = 0x00000040;
		m_bits[5] = 0;
	}

private:
	UnsignedInt m_bits[6];
};

typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

struct Rva0021FC80Mask
{
	UnsignedInt m_bits[6];

	enum BogusInitType
	{
		kInit = 0
	};

	Rva0021FC80Mask() {}

	Rva0021FC80Mask(BogusInitType, Int first, Int second)
	{
		m_bits[0] = 0;
		m_bits[1] = 0;
		m_bits[2] = 0;
		m_bits[3] = 0x00200000;
		m_bits[4] = 0x00000040;
		m_bits[5] = 0;
	}
};

class AttributeHandleStandIn
{
public:
	AttributeHandleStandIn();
	~AttributeHandleStandIn();

private:
	UnsignedInt m_handle;
};

class Rva0039FF30Filter : public AttributeHandleStandIn
{
public:
	void setMasks(Rva0021FC80Mask, Rva0021FC80Mask);
};

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

class Rva00265150RJFilter : public PartitionFilter
{
public:
	Rva00265150RJFilter(void *subobject, void *extra, Bool match)
		: m_subobject(subobject), m_extra(extra), m_match(match) {}
	virtual ~Rva00265150RJFilter() {}
	virtual Bool allow(Object *);

	void *m_subobject;
	void *m_extra;
	Bool m_match;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *, Real, Int, PartitionFilter *);
};

extern PartitionManager *ThePartitionManager;

class ExitInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual Bool slot06() = 0;
};

class Rva002D0A80ContainView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual Bool slot10() = 0;
};

enum Relationship
{
	Relationship_Thunk = 0
};

class Object
{
public:
	ExitInterface *getObjectExitInterface() const;
	Relationship getRelationship(const Object *) const;
};

class Rva000CBA20Point
{
public:
	Real x;
	Real y;
};

class Rva000CBA20
{
	char m_pad[0x38];
	Real m_x;
	Real m_y;

public:
	Real distSq(const Rva000CBA20Point *);
};

Object *bfmeQueryRallyOverride(Object *object, const Coord3D *position)
{
	Object *source = object;
	const Coord3D *point = position;
	if (source && point)
	{
		Rva0039FF30Filter handle;
		handle.setMasks(*(const Rva0021FC80Mask *)&KINDOFMASK_NONE,
			Rva0021FC80Mask(Rva0021FC80Mask::kInit, 117, 134));
		Rva00265150RJFilter filter(&handle, 0, true);
		Object *found = ThePartitionManager->getClosestObject(
			point, 1.0f, 1, &filter);
		if (found)
		{
			Rva002D0A80ContainView *contain =
				*(Rva002D0A80ContainView **)((char *)found + 0x1fc);
			if (contain && contain->slot10() &&
				source->getObjectExitInterface() != 0 &&
				source->getObjectExitInterface()->slot06() &&
				source->getRelationship(found) == (Relationship)2 &&
				((Rva000CBA20 *)found)->distSq(
					(const Rva000CBA20Point *)point) <
				*(const Real *)0x010CB798)
				return found;
		}
	}
	return 0;
}
