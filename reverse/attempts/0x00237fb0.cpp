// ?rva00237fb0@Rva00237FB0Owner@@QAEXPAVRva00237FB0Param@@@Z
// partial score=0.23 date=2026-09-21
// Retail 0x00237FB0, 413 bytes.
// stlport
//
// 'this'-0xC4 holds a HordeContain-family interface pointer (same family as
// Code/GameEngine/Source/GameLogic/Object/Contain/Rva0023A380HordeContainLookup.cpp
// and CaveContainChangeTeamOnAllConnectedCaves.cpp's BfmeK1101::getContainerList
// idiom: the interface's vtable+0x104 slot returns a pointer directly onto an
// embedded _STL::list<Object*>). The single caller-supplied parameter is
// itself both a list pointer (its own contained list, used to receive the
// copies) and, at +0x30, a HordeContain member-index tree owner (same
// BfmeMemberIndexNode/_M_increment shape as Rva0023A380HordeContainLookup.cpp).
//
// Shape: (1) copy every element of the -0xC4 interface's list into the
// parameter's own list; (2) walk the parameter's own +0x30 member-index tree,
// resolve each node's key through TheBfmeGameLogic's inlined hash and append
// the resolved Object* into that same list; (3) walk the -0xC4 interface's
// list a second time, calling vtable slot 0xa0 on each element into a fresh
// throwaway list, then destroy that temporary list
// (Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainDestructors.cpp's
// tg_000cebd0 target). No caller or vtable owner is proven, so the class
// names below keep the address token.

typedef unsigned int UnsignedInt;
class Object;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

typedef _STL::list<Object *> BfmeMemberList;
typedef _STL::hash_map<UnsignedInt, Object *, _STL::hash<UnsignedInt>,
	_STL::equal_to<UnsignedInt> > BfmeObjectPtrHash;

class BfmeGameLogicInline
{
public:
	__forceinline Object *findObjectByID(UnsignedInt key)
	{
		if (key == 0)
			return 0;
		BfmeObjectPtrHash::iterator it = m_objectHash.find(key);
		if (it == m_objectHash.end())
			return 0;
		return (*it).second;
	}

	char m_head[0xb0];
	BfmeObjectPtrHash m_objectHash;
};
extern BfmeGameLogicInline *TheBfmeGameLogicInline;

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
struct _Rb_tree_node_base { };

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}

// Address-derived: only vtable slot 0x104/4 (index 65) is proven.
#define RVA00237FB0_IFACE_SLOT(n) virtual void slot##n();
class Rva00237FB0SourceIface
{
public:
	RVA00237FB0_IFACE_SLOT(00) RVA00237FB0_IFACE_SLOT(01) RVA00237FB0_IFACE_SLOT(02) RVA00237FB0_IFACE_SLOT(03)
	RVA00237FB0_IFACE_SLOT(04) RVA00237FB0_IFACE_SLOT(05) RVA00237FB0_IFACE_SLOT(06) RVA00237FB0_IFACE_SLOT(07)
	RVA00237FB0_IFACE_SLOT(08) RVA00237FB0_IFACE_SLOT(09) RVA00237FB0_IFACE_SLOT(10) RVA00237FB0_IFACE_SLOT(11)
	RVA00237FB0_IFACE_SLOT(12) RVA00237FB0_IFACE_SLOT(13) RVA00237FB0_IFACE_SLOT(14) RVA00237FB0_IFACE_SLOT(15)
	RVA00237FB0_IFACE_SLOT(16) RVA00237FB0_IFACE_SLOT(17) RVA00237FB0_IFACE_SLOT(18) RVA00237FB0_IFACE_SLOT(19)
	RVA00237FB0_IFACE_SLOT(20) RVA00237FB0_IFACE_SLOT(21) RVA00237FB0_IFACE_SLOT(22) RVA00237FB0_IFACE_SLOT(23)
	RVA00237FB0_IFACE_SLOT(24) RVA00237FB0_IFACE_SLOT(25) RVA00237FB0_IFACE_SLOT(26) RVA00237FB0_IFACE_SLOT(27)
	RVA00237FB0_IFACE_SLOT(28) RVA00237FB0_IFACE_SLOT(29) RVA00237FB0_IFACE_SLOT(30) RVA00237FB0_IFACE_SLOT(31)
	RVA00237FB0_IFACE_SLOT(32) RVA00237FB0_IFACE_SLOT(33) RVA00237FB0_IFACE_SLOT(34) RVA00237FB0_IFACE_SLOT(35)
	RVA00237FB0_IFACE_SLOT(36) RVA00237FB0_IFACE_SLOT(37) RVA00237FB0_IFACE_SLOT(38) RVA00237FB0_IFACE_SLOT(39)
	virtual UnsignedInt callSlot40(void);	// index 40, vtable+0xa0
	RVA00237FB0_IFACE_SLOT(41) RVA00237FB0_IFACE_SLOT(42) RVA00237FB0_IFACE_SLOT(43) RVA00237FB0_IFACE_SLOT(44)
	RVA00237FB0_IFACE_SLOT(45) RVA00237FB0_IFACE_SLOT(46) RVA00237FB0_IFACE_SLOT(47) RVA00237FB0_IFACE_SLOT(48)
	RVA00237FB0_IFACE_SLOT(49) RVA00237FB0_IFACE_SLOT(50) RVA00237FB0_IFACE_SLOT(51) RVA00237FB0_IFACE_SLOT(52)
	RVA00237FB0_IFACE_SLOT(53) RVA00237FB0_IFACE_SLOT(54) RVA00237FB0_IFACE_SLOT(55) RVA00237FB0_IFACE_SLOT(56)
	RVA00237FB0_IFACE_SLOT(57) RVA00237FB0_IFACE_SLOT(58) RVA00237FB0_IFACE_SLOT(59) RVA00237FB0_IFACE_SLOT(60)
	RVA00237FB0_IFACE_SLOT(61) RVA00237FB0_IFACE_SLOT(62) RVA00237FB0_IFACE_SLOT(63) RVA00237FB0_IFACE_SLOT(64)
	virtual BfmeMemberList *getMemberList();	// index 65, vtable+0x104
};
#undef RVA00237FB0_IFACE_SLOT

