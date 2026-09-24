// Retail 0x00236CA0 is slot 43 of HordeContain vtable 0x010AED58, installed
// by the matched HordeContain constructor and shared by AODHordeContain and
// HorseHordeContain. ILT 0x0003DEC4 jumps directly to this body. The member
// name stays address-derived.
// The receiver is the HordeContain subobject at owner+0xDC, with the member
// list at receiver-0xAC and the member-index header at receiver+0x30. Those
// offsets match the landed HordeContain list/index methods at 0x0023A270 and
// 0x00237E50, and the owner/list offsets match 0x00243EA0.
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>

typedef unsigned int UnsignedInt;
typedef bool Bool;

class UpgradeTemplate;

struct RGBColor
{
	float red;
	float green;
	float blue;
};

class Drawable
{
public:
	void colorFlash(const RGBColor *, UnsignedInt, UnsignedInt, UnsignedInt);
};

class Object
{
public:
#define BFME_OBJECT_SLOT(N) virtual void slot##N() = 0
	BFME_OBJECT_SLOT(00); BFME_OBJECT_SLOT(01); BFME_OBJECT_SLOT(02);
	BFME_OBJECT_SLOT(03); BFME_OBJECT_SLOT(04); BFME_OBJECT_SLOT(05);
	BFME_OBJECT_SLOT(06); BFME_OBJECT_SLOT(07); BFME_OBJECT_SLOT(08);
	BFME_OBJECT_SLOT(09);
#undef BFME_OBJECT_SLOT
	virtual Drawable *getDrawable() const = 0; // vtable +0x28
	Bool affectedByUpgrade(const UpgradeTemplate *) const;
	void giveUpgrade(const UpgradeTemplate *);
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

template <int N>
class Rva00236CA0Slots : public Rva00236CA0Slots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template <>
class Rva00236CA0Slots<0>
{
};

class Rva00236CA0HordeContain : public Rva00236CA0Slots<43>
{
public:
	virtual void rva00236ca0(UpgradeTemplate *upgrade);

private:
	char m_pad004[0x2c];
	BfmeMemberIndexNode *m_memberIndex;
};

void Rva00236CA0HordeContain::rva00236ca0(UpgradeTemplate *upgrade)
{
	BfmeMemberList &members = *(BfmeMemberList *)((char *)this - 0xac);
	BfmeMemberList::iterator it = members.begin();
	Object *owner = *(Object **)((char *)this - 0xdc);
	RGBColor color = { 0.99f, 0.99f, 0.99f };
	owner->giveUpgrade(upgrade);
	while (it != members.end())
	{
		Object *member = *it;
		if (member->affectedByUpgrade(upgrade))
		{
			member->giveUpgrade(upgrade);
			Drawable *drawable = member->getDrawable();
			if (drawable)
				drawable->colorFlash(&color, 4, 4, 15);
		}
		++it;
	}

	BfmeMemberIndexNode *entry = m_memberIndex->m_next;
	while (entry != m_memberIndex)
	{
		UnsignedInt id = entry->m_key;
		Object *member = (Object *)id;
		if (id != 0)
			member = TheBfmeGameLogic->findObjectByID(id);
		member->giveUpgrade(upgrade);
		Drawable *drawable = member->getDrawable();
		if (drawable)
			drawable->colorFlash(&color, 4, 4, 15);
		entry = (BfmeMemberIndexNode *)_STL::_Rb_global<bool>::_M_increment(
			(_STL::_Rb_tree_node_base *)entry);
	}
}
