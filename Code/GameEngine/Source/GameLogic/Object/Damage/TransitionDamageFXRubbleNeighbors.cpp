// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Include
// Retail 0x002539F0..0x00253B87 is slot 39 of the BehaviorModuleInterface
// table 0x010B2598 that the TransitionDamageFX constructor 0x00252F50 installs
// at +0x0C. ModuleFactory registers "TransitionDamageFX" (string 0x0108FCD8 at
// 0x0012FA95) with instance creator 0x0011E880, which allocates 0xE0 bytes and
// runs that constructor, and with data creator 0x00124770. The slot's original
// name is not known, so the method keeps its address.
//
// For every RubbleNeighbor record that names sub-objects and an OCL, the body
// moves the record's NeighborOffset into world space from the owner's bones,
// asks the partition manager for the closest object of KindOf bit 7 or 59
// within 30000, and keeps a copy of the record carrying that object's ID.

#include "basetype.h"
#include "ascii_string.h"

class Matrix3D;
class ModuleData;
class ObjectCreationList;

typedef Int ObjectID;

namespace _STL
{
template <class Type>
class allocator
{
};

// Only the members this body touches. The destructor and push_back stay out of
// line, as retail calls them (0x000658A0 and 0x00253630).
template <class Type, class Allocator>
class vector
{
public:
	~vector();
	void push_back(const Type *value);

	const Type *begin() const { return _M_start; }
	const Type *end() const { return _M_finish; }
	Bool empty() const { return _M_start == _M_finish; }

protected:
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};
}

class Thing
{
public:
	void convertBonePosToWorldPos(const Coord3D *bonePos,
		const Matrix3D *boneTransform, Coord3D *worldPos,
		Matrix3D *worldTransform) const;
};

class Object : public Thing
{
public:
	ObjectID getID() const { return m_id; }

private:
	unsigned char m_00_to_74[0x74];
	ObjectID m_id;
};

// 192-bit KindOf mask; the filter constructor 0x00251980 copies 24 bytes.
struct Rva002539F0KindOfMask
{
	Rva002539F0KindOfMask(Int first, Int second)
	{
		memset(m_words, 0, sizeof(m_words));
		m_words[first >> 5] |= 1u << (first & 31);
		m_words[second >> 5] |= 1u << (second & 31);
	}

	UnsignedInt m_words[6];
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *m_next;
};

// Retail table 0x010B243C.
class Rva0025F2D0KindOfAnyFilter : public PartitionFilter
{
public:
	Rva0025F2D0KindOfAnyFilter(const Rva002539F0KindOfMask &mask)
		: m_mask(mask) {}
	virtual ~Rva0025F2D0KindOfAnyFilter() {}
	virtual Bool allow(Object *);

	Rva002539F0KindOfMask m_mask;
};

enum DistanceCalculationType
{
	FROM_CENTER_2D = 0
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real radius,
		DistanceCalculationType distanceType, PartitionFilter *filters);
};
extern PartitionManager *ThePartitionManager;

// 44-byte RubbleNeighbor record, copy constructor 0x00252A50. The INI parser
// 0x00253680 fills +0x04 from SubObject, +0x10 from OCL, +0x14 from
// NeighborOffset and +0x20 from OCLOffset; +0x00 starts zero and this body
// stores the found object's ID there.
class Gen00252A50
{
public:
	Gen00252A50(const Gen00252A50 &other);

	ObjectID m_objectID;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_subObjects;
	const ObjectCreationList *m_ocl;
	Coord3D m_neighborOffset;
	Coord3D m_oclOffset;
};

// The push_back at 0x00253630 is spelled with its own address-named element.
struct Rva00253630Element
{
	char m_body[44];
};

// Field table 0x00C8DBF0 parses INI key RubbleNeighbor into +0x1034; ModuleFactory
// sizes the whole record at 0x1040.
class TransitionDamageFXModuleData
{
public:
	unsigned char m_00_to_1034[0x1034];
	_STL::vector<Gen00252A50, _STL::allocator<Gen00252A50> > m_rubbleNeighbors;
};

class ObjectModule
{
public:
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void rva002539F0(Int) = 0;
};

// The three-slot table the constructor installs at +0x10 (0x010B2588).
class DamageModuleInterface
{
public:
	virtual void slot00();
};

// Layout from constructor 0x00252F50: interfaces at +0x0C and +0x10, 0x30
// zeroed words from +0x14, and the vector at +0xD4 (allocation 0xE0).
class TransitionDamageFX : public ObjectModule,
	public BehaviorModuleInterface,
	public DamageModuleInterface
{
public:
	virtual void rva002539F0(Int);

	const TransitionDamageFXModuleData *getTransitionDamageFXModuleData() const
	{
		return (const TransitionDamageFXModuleData *)m_moduleData;
	}

private:
	UnsignedInt m_particleSystemID[4][12];
	_STL::vector<Rva00253630Element, _STL::allocator<Rva00253630Element> >
		m_resolvedNeighbors;
};

void TransitionDamageFX::rva002539F0(Int)
{
	const TransitionDamageFXModuleData *d = getTransitionDamageFXModuleData();
	if (d == NULL)
		return;

	Rva002539F0KindOfMask mask(7, 59);
	for (const Gen00252A50 *it = d->m_rubbleNeighbors.begin();
		it != d->m_rubbleNeighbors.end(); ++it)
	{
		if (it->m_subObjects.empty() || it->m_ocl == NULL)
			continue;

		const Coord3D &offset = it->m_neighborOffset;
		Coord3D pos;
		pos.x = offset.x;
		pos.y = offset.y;
		pos.z = offset.z;
		m_object->convertBonePosToWorldPos(&pos, NULL, &pos, NULL);

		Object *other = ThePartitionManager->getClosestObject(&pos, 30000.0f,
			FROM_CENTER_2D,
			&Rva0025F2D0KindOfAnyFilter(mask));
		if (other != NULL && other != m_object)
		{
			Gen00252A50 neighbor(*it);
			neighbor.m_objectID = other->getID();
			m_resolvedNeighbors.push_back(
				reinterpret_cast<const Rva00253630Element *>(&neighbor));
		}
	}
}
