// The receiver of bfmeNotifyCCB is an Object: the cleared word is
// Object::m_modelConditionFlags[7] at +0x12C, and the call is the ILT
// 0x0002191D thunk to Object::notifyModelConditionChanged.

#define OBJECT_TU_MEMBERS void notifyModelConditionChanged();
#include "../GameLogic/Object/object.h"

struct BfmeOwnerCCB
{
	unsigned char m_bfmeHead[0x10];
	Object *m_bfmeMid;
};

class BfmeThingCCB
{
public:
	void bfmeGoCCB(void *spare);
	unsigned char m_bfmeHead[0x1c];
	BfmeOwnerCCB *m_bfmeOwner;
};

void BfmeThingCCB::bfmeGoCCB(void *spare)
{
	Object *sub = m_bfmeOwner->m_bfmeMid;
	if (sub->m_modelConditionFlags[7] & 0x400000u)
	{
		sub->m_modelConditionFlags[7] &= ~0x400000u;
		sub->notifyModelConditionChanged();
	}
}