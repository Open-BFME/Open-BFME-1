// ?d_00237fb0@@YAXXZ
// partial score=0.939 date=2026-09-24
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /EHsc /FAsc /Fabuild/rva00237fb0_inline_header.cod
// stlport
// The body at 0x00237FB0 reads a member index at this+0x30.
// It reads a member list through the interface at this-0xC4 and calls slot 40 on this.
// The evidence does not identify the owning class, so the type keeps the retail address.

typedef int Int;
typedef unsigned int UnsignedInt;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

class Object;

typedef _STL::list<Object *> BfmeMemberList;
typedef _STL::list<int> BfmeMemberIdList;

class ListIntDtorAdapter : public BfmeMemberIdList
{
public:
	__declspec(noinline) ~ListIntDtorAdapter() {}
};
typedef _STL::hash_map<UnsignedInt, Object *, _STL::hash<UnsignedInt>,
	_STL::equal_to<UnsignedInt> > BfmeObjectPtrHash;

class GameLogic
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
struct _Rb_tree_node_base;

template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}

#define RVA00237FB0_SOURCE_SLOT(N) virtual void slot##N() = 0;
class Rva00237FB0MemberSource
{
public:
	RVA00237FB0_SOURCE_SLOT(00) RVA00237FB0_SOURCE_SLOT(01) RVA00237FB0_SOURCE_SLOT(02) RVA00237FB0_SOURCE_SLOT(03)
	RVA00237FB0_SOURCE_SLOT(04) RVA00237FB0_SOURCE_SLOT(05) RVA00237FB0_SOURCE_SLOT(06) RVA00237FB0_SOURCE_SLOT(07)
	RVA00237FB0_SOURCE_SLOT(08) RVA00237FB0_SOURCE_SLOT(09) RVA00237FB0_SOURCE_SLOT(10) RVA00237FB0_SOURCE_SLOT(11)
	RVA00237FB0_SOURCE_SLOT(12) RVA00237FB0_SOURCE_SLOT(13) RVA00237FB0_SOURCE_SLOT(14) RVA00237FB0_SOURCE_SLOT(15)
	RVA00237FB0_SOURCE_SLOT(16) RVA00237FB0_SOURCE_SLOT(17) RVA00237FB0_SOURCE_SLOT(18) RVA00237FB0_SOURCE_SLOT(19)
	RVA00237FB0_SOURCE_SLOT(20) RVA00237FB0_SOURCE_SLOT(21) RVA00237FB0_SOURCE_SLOT(22) RVA00237FB0_SOURCE_SLOT(23)
	RVA00237FB0_SOURCE_SLOT(24) RVA00237FB0_SOURCE_SLOT(25) RVA00237FB0_SOURCE_SLOT(26) RVA00237FB0_SOURCE_SLOT(27)
	RVA00237FB0_SOURCE_SLOT(28) RVA00237FB0_SOURCE_SLOT(29) RVA00237FB0_SOURCE_SLOT(30) RVA00237FB0_SOURCE_SLOT(31)
	RVA00237FB0_SOURCE_SLOT(32) RVA00237FB0_SOURCE_SLOT(33) RVA00237FB0_SOURCE_SLOT(34) RVA00237FB0_SOURCE_SLOT(35)
	RVA00237FB0_SOURCE_SLOT(36) RVA00237FB0_SOURCE_SLOT(37) RVA00237FB0_SOURCE_SLOT(38) RVA00237FB0_SOURCE_SLOT(39)
	RVA00237FB0_SOURCE_SLOT(40) RVA00237FB0_SOURCE_SLOT(41) RVA00237FB0_SOURCE_SLOT(42) RVA00237FB0_SOURCE_SLOT(43)
	RVA00237FB0_SOURCE_SLOT(44) RVA00237FB0_SOURCE_SLOT(45) RVA00237FB0_SOURCE_SLOT(46) RVA00237FB0_SOURCE_SLOT(47)
	RVA00237FB0_SOURCE_SLOT(48) RVA00237FB0_SOURCE_SLOT(49) RVA00237FB0_SOURCE_SLOT(50) RVA00237FB0_SOURCE_SLOT(51)
	RVA00237FB0_SOURCE_SLOT(52) RVA00237FB0_SOURCE_SLOT(53) RVA00237FB0_SOURCE_SLOT(54) RVA00237FB0_SOURCE_SLOT(55)
	RVA00237FB0_SOURCE_SLOT(56) RVA00237FB0_SOURCE_SLOT(57) RVA00237FB0_SOURCE_SLOT(58) RVA00237FB0_SOURCE_SLOT(59)
	RVA00237FB0_SOURCE_SLOT(60) RVA00237FB0_SOURCE_SLOT(61) RVA00237FB0_SOURCE_SLOT(62) RVA00237FB0_SOURCE_SLOT(63)
	RVA00237FB0_SOURCE_SLOT(64)
	virtual const BfmeMemberList &getMemberList() const = 0;
};
#undef RVA00237FB0_SOURCE_SLOT

