// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep
// stlport
// Two more BFME HordeContain secondary-interface slots, laid out like
// HordeContain_getMembers.cpp (retail 0x002388F0, slot 60): the contained
// list lives in the OpenContain part below this interface and the member
// index tree sits at +0x30.
//
// Retail 0x00237BD0 (ILT 0x0000812A, slot 53) answers whether any member's
// +0x360 field equals the argument; retail 0x00238AE0 (ILT 0x0000B5D2, slot 80)
// hands the argument to virtual slot 20 of every member.  Both walk the
// contained list first and then the member index through TheGameLogic.
// IDENTITY IS NOT RECOVERED: the slot names and the member fields are named
// for the addresses.

typedef int Int;
typedef unsigned int UnsignedInt;

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

class Object
{
};

typedef _STL::list<Object *> BfmeMemberList;

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

typedef _STL::hash_map<UnsignedInt, Object *, _STL::hash<UnsignedInt>,
	_STL::equal_to<UnsignedInt> > BfmeObjectPtrHash;

class BfmeGameLogic
{
public:
	__forceinline Object *findObjectByID(UnsignedInt key)
	{
		BfmeObjectPtrHash::iterator it = m_objectHash.find(key);
		if (it == m_objectHash.end())
			return 0;
		return (*it).second;
	}

	char m_head[0xb0];
	BfmeObjectPtrHash m_objectHash;
};

class GameLogic;
extern GameLogic *TheGameLogic;
static inline BfmeGameLogic *logicView00237BD0() { return (BfmeGameLogic *)TheGameLogic; }


class Rva00237BD0Member
{
public:
	char m_head[0x360];
	void *m_rva00237BD0Key;
};

class Rva00238AE0Member
{
public:
#define MEMBER_SLOT(N) virtual void slot##N() = 0
	MEMBER_SLOT(00); MEMBER_SLOT(01); MEMBER_SLOT(02); MEMBER_SLOT(03);
	MEMBER_SLOT(04); MEMBER_SLOT(05); MEMBER_SLOT(06); MEMBER_SLOT(07);
	MEMBER_SLOT(08); MEMBER_SLOT(09); MEMBER_SLOT(10); MEMBER_SLOT(11);
	MEMBER_SLOT(12); MEMBER_SLOT(13); MEMBER_SLOT(14); MEMBER_SLOT(15);
	MEMBER_SLOT(16); MEMBER_SLOT(17); MEMBER_SLOT(18); MEMBER_SLOT(19);
#undef MEMBER_SLOT
	virtual void rva00238AE0Notify(void *arg) = 0;
};

class Rva00238AE0OpenContainInterface
{
public:
#define OPEN_SLOT(N) virtual Int slot##N() = 0
	OPEN_SLOT(00); OPEN_SLOT(01); OPEN_SLOT(02); OPEN_SLOT(03);
	OPEN_SLOT(04); OPEN_SLOT(05); OPEN_SLOT(06); OPEN_SLOT(07);
	OPEN_SLOT(08); OPEN_SLOT(09); OPEN_SLOT(10); OPEN_SLOT(11);
	OPEN_SLOT(12); OPEN_SLOT(13); OPEN_SLOT(14); OPEN_SLOT(15);
	OPEN_SLOT(16); OPEN_SLOT(17); OPEN_SLOT(18); OPEN_SLOT(19);
	OPEN_SLOT(20); OPEN_SLOT(21); OPEN_SLOT(22); OPEN_SLOT(23);
	OPEN_SLOT(24); OPEN_SLOT(25); OPEN_SLOT(26); OPEN_SLOT(27);
	OPEN_SLOT(28); OPEN_SLOT(29); OPEN_SLOT(30); OPEN_SLOT(31);
	OPEN_SLOT(32); OPEN_SLOT(33); OPEN_SLOT(34); OPEN_SLOT(35);
	OPEN_SLOT(36); OPEN_SLOT(37); OPEN_SLOT(38); OPEN_SLOT(39);
	OPEN_SLOT(40); OPEN_SLOT(41); OPEN_SLOT(42); OPEN_SLOT(43);
	OPEN_SLOT(44); OPEN_SLOT(45); OPEN_SLOT(46); OPEN_SLOT(47);
	OPEN_SLOT(48); OPEN_SLOT(49); OPEN_SLOT(50); OPEN_SLOT(51);
	OPEN_SLOT(52); OPEN_SLOT(53); OPEN_SLOT(54); OPEN_SLOT(55);
	OPEN_SLOT(56); OPEN_SLOT(57); OPEN_SLOT(58); OPEN_SLOT(59);
	OPEN_SLOT(60); OPEN_SLOT(61); OPEN_SLOT(62); OPEN_SLOT(63);
	OPEN_SLOT(64);
#undef OPEN_SLOT
	virtual const BfmeMemberList &getMemberList() const = 0;
};

