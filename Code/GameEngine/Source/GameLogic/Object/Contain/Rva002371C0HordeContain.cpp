// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x002371C0 is slot 47 of the HordeContain interface vtable
// 0x010AED58, installed by the matched HordeContain constructor and shared
// by AODHordeContain and HorseHordeContain. The address-derived member name
// keeps the original method name opaque.
// The call at this-0xC4 uses interface slot 65, as in the matched
// Rva00237E50 member selector. The member-index header at this+0x30 and its
// key-at-+0x10 node layout are independently used by matched HordeContain
// body 0x0023A270. The list and hash lookup follow those verified siblings.

typedef unsigned int UnsignedInt;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

class Object;
struct Coord3D;

class Pathfinder
{
public:
	void updatePos(Object *, const Coord3D *);
};

#pragma comment(linker, "/alternatename:?updatePos@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@@Z=?j_00013647@@YAXXZ")

class AI
{
public:
	char m_pad[0x0c];
	Pathfinder *pathfinder;
};

extern AI *TheAI;

typedef _STL::list<Object *> BfmeMemberList;
typedef _STL::hash_map<UnsignedInt, Object *, _STL::hash<UnsignedInt>,
	_STL::equal_to<UnsignedInt> > BfmeObjectPtrHash;

class GameLogic
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

extern GameLogic *TheBfmeGameLogic;

template <int N> class Rva002371C0MemberViewSlots : public Rva002371C0MemberViewSlots<N - 1>
{
public:
	virtual int unused(char (*)[N]) = 0;
};

template <> class Rva002371C0MemberViewSlots<0>
{
};

class Rva002371C0MemberView : public Rva002371C0MemberViewSlots<65>
{
public:
	virtual const BfmeMemberList &getMemberList() const = 0;
};

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
struct _Rb_tree_node_base;

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}

class Rva002371C0HordeContain
{
public:
	void rva002371c0();

private:
	char m_head[0x30];
	BfmeMemberIndexNode *m_memberIndex;
};

void Rva002371C0HordeContain::rva002371c0()
{
	const BfmeMemberList &members =
		((Rva002371C0MemberView *)((char *)this - 0xc4))->getMemberList();
	for (BfmeMemberList::const_iterator it = members.begin();
		it != members.end(); ++it)
	{
		Object *object = *it;
		if (object != 0)
			TheAI->pathfinder->updatePos(object,
				(const Coord3D *)((const char *)object + 0x38));
	}

	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while (entry != m_memberIndex)
	{
		UnsignedInt key = entry->m_key;
		if (key != 0)
		{
			Object *object = TheBfmeGameLogic->findObjectByID(key);
			if (object != 0)
				TheAI->pathfinder->updatePos(object,
					(const Coord3D *)((const char *)object + 0x38));
		}
		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}
}
