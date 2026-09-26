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
	UnsignedInt nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class AttributeModifierDefinition
{
public:
	char m_unused[0xc];
	UnsignedInt m_flags;
};

class AttributeModifierDefinitionStore
{
public:
	Int indexOf(Int key) const;
};

class Rva0036B140Item;

class Rva0036B140Collection
{
public:
	Rva0036B140Item *itemAt(Int index) const;
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
	Player *getControllingPlayer(void) const;
	Bool applyAttributeModifier(const AsciiString &name, Int duration);

private:
	friend class Rva00239AF0;
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate(void) const;
};

class Rva2225E0Filter
{
public:
	Bool accepts(Object *object, Player *player);
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
	Object *findObjectByID(Int key);
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
#pragma comment(linker, "/alternatename:?nameToKey@NameKeyGenerator@@QAEIPBD@Z=?j_0003add7@@YAXXZ")
#pragma comment(linker, "/alternatename:?indexOf@AttributeModifierDefinitionStore@@QBEHH@Z=?j_000268e6@@YAXXZ")
#pragma comment(linker, "/alternatename:?itemAt@Rva0036B140Collection@@QBEPAVRva0036B140Item@@H@Z=?j_0001dbba@@YAXXZ")
#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?accepts@Rva2225E0Filter@@QAE_NPAVObject@@PAVPlayer@@@Z=?j_0001da34@@YAXXZ")
#pragma comment(linker, "/alternatename:?applyAttributeModifier@Object@@QAE_NABVAsciiString@@H@Z=?j_00037a56@@YAXXZ")
#pragma comment(linker, "/alternatename:?findObjectByID@GameLogic@@QAEPAVObject@@H@Z=?j_0001f253@@YAXXZ")
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
		nameData = (const char *)0x0107388b;

	UnsignedInt key = TheNameKeyGenerator->nameToKey(nameData);
	Int definitionIndex = TheAttributeModifierDefinitionStore->indexOf(key);
	AttributeModifierDefinition *definition =
		(AttributeModifierDefinition *)
		((Rva0036B140Collection *)TheAttributeModifierDefinitionStore)->itemAt(
			definitionIndex);
	if (definition != 0 && (definition->m_flags & 0x40) == 0)
	{
		while (node != members.end())
		{
			Object *object = *node;
			if (filter == 0 ||
				filter->accepts(object, (Player *)
						owner->getControllingPlayer()))
				object->applyAttributeModifier(name, duration);
			++node;
		}

		BfmeMemberIndexNode *memberIndex =
			*(BfmeMemberIndexNode **)((char *)this + 0x30);
		BfmeMemberIndexNode *entry = memberIndex->m_next;
		if (entry != memberIndex)
		{
			do
			{
				Object *object = TheGameLogic->findObjectByID(entry->m_key);
				if (object != 0 &&
					(filter == 0 ||
						filter->accepts(object, (Player *)
								owner->getControllingPlayer())))
					object->applyAttributeModifier(name, duration);
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
