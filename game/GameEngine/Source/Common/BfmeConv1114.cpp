// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// Open-BFME5 conversions.
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <map>
#include "Thing/GameLogicObjectLookup.h"

class Player;
#define OBJECT_TU_MEMBERS \
	bool hasUpgradeMask(unsigned int bit) const; \
	bool isLocallyControlled() const; \
	void notifyRva001C8830(Player *player);
#include "../GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

typedef _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> > BfmeObjectMap1114;

class BfmeB1114
{
public:
	char m_bfmePad[0xb0];
	BfmeObjectMap1114 m_bfmeObjects;
};

extern GameLogic *TheGameLogic;

struct BfmeL1114
{
	BfmeL1114 *m_bfme00;
	char m_bfmePad[4];
	Object *m_bfme08;
};

struct BfmeNode1114
{
	char m_bfmePad[8];
	BfmeNode1114 *m_bfme08;
	char m_bfmePad1[4];
	int m_bfme10;
};

// 0x012F0898 is retail's `GameLogic *TheGameLogic`; this TU's local view type
// is BfmeB1114, so cast at the use.
static __forceinline BfmeB1114 *bfmeGlobalLogic1114()
{
	return (BfmeB1114 *)TheGameLogic;
}

class BfmeW1114
{
public:
	char bfmeGo1114A(int a);
	void bfmeGo1114C(class Player *player);
	char m_bfmePad[0x30];
	BfmeNode1114 *m_bfme30;
};

char BfmeW1114::bfmeGo1114A(int a)
{
	BfmeL1114 *h1 = *(BfmeL1114 **)((char *)this - 0xac);
	BfmeL1114 *q = h1->m_bfme00;
	BfmeNode1114 *h;
	BfmeNode1114 *p;

	while (q != h1) {
		if (q->m_bfme08->hasUpgradeMask(a))
			return 1;
		q = q->m_bfme00;
		h1 = *(BfmeL1114 **)((char *)this - 0xac);
	}
	h = m_bfme30;
	p = h->m_bfme08;
	while (p != h) {
		Object *k = TheGameLogic->findObjectByID(p->m_bfme10);

		if (k && k->hasUpgradeMask(a))
			return 1;
		p = reinterpret_cast<BfmeNode1114 *>(_STL::_Rb_global<bool>::_M_increment(
			reinterpret_cast<_STL::_Rb_tree_node_base *>(p)));
		h = m_bfme30;
	}
	return 0;
}

class Drawable
{
private:
	friend class BfmeW1114;
	void applyPendingModelConditionFlags(bool pending);
};

void BfmeW1114::bfmeGo1114C(Player *player)
{
	BfmeL1114 *list = *(BfmeL1114 **)((char *)this - 0xac);
	BfmeL1114 *node = list->m_bfme00;

	while (node != list)
	{
		Object *object = (Object *)node->m_bfme08;
		if (object)
		{
			object->notifyRva001C8830(player);
			Drawable *drawable = object->getDrawable();
			if (drawable && object->isLocallyControlled())
				drawable->applyPendingModelConditionFlags(false);
		}

		node = node->m_bfme00;
		list = *(BfmeL1114 **)((char *)this - 0xac);
	}

	BfmeNode1114 *root = m_bfme30;
	BfmeNode1114 *tree = root->m_bfme08;
	while (tree != root)
	{
		BfmeNode1114 *entry = tree;
		unsigned int id = entry->m_bfme10;
		Object *object = 0;
		if (id)
		{
			BfmeObjectMap1114::iterator iterator = bfmeGlobalLogic1114()->m_bfmeObjects.find(id);
			if (iterator != bfmeGlobalLogic1114()->m_bfmeObjects.end())
				object = (*iterator).second;
		}

		if (object)
		{
			object->notifyRva001C8830(player);
			Drawable *drawable = object->getDrawable();
			if (drawable && object->isLocallyControlled())
				drawable->applyPendingModelConditionFlags(false);
		}

		tree = reinterpret_cast<BfmeNode1114 *>(_STL::_Rb_global<bool>::_M_increment(
			reinterpret_cast<_STL::_Rb_tree_node_base *>(tree)));
		root = m_bfme30;
	}
}
