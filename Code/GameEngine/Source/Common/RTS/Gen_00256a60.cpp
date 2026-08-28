// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the anonymous retail body at 0x00256A60, converted from the
// Code/gen_asm naked dump to real C++.
//
// It is the third member of the addSupplyWarehouse / addSupplyCenter family
// (0x000E68C0 / 0x000E6870): the same guarded `list<ObjectID>::push_back` of
// Object::getID(), differing only in which member the list is -- here retail
// this+0x24.  The owner class is NOT identified: the only reference is a tail
// `jmp` from the null-checked forwarder at 0x001BF4D0, whose `this` is the
// object held at Object+0x1E8 -- one of a family of four such forwarders
// (0x001BF490/4B0/4D0/4F0) -- and nothing in the ledger names that member
// yet.  So the name here is address-derived on purpose: it disclaims identity
// rather than asserting one.
//
// See ResourceGatheringManager_addSupply.cpp in this directory for why
// _STLP_NO_EXCEPTIONS is what makes this shape reachable at all.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef unsigned int ObjectID;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ObjectID getID(void) const { return m_id; }
private:
	char m_objectPad[0x74];
	ObjectID m_id;
};

struct Gen_00256a60
{
	void m(Object *obj);

	char m_slice_pad[0x24];				// retail this+0x00 .. +0x23, untouched
	_STL::list<ObjectID> m_objectIDs;	// retail this+0x24
};

// ?m@Gen_00256a60@@QAEXPAVObject@@@Z
void Gen_00256a60::m(Object *obj)
{
	if (obj == NULL)
		return;

	m_objectIDs.push_back(obj->getID());
}
