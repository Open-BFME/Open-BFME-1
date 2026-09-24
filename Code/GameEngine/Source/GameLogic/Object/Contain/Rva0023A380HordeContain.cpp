// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x0023A380, 369 bytes.
//
// Address-derived HordeContain-related body: the contained-member list at
// this-0xAC and member-index tree at this+0x30 match the already-landed
// Rva0023A270HordeContain body. Each visited Object's +0x200 field is an
// address-derived interface whose vtable slot 0x48 returns an id; that id is
// resolved through TheBfmeGameLogic's object hash. The exact identity of the
// interface and the +0x214/+0x74 chase on the resolved Object are unproven.
//
// At the first slot-0x48 call, an explicit typed vtable view emits the retail
// EAX vtable temporary. A one-argument __fastcall function pointer puts the
// receiver in ECX, matching thiscall for this no-explicit-argument slot. The
// member-call form at the second site already emits retail's EDX temporary.

typedef unsigned int UnsignedInt;
class Object;

typedef UnsignedInt (__fastcall *Rva0023A380Slot48)(void *);
struct Rva0023A380Vtable
{
	void *slots[18];
	Rva0023A380Slot48 slot48;
};

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

// Retail 0x012F0898 TheBfmeGameLogic. Only the bucket vector's placement
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

		Rva0023A380Vtable *vtable = *(Rva0023A380Vtable **)iface;
		UnsignedInt candidate = vtable->slot48(iface);
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
