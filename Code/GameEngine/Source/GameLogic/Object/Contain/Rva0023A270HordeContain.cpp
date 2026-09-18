// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// Retail 0x0023A270, 210 bytes.
// The HordeContain interface at this pointer sees the contained list at -0xAC
// and the member index at +0x30.  Vtable slot 113 proves the owner and ABI,
// but the original method name is not present in the available evidence.

typedef bool Bool;
typedef unsigned int UnsignedInt;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

class Object
{
};

class FXList
{
public:
	bool bfmeIsBlocked();
	void doFXObj(const Object *, const Object *) const;
};

struct BfmeMemberNode
{
	BfmeMemberNode *m_next;
	BfmeMemberNode *m_previous;
	Object *m_object;
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
struct _Rb_tree_node_base
{
};

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}

typedef _STL::list<Object *> BfmeMemberList;
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

extern BfmeGameLogic *TheBfmeGameLogic;

class Rva0023A270HordeContain
{
public:
	void rva0023a270(FXList *fx);

private:
	BfmeMemberList &memberList() const
	{
		return *(BfmeMemberList *)((char *)this - 0xac);
	}

	char m_head[0x30];
	BfmeMemberIndexNode *m_memberIndex;
};

// ?rva0023a270@Rva0023A270HordeContain@@QAEXPAVFXList@@@Z
void Rva0023A270HordeContain::rva0023a270(FXList *fx)
{
	BfmeMemberList &members = memberList();
	BfmeMemberList::iterator node = members.begin();

	while (node != members.end())
	{
		Object *object = *node;
		if (fx != 0 && !fx->bfmeIsBlocked())
			fx->doFXObj(object, 0);
		++node;
	}

	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while (entry != m_memberIndex)
	{
		UnsignedInt key = entry->m_key;
		Object *object = (Object *)key;
		if (key != 0)
			object = TheBfmeGameLogic->findObjectByID(key);
		if (fx != 0 && !fx->bfmeIsBlocked())
			fx->doFXObj(object, 0);

		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}
}
