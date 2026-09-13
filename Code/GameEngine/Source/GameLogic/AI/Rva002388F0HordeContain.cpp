// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep
// stlport
// BFME HordeContain::getMembers, retail 0x002388F0, 286 bytes.
// The dump thunk at ILT 0x00011D24 is HordeContain's secondary-interface slot 60.

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

extern BfmeGameLogic *TheGameLogic;

class Rva002388F0OpenContainInterface
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
	virtual const BfmeMemberList &getMemberList() const = 0;
#undef OPEN_SLOT
};

class Rva002388F0HordeContain
{
public:
#define HORDE_SLOT(N) virtual void slot##N() = 0
	HORDE_SLOT(00); HORDE_SLOT(01); HORDE_SLOT(02); HORDE_SLOT(03);
	HORDE_SLOT(04); HORDE_SLOT(05); HORDE_SLOT(06); HORDE_SLOT(07);
	HORDE_SLOT(08); HORDE_SLOT(09); HORDE_SLOT(10); HORDE_SLOT(11);
	HORDE_SLOT(12); HORDE_SLOT(13); HORDE_SLOT(14); HORDE_SLOT(15);
	HORDE_SLOT(16); HORDE_SLOT(17); HORDE_SLOT(18); HORDE_SLOT(19);
	HORDE_SLOT(20); HORDE_SLOT(21); HORDE_SLOT(22); HORDE_SLOT(23);
	HORDE_SLOT(24); HORDE_SLOT(25); HORDE_SLOT(26); HORDE_SLOT(27);
	HORDE_SLOT(28); HORDE_SLOT(29); HORDE_SLOT(30); HORDE_SLOT(31);
	HORDE_SLOT(32); HORDE_SLOT(33); HORDE_SLOT(34); HORDE_SLOT(35);
	HORDE_SLOT(36); HORDE_SLOT(37); HORDE_SLOT(38); HORDE_SLOT(39);
	HORDE_SLOT(40); HORDE_SLOT(41); HORDE_SLOT(42); HORDE_SLOT(43);
	HORDE_SLOT(44); HORDE_SLOT(45); HORDE_SLOT(46); HORDE_SLOT(47);
	HORDE_SLOT(48); HORDE_SLOT(49); HORDE_SLOT(50); HORDE_SLOT(51);
	HORDE_SLOT(52); HORDE_SLOT(53); HORDE_SLOT(54); HORDE_SLOT(55);
	HORDE_SLOT(56); HORDE_SLOT(57); HORDE_SLOT(58); HORDE_SLOT(59);
	virtual void getMembers(BfmeMemberList *members);
#undef HORDE_SLOT

private:
	char m_head[0x2c];
	BfmeMemberIndexNode *m_memberIndex;
};

// ?getMembers@HordeContain@@UAEXPAV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@@Z
void Rva002388F0HordeContain::getMembers(BfmeMemberList *members)
{
	members->clear();

	const BfmeMemberList &contained =
		((Rva002388F0OpenContainInterface *)((char *)this - 0xc4))
			->getMemberList();
	for (BfmeMemberList::const_iterator it = contained.begin();
		it != contained.end(); ++it)
	{
		members->push_back(*it);
	}

	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while (entry != m_memberIndex)
	{
		UnsignedInt key = entry->m_key;
		if (key != 0)
		{
			Object *object = TheGameLogic->findObjectByID(key);
			if (object != 0)
				members->push_back(object);
		}
		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}
}