#define RVA00237FB0_OWNER_SLOT(N) virtual void slot##N() = 0;
class Rva00237FB0Owner
{
public:
	RVA00237FB0_OWNER_SLOT(00) RVA00237FB0_OWNER_SLOT(01) RVA00237FB0_OWNER_SLOT(02) RVA00237FB0_OWNER_SLOT(03)
	RVA00237FB0_OWNER_SLOT(04) RVA00237FB0_OWNER_SLOT(05) RVA00237FB0_OWNER_SLOT(06) RVA00237FB0_OWNER_SLOT(07)
	RVA00237FB0_OWNER_SLOT(08) RVA00237FB0_OWNER_SLOT(09) RVA00237FB0_OWNER_SLOT(10) RVA00237FB0_OWNER_SLOT(11)
	RVA00237FB0_OWNER_SLOT(12) RVA00237FB0_OWNER_SLOT(13) RVA00237FB0_OWNER_SLOT(14) RVA00237FB0_OWNER_SLOT(15)
	RVA00237FB0_OWNER_SLOT(16) RVA00237FB0_OWNER_SLOT(17) RVA00237FB0_OWNER_SLOT(18) RVA00237FB0_OWNER_SLOT(19)
	RVA00237FB0_OWNER_SLOT(20) RVA00237FB0_OWNER_SLOT(21) RVA00237FB0_OWNER_SLOT(22) RVA00237FB0_OWNER_SLOT(23)
	RVA00237FB0_OWNER_SLOT(24) RVA00237FB0_OWNER_SLOT(25) RVA00237FB0_OWNER_SLOT(26) RVA00237FB0_OWNER_SLOT(27)
	RVA00237FB0_OWNER_SLOT(28) RVA00237FB0_OWNER_SLOT(29) RVA00237FB0_OWNER_SLOT(30) RVA00237FB0_OWNER_SLOT(31)
	RVA00237FB0_OWNER_SLOT(32) RVA00237FB0_OWNER_SLOT(33) RVA00237FB0_OWNER_SLOT(34) RVA00237FB0_OWNER_SLOT(35)
	RVA00237FB0_OWNER_SLOT(36) RVA00237FB0_OWNER_SLOT(37) RVA00237FB0_OWNER_SLOT(38) RVA00237FB0_OWNER_SLOT(39)
	virtual UnsignedInt applyMember(Object *) = 0;

	void copyMembersToList(BfmeMemberList *output);

private:
	char m_pad[0x2c];
	BfmeMemberIndexNode *m_memberIndex;
};
#undef RVA00237FB0_OWNER_SLOT

void Rva00237FB0Owner::copyMembersToList(BfmeMemberList *output)
{
	const BfmeMemberList &members =
		((Rva00237FB0MemberSource *)((char *)this - 0xc4))->getMemberList();

	for (BfmeMemberList::const_iterator it = members.begin(); it != members.end(); ++it)
	{
		output->push_back(*it);
	}

	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while (entry != m_memberIndex)
	{
		UnsignedInt key = entry->m_key;
		Object *object = TheBfmeGameLogic->findObjectByID(key);
		if (object != 0)
			output->push_back(object);

		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}

	ListIntDtorAdapter temp;
	for (BfmeMemberList::const_iterator it = members.begin(); it != members.end(); ++it)
	{
		const int &memberValue = *(const int *)(const void *)&*it;
		temp.push_back(memberValue);
	}

	for (BfmeMemberIdList::iterator it = temp.begin(); it != temp.end(); ++it)
	{
		applyMember((Object *)(unsigned int)*it);
	}
}

// ?copyMembersToList@Rva00237FB0Owner@@QAEXPAV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@@Z
