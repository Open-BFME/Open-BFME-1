// stlport
// Open-BFME5 conversions.

#include <map>

// GameLogic::findObjectByID(ObjectID) is the retail lookup these callers reach;
// GameLogicObjectLookup.h carries the declaration and its proof. Only the
// declaration is used: the body stays in GameLogicFindObjectByID.cpp.
#include "Thing/GameLogicObjectLookup.h"

class UpgradeTemplate;
#define OBJECT_TU_MEMBERS bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
#include "../GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

struct BfmeL1113
{
	BfmeL1113 *m_bfme00;
	char m_bfmePad[4];
	Object *m_bfme08;
};

struct BfmeNode1113
{
	char m_bfmePad[8];
	BfmeNode1113 *m_bfme08;
	char m_bfmePad1[4];
	int m_bfme10;
};

// Retail's global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined once
// in game/GameEngine/Source/GameLogic/System/GameLogic.cpp; Thing/GameLogicObjectLookup.h
// above already declares the real GameLogic view this TU calls through.
extern GameLogic *TheGameLogic;

class BfmeW1113
{
public:
	char bfmeGo1113A(int a);
	char m_bfmePad[0x30];
	BfmeNode1113 *m_bfme30;
};

char BfmeW1113::bfmeGo1113A(int a)
{
	BfmeL1113 *h1 = *(BfmeL1113 **)((char *)this - 0xac);
	BfmeL1113 *q = h1->m_bfme00;
	BfmeNode1113 *h;
	BfmeNode1113 *p;

	while (q != h1) {
		if (q->m_bfme08->affectedByUpgrade(reinterpret_cast<const UpgradeTemplate *>(a)))
			return 1;
		q = q->m_bfme00;
		h1 = *(BfmeL1113 **)((char *)this - 0xac);
	}
	h = m_bfme30;
	p = h->m_bfme08;
	while (p != h) {
		Object *k = TheGameLogic->findObjectByID(p->m_bfme10);

		if (k->affectedByUpgrade(reinterpret_cast<const UpgradeTemplate *>(a)))
			return 1;
		p = reinterpret_cast<BfmeNode1113 *>(_STL::_Rb_global<bool>::_M_increment(
			reinterpret_cast<_STL::_Rb_tree_node_base *>(p)));
		h = m_bfme30;
	}
	return 0;
}
