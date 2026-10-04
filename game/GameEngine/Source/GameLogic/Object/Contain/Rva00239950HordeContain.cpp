// Retail 0x00239950, address-derived Horde-family propagation with four opaque arguments.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

class Player;
class Drawable
{
public:
	void setTerrainDecalFadeTarget(Real target, Real rate);
};

class BfmeThingMB
{
public:
	void bfmeSetMB(void *what);
};

class Object
{
public:
#define OBJECT_SLOT(N) virtual void *objectSlot##N();
	OBJECT_SLOT(00) OBJECT_SLOT(01) OBJECT_SLOT(02) OBJECT_SLOT(03)
	OBJECT_SLOT(04) OBJECT_SLOT(05) OBJECT_SLOT(06) OBJECT_SLOT(07)
	OBJECT_SLOT(08) OBJECT_SLOT(09)
	virtual Drawable *getDrawable() const;
#undef OBJECT_SLOT
};

class Rva2225E0Filter
{
public:
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
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
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

class GameLogic;

// The retail global at 0x012F0898 is EA's GameLogic *TheGameLogic; this TU
// reads it through a local view of the object-id hash only.
extern GameLogic *TheGameLogic;

template <int N>
class Rva00239950MemberViewSlots : public Rva00239950MemberViewSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template <>
class Rva00239950MemberViewSlots<0>
{
};

class Rva00239950MemberView : public Rva00239950MemberViewSlots<65>
{
public:
	virtual BfmeMemberList &getMemberList() const = 0;
};

class Rva00239950HordeContain
{
public:
	void rva00239950(void *what, Real target, Real rate,
		Rva2225E0Filter *filter);

private:
	char m_head[0x30];
	BfmeMemberIndexNode *m_memberIndex;
};

// Retail calls both stand-in members through ILT thunks at 0x00020824 and
// 0x0001da34; route the calls straight at the thunk entry points.
extern void j_00020824();
extern void j_0001da34();

__forceinline Player *rva00239950GetControllingPlayer(Object *owner)
{
	typedef Player *(Object::*GetControllingPlayer)() const;
	union { void (*fn)(); GetControllingPlayer call; } u = { j_00020824 };
	return (owner->*u.call)();
}

__forceinline Bool rva00239950Accepts(Rva2225E0Filter *filter, Object *object,
	Player *player)
{
	typedef Bool (Rva2225E0Filter::*Accepts)(Object *, Player *);
	union { void (*fn)(); Accepts call; } u = { j_0001da34 };
	return (filter->*u.call)(object, player);
}

// ?rva00239950@Rva00239950HordeContain@@QAEXPAXMMPAVRva2225E0Filter@@@Z
void Rva00239950HordeContain::rva00239950(void *what, Real target,
	Real rate, Rva2225E0Filter *filter)
{
	BfmeMemberList &members =
		((Rva00239950MemberView *)((char *)this - 0xc4))->getMemberList();
	BfmeMemberList::iterator node = members.begin();
	Object *owner = *(Object **)((char *)this - 0xdc);

	while (node != members.end())
	{
		Object *object = *node;
		if (filter == 0 || rva00239950Accepts(filter, object,
			rva00239950GetControllingPlayer(owner)))
		{
			Drawable *drawable = object->getDrawable();
			if (drawable != 0)
			{
				((BfmeThingMB *)drawable)->bfmeSetMB(what);
				drawable->setTerrainDecalFadeTarget(target, rate);
			}
		}
		++node;
	}

	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while (entry != m_memberIndex)
	{
		UnsignedInt key = entry->m_key;
		if (key != 0)
		{
			Object *object =
				((BfmeGameLogic *)TheGameLogic)->findObjectByID(key);
			if (object != 0)
			{
				if (filter == 0 || rva00239950Accepts(filter, object,
					rva00239950GetControllingPlayer(owner)))
				{
					Drawable *drawable = object->getDrawable();
					if (drawable != 0)
					{
						((BfmeThingMB *)drawable)->bfmeSetMB(what);
						drawable->setTerrainDecalFadeTarget(target, rate);
					}
				}
			}
		}
		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}
}