class Pathfinder
{
public:
	void removeObjectFromPathfindMap(Object *obj);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

private:
	unsigned char m_head[0x0c];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

class Rva0023C200Member
{
public:
	unsigned char m_head[0x90];
	unsigned int m_bfmeFlags90;
};

struct BfmeBoxAFB
{
	void *first;
	void *second;
	void go(void *a, void *b);
};

class BfmeThingAFB
{
public:
	void bfmeGoAFB();
	BfmeBoxAFB *bfmeGetBoxAFB();
};

class Rva00237BD0HordeContain
{
public:
	bool hasMemberKeyedTo(void *key);
	void notifyMembers(void *arg);
	bool hasLiveIndexedMember();
	void removeMembersFromPathfindMap();
	void refreshMemberAttributeModifiers();

private:
	void *m_vtbl;
	char m_head[0x2c];
	BfmeMemberIndexNode *m_memberIndex;
};

bool Rva00237BD0HordeContain::hasMemberKeyedTo(void *key)
{
	if (key == 0)
		return false;

	const BfmeMemberList &contained =
		*(const BfmeMemberList *)((char *)this - 0xac);
	for (BfmeMemberList::const_iterator it = contained.begin();
		it != contained.end(); ++it)
	{
		Rva00237BD0Member *member = (Rva00237BD0Member *)*it;
		if (member != 0 && member->m_rva00237BD0Key == key)
			return true;
	}

	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while (entry != m_memberIndex)
	{
		UnsignedInt id = entry->m_key;
		if (id != 0)
		{
			Rva00237BD0Member *member =
				(Rva00237BD0Member *)logicView00237BD0()->findObjectByID(id);
			if (member != 0 && member->m_rva00237BD0Key == key)
				return true;
		}
		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}
	return false;
}

void Rva00237BD0HordeContain::notifyMembers(void *arg)
{
	const BfmeMemberList &contained =
		((Rva00238AE0OpenContainInterface *)((char *)this - 0xc4))
			->getMemberList();
	for (BfmeMemberList::const_iterator it = contained.begin();
		it != contained.end(); ++it)
	{
		Rva00238AE0Member *member = (Rva00238AE0Member *)*it;
		if (member != 0)
			member->rva00238AE0Notify(arg);
	}

	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while (entry != m_memberIndex)
	{
		UnsignedInt id = entry->m_key;
		if (id != 0)
		{
			Rva00238AE0Member *member =
				(Rva00238AE0Member *)logicView00237BD0()->findObjectByID(id);
			if (member != 0)
				member->rva00238AE0Notify(arg);
		}
		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}
}

// Retail 0x00237CD0 (121 bytes): true as soon as one key in the member index
// still resolves to a live object through TheGameLogic.
bool Rva00237BD0HordeContain::hasLiveIndexedMember()
{
	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while (entry != m_memberIndex)
	{
		UnsignedInt id = entry->m_key;
		if (id != 0 && logicView00237BD0()->findObjectByID(id) != 0)
			return true;
		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}
	return false;
}

// Retail 0x0023C200 (208 bytes): interface slot 46 (rdata 0x00CAE2E8 via ILT
// 0x0000BE9C) -- the slot the formation snap at 0x0023D850 calls first.  Every
// contained and indexed member without flag 0x10000000 at +0x90 is taken off
// the pathfind map.
void Rva00237BD0HordeContain::removeMembersFromPathfindMap()
{
	const BfmeMemberList &contained =
		((Rva00238AE0OpenContainInterface *)((char *)this - 0xc4))
			->getMemberList();
	for (BfmeMemberList::const_iterator it = contained.begin();
		it != contained.end(); ++it)
	{
		Rva0023C200Member *member = (Rva0023C200Member *)*it;
		if (member != 0 && !(member->m_bfmeFlags90 & 0x10000000))
			TheAI->pathfinder()->removeObjectFromPathfindMap((Object *)member);
	}

	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while (entry != m_memberIndex)
	{
		UnsignedInt id = entry->m_key;
		if (id != 0)
		{
			Rva0023C200Member *member =
				(Rva0023C200Member *)logicView00237BD0()->findObjectByID(id);
			if (member != 0 && !(member->m_bfmeFlags90 & 0x10000000))
				TheAI->pathfinder()->removeObjectFromPathfindMap((Object *)member);
		}
		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}
}

// Retail 0x00247E80 (195 bytes): interface slot 110 (rdata 0x00CAE3E8 via ILT
// 0x0003330C).  Runs the per-object attribute-modifier refresh
// (BfmeThingAFB::bfmeGoAFB, as in Object_containPairDispatch.cpp) on every
// contained member -- the list holds no nulls -- and every live indexed
// member, then clears the horde owner's own modifier pair the same way the
// refresh's fallback does.
void Rva00237BD0HordeContain::refreshMemberAttributeModifiers()
{
	const BfmeMemberList &contained =
		((Rva00238AE0OpenContainInterface *)((char *)this - 0xc4))
			->getMemberList();
	for (BfmeMemberList::const_iterator it = contained.begin();
		it != contained.end(); ++it)
	{
		((BfmeThingAFB *)*it)->bfmeGoAFB();
	}

	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while (entry != m_memberIndex)
	{
		UnsignedInt id = entry->m_key;
		if (id != 0)
		{
			BfmeThingAFB *member = (BfmeThingAFB *)logicView00237BD0()->findObjectByID(id);
			if (member != 0)
				member->bfmeGoAFB();
		}
		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}

	BfmeBoxAFB *helper = (*(BfmeThingAFB **)((char *)this - 0xdc))->bfmeGetBoxAFB();
	if (helper)
	{
		BfmeBoxAFB *pair = reinterpret_cast<BfmeBoxAFB *>(reinterpret_cast<char *>(helper) + 0x20);
		pair->go(pair->first, pair->second);
	}
}