class Rva00237FB0Owner
{
public:
	BfmeMemberList *sourceList() const
	{
		void *ifaceThis = (char *)this - 0xc4;
		void *vtbl = *(void **)ifaceThis;
		void *slotAddr = *(void **)((char *)vtbl + 0x104);
		typedef BfmeMemberList *(Rva00237FB0Owner::*Fn)();
		union { void (*raw)(void); Fn member; } u;
		u.raw = (void (*)(void))slotAddr;
		return (((Rva00237FB0Owner *)ifaceThis)->*u.member)();
	}

	UnsignedInt callSlot40(Object *arg)
	{
		void *ifaceThis = (char *)this - 0xc4;
		void *vtbl = *(void **)ifaceThis;
		void *slotAddr = *(void **)((char *)vtbl + 0xa0);
		typedef UnsignedInt (Rva00237FB0Owner::*Fn)(Object *);
		union { void (*raw)(void); Fn member; } u;
		u.raw = (void (*)(void))slotAddr;
		return (((Rva00237FB0Owner *)ifaceThis)->*u.member)(arg);
	}

	void rva00237fb0(class Rva00237FB0Param *param);
};

class Rva00237FB0Param
{
public:
	BfmeMemberList *asList() { return (BfmeMemberList *)this; }
	BfmeMemberIndexNode *memberIndex() { return m_memberIndex; }

private:
	char m_pad[0x30];
	BfmeMemberIndexNode *m_memberIndex;	// +0x30
};

// ?rva00237fb0@Rva00237FB0Owner@@QAEXPAVRva00237FB0Param@@@Z
void Rva00237FB0Owner::rva00237fb0(Rva00237FB0Param *param)
{
	BfmeMemberList *src = sourceList();
	BfmeMemberList *dst = param->asList();

	for (BfmeMemberList::iterator it = src->begin(); it != src->end(); ++it)
	{
		dst->push_back(*it);
	}

	BfmeMemberIndexNode *entry = param->memberIndex()->m_next;
	BfmeMemberIndexNode *header = param->memberIndex();
	while (entry != header)
	{
		UnsignedInt key = entry->m_key;
		Object *resolved = TheBfmeGameLogicInline->findObjectByID(key);
		if (resolved != 0)
			dst->push_back(resolved);

		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}

	BfmeMemberList temp;
	for (BfmeMemberList::iterator it2 = src->begin(); it2 != src->end(); ++it2)
	{
		Object *obj = *it2;
		callSlot40(obj);
		temp.push_back(obj);
	}
}
