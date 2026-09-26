// Retail 0x002D0A80, 429 bytes. Query a nearby rally override object.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob1 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <bitset>

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

struct Coord3D { Real x; Real y; Real z; };

template <int NUMBITS>
class BitFlags
{
public:
	 enum BogusInitType { kInit = 0 };
	 BitFlags() {}
	 BitFlags(BogusInitType, Int first, Int second)
	 {
		 m_bits._Unchecked_set((size_t)first);
		 m_bits._Unchecked_set((size_t)second);
	 }
private:
	 _STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

struct Rva0021FC80Mask
{
	_STL::bitset<192> bits;
	enum BogusInitType { kInit = 0 };
	Rva0021FC80Mask() {}
	Rva0021FC80Mask(BogusInitType, Int first, Int second)
	{
		bits._Unchecked_set((size_t)first);
		bits._Unchecked_set((size_t)second);
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

enum Relationship { Relationship_Thunk = 0 };
class Object
{
public:
	ExitInterface *getObjectExitInterface() const;
	Relationship getRelationship(const Object *) const;
};

class Rva000CBA20Point { public: Real x; Real y; };
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
	if (object == 0)
		return 0;
	if (position == 0)
		return 0;

	Rva0039FF30Filter handle;
	handle.setMasks(
		Rva0021FC80Mask(Rva0021FC80Mask::kInit, 117, 134),
		*(const Rva0021FC80Mask *)&KINDOFMASK_NONE);
	Rva00265150RJFilter filter(&handle, 0, true);
	Object *found = ThePartitionManager->getClosestObject(
		position, 1.0f, 1, &filter);
	if (found)
	{
		Rva002D0A80ContainView *contain =
			*(Rva002D0A80ContainView **)((char *)found + 0x1fc);
		if (contain && contain->slot10() &&
			object->getObjectExitInterface() != 0 &&
			object->getObjectExitInterface()->slot06() &&
			object->getRelationship(found) == (Relationship)2 &&
			((Rva000CBA20 *)found)->distSq(
				(const Rva000CBA20Point *)position) <
			*(const Real *)0x010CB798)
			return found;
	}
	return 0;
}
