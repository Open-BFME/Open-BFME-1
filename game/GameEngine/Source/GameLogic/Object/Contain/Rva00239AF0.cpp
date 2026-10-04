// Retail RVA 0x00239AF0 is installed at slot 108 in the AOD, Horde, and Horse
// contain vtables. That establishes the shared slot, not a class or method name,
// so the C++ identity remains address-derived. The retail lookup is indexOf(key)
// followed by itemAt(index); the owning Object supplies the filter's Player.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Retail body: 330 bytes. Caller identity remains address-derived.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Object;
class Player;

class AsciiString
{
public:
	void *m_data;
};

class NameKeyGenerator
{
public:
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern const char g_bfmeEmptyAscii[1];

class AttributeModifierDefinition
{
public:
	char m_unused[0xc];
	UnsignedInt m_flags;
};

class AttributeModifierDefinitionStore
{
public:
};

class Rva0036B140Item;

class Rva0036B140Collection
{
public:
};

extern AttributeModifierDefinitionStore *TheAttributeModifierDefinitionStore;

class AttributeModifierPoolUpdate
{
public:
	Bool applyAttributeModifier(const AsciiString &name, Int duration);
};

class Rva00239AF0;

class Object
{
public:
private:
	friend class Rva00239AF0;
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate(void) const;
};

class Rva2225E0Filter
{
public:
};

struct BfmeMemberIndexNode;

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
class GameLogic
{
public:
};

extern GameLogic *TheGameLogic;

#define BFME_SLOT(N) virtual Int bfmeSlot##N(void) = 0

class Rva00239AF0MemberListInterface
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03);
	BFME_SLOT(04); BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07);
	BFME_SLOT(08); BFME_SLOT(09); BFME_SLOT(10); BFME_SLOT(11);
	BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14); BFME_SLOT(15);
	BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23);
	BFME_SLOT(24); BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27);
	BFME_SLOT(28); BFME_SLOT(29); BFME_SLOT(30); BFME_SLOT(31);
	BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34); BFME_SLOT(35);
	BFME_SLOT(36); BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39);
	BFME_SLOT(40); BFME_SLOT(41); BFME_SLOT(42); BFME_SLOT(43);
	BFME_SLOT(44); BFME_SLOT(45); BFME_SLOT(46); BFME_SLOT(47);
	BFME_SLOT(48); BFME_SLOT(49); BFME_SLOT(50); BFME_SLOT(51);
	BFME_SLOT(52); BFME_SLOT(53); BFME_SLOT(54); BFME_SLOT(55);
	BFME_SLOT(56); BFME_SLOT(57); BFME_SLOT(58); BFME_SLOT(59);
	BFME_SLOT(60); BFME_SLOT(61); BFME_SLOT(62); BFME_SLOT(63);
	BFME_SLOT(64);
	virtual BfmeMemberList *getMemberList(void) = 0;
};

#undef BFME_SLOT

// These helpers are all matched elsewhere. Select the ILTs used by this body.
extern void j_0003add7();
extern void j_000268e6();
extern void j_0001dbba();
extern void j_00020824();
extern void j_0001da34();
extern void j_00037a56();
extern void j_0001f253();
class Rva00239AF0
{
public:
	void rva00239AF0(const AsciiString &name,
		Rva2225E0Filter *filter, Int duration);
};

// ?rva00239AF0@Rva00239AF0@@QAEXABVAsciiString@@PAVRva2225E0Filter@@H@Z
void Rva00239AF0::rva00239AF0(const AsciiString &name,
	Rva2225E0Filter *filter, Int duration)
{
	void *savedThis = this;
	Rva00239AF0MemberListInterface *base =
		(Rva00239AF0MemberListInterface *)((char *)savedThis - 0xc4);
	BfmeMemberList &members =
		*base->getMemberList();
	BfmeMemberList::iterator node = members.begin();
	{
		Object *owner =
			*(Object **)((char *)savedThis - 0xdc);

	const char *nameData = (const char *)name.m_data;
	if (nameData != 0)
		nameData += 8;
	else
		nameData = g_bfmeEmptyAscii;

	typedef UnsignedInt (NameKeyGenerator::*FnNameKey)(const char *);
	union { void (*fn)(); FnNameKey call; } uNameKey = { j_0003add7 };
	UnsignedInt key = (TheNameKeyGenerator->*uNameKey.call)(nameData);
	typedef Int (AttributeModifierDefinitionStore::*FnIndexOf)(Int) const;
	union { void (*fn)(); FnIndexOf call; } uIndexOf = { j_000268e6 };
	Int definitionIndex =
		(TheAttributeModifierDefinitionStore->*uIndexOf.call)(key);
	typedef Rva0036B140Item *(Rva0036B140Collection::*FnItemAt)(Int) const;
	union { void (*fn)(); FnItemAt call; } uItemAt = { j_0001dbba };
	AttributeModifierDefinition *definition =
		(AttributeModifierDefinition *)
		((Rva0036B140Collection *)TheAttributeModifierDefinitionStore
			->*uItemAt.call)(definitionIndex);
	if (definition != 0 && (definition->m_flags & 0x40) == 0)
	{
		typedef Player *(Object::*FnOwner)(void) const;
		union { void (*fn)(); FnOwner call; } uOwner = { j_00020824 };
		typedef Bool (Rva2225E0Filter::*FnFilter)(Object *, Player *);
		union { void (*fn)(); FnFilter call; } uAccepts = { j_0001da34 };
		typedef Bool (Object::*FnApply)(const AsciiString &, Int);
		union { void (*fn)(); FnApply call; } uApply = { j_00037a56 };
		while (node != members.end())
		{
			Object *object = *node;
			if (filter == 0 ||
				(filter->*uAccepts.call)(object,
					(Player *)(owner->*uOwner.call)()))
				(object->*uApply.call)(name, duration);
			++node;
		}

		typedef Object *(GameLogic::*FnFind)(Int);
		union { void (*fn)(); FnFind call; } uFind = { j_0001f253 };
		BfmeMemberIndexNode *memberIndex =
			*(BfmeMemberIndexNode **)((char *)this + 0x30);
		BfmeMemberIndexNode *entry = memberIndex->m_next;
		if (entry != memberIndex)
		{
			do
			{
				Object *object = (TheGameLogic->*uFind.call)(entry->m_key);
				if (object != 0 &&
					(filter == 0 ||
						(filter->*uAccepts.call)(object,
							(Player *)(owner->*uOwner.call)())))
					(object->*uApply.call)(name, duration);
				entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
					(_STL::_Rb_tree_node_base *)entry);
			}
			while (entry != *(BfmeMemberIndexNode **)((char *)this + 0x30));
		}
	}
	}

	Object *owner = *(Object **)((char *)this - 0xdc);
	AttributeModifierPoolUpdate *pool = owner->findAttributeModifierPoolUpdate();
	if (pool != 0)
		pool->applyAttributeModifier(name, duration);
}
