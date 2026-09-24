// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00239C90 has no proven semantic owner or named caller. Keep the
// address-derived class and method until stronger identity evidence appears.
// The body establishes the member-list view at this-0xC4, owner at this-0xDC,
// and member-index header at this+0x30. Its call targets retain their pinned
// retail addresses.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;

class BfmeMsgXI
{
};

class BfmeRvaA760Object
{
};

class BfmeRvaA760ProbeInterface
{
public:
	bool accepts(BfmeRvaA760Object *object, int currentPlayer);
};

class BfmeR1094
{
};

class BfmeK1094
{
public:
	BfmeR1094 *bfmeCur1094();
};

class BfmeH1040
{
public:
	void bfmeAdd1040(void *message);
};

class AttributeModifierPoolUpdate;
class Object
{
	friend class Rva00239C90Interface;

	private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
};

class BfmeTargetXI
{
public:
	void bfmeUseXI(BfmeMsgXI *message);
};

typedef _STL::list<BfmeRvaA760Object *> BfmeMemberList;
typedef _STL::hash_map<UnsignedInt, BfmeRvaA760Object *,
	_STL::hash<UnsignedInt>, _STL::equal_to<UnsignedInt> > BfmeObjectPtrHash;

struct BfmeMemberIndexNode
{
	UnsignedInt m_color;
	BfmeMemberIndexNode *m_parent;
	BfmeMemberIndexNode *m_left;
	BfmeMemberIndexNode *m_right;
	UnsignedInt m_key;
};

namespace _STL
{
struct _Rb_tree_node_base;

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};
}

class GameLogic
{
public:
	__forceinline BfmeRvaA760Object *findObjectByID(UnsignedInt key)
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

template <int N>
class Rva00239C90MemberViewSlots : public Rva00239C90MemberViewSlots<N - 1>
{
public:
	virtual int unused(char (*)[N]) = 0;
};

template <>
class Rva00239C90MemberViewSlots<0>
{
};

class Rva00239C90MemberView : public Rva00239C90MemberViewSlots<65>
{
public:
	virtual const BfmeMemberList &getMemberList() const = 0;
};

class Rva00239C90Interface
{
public:
	void rva00239c90(BfmeMsgXI *message, BfmeRvaA760ProbeInterface *filter);

private:
	char m_head[0x30];
	BfmeMemberIndexNode *m_memberIndex;
};

void Rva00239C90Interface::rva00239c90(
	BfmeMsgXI *message, BfmeRvaA760ProbeInterface *filter)
{
	const BfmeMemberList &members =
		((Rva00239C90MemberView *)((char *)this - 0xc4))->getMemberList();
	BfmeK1094 *owner =
		*(BfmeK1094 **)((char *)this - 0xdc);

	for (BfmeMemberList::const_iterator it = members.begin();
		it != members.end(); ++it)
	{
		BfmeRvaA760Object *member = *it;
		if (filter == 0 || filter->accepts(member,
			(int)owner->bfmeCur1094()))
			((BfmeH1040 *)member)->bfmeAdd1040(message);
	}

	BfmeMemberIndexNode *entry = m_memberIndex->m_left;
	while (entry != m_memberIndex)
	{
		UnsignedInt key = entry->m_key;
		if (key != 0)
		{
			BfmeRvaA760Object *member =
				TheBfmeGameLogic->findObjectByID(key);
			if (member != 0
				&& (filter == 0 || filter->accepts(member,
					(int)owner->bfmeCur1094())))
				((BfmeH1040 *)member)->bfmeAdd1040(message);
		}
		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}

	Object *object = *(Object **)((char *)this - 0xdc);
	AttributeModifierPoolUpdate *pool =
		object->findAttributeModifierPoolUpdate();
	if (pool != 0)
		((BfmeTargetXI *)pool)->bfmeUseXI(message);
}
