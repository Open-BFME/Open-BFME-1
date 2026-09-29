// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep
// stlport
// Retail 0x00236E10 (253 bytes, ILT 0x0002F464): a HordeContain primary-
// vtable slot (rdata 0x00CAE614).  It initialises a function-static
// NAMEKEY("TemporarilyDefectUpdate") it never reads -- the EH frame is MSVC
// guarding that static's initialiser -- and passes its argument to virtual
// slot 23 of every contained member and every live indexed member.  The
// primary part keeps the contained list at +0x18 and the member index at
// +0xF4 (the secondary interface sees them at -0xAC and +0x30).
// IDENTITY IS NOT RECOVERED: the slot name keeps the address.

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


enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Rva00236E10Member
{
public:
#define MEMBER_SLOT(N) virtual void slot##N() = 0
	MEMBER_SLOT(00); MEMBER_SLOT(01); MEMBER_SLOT(02); MEMBER_SLOT(03);
	MEMBER_SLOT(04); MEMBER_SLOT(05); MEMBER_SLOT(06); MEMBER_SLOT(07);
	MEMBER_SLOT(08); MEMBER_SLOT(09); MEMBER_SLOT(10); MEMBER_SLOT(11);
	MEMBER_SLOT(12); MEMBER_SLOT(13); MEMBER_SLOT(14); MEMBER_SLOT(15);
	MEMBER_SLOT(16); MEMBER_SLOT(17); MEMBER_SLOT(18); MEMBER_SLOT(19);
	MEMBER_SLOT(20); MEMBER_SLOT(21); MEMBER_SLOT(22);
#undef MEMBER_SLOT
	virtual void rva00236E10Apply(void *arg) = 0;
};

class Rva00236E10HordeContain
{
public:
	void applyToMembers(void *arg);

private:
	unsigned char m_head[0x18];
	BfmeMemberList m_containList;
	unsigned char m_mid[0xf4 - 0x18 - sizeof(BfmeMemberList)];
	BfmeMemberIndexNode *m_memberIndex;
};

void Rva00236E10HordeContain::applyToMembers(void *arg)
{
	BfmeMemberList::iterator it = m_containList.begin();
	static NameKeyType key_TemporarilyDefectUpdate =
		TheNameKeyGenerator->nameToKey("TemporarilyDefectUpdate");
	for (; it != m_containList.end(); ++it)
		((Rva00236E10Member *)*it)->rva00236E10Apply(arg);

	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while (entry != m_memberIndex)
	{
		UnsignedInt id = entry->m_key;
		if (id != 0)
		{
			Rva00236E10Member *member =
				(Rva00236E10Member *)TheGameLogic->findObjectByID(id);
			if (member != 0)
				member->rva00236E10Apply(arg);
		}
		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}
}
