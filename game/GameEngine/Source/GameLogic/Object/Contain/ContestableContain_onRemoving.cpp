// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?onRemoving@ContestableContain@@UAEXPAVObject@@@Z
// BFME retail ContestableContain::onRemoving at RVA 0x0021D360, 245 bytes.
//
// Identity: the matched ContestableContain constructor (0x0021BEE0) and
// destructor (0x0021B6F0) install the secondary vtable 0x010AB140, whose slot
// +0x48 is j_0004593a -> 0x0021D360.  The same slot of GarrisonContain's
// secondary vtable 0x010AB598 holds j_00005c22 -> GarrisonContain::onRemoving,
// and this body calls that ILT directly on its own this first: the usual
// Derived::onRemoving calling Base::onRemoving.  It then works on
// ContestableContain::m_objectData (primary +0x9C4, ContestableContain.cpp)
// and finishes in the matched ContestableContain::updateContestStatus.
//
// As in GarrisonContain_onRemoving.cpp the incoming ECX is the secondary
// (contain-interface) subobject; the complete module is ECX-0x20.  This view
// therefore lays ContestableContain out from that subobject.
//
// Shape: the map lookup is assigned from two separate find temporaries and
// handed by value to an inline tail whose by-value parameter takes the dead
// argument home; the tail walks a register copy of it and passes the
// parameter's address to bfmeDoBDB.  Constructing the lookup in place, or
// passing the register copy's address, keeps the iterator in memory and grows
// the frame.

#include <map>

class Object;

// The helper behind ILT 0x0000FAA6 (0x001CB020), called with 0 on the object.
// 0x001CB020 is defined as BfmeObjAS::bfmeParentAS (RvaC4390Second_resolve.cpp).
class BfmeObjAS
{
public:
	BfmeObjAS *bfmeParentAS(int index);
};

class Rva0025DF30Object
{
public:
	Rva0025DF30Object *related(int index)
	{
		return reinterpret_cast<Rva0025DF30Object *>(
			reinterpret_cast<BfmeObjAS *>(this)->bfmeParentAS(index));
	}
};

class GarrisonContain
{
public:
	virtual void onRemoving(Object *);
};

class BfmeSubBDB
{
public:
	void bfmeDoBDB(void *, int);		// ILT 0x0001A4F6 -> 0x0021D070
};

// ContestableContain.cpp's map payload: target pointer at node+0x14 and
// byte counter at node+0x18.
struct ContestableMapEntry
{
	Object *m_object;
	unsigned char m_count;
	unsigned char m_pad[3];
};

typedef _STL::map<Object *, ContestableMapEntry> ContestableObjectDataMap;

// The complete module (secondary - 0x20): an Object query at vtable +0x6C.
class ContestableContainPrimary0021D360
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual int querySlot6C(Object *object);	// +0x6C
};

// The secondary vtable 0x010AB140 up to the slots this body uses.
class ContestableContainInterface0021D360
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void onRemoving(Object *object);	// +0x48
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual bool querySlotC4();			// +0xC4
};

class ContestableContain : public ContestableContainInterface0021D360
{
public:
	virtual void onRemoving(Object *object);
	void updateContestStatus();

private:
	void removeTracked(Object *object, Object *related, ContestableContainPrimary0021D360 *primary,
		ContestableObjectDataMap::iterator passed);

	char m_unreconstructed[0x9a4 - 4];
	ContestableObjectDataMap m_objectData;		// secondary +0x9A4, primary +0x9C4
};

__forceinline void ContestableContain::removeTracked(Object *object, Object *related,
	ContestableContainPrimary0021D360 *primary, ContestableObjectDataMap::iterator passed)
{
	ContestableObjectDataMap::iterator found(passed);
	if (found != m_objectData.end())
	{
		for (ContestableObjectDataMap::iterator it = m_objectData.begin(); it != m_objectData.end(); ++it)
		{
			if (it->second.m_object == object || it->second.m_object == related)
			{
				it->second.m_object = 0;
				--found->second.m_count;
			}
			if (!related && it->first == found->second.m_object)
				--it->second.m_count;
		}
		((BfmeSubBDB *)primary)->bfmeDoBDB(object, (int)&passed);
		((ContestableContain *)primary)->updateContestStatus();
	}
}

void ContestableContain::onRemoving(Object *object)
{
	if (!object)
		return;

	GarrisonContain *base = (GarrisonContain *)this;
	base->GarrisonContain::onRemoving(object);

	if (!querySlotC4())
		return;

	ContestableContainPrimary0021D360 *primary = (ContestableContainPrimary0021D360 *)((char *)this - 0x20);
	Object *related = primary->querySlot6C(object)
		? (Object *)((Rva0025DF30Object *)object)->related(0) : 0;

	ContestableObjectDataMap::iterator found;
	if (related)
		found = m_objectData.find(related);
	else
		found = m_objectData.find(object);
	removeTracked(object, related, primary, found);
}
