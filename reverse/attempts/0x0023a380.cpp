// ?rva0023a380@Rva0023A380HordeContain@@QAEII@Z
// partial score=0.9946 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva0023a380@Rva0023A380HordeContain@@QAEII@Z
// Retail 0x0023A380, 369 bytes.
//
// Address-derived HordeContain-related body: the contained-member list at
// this-0xAC and the member index tree at this+0x30 match the already-landed
// Rva0023A270HordeContain::rva0023a270 (same file/class family).  Each
// visited Object's +0x200 field is a virtual interface whose vtable slot
// 0x48 (index 18) returns an id; that id is resolved back to an Object via
// GameLogic::findObjectByID (retail 0x0009A510, ILT thunk 0x0001F253).
//
// findObjectByID is ONE inline body (the ZH header's commented-out hash
// lookup) used at all three sites.  MSVC 7.1's inliner itself declines the
// first site and emits a call to the out-of-line copy, and expands the two
// member-index sites; the second site's id==0 guard is what folds the
// iface2 slot48()==0 exit, so the member-index loop has no explicit
// pre-check -- only the post-lookup candidate2 != 0 test retail keeps.
//
// The exact identity of the +0x200 interface, its slot-0x48 method, and the
// +0x214/+0x74 chase on the resolved Object are unproven; names below keep
// the address token rather than guess a class.

typedef unsigned int UnsignedInt;
class Object;

// object+0x200 virtual interface; only vtable slot 0x48 (index 18) is
// proven by this body's evidence.
class Rva0023A380BodyShim
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0; virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0; virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0; virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual UnsignedInt slot48() = 0;
};

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

typedef _STL::list<Object *> BfmeMemberList;
typedef _STL::hash_map<UnsignedInt, Object *, _STL::hash<UnsignedInt>,
	_STL::equal_to<UnsignedInt> > BfmeObjectPtrHash;

// retail 0x012F0898 TheBfmeGameLogic.  Only the bucket vector's placement
// matters (this+0xB4/+0xB8), as in GameLogicFindObjectByID.cpp.
class GameLogic
{
public:
	Object *findObjectByID(int id)
	{
		if (id == 0)
			return 0;
		BfmeObjectPtrHash::iterator it = m_objectHash.find(id);
		if (it == m_objectHash.end())
			return 0;
		return (*it).second;
	}

	char m_head[0xb0];
	BfmeObjectPtrHash m_objectHash;
};
extern GameLogic *TheBfmeGameLogic;

struct BfmeMemberIndexNode
{
	UnsignedInt m_color;
	BfmeMemberIndexNode *m_parent;
	BfmeMemberIndexNode *m_next;
	BfmeMemberIndexNode *m_right;
	UnsignedInt m_key;
};

namespace _STL
{
struct _Rb_tree_node_base
{
};

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}

class Rva0023A380HordeContain
{
public:
	UnsignedInt rva0023a380(UnsignedInt targetId);

private:
	BfmeMemberList &memberList() const
	{
		return *(BfmeMemberList *)((char *)this - 0xac);
	}

	char m_head[0x30];
	BfmeMemberIndexNode *m_memberIndex;
};

// ?rva0023a380@Rva0023A380HordeContain@@QAEII@Z
UnsignedInt Rva0023A380HordeContain::rva0023a380(UnsignedInt targetId)
{
	UnsignedInt result = 0;

	BfmeMemberList::iterator node = memberList().begin();
	for (; node != memberList().end(); ++node)
	{
		Rva0023A380BodyShim *iface = *(Rva0023A380BodyShim **)((char *)*node + 0x200);
		if (iface == 0)
			continue;

		UnsignedInt candidate = iface->slot48();
		if (candidate == 0)
			continue;

		Object *found = TheBfmeGameLogic->findObjectByID(candidate);
		if (found != 0)
		{
			void *field214 = *(void **)((char *)found + 0x214);
			if (field214 != 0 && *(UnsignedInt *)((char *)field214 + 0x74) == targetId)
				candidate = *(UnsignedInt *)((char *)field214 + 0x74);
		}
		if (candidate == targetId)
			result = candidate;
		else if (result == 0)
			result = candidate;
	}

	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while (entry != m_memberIndex)
	{
		UnsignedInt key = entry->m_key;
		Object *obj2 = TheBfmeGameLogic->findObjectByID(key);
		Rva0023A380BodyShim *iface2 = *(Rva0023A380BodyShim **)((char *)obj2 + 0x200);
		if (iface2 != 0)
		{
			UnsignedInt candidate2 = iface2->slot48();
			Object *obj3 = TheBfmeGameLogic->findObjectByID(candidate2);
			if (obj3 != 0)
			{
				void *field214b = *(void **)((char *)obj3 + 0x214);
				if (field214b != 0 && *(UnsignedInt *)((char *)field214b + 0x74) == targetId)
					candidate2 = *(UnsignedInt *)((char *)field214b + 0x74);
			}
			if (candidate2 != 0)
			{
				if (candidate2 == targetId)
					result = candidate2;
				else if (result == 0)
					result = candidate2;
			}
		}

		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}

	return result;
}
