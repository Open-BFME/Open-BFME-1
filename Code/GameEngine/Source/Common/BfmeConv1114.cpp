// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// Open-BFME5 conversions.
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

class Object;

typedef _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> > BfmeObjectMap1114;

class GameLogic
{
public:
	char m_bfmePad[0xb0];
	BfmeObjectMap1114 m_bfmeObjects;
};

extern GameLogic *TheGameLogic;

class BfmeK1114
{
public:
	char bfmeChk1114(int a);
};

struct BfmeL1114
{
	BfmeL1114 *m_bfme00;
	char m_bfmePad[4];
	BfmeK1114 *m_bfme08;
};

struct BfmeNode1114
{
	char m_bfmePad[8];
	BfmeNode1114 *m_bfme08;
	char m_bfmePad1[4];
	int m_bfme10;
};

class BfmeB1114
{
public:
	BfmeK1114 *bfmeFind1114(int a);
};

extern BfmeB1114 *g_bfmeB1114;

BfmeNode1114 *__cdecl bfmeNext1114(BfmeNode1114 *p);

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
		if (q->m_bfme08->bfmeChk1114(a))
			return 1;
		q = q->m_bfme00;
		h1 = *(BfmeL1114 **)((char *)this - 0xac);
	}
	h = m_bfme30;
	p = h->m_bfme08;
	while (p != h) {
		BfmeK1114 *k = g_bfmeB1114->bfmeFind1114(p->m_bfme10);

		if (k && k->bfmeChk1114(a))
			return 1;
		p = bfmeNext1114(p);
		h = m_bfme30;
	}
	return 0;
}

class Drawable;

class BfmeTargetJB
{
public:
	bool bfmeTailJB(void);
};

class Object : public BfmeTargetJB
{
public:
	void notifyRva001C8830(Player *player);
};

class BfmeObjectDrawableDispatch
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual Drawable *getDrawable(void);
};

class DrawableApplyPendingThunk
{
public:
	void apply(bool pending);
};

#pragma comment(linker, "/alternatename:?apply@DrawableApplyPendingThunk@@QAEX_N@Z=?j_0002d439@@YAXXZ")

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
			Drawable *drawable = ((BfmeObjectDrawableDispatch *)object)->getDrawable();
			if (drawable && object->bfmeTailJB())
				((DrawableApplyPendingThunk *)drawable)->apply(false);
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
			BfmeObjectMap1114::iterator iterator = TheGameLogic->m_bfmeObjects.find(id);
			if (iterator != TheGameLogic->m_bfmeObjects.end())
				object = (*iterator).second;
		}

		if (object)
		{
			object->notifyRva001C8830(player);
			Drawable *drawable = ((BfmeObjectDrawableDispatch *)object)->getDrawable();
			if (drawable && object->bfmeTailJB())
				((DrawableApplyPendingThunk *)drawable)->apply(false);
		}

		tree = bfmeNext1114(tree);
		root = m_bfme30;
	}
}
