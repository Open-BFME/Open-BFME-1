#define OBJECT_TU_MEMBERS void bfmeResetAllUpgrades();
#include "../GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

// Retail ILTs 0x00022C73, 0x0002EAD2 and 0x00041AD8 route to
// BfmeC1058::bfmeGo1058C, Object::bfmeResetAllUpgrades and
// BfmeThingAFB::bfmeGoAFB, respectively.
class BfmeC1058
{
public:
	void bfmeGo1058C();
};

class BfmeThingAFB
{
public:
	void bfmeGoAFB();
};

class BfmeOwnerBUD
{
public:
	unsigned char m_bfmeHead[0x210];
	BfmeC1058 *m_bfmeSub;
};

class BfmeThingBUD
{
public:
	void bfmeGoBUD();
	unsigned char m_bfmeHead[8];
	BfmeOwnerBUD *m_bfmeOwner;
};

void BfmeThingBUD::bfmeGoBUD()
{
	BfmeOwnerBUD *owner = m_bfmeOwner;
	BfmeC1058 *sub = owner->m_bfmeSub;
	if (sub != 0)
		sub->bfmeGo1058C();
	reinterpret_cast<Object *>(owner)->bfmeResetAllUpgrades();
	reinterpret_cast<BfmeThingAFB *>(owner)->bfmeGoAFB();
}
